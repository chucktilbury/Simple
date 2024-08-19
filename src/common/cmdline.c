/**
 * @file cmdline.c
 *
 * @brief Use the GNU command line parser getopt_long() to parse a command
 * line with a fre enhancements.
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 2024-06-10
 * @copyright Copyright (c) 2024
 *
 */
#include <ctype.h>
#include <getopt.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmdline.h"
#include "memory.h"
#include "myassert.h"
#include "ptr_lst.h"

static _cmdline_t_* cmdline = NULL;

// private interface for parser.
_cmdline_t_* _get_cmdline_(void) {
    return cmdline;
}

/**
 * @brief Search for a short option in the command list.
 *
 * @param c
 * @return _cmd_opt_t_*
 */
_cmd_opt_t_* search_short(int c) {

    int post = 0;
    _cmd_opt_t_* ptr;
    while(NULL != (ptr = iterate_ptr_lst(cmdline->cmd_opts, &post))) {
        if(ptr->short_opt == c)
            return ptr;
    }

    return NULL;
}

/**
 * @brief Search for a long option in the command list.
 *
 * @param opt
 * @return _cmd_opt_t_*
 */
_cmd_opt_t_* search_long(const char* opt) {

    int post = 0;
    _cmd_opt_t_* ptr;
    while(NULL != (ptr = iterate_ptr_lst(cmdline->cmd_opts, &post))) {
        if(!strcmp(ptr->long_opt, opt))
            return ptr;
    }

    return NULL;
}

/**
 * @brief Search for a name in the command list.
 *
 * @param name
 * @return _cmd_opt_t_*
 */
_cmd_opt_t_* search_name(const char* name) {

    int post = 0;
    _cmd_opt_t_* ptr;
    while(NULL != (ptr = iterate_ptr_lst(cmdline->cmd_opts, &post))) {
        if(!strcmp(ptr->name, name))
            return ptr;
    }

    return NULL;
}

/**
 * @brief Search for an option that has no name in the command list.
 *
 * @return _cmd_opt_t_*
 */
_cmd_opt_t_* search_no_name(void) {

    int post = 0;
    _cmd_opt_t_* ptr;
    while(NULL != (ptr = iterate_ptr_lst(cmdline->cmd_opts, &post))) {
        if(ptr->short_opt == 0 && strlen(ptr->long_opt) == 0)
            return ptr;
    }

    return NULL;
}

/******************************************************************************
 *
 * Public Interface
 *
 */

/**
 * @brief Initialize the command line. Allocates data structures and fills in
 * what we have.
 *
 * @param intro
 * @param outtro
 * @param name
 * @param version
 */
void init_cmdline(const char* intro, const char* outtro, const char* name, const char* version) {

    _cmdline_t_* ptr = _ALLOC_DS(_cmdline_t_);
    ptr->prog        = NULL;
    ptr->intro       = _DUP_STR(intro);
    ptr->outtro      = _DUP_STR(outtro);
    ptr->name        = _DUP_STR(name);
    ptr->version     = _DUP_STR(version);
    ptr->cmd_opts    = create_ptr_lst();
    ptr->sopts       = create_string(NULL);
    append_string_str(ptr->sopts, "-:");
    ptr->flag     = 0;
    ptr->min_reqd = 0;

    cmdline = ptr;
}

/**
 * @brief Free all memory associated with the data structure.
 *
 */
