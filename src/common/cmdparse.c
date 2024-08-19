/**
 * @file parse.c
 *
 * @brief Internal command line parser. See the readme for more information
 * about the format of command line options parsed by this module.
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 2024-06-17
 * @copyright Copyright (c) 2024
 *
 */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "cmderrors.h"
#include "cmdline.h"
#include "cmdparse.h"
#include "memory.h"
#include "myassert.h"

#define EOI 1
#define EOS 0

static _cmdline_t_* cmdline;
// defined in cmdline.c, but not part of the public interface.
_cmdline_t_* _get_cmdline_(void);
_cmd_opt_t_* search_short(int c);
_cmd_opt_t_* search_long(const char* opt);
_cmd_opt_t_* search_name(const char* name);
_cmd_opt_t_* search_no_name(void);

typedef struct {
    int argc;
    char** argv;
    int aidx;
    int sidx;
} _parser_t_;

static _parser_t_* parser;

// return the current character
static int get_char(void) {

    if(parser->aidx >= parser->argc)
        return EOI; // no more characters are available
    else
        return parser->argv[parser->aidx][parser->sidx];
}

// return the new character.
static int consume_char(void) {

    if(parser->aidx == parser->argc)
        return EOI; // no more characters are available
    else if(parser->argv[parser->aidx][parser->sidx] == 0) {
        parser->aidx++;
        parser->sidx = 0;
        return get_char(); // returns EOS
    }
    else {
        parser->sidx++;
        return parser->argv[parser->aidx][parser->sidx];
    }
}

// return the full text of the option currently being parsed.
static const char* crnt_opt(void) {

    if(parser->aidx >= parser->argc)
        return parser->argv[parser->argc - 1];
    else
        return parser->argv[parser->aidx];
}

// returns true if the character is a single-character token.
// Includes the EOI and EOS characters.
static inline bool is_a_token(int ch) {

    switch(ch) {
        case '=':
        case ':':
        case ',':
        case EOI:
        case EOS:
            return true;
        default:
            return false;
    }
}

static void init_parser(int argc, char** argv) {

    parser       = _ALLOC_DS(_parser_t_);
    parser->argc = argc;
    parser->argv = argv;
    parser->aidx = 1;
    parser->sidx = 0;

    // get the data structure pointer from cmdline.c
    cmdline = _get_cmdline_();
}

// return the number of characters that were read.
int read_word(String* str) {

    clear_string(str);
    int count = 0;

    int ch = get_char();
    while(isprint(ch) && !is_a_token(ch)) {
        append_string_char(str, ch);
        ch = consume_char();
        count++;
    }

    return count;
}

// when this is entered, the short options are an array of characters.
static int parse_short(void) {

    String* str = create_string(NULL);

    bool finished = false;
    int state     = 0;
    int ch;
    _cmd_opt_t_* opt = NULL;

    while(!finished) {
        ch = get_char();
        switch(state) {
            case 0:
                // initial state;
                if(isprint(ch) && !is_a_token(ch)) {
                    opt = search_short(ch);
                    if(opt != NULL) {
                        if(opt->callback != NULL)
                            (*opt->callback)();

                        if(opt->flag & CMD_RARG)
                            state = 2;
                        else if(opt->flag & CMD_OARG)
                            state = 3;
                        else {
                            opt->flag |= CMD_SEEN;
                            state = 1;
                        }
                        consume_char();
                    }
                    else
                        error("unknown short command option: '%s'", crnt_opt());
                }
                else
                    error("expected a short option in '%s', but got '%c'", crnt_opt(), ch);
                break;

            case 1:
                // expect a command option or EOS, else error
                if(isprint(ch) && !is_a_token(ch)) {
                    opt = search_short(ch);
                    if(opt != NULL) {
                        if(opt->callback != NULL)
                            (*opt->callback)();

                        if(opt->flag & CMD_RARG)
                            state = 2;
                        else if(opt->flag & CMD_OARG)
                            state = 3;
                        else
                            opt->flag |= CMD_SEEN;
                        consume_char();
                    }
                    else if(ch == EOS)
                        state = 100;
                    else
                        error("unknown short command option: '%s'", crnt_opt());
                }
                else
                    error("expected a short command option in '%s', but got "
                          "'%c'",
                          crnt_opt(), ch);
                break;

            case 2:
                // expecting a '=' or an error for required arg
                if(ch == '=') {
                    consume_char();
                    state = 4;
                }
                else
                    error("command option '%s' requires an argument.", crnt_opt());
                break;

            case 3:
                // expecting a '=' or another cmd option, else an error.
                if(ch == '=') {
                    consume_char();
                    state = 4;
                }
                else
                    state = 1;
                break;

            case 4:
                // a command arg is required, else an error
                if(read_word(str) > 0) {
                    if(opt->flag & CMD_LIST) {
                        append_str_lst(opt->values, copy_string(str));
                        state = 5;
                    }
                    else {
                        if(opt->flag & CMD_SEEN)
                            warning("duplicate option value being replaced: %s", crnt_opt());
                        clear_str_lst(opt->values);
                        append_str_lst(opt->values, copy_string(str));
                        state = 6;
                    }
                }
                else
                    error("expected an option argument in '%s', but got a %c",
                          crnt_opt(), ch);
                break;

            case 5:
                // a ',' or EOS is required, else an error
                if(ch == ',') {
                    consume_char();
                    state = 4;
                }
                else if(ch == EOS) {
                    consume_char();
                    opt->flag |= CMD_SEEN;
                    state = 100;
                }
                else
                    error("unexpected character in command argument '%s': '%c'",
                          crnt_opt(), ch);
                break;

            case 6:
                // verify EOS
                if(ch != EOS)
                    error("unexpected character following command option '%s': "
                          "%c",
                          crnt_opt(), ch);
                else {
                    opt->flag |= CMD_SEEN;
                    state = 100;
                }
                break;

            case 100:
                // finished with this element
                destroy_string(str);
                finished = true;
                break;

            default:
                fprintf(stderr, "CMD Internal error: unknown state in %s: %d\n",
                        __func__, state);
                abort();
        }
    }

    return 0;
}

