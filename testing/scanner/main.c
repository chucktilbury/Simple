#include "common.h"
#include "scanner.h"
#include "tokens.h"

#ifndef USE_TRACE
#define USE_TRACE
#include "trace.h"
#endif

#include "cmdline.h"

void print_token(Token* tok) {

    ENTER;
    TRACE("type: %s: %s", token_to_str(tok->type), raw_string(tok->str));
    RET;
}

int main(int argc, char** argv) {

    INIT_TRACE();
    PUSH_TRACE_STATE(TRACE_ON);
    
    ENTER;

    init_cmdline("Scanner Test Program", "", "Scanner Test", "0.0.0");

    // standard options that control the command line parser behaviors
    add_cmdline('V', "version", NULL, "show the version", NULL, show_version, CMD_NARG);
    add_cmdline('h', "help", NULL, "show this help text", NULL, show_help, CMD_NARG);

    // list of files should always be the last one
    add_cmdline(0, NULL, "list of files", "list of files to be processed", NULL,
                NULL, CMD_STR | CMD_REQD);

    // see what we got.
    parse_cmdline(argc, argv, 0);

    init_scanner(get_cmdline("list of files")); //"../testing/scanner/test_input1.txt");

    Token* tok = get_token();

    while(true) {
        print_token(tok);
        if(tok->type == TOK_END_OF_INPUT)
            break;
        else if(tok->type == TOK_END_OF_FILE)
            close_file();
        tok = consume_token();
    }

    RETURN(0);
}

