%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "ast.h"
#include "str.h"
#include "parse.h"
#include "memory.h"

int yycolumn = 1;

typedef struct _file_stack_ {
    const char* fname;
    int line;
    int col;
    FILE* fptr;
    YY_BUFFER_STATE buffer;
    struct _file_stack_* next;
} FileStack;

#define MAX_INCL 15
FileStack* fstack = NULL;
int incl_depth = 0;

String* convert_token(const char* str) {

    String* ptr = create_string("TOK");
    if(isalnum(str[1]))
        append_string_char(ptr, '_');

    for(unsigned i = 1; i < strlen(&str[1]); i++) {
        switch(str[i]) {
            case '!':
                append_string_str(ptr, "_BANG");
                break;
            case '@':
                append_string_str(ptr, "_AT");
                break;
            case '^':
                append_string_str(ptr, "_CARAT");
                break;
            case '&':
                append_string_str(ptr, "_AMPER");
                break;
            case '+':
                append_string_str(ptr, "_PLUS");
                break;
            case '-':
                append_string_str(ptr, "_MINUS");
                break;
            case '/':
                append_string_str(ptr, "_SLASH");
                break;
            case '%':
                append_string_str(ptr, "_PERCENT");
                break;
            case '*':
                append_string_str(ptr, "_STAR");
                break;
            case '?':
                append_string_str(ptr, "_QUESTION");
                break;
            case '(':
                append_string_str(ptr, "_OPAREN");
                break;
            case ')':
                append_string_str(ptr, "_CPAREN");
                break;
            case '<':
                append_string_str(ptr, "_OPBRACE");
                break;
            case '>':
                append_string_str(ptr, "_CPBRACE");
                break;
            case ':':
                append_string_str(ptr, "_COLON");
                break;
            case '|':
                append_string_str(ptr, "_BAR");
                break;
            case ',':
                append_string_str(ptr, "_COMMA");
                break;
            case '.':
                append_string_str(ptr, "_DOT");
                break;
            case ';':
                append_string_str(ptr, "_SEMICOLON");
                break;
            case '=':
                append_string_str(ptr, "_EQUAL");
                break;
            case '[':
                append_string_str(ptr, "_OSBRACE");
                break;
            case ']':
                append_string_str(ptr, "_CSBRACE");
                break;
            case '{':
                append_string_str(ptr, "_OCBRACE");
                break;
            case '}':
                append_string_str(ptr, "_CCBRACE");
                break;
            case '\'':
                append_string_str(ptr, "_SQUOTE");
                break;
            case '\"':
                append_string_str(ptr, "_DQUOTE");
                break;
            case '$':
                append_string_str(ptr, "_DOLLAR");
                break;
            default:
                append_string_char(ptr, toupper(str[i]));
                break;
        }
    }

    return ptr;
}

/* This is executed before every action. */
#define YY_USER_ACTION                                                   \
  fstack->col = yycolumn;                  \
  if (yylineno == prev_yylineno) yycolumn += yyleng;                     \
  else {                                                                 \
    for (yycolumn = 1; yytext[yyleng - yycolumn] != '\n'; ++yycolumn) {} \
    prev_yylineno = yylineno;                                            \
  }

%}

/* state definitions */
%x SQUOTES
%x DQUOTES
%x CSYMBOL
%option noinput nounput
%option yylineno
%option noyywrap

%%

   /* Any indented text before the first rule goes at the top of the lexer.  */
   // int start_line, start_column;
   int prev_yylineno = yylineno;

\n      { fstack->line++; fstack->col = 1; }
[ \t\r]     {  }

"+"         { return '+'; }
"*"         { return '*'; }
"?"         { return '?'; }
"("         { return '('; }
")"         { return ')'; }
":"         { return ':'; }
"|"         { return '|'; }
";"         { return ';'; }
","         { return ','; }
"="         { return '='; }
"$"         { return '$'; }

[a-z_][a-zA-Z_0-9]* {
        yylval.str = create_string(yytext);
        return IDENT;
    }

[A-Z][a-zA-Z_0-9]* {
        // These are "keepers" and are part of the AST content
        yylval.str = create_string(NULL);
        append_string_fmt(yylval.str, "SOK_%s", yytext);
        //append_string_fmt(yylval.str, "TOK_%s", yytext);
        upper_string(yylval.str);
        return TERMINAL;
    }

\'([^\'\n]*)\' {
        // These are "syntax" and direct the function of the AST
        yylval.str = convert_token(yytext);
        return TERMINAL;
    }

\"([^\"\n])*\" {
        // These are "syntax" and direct the function of the AST
        yylval.str = convert_token(yytext);
        return TERMINAL;
    }

. {
        // Just put up a warning, but ignore the character.
        printf("Warning: unrecognized character: %c (0x%02X)\n",
                yytext[0], yytext[0]);
    }

    /* comments */
"#".*\n { fstack->line++; fstack->col = 1; }

<<EOF>> {

        incl_depth--;

        FileStack* tmp = fstack;

#ifdef ENABLE_PARSER_TRACE
        fprintf(stderr, ">>>>>> closing file: %s\n", tmp->fname);
#endif

        free((void*)tmp->fname);
        fclose(tmp->fptr);
        free(tmp);

        fstack = fstack->next;

        if(fstack == NULL) {
            yyterminate();
        }
        else {
            yy_delete_buffer(YY_CURRENT_BUFFER);
            yy_switch_to_buffer(fstack->buffer);
        }
    }


%%

void open_file(const char *fname) {

#ifdef ENABLE_PARSER_TRACE
    fprintf(stderr, "<<<<<<< opening file: %s\n", fname);
#endif

    if(incl_depth > MAX_INCL) {
        fprintf(stderr, "FATAL ERROR: Maximum include depth exceeded\n");
        exit(1);
    }
    incl_depth++;

    FileStack* fs = malloc(sizeof(FileStack));
    fs->fname = _DUP_STR(fname);
    fs->line = 1;
    fs->col = 1;
    fs->next = NULL;

    yyin = fopen(fname, "r");
    if(yyin == NULL) {
        fprintf(stderr, "fatal error: cannot open input file: '%s': %s\n", fname,
                strerror(errno));
        exit(1);
    }

    fs->fptr = yyin;
    yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
    fs->buffer = YY_CURRENT_BUFFER;

    if(fstack != NULL)
        fs->next = fstack;

    fstack = fs;
}

int get_line_no(void) {

    if(fstack != NULL)
        return fstack->line;
    else
        return -1;
}

int get_col_no(void) {

    if(fstack != NULL)
        return fstack->col;
    else
        return -1;
}

const char* get_file_name(void) {

    if(fstack != NULL)
        return fstack->fname;
    else
        return "no file open";
}
