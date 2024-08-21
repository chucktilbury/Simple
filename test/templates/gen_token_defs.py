# Generate the token definitions

with open("terminals.txt", "r") as fp:
    terms = [s.strip() for s in fp.readlines()]

with open("token_defs.h", "w") as fp:
    fp.write("#ifndef _TOKEN_DEFS_H_\n")
    fp.write("#define _TOKEN_DEFS_H_\n\n")

    fp.write("typedef enum {\n")
    for item in terms:
        fp.write("    %s,\n"%(item))
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

with open("token_defs.c", "w") as fp:
    fp.write("\n#include <stdio.h>\n\n")
    fp.write("\n#include <strings.h>\n\n")
    fp.write("#include \"token_defs.h\"\n\n")

    fp.write("token_database_t keywords[] = {\n")
    with open("tokens.txt", "r") as fp1:
        items = [s.strip() for s in fp1.readlines()]
    for item in items:
        fp.write("    %s\n"%(item))
    fp.write("};\n")
    fp.write("#define NUM_KEYWORDS (sizeof(keywords)/sizeof(token_database_t))\n\n")

    fp.write("const char* token_type_to_str(TokenType type) {\n\n")
    fp.write("    return ")
    with open("translate.txt", "r") as fp1:
        items = [s.strip() for s in fp1.readlines()]

    fp.write("%s\n"%(items[0]))
    for item in items[1:]:
        fp.write("        %s\n"%(item))
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