void uninit_cmdline(void) {

    if(cmdline != NULL) {
        if(cmdline->prog != NULL)
            _FREE(cmdline->prog);
        if(cmdline->intro != NULL)
            _FREE(cmdline->intro);
        if(cmdline->outtro != NULL)
            _FREE(cmdline->outtro);
        if(cmdline->name != NULL)
            _FREE(cmdline->name);
        if(cmdline->version != NULL)
            _FREE(cmdline->version);

        if(cmdline->cmd_opts != NULL) {
            int post = 0;
            _cmd_opt_t_* ptr;
            while(NULL != (ptr = iterate_ptr_lst(cmdline->cmd_opts, &post))) {
                if(ptr->name != NULL)
                    _FREE(ptr->name);
                if(ptr->help != NULL)
                    _FREE(ptr->help);
                if(ptr->long_opt != NULL)
                    _FREE(ptr->long_opt);
                if(ptr->values != NULL)
                    destroy_str_lst(ptr->values);
                _FREE(ptr);
            }
            destroy_ptr_lst(cmdline->cmd_opts);
        }

        // note to self: order of these operations is important
        if(cmdline->sopts != NULL)
            destroy_string(cmdline->sopts);
        _FREE(cmdline);
    }
}

/**
 * @brief Add an option to the command line parser. Do this before parsing
 * the command line. The short opt must not be zero or -1. If it's a printable
 * character as given by isgraph(), then it's a cmd arg and listed as such.
 * Otherwise it's used in the switch statement to discover the arg and it
 * should be a value over 255. Practice is to use a value over 1000.
 *
 * @param short_opt
 * @param long_opt
 * @param name
 * @param help
 * @param flag
 */
void add_cmdline(int short_opt,
                 const char* long_opt,
                 const char* name,
                 const char* help,
                 const char* value,
                 cmdline_callback cb,
                 CmdType flag) {

    ASSERT_MSG(cmdline != NULL, "init the cmdline data structure before calling this.");

    if(flag & CMD_REQD)
        cmdline->min_reqd++;

    // capture the help and all.
    _cmd_opt_t_* ptr = _ALLOC_DS(_cmd_opt_t_);
    ptr->short_opt   = short_opt;
    ptr->long_opt    = _DUP_STR(long_opt); // opt->name;
    ptr->help        = _DUP_STR(help);
    ptr->name        = _DUP_STR(name);
    ptr->values      = create_str_lst();
    ptr->flag        = flag;
    ptr->callback    = cb;
    if(value != NULL)
        append_str_lst(ptr->values, create_string(value));

    append_ptr_lst(cmdline->cmd_opts, ptr);
}

/**
 * @brief Read the command line and fill out the data structure with the
 * options. If the flag is non-zero then non-options are errors.
 *
 * Globals defined by getopt:
 * optind - The current index into the command line
 * opterr - If this is set to 0 then getopt does not print error messages.
 *          Otherwise, getopt does print them by default.
 *
 * @param argc
 * @param argv
 * @param flag
 */
void parse_cmdline(int argc, char** argv, int flag) {

    ASSERT_MSG(cmdline != NULL, "init the cmdline data structure before calling this.");

    cmdline->prog = _DUP_STR(argv[0]);
    cmdline->flag = flag;

    if(argc <= cmdline->min_reqd)
        error("at least %d command arguments are required.", cmdline->min_reqd);

    internal_parse_cmdline(argc, argv);

    // verify that all of the required options have a value
    int post = 0;
    _cmd_opt_t_* op;
    while(NULL != (op = iterate_ptr_lst(cmdline->cmd_opts, &post))) {
        if((op->flag & CMD_REQD) && (!(op->flag & CMD_SEEN) || (op->values->len == 0))) {
            if(op->short_opt != 0)
                error("required command parameter '-%c' missing.", op->short_opt);
            else if(strlen(op->long_opt) > 0)
                error("required command parameter '--%s' missing.", op->long_opt);
            else
                error("required command parameter '%s' missing.", op->name);
        }
    }
}

/**
 * @brief Iterate the option, if it's a list. Otherwise, just get it.
 *
 * @param name
 * @param post
 * @return const char*
 */
const char* iterate_cmdline(const char* name, int* post) {

    _cmd_opt_t_* opt = search_name(name);
    ASSERT_MSG(opt != NULL, "cannot find the option searched for: %s", name);

    return raw_string(iterate_str_lst(opt->values, post));
}

/**
 * @brief Retrieve a command line option from the data structure. If it's a
 * list, just keep retrieving the first option.
 *
 * @param name
 * @return const char*
 */
