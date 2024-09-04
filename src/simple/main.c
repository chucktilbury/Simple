/*
 *
 */
#include "common.h"
#include "cmdline.h"
#include "trace.h"

void init(int argc, char** argv) {

    init_cmdline("Simple Language Compiler", "", "Simple", "0.0.0");

    // verbosity level, values 0-10
    add_cmdline('v', "verbosity", "verbo", "control how much text is displayed during execution",
                "0", NULL, CMD_NUM | CMD_RARG);

    // standard options that control the command line parser behaviors
    add_cmdline('V', "version", NULL, "show the version", NULL, show_version, CMD_NARG);
    add_cmdline('h', "help", NULL, "show this help text", NULL, show_help, CMD_NARG);

    // list of files should always be the last one
    add_cmdline(0, NULL, "list of files", "list of files to be processed", NULL,
                NULL, CMD_STR | CMD_REQD);

    // see what we got.
    parse_cmdline(argc, argv, 0);
}

// void dump_str_lst(StrLst* lst, const char* str) {

//     int post = 0;
//     String* ptr;

//     printf("%s\n", str);
//     post = 0;

//     while(NULL != (ptr = iterate_str_lst(lst, &post)))
//         printf("%3d. %s\n", post, raw_string(ptr));
// }

// #include "regurg.h"
int main(int argc, char** argv) {

    INIT_TRACE();
    PUSH_TRACE_STATE(TRACE_ON);

    init(argc, argv);
    // terms  = create_str_lst();
    // nterms = create_str_lst();

    // yydebug = 0;

    // open_file(get_cmdline("list of files"));
    // yyparse();

    // sort_str_lst(nterms);
    // sort_str_lst(terms);

    // // dump_str_lst(terms, "\nTERMINALS");
    // // dump_str_lst(nterms, "\nNON TERMINALS");

    // // traverse_ast(NULL, NULL);
    // regurg();

    // //emit();

    return 0;
}
