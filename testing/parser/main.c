#include "common.h"
#include "scanner.h"
#include "parser.h"

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

    parse();

    RETURN(0);
}