const char* get_cmdline(const char* name) {

    _cmd_opt_t_* opt = search_name(name);
    ASSERT_MSG(opt != NULL, "cannot find the option searched for: %s", name);

    if((opt->flag & CMD_REQD) || (opt->flag & CMD_RARG) || (opt->flag & CMD_OARG)) {
        int post = 0;
        return iterate_cmdline(name, &post);
    }
    else {
        if(opt->flag & CMD_SEEN)
            return opt->name;
        else
            return NULL;
    }
}

/**
 * @brief Show the help message and exit the program.
 *
 */
void show_help(void) {

    char tmp[64];

    printf("\nUsage: %s [options]", cmdline->prog);
    if(!cmdline->flag)
        printf(" files\n");
    else
        printf("\n");

    printf("%s v%s\n", cmdline->name, cmdline->version);
    printf("%s\n\n", cmdline->intro);
    printf("Options:\n");
    printf("  Parm             Args        Help\n");
    printf("-+----------------+-----------+------------------------------------"
           "---------\n");

    int post = 0;
    _cmd_opt_t_* ptr;

    while(NULL != (ptr = iterate_ptr_lst(cmdline->cmd_opts, &post))) {
        if(isgraph(ptr->short_opt) || strlen(ptr->long_opt) > 0) {
            strcpy(tmp, " ");
            if(isgraph(ptr->short_opt)) // could be zero
                snprintf(tmp, sizeof(tmp), "-%c", ptr->short_opt);
            printf("%4s", tmp);
            // printf("%s", tmp);

            strcpy(tmp, " ");
            if(strlen(ptr->long_opt) > 0) // should never be NULL
                snprintf(tmp, sizeof(tmp), "--%s", ptr->long_opt);
            printf(" %-14s", tmp);
            // printf(" %s", tmp);

            if((ptr->flag & CMD_RARG) || (ptr->flag & CMD_OARG)) {
                int c = (ptr->flag & CMD_NUM)  ? 'N' :
                        (ptr->flag & CMD_STR)  ? 'S' :
                        (ptr->flag & CMD_BOOL) ? 'B' :
                                                 '?';

                if(ptr->flag & CMD_LIST)
                    snprintf(tmp, sizeof(tmp), "[%c,%c, ...]", c, c);
                else
                    snprintf(tmp, sizeof(tmp), "[%c]", c);
            }
            else
                strcpy(tmp, "  ");
            printf("%-12s", tmp);
            // printf("%s", tmp);

            if(ptr->flag & CMD_REQD)
                snprintf(tmp, sizeof(tmp), "(reqd) %s", ptr->help);
            else
                snprintf(tmp, sizeof(tmp), "%s", ptr->help);
            printf("%s\n", tmp);
        }
        else {
            snprintf(tmp, sizeof(tmp), "%s", ptr->name);
            printf("  %-17s", tmp);

            int c = (ptr->flag & CMD_NUM)  ? 'N' :
                    (ptr->flag & CMD_STR)  ? 'S' :
                    (ptr->flag & CMD_BOOL) ? 'B' :
                                             '?';
            snprintf(tmp, sizeof(tmp), "[%c,%c, ...]", c, c);
            printf("%-12s", tmp);

            if(ptr->flag & CMD_REQD)
                snprintf(tmp, sizeof(tmp), "(reqd) %s", ptr->help);
            else
                snprintf(tmp, sizeof(tmp), "%s", ptr->help);
            printf("%s\n", tmp);
        }
    }
    printf("-+----------------+-----------+------------------------------------"
           "---------\n");
    printf("  S = string, N = number, B = bool ('on'|'off'|'true'|'false')\n");

    printf("\n%s\n\n", cmdline->outtro);
    exit(1);
}

/**
 * @brief Show the version that was registered in the init
 *
 */
void show_version(void) {

    printf("%s v%s\n", cmdline->name, cmdline->version);
    exit(1);
}
