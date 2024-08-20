# Generate boilerplate for the PARSER files
import sys, os

with open("non_terminals.txt", "r") as fp:
    str_list = [s.strip() for s in fp.readlines() ]

with open("parser.h", "w") as fp:
    fp.write("\n#ifndef _PARSER_H_\n#define _PARSER_H_\n\n")
    fp.write("#include \"ast.h\"\n\n")
    for str in str_list:
        fp.write("ast_%s_t* parse_%s(void);\n"%(str, str))
    fp.write("\nvoid recover_error(void);\n")
    fp.write("AstNode* parse(void);\n\n")
    fp.write("\n#endif /* _PARSER_H_ */\n\n")

for str in str_list:
    with open("%s.c"%(str), "w") as fp:
        fp.write("\n\n/*\n    Production being parsed:\n\n */\n")
        fp.write("#include \"common.h\"\n")
        fp.write("#include \"tokens.h\"\n")
        fp.write("#include \"errors.h\"\n")
        fp.write("#include \"parser.h\"\n\n")
        fp.write("ast_%s_t* parse_%s(void) {\n\n"%(str, str))
        fp.write("    ENTER;\n\n")
        fp.write("    ast_%s_t* node = NULL;\n"%(str))
        fp.write("    int state = 0;\n")
        fp.write("    bool finished = false;\n")
        fp.write("    void* post = post_token_queue();\n\n")
        fp.write("    while(!finished) {\n")
        fp.write("        switch(state) {\n")
        fp.write("            case 0:\n")
        fp.write("                // initial state\n")
        fp.write("                TRACE_STATE(state);\n")
        fp.write("                break;\n\n")
        fp.write("            case 100:\n")
        fp.write("                // production recognized\n")
        fp.write("                TRACE_STATE(state);\n")
        fp.write("                node = (ast_%s_t*)create_ast_node(AST_%s);\n"%(str, str.upper()))
        fp.write("                finished = true;\n")
        fp.write("                break;\n\n")
        fp.write("            case 101:\n")
        fp.write("                // not a match, not an error\n")
        fp.write("                TRACE_STATE(state);\n")
        fp.write("                reset_token_queue(post);\n")
        fp.write("                finished = true;\n")
        fp.write("                break;\n\n")
        fp.write("            case 102:\n")
        fp.write("                // error found\n")
        fp.write("                TRACE_STATE(state);\n")
        fp.write("                recover_error();\n")
        fp.write("                finished = true;\n")
        fp.write("                break;\n\n")
        fp.write("            default:\n")
        fp.write("                FATAL(\"unknown state: %d\", state);\n")
        fp.write("        }\n")
        fp.write("    }\n\n")
        fp.write("    RETURN(node);\n")
        fp.write("}\n\n")
