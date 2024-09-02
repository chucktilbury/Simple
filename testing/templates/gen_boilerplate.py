import re
import time
import os

terminals = []
non_terminals = []
keywords = {}
translate = []
rules = {}
rule_name = ""

def convert(str):

    s = "TOK"
    for c in str:
        if c == '!': s += "_BANG"
        elif c == '@': s += "_AT"
        elif c == '#': s += "_HASH"
        elif c == '$': s += "_DOLLAR"
        elif c == '%': s += "_PERCENT"
        elif c == '^': s += "_CARAT"
        elif c == '&': s += "_AMPERSAND"
        elif c == '*': s += "_STAR"
        elif c == '(': s += "_OPAREN"
        elif c == ')': s += "_CPAREN"
        elif c == '-': s += "_MINUS"
        elif c == '=': s += "_EQUAL"
        elif c == '+': s += "_PLUS"
        elif c == '[': s += "_OSBRACE"
        elif c == ']': s += "_CSBRACE"
        elif c == '{': s += "_OCBRACE"
        elif c == '}': s += "_CCBRACE"
        elif c == '\\': s += "_BSLASH"
        elif c == ':': s += "_COLON"
        elif c == ';': s += "_SEMICOLON"
        elif c == '\'': s += "_SQUOTE"
        elif c == '\"': s += "_DQUOTE"
        elif c == ',': s += "_COMMA"
        elif c == '<': s += "_OPBRACE"
        elif c == '.': s += "_DOT"
        elif c == '>': s += "_CPBRACE"
        elif c == '/': s += "_SLASH"
        elif c == '?': s += "_QUESTION"
        elif c == '~': s += "_TILDE"
    return s

def gen_lists():

    with open("../../docs/simple-grammar.txt", "r") as fp:
        grammar = [ s.strip() for s in fp.readlines() ]

    for line in grammar:
        if len(line) > 0:
            if line[0] == ':' or line[0] == '|':
                rules[rule_name].append("    %s"%(line))
                res = re.findall(r"\'([^\']+)\'", line)
                for mat in res:
                    if re.match(r"[a-z]+", mat):
                        s = "TOK_%s"%(mat.upper())
                        if not s in terminals:
                            terminals.append(s)
                            keywords[s] = mat
                            translate.append("(type == %s)? \"%s\" :"%(s, mat))
                    else:
                        #print(mat)
                        s = convert(mat)
                        if not s in terminals:
                            terminals.append(s)
                            translate.append("(type == %s)? \"%s\" :"%(s, mat))

                res = re.findall(r"([A-Z_]+)", line)
                for mat in res:
                    if mat != "_":
                        s = "TOK_"+mat
                        if not s in terminals:
                            terminals.append(s)
                            translate.append("(type == %s)? \"%s\" :"%(s, mat))
            elif line[0] == ';':
                #print("end:", line)
                rules[rule_name].append("    ;")
                pass
            else:
                #print("non terminal:", line)
                if not line in non_terminals:
                    non_terminals.append(line)
                    rules[line] = []
                    rule_name = line
                else:
                    print("duplicate non terminal symbol is illegal")
                    exit(1)

