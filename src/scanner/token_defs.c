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

#include "tokens.h"

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

const char* token_to_str(TokenType type) {

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

const char* token_type_to_str(Token* tok) {

    TokenType type = token_type(tok);
    return (type == TOK_START)? "TOK_START" :
        (type == TOK_IMPORT)? "TOK_IMPORT" :
        (type == TOK_AS)? "TOK_AS" :
        (type == TOK_IDENT)? "TOK_IDENT" :
        (type == TOK_INCLUDE)? "TOK_INCLUDE" :
        (type == TOK_PRIVATE)? "TOK_PRIVATE" :
        (type == TOK_PUBLIC)? "TOK_PUBLIC" :
        (type == TOK_PROTECTED)? "TOK_PROTECTED" :
        (type == TOK_FLOAT)? "TOK_FLOAT" :
        (type == TOK_INTEGER)? "TOK_INTEGER" :
        (type == TOK_STRING)? "TOK_STRING" :
        (type == TOK_BOOLEAN)? "TOK_BOOLEAN" :
        (type == TOK_NOTHING)? "TOK_NOTHING" :
        (type == TOK_LIST)? "TOK_LIST" :
        (type == TOK_DICT)? "TOK_DICT" :
        (type == TOK_OPAREN)? "TOK_OPAREN" :
        (type == TOK_COMMA)? "TOK_COMMA" :
        (type == TOK_CPAREN)? "TOK_CPAREN" :
        (type == TOK_LITERAL_DSTR)? "TOK_LITERAL_DSTR" :
        (type == TOK_LITERAL_SSTR)? "TOK_LITERAL_SSTR" :
        (type == TOK_LITERAL_FLOAT)? "TOK_LITERAL_FLOAT" :
        (type == TOK_LITERAL_INTEGER)? "TOK_LITERAL_INTEGER" :
        (type == TOK_LITERAL_BOOL)? "TOK_LITERAL_BOOL" :
        (type == TOK_CONST)? "TOK_CONST" :
        (type == TOK_EQUAL)? "TOK_EQUAL" :
        (type == TOK_COLON)? "TOK_COLON" :
        (type == TOK_OSBRACE)? "TOK_OSBRACE" :
        (type == TOK_CSBRACE)? "TOK_CSBRACE" :
        (type == TOK_DOT)? "TOK_DOT" :
        (type == TOK_OR)? "TOK_OR" :
        (type == TOK_AND)? "TOK_AND" :
        (type == TOK_EQU)? "TOK_EQU" :
        (type == TOK_NEQU)? "TOK_NEQU" :
        (type == TOK_LT)? "TOK_LT" :
        (type == TOK_GT)? "TOK_GT" :
        (type == TOK_LTE)? "TOK_LTE" :
        (type == TOK_GTE)? "TOK_GTE" :
        (type == TOK_NOT)? "TOK_NOT" :
        (type == TOK_EQUAL_EQUAL)? "TOK_EQUAL_EQUAL" :
        (type == TOK_BANG_EQUAL)? "TOK_BANG_EQUAL" :
        (type == TOK_OPBRACE)? "TOK_OPBRACE" :
        (type == TOK_CPBRACE)? "TOK_CPBRACE" :
        (type == TOK_OPBRACE_EQUAL)? "TOK_OPBRACE_EQUAL" :
        (type == TOK_CPBRACE_EQUAL)? "TOK_CPBRACE_EQUAL" :
        (type == TOK_PLUS)? "TOK_PLUS" :
        (type == TOK_MINUS)? "TOK_MINUS" :
        (type == TOK_STAR)? "TOK_STAR" :
        (type == TOK_SLASH)? "TOK_SLASH" :
        (type == TOK_PERCENT)? "TOK_PERCENT" :
        (type == TOK_BANG)? "TOK_BANG" :
        (type == TOK_NAMESPACE)? "TOK_NAMESPACE" :
        (type == TOK_OCBRACE)? "TOK_OCBRACE" :
        (type == TOK_CCBRACE)? "TOK_CCBRACE" :
        (type == TOK_CLASS)? "TOK_CLASS" :
        (type == TOK_VIRTUAL)? "TOK_VIRTUAL" :
        (type == TOK_CREATE)? "TOK_CREATE" :
        (type == TOK_DESTROY)? "TOK_DESTROY" :
        (type == TOK_PLUS_EQUAL)? "TOK_PLUS_EQUAL" :
        (type == TOK_MINUS_EQUAL)? "TOK_MINUS_EQUAL" :
        (type == TOK_STAR_EQUAL)? "TOK_STAR_EQUAL" :
        (type == TOK_SLASH_EQUAL)? "TOK_SLASH_EQUAL" :
        (type == TOK_PERCENT_EQUAL)? "TOK_PERCENT_EQUAL" :
        (type == TOK_INLINE)? "TOK_INLINE" :
        (type == TOK_BREAK)? "TOK_BREAK" :
        (type == TOK_CONTINUE)? "TOK_CONTINUE" :
        (type == TOK_YIELD)? "TOK_YIELD" :
        (type == TOK_TYPE)? "TOK_TYPE" :
        (type == TOK_RETURN)? "TOK_RETURN" :
        (type == TOK_RAISE)? "TOK_RAISE" :
        (type == TOK_TRACE)? "TOK_TRACE" :
        (type == TOK_PRINT)? "TOK_PRINT" :
        (type == TOK_EXIT)? "TOK_EXIT" :
        (type == TOK_WHILE)? "TOK_WHILE" :
        (type == TOK_DO)? "TOK_DO" :
        (type == TOK_FOR)? "TOK_FOR" :
        (type == TOK_IN)? "TOK_IN" :
        (type == TOK_IF)? "TOK_IF" :
        (type == TOK_ELSE)? "TOK_ELSE" :
        (type == TOK_TRY)? "TOK_TRY" :
        (type == TOK_EXCEPT)? "TOK_EXCEPT" :
        (type == TOK_FINAL)? "TOK_FINAL" :
        (type == TOK_CARAT)? "TOK_CARAT" :
        (type == TOK_PIPE)? "TOK_PIPE" :
        (type == TOK_AMPERSAND)? "TOK_AMPERSAND" :
        (type == TOK_UNARY_MINUS)? "TOK_UNARY_MINUS" :
        (type == TOK_UNARY_NOT)? "TOK_UNARY_NOT" :
        (type == TOK_END_OF_INPUT)? "TOK_END_OF_INPUT" :
        (type == TOK_END_OF_FILE)? "TOK_END_OF_FILE" :
        (type == TOK_ERROR)? "TOK_ERROR" : "UNKNOWN";

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

