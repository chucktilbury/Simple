# Generate boilerplate for the AST files
import sys, os

with open("non_terminals.txt", "r") as fp:
    str_list = [s.strip() for s in fp.readlines() ]

with open("ast.h", "w") as fp:
    fp.write("\n#ifndef _AST_H_\n#define _AST_H_\n\n")

    fp.write("typedef enum {\n")
    for str in str_list:
        fp.write("    AST_%s,\n"%(str.upper()))
    fp.write("} AstNodeType;\n\n")

    fp.write("typedef struct _ast_node_ {\n")
    fp.write("    AstNodeType type;\n")
    fp.write("} AstNode;\n\n")

    for str in str_list:
        fp.write("/*\n    Production being parsed:\n\n */\n")
        fp.write("typedef struct _ast_%s_ {\n"%(str))
        fp.write("    AstNode node;\n\n")
        fp.write("} ast_%s_t;\n\n"%(str))

    fp.write("#define CALL_NODE_FUNC(f) do { \\\n")
    fp.write("        if((f) != NULL) { \\\n")
    fp.write("            (*f)((AstNode*)node); \\\n")
    fp.write("        }\\\n")
    fp.write("    } while(0)\n\n")

    fp.write("typedef void (*AstFuncPtr)(AstNode* node);\n")
    fp.write("AstNode* create_ast_node(AstNodeType type);\n\n")
    for str in str_list:
        fp.write("void traverse_%s(ast_%s_t* node, AstFuncPtr pre, AstFuncPtr post);\n"%(str, str))
    fp.write("\n#endif /* _AST_H_ */\n\n")

for str in str_list:
    with open("%s.c"%(str), "w") as fp:
        fp.write("\n\n/*\n    Production being parsed:\n\n */\n")
        fp.write("#include \"common.h\"\n")
        fp.write("#include \"trace.h\"\n")
        fp.write("#include \"errors.h\"\n")
        fp.write("#include \"ast.h\"\n\n")
        fp.write("void traverse_%s(ast_%s_t* node, AstFuncPtr pre, AstFuncPtr post) {\n\n"%(str, str))
        fp.write("    ENTER;\n")
        fp.write("    CALL_NODE_FUNC(pre);\n\n")
        fp.write("    CALL_NODE_FUNC(post);\n")
        fp.write("    RET;\n")
        fp.write("}\n\n")
