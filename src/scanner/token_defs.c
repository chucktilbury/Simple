/**
 *
 * @file token_defs.c
 *
 * @brief Token definition implementation.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include <stdio.h>
#include <strings.h>

#include "token_defs.h"

static token_database_t keywords[] = {
    {"and", TOK_AND},
    {"as", TOK_AS},
    {"boolean", TOK_BOOLEAN},
    {"break", TOK_BREAK},
    {"class", TOK_CLASS},
    {"const", TOK_CONST},
    {"continue", TOK_CONTINUE},
    {"create", TOK_CREATE},
    {"destroy", TOK_DESTROY},
    {"dict", TOK_DICT},
    {"do", TOK_DO},
    {"else", TOK_ELSE},
    {"equ", TOK_EQU},
    {"except", TOK_EXCEPT},
    {"exit", TOK_EXIT},
    {"final", TOK_FINAL},
    {"float", TOK_FLOAT},
    {"for", TOK_FOR},
    {"gt", TOK_GT},
    {"gte", TOK_GTE},
    {"if", TOK_IF},
    {"import", TOK_IMPORT},
    {"in", TOK_IN},
    {"include", TOK_INCLUDE},
    {"integer", TOK_INTEGER},
    {"list", TOK_LIST},
    {"lt", TOK_LT},
    {"lte", TOK_LTE},
    {"namespace", TOK_NAMESPACE},
    {"nequ", TOK_NEQU},
    {"not", TOK_NOT},
    {"nothing", TOK_NOTHING},
    {"or", TOK_OR},
    {"print", TOK_PRINT},
    {"private", TOK_PRIVATE},
    {"protected", TOK_PROTECTED},
    {"public", TOK_PUBLIC},
    {"raise", TOK_RAISE},
    {"return", TOK_RETURN},
    {"start", TOK_START},
    {"string", TOK_STRING},
    {"trace", TOK_TRACE},
    {"try", TOK_TRY},
    {"type", TOK_TYPE},
    {"virtual", TOK_VIRTUAL},
    {"while", TOK_WHILE},
    {"yield", TOK_YIELD},
};
#define NUM_KEYWORDS (sizeof(keywords)/sizeof(token_database_t))

const char* token_type_to_str(TokenType type) {

    return (type == TOK_START)? "start" :
        (type == TOK_IMPORT)? "import" :
        (type == TOK_AS)? "as" :
        (type == TOK_IDENT)? "IDENT" :
        (type == TOK_INCLUDE)? "include" :
        (type == TOK_PRIVATE)? "private" :
        (type == TOK_PUBLIC)? "public" :
        (type == TOK_PROTECTED)? "protected" :
        (type == TOK_FLOAT)? "float" :
        (type == TOK_INTEGER)? "integer" :
        (type == TOK_STRING)? "string" :
        (type == TOK_BOOLEAN)? "boolean" :
        (type == TOK_NOTHING)? "nothing" :
        (type == TOK_LIST)? "list" :
        (type == TOK_DICT)? "dict" :
        (type == TOK_OPAREN)? "(" :
        (type == TOK_COMMA)? "," :
        (type == TOK_CPAREN)? ")" :
        (type == TOK_LITERAL_DSTR)? "LITERAL_DSTR" :
        (type == TOK_LITERAL_SSTR)? "LITERAL_SSTR" :
        (type == TOK_LITERAL_FLOAT)? "LITERAL_FLOAT" :
        (type == TOK_LITERAL_INTEGER)? "LITERAL_INTEGER" :
        (type == TOK_LITERAL_BOOL)? "LITERAL_BOOL" :
        (type == TOK_CONST)? "const" :
        (type == TOK_EQUAL)? "=" :
        (type == TOK_COLON)? ":" :
        (type == TOK_OSBRACE)? "[" :
        (type == TOK_CSBRACE)? "]" :
        (type == TOK_DOT)? "." :
        (type == TOK_OR)? "or" :
        (type == TOK_AND)? "and" :
        (type == TOK_NOT)? "not" :
        (type == TOK_EQU)? "equ" :
        (type == TOK_NEQU)? "nequ" :
        (type == TOK_LT)? "lt" :
        (type == TOK_GT)? "gt" :
        (type == TOK_LTE)? "lte" :
        (type == TOK_GTE)? "gte" :
        (type == TOK_EQUAL_EQUAL)? "==" :
        (type == TOK_BANG_EQUAL)? "!=" :
        (type == TOK_OPBRACE)? "<" :
        (type == TOK_CPBRACE)? ">" :
        (type == TOK_OPBRACE_EQUAL)? "<=" :
        (type == TOK_CPBRACE_EQUAL)? ">=" :
        (type == TOK_PLUS)? "+" :
        (type == TOK_MINUS)? "-" :
        (type == TOK_STAR)? "*" :
        (type == TOK_SLASH)? "/" :
        (type == TOK_PERCENT)? "%" :
        (type == TOK_BANG)? "!" :
        (type == TOK_NAMESPACE)? "namespace" :
        (type == TOK_OCBRACE)? "{" :
        (type == TOK_CCBRACE)? "}" :
        (type == TOK_CLASS)? "class" :
        (type == TOK_VIRTUAL)? "virtual" :
        (type == TOK_CREATE)? "create" :
        (type == TOK_DESTROY)? "destroy" :
        (type == TOK_PLUS_EQUAL)? "+=" :
        (type == TOK_MINUS_EQUAL)? "-=" :
        (type == TOK_STAR_EQUAL)? "*=" :
        (type == TOK_SLASH_EQUAL)? "/=" :
        (type == TOK_PERCENT_EQUAL)? "%=" :
        (type == TOK_INLINE)? "INLINE" :
        (type == TOK_BREAK)? "break" :
        (type == TOK_CONTINUE)? "continue" :
        (type == TOK_YIELD)? "yield" :
        (type == TOK_TYPE)? "type" :
        (type == TOK_RETURN)? "return" :
        (type == TOK_RAISE)? "raise" :
        (type == TOK_TRACE)? "trace" :
        (type == TOK_PRINT)? "print" :
        (type == TOK_EXIT)? "exit" :
        (type == TOK_WHILE)? "while" :
        (type == TOK_DO)? "do" :
        (type == TOK_FOR)? "for" :
        (type == TOK_IN)? "in" :
        (type == TOK_IF)? "if" :
        (type == TOK_ELSE)? "else" :
        (type == TOK_TRY)? "try" :
        (type == TOK_EXCEPT)? "except" :
        (type == TOK_FINAL)? "final" :
        (type == TOK_CARAT)? "^" :
        (type == TOK_PIPE)? "|" :
        (type == TOK_AMPERSAND)? "&" :
        (type == TOK_END_OF_INPUT)? "END OF INPUT" :
        (type == TOK_END_OF_FILE)? "END OF FILE" :
        (type == TOK_ERROR)? "ERROR" : "UNKNOWN";
}

token_database_t* find_keyword(const char* str) {

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
        return NULL;
}

