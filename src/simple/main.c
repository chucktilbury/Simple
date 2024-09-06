/*
 *
 */
#include "common.h"
#include "cmdline.h"
#include "trace.h"
#include "parser.h"

void init_simple(int argc, char** argv) {

    ENTER;
    init_cmdline("Simple Language Compiler", "", "Simple", "0.0.0");

    add_cmdline('i', NULL, "incl", "add an include search directory", "./", NULL, CMD_STR|CMD_RARG);

    // verbosity level, values 0-10
    add_cmdline('v', "verbosity", "verbo", "control how much text is displayed during execution",
                "0", NULL, CMD_NUM | CMD_RARG);

    add_cmdline(0, "ptrace", "tp", "trace parser execution", NULL, NULL, CMD_NARG|CMD_BOOL);
    add_cmdline(0, "atrace", "ta", "trace the AST execution", NULL, NULL, CMD_NARG|CMD_BOOL);

    // standard options that control the command line parser behaviors
    add_cmdline('V', "version", NULL, "show the version", NULL, show_version, CMD_NARG);
    add_cmdline('h', "help", NULL, "show this help text", NULL, show_help, CMD_NARG);

    // list of files should always be the last one
    add_cmdline(0, NULL, "list of files", "list of files to be processed", NULL,
                NULL, CMD_STR | CMD_REQD);

    // see what we got.
    parse_cmdline(argc, argv, 0);
    RET;
}

int main(int argc, char** argv) {

    INIT_TRACE();
    PUSH_TRACE_STATE(TRACE_ON);
    ENTER;

    init_simple(argc, argv);

    ast_module_t* module = parse();

    traverse_ast(module, NULL, NULL);

    RETURN(0);
}