def gen_ast():

    with open("ast/ast.h", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file ast.h\n *\n")
        fp.write(" * @brief AST traverse public interface.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("\n#ifndef _AST_H_\n#define _AST_H_\n\n")

        fp.write("typedef enum {\n")
        for str in rules:
            fp.write("    AST_%s,\n"%(str.upper()))
        fp.write("} AstNodeType;\n\n")

        fp.write("typedef struct _ast_node_ {\n")
        fp.write("    AstNodeType type;\n")
        fp.write("} AstNode;\n\n")

        for str in rules:
            fp.write("/**\n *\n")
            fp.write(" * Grammar production:\n *\n * %s\n"%(str))
            for s in rules[str]:
                fp.write(" * %s\n"%(s))
            fp.write(" */\n")
            fp.write("typedef struct _ast_%s_ {\n"%(str))
            fp.write("    AstNode node;\n\n")
            fp.write("} ast_%s_t;\n\n"%(str))

        fp.write("#define CALL_NODE_FUNC(f) do { \\\n")
        fp.write("        if((f) != NULL) { \\\n")
        fp.write("            (*f)((AstNode*)node); \\\n")
        fp.write("        }\\\n")
        fp.write("    } while(0)\n\n")

        fp.write("typedef void (*AstFuncPtr)(AstNode* node);\n")
        fp.write("AstNode* create_ast_node(AstNodeType type);\n")
        fp.write("void traverse_ast(ast_%s_t* node, AstFuncPtr pre, AstFuncPtr post);\n\n"%(non_terminals[0]))
        for str in rules:
            fp.write("void traverse_%s(ast_%s_t* node, AstFuncPtr pre, AstFuncPtr post);\n"%(str, str))
        fp.write("\n#endif /* _AST_H_ */\n\n")

    with open("ast/ast.c", "w") as fp:
            fp.write("/**\n *\n")
            fp.write(" * @file %s.c\n *\n"%(str))
            fp.write(" * @brief AST implementation.\n")
            fp.write(" * This file was generated on %s.\n"%(time.asctime()))
            fp.write(" *\n */\n")
            fp.write("#include \"common.h\"\n")
            fp.write("#include \"trace.h\"\n")
            fp.write("#include \"errors.h\"\n")
            fp.write("#include \"ast.h\"\n\n")
            fp.write("static size_t node_size(AstNodeType type) {\n\n")
            fp.write("    return\n")
            for str in rules:
                fp.write("    (type == AST_%s)? sizeof(ast_%s_t) : \n"%(str.upper(), str))
            fp.write("    0; // error if we reach here\n")
            fp.write("}\n\n")
            fp.write("AstNode* create_ast_node(AstNodeType type) {\n\n")
            fp.write("    AstNode* node = _ALLOC(node_size(type));\n")
            fp.write("    node->type = type;\n")
            fp.write("    return node;\n")
            fp.write("}\n\n")
            fp.write("void traverse_ast(ast_%s_t* node, AstFuncPtr pre, AstFuncPtr post) {\n\n"%(non_terminals[0]))
            fp.write("    traverse_%s(node, pre, post);\n"%(non_terminals[0]))
            fp.write("}\n\n")

    for str in rules:
        with open("ast/%s.c"%(str), "w") as fp:
            fp.write("/**\n *\n")
            fp.write(" * @file %s.c\n *\n"%(str))
            fp.write(" * @brief Traverse AST for node %s.\n"%(str))
            fp.write(" * This file was generated on %s.\n"%(time.asctime()))
            fp.write(" *\n */\n")
            fp.write("#include \"common.h\"\n")
            fp.write("#include \"trace.h\"\n")
            fp.write("#include \"errors.h\"\n")
            fp.write("#include \"ast.h\"\n\n")
            fp.write("/**\n *\n")
            fp.write(" * Grammar production:\n *\n * %s\n"%(str))
            for s in rules[str]:
                fp.write(" * %s\n"%(s))
            fp.write(" */\n")
            fp.write("void traverse_%s(ast_%s_t* node, AstFuncPtr pre, AstFuncPtr post) {\n\n"%(str, str))
            fp.write("    ENTER;\n")
            fp.write("    CALL_NODE_FUNC(pre);\n\n")
            fp.write("    CALL_NODE_FUNC(post);\n")
            fp.write("    RET;\n")
            fp.write("}\n\n")

def gen_parse():

    with open("parser/parser.h", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file parser.h\n *\n")
        fp.write(" * @brief Parse grammar public interface.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("#ifndef _PARSER_H_\n#define _PARSER_H_\n\n")
        fp.write("#include \"ast.h\"\n\n")
        fp.write("typedef struct {\n")
        fp.write("    int mode;\n")
        fp.write("} parser_state_t;\n\n")
        fp.write("#include \"parser_prototypes.h\"\n\n")
        fp.write("void recover_error(void);\n")
        fp.write("ast_%s_t* parse(void);\n\n"%(non_terminals[0]))
        fp.write("#endif /* _PARSER_H_ */\n\n")

    with open("parser/parser_prototypes.h", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file parser_prototypes.h\n *\n")
        fp.write(" * @brief Internal prototypes for parser.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("#ifndef _PARSER_PROTOTYPES_H_\n#define _PARSER_PROTOTYPES_H_\n\n")
        for str in rules:
            fp.write("ast_%s_t* parse_%s(parser_state_t* pstate);\n"%(str, str))
        fp.write("\n#endif /* _PARSER_PROTOTYPES_H_ */\n\n")

    with open("parser/parser.c", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file parser.c\n *\n")
        fp.write(" * @brief Parser external interface implementation.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("#include \"common.h\"\n")
        fp.write("#include \"ast.h\"\n")
        fp.write("#include \"parser.h\"\n\n")
        fp.write("void recover_error(void) {\n\n")
        fp.write("}\n\n")
        fp.write("ast_%s_t* parse(void) {\n\n"%(non_terminals[0]))
        fp.write("    parser_state_t* pstate = _ALLOC_DS(parser_state_t);\n")
        fp.write("    pstate->mode = 0;\n")
        fp.write("    ast_%s_t* %s = parse_%s(pstate);\n"%(non_terminals[0], non_terminals[0], non_terminals[0]))
        fp.write("    return %s;\n"%(non_terminals[0]))
        fp.write("}\n\n")

    for str in rules:
        with open("parser/%s.c"%(str), "w") as fp:
            fp.write("/**\n *\n")
            fp.write(" * @file %s.c\n *\n"%(str))
            fp.write(" * @brief Parse grammar production %s.\n"%(str))
            fp.write(" * This file was generated on %s.\n"%(time.asctime()))
            fp.write(" *\n */\n")
            fp.write("#include \"common.h\"\n")
            fp.write("#include \"tokens.h\"\n")
            fp.write("#include \"errors.h\"\n")
            fp.write("#include \"parser.h\"\n\n")
            fp.write("/**\n *\n")
            fp.write(" * Grammar production:\n *\n * %s\n"%(str))
            for s in rules[str]:
                fp.write(" * %s\n"%(s))
            fp.write(" */\n")
            fp.write("ast_%s_t* parse_%s(parser_state_t* pstate) {\n\n"%(str, str))
            fp.write("    ASSERT(pstate != NULL);\n")
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

def gen_token_defs():

    with open("tokens/token_defs.h", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file token_defs.h\n *\n")
        fp.write(" * @brief Token definitions public interface.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("#ifndef _TOKEN_DEFS_H_\n")
        fp.write("#define _TOKEN_DEFS_H_\n\n")

        fp.write("typedef enum {\n")
        for item in terminals:
            fp.write("    %s,\n"%(item))
        fp.write("    TOK_CARAT,\n")
        fp.write("\n    TOK_END_OF_INPUT,\n")
        fp.write("    TOK_END_OF_FILE,\n")
        fp.write("    TOK_ERROR,\n")
        fp.write("} TokenType;\n\n")

        fp.write("typedef struct {\n")
        fp.write("    const char* str;\n")
        fp.write("    TokenType type;\n")
        fp.write("} token_database_t;\n\n")

        fp.write("const char* token_type_to_str(TokenType type);\n")
        fp.write("token_database_t* find_keyword(const char* str);\n\n")

        fp.write("#endif /* _TOKEN_DEFS_H_ */\n\n")

    with open("tokens/token_defs.c", "w") as fp:
        fp.write("/**\n *\n")
        fp.write(" * @file token_defs.c\n *\n")
        fp.write(" * @brief Token definition implementation.\n")
        fp.write(" * This file was generated on %s.\n"%(time.asctime()))
        fp.write(" *\n */\n")
        fp.write("#include <stdio.h>\n")
        fp.write("#include <strings.h>\n\n")
        fp.write("#include \"token_defs.h\"\n\n")

        fp.write("static token_database_t keywords[] = {\n")
        for item in dict(sorted(keywords.items(), key=lambda item: item[1])):
            fp.write("    {\"%s\", %s},\n"%(keywords[item], item))
        fp.write("};\n")
        fp.write("#define NUM_KEYWORDS (sizeof(keywords)/sizeof(token_database_t))\n\n")

        fp.write("const char* token_type_to_str(TokenType type) {\n\n")
        fp.write("    return ")

        fp.write("%s\n"%(translate[0]))
        for item in translate[1:]:
            fp.write("        %s\n"%(item))
        fp.write("    (type == TOK_CARAT)? \"^\" :\n")
        fp.write("    (type == TOK_END_OF_INPUT)? \"END OF INPUT\" :\n")
        fp.write("    (type == TOK_END_OF_FILE)? \"END OF FILE\" :\n")
        fp.write("    (type == TOK_ERROR)? \"ERROR\" :\n")
        fp.write("        \"UNKNOWN\";\n")

        fp.write("}\n\n")

        fp.write("token_database_t* find_keyword(const char* str) {\n")

        s = '''
        int l = 0, r = NUM_KEYWORDS - 1, m, x;

        while(l <= r) {
            m = l + (r - l) / 2;
            x = strcasecmp(keywords[m].str, str);

            if(x == 0) {
                return &keywords[m];
            }
            if(x < 0) {
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        return NULL;'''
        fp.write(s)
        fp.write("\n}\n\n")

def installer() :
    os.system("mkdir parser ast tokens")

    gen_ast()
    gen_parse()
    gen_token_defs()

    os.system("mv -f parser/*.c parser/*.h ../../src/parser/")
    os.system("mv -f ast/*.c ast/*.h ../../src/ast/")
    os.system("mv -f tokens/*.c tokens/*.h ../../src/tokens/")
    os.system("rm -rf parser ast tokens")


if __name__ == '__main__':
    
    print("Before you run this, know that it will destroy the parser")
    print("and all of the manual changes that were made to it.")
    exit(1)

    gen_lists()

    with open("non-terminals.txt", "w") as fp:
        for item in non_terminals:
            fp.write("%s\n"%(item))