static int parse_long(void) {

    // read long name
    String* str = create_string(NULL);
    read_word(str);

    _cmd_opt_t_* opt = search_long(raw_string(str));
    if(opt != NULL) {
        if(opt->callback != NULL)
            (*opt->callback)();

        bool finished = false;
        int state     = 0;
        int ch;

        while(!finished) {
            ch = get_char();
            switch(state) {
                case 0:
                    // see if there is supposed to be an arg
                    if(opt->flag & CMD_RARG)
                        state = 1;
                    else if(opt->flag & CMD_OARG)
                        state = 2;
                    else
                        // no args expected, check for one, just in case
                        state = 3;
                    break;

                case 1:
                    // required arg
                    if(ch == '=') {
                        consume_char();
                        state = 4;
                    }
                    else
                        error("expected an argument for command option: %s",
                              raw_string(str));
                    break;

                case 2:
                    // optional arg
                    if(ch == '=') {
                        consume_char();
                        state = 4;
                    }
                    else if(ch == EOS) {
                        consume_char();
                        state = 100;
                    }
                    else
                        error("unexpected character following command option "
                              "'%s': %c",
                              crnt_opt(), ch);
                    break;

                case 3:
                    // make sure no arg is present
                    if(ch != EOS)
                        error("unexpected character following command option "
                              "'%s': %c",
                              crnt_opt(), ch);
                    else {
                        state = 100;
                    }
                    break;

                case 4:
                    // a word is required or error
                    if(read_word(str) > 0) {
                        if(opt->flag & CMD_LIST) {
                            append_str_lst(opt->values, copy_string(str));
                            state = 5;
                        }
                        else {
                            if(opt->flag & CMD_SEEN)
                                warning("duplicate option value being "
                                        "replaced: %s",
                                        crnt_opt());
                            clear_str_lst(opt->values);
                            append_str_lst(opt->values, copy_string(str));
                            state = 3;
                        }
                    }
                    else
                        error("expected an option argument, but got a %c in "
                              "'%s'",
                              ch, crnt_opt());
                    break;

                case 5:
                    // a comma or EOS is expected, or error
                    if(ch == ',') {
                        consume_char();
                        state = 4;
                    }
                    else if(ch == EOS) {
                        consume_char();
                        state = 100;
                    }
                    else
                        error("unexpected character in command argument '%s': "
                              "%c",
                              crnt_opt(), ch);
                    break;

                case 100:
                    // all done
                    opt->flag |= CMD_SEEN;
                    destroy_string(str);
                    finished = true;
                    break;

                default:
                    fprintf(stderr, "CMD Internal error: unknown state in %s: %d\n",
                            __func__, state);
                    abort();
            }
        }
    }
    else
        error("unknown command line option: %s", raw_string(str));

    return 0;
}

static int parse_word(void) {

    String* str = create_string(NULL);
    read_word(str);

    _cmd_opt_t_* opt = search_no_name();
    if(opt != NULL) {
        if(opt->callback != NULL)
            (*opt->callback)();

        opt->flag |= CMD_SEEN;
        append_str_lst(opt->values, str);
    }
    else
        error("misplaced command line argument: %s", raw_string(str));

    return 0;
}

void internal_parse_cmdline(int argc, char** argv) {

    init_parser(argc, argv);

    int state     = 0;
    bool finished = false;
    int ch;

    while(!finished) {
        ch = get_char();
        switch(state) {
            case 0:
                // first char after init
                if(ch == '-') {
                    consume_char();
                    state = 1;
                }
                else if(!is_a_token(ch))
                    state = parse_word();
                else if(ch == EOS)
                    consume_char();
                else if(ch == EOI)
                    state = 100;
                else
                    error("expected a command option in '%s', but got '%c'",
                          crnt_opt(), ch);
                // does not return
                break;

            case 1:
                // double or single dash
                if(ch == '-') {
                    consume_char();
                    state = parse_long();
                }
                else
                    state = parse_short();
                break;

            case 100:
                // finished reading options
                finished = true;
                break;

            default:
                fprintf(stderr, "CMD Internal error: unknown state in %s: %d\n",
                        __func__, state);
                abort();
        }
    }
}
