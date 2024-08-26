/**
 *
 * @file raise_statement.c
 *
 * @brief Parse grammar production raise_statement.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "tokens.h"
#include "errors.h"
#include "parser.h"

/**
 *
 * Grammar production:
 *
 * raise_statement
 *     : 'raise' '(' IDENT ',' string_literal ')'
 *     ;
 */
ast_raise_statement_t* parse_raise_statement(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_raise_statement_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* id;
    ast_string_literal_t* str;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE(state);
                if(TOK_RAISE == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else 
                    state = 101;
                break;

            case 1:
                TRACE_STATE(state);
                if(TOK_OPAREN == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else {
                    EXPECTED("a '('");
                    state = 102;
                }
                break;

            case 2:
                TRACE_STATE(state);
                if(TOK_IDENT == TTYPE) {
                    id = copy_token(get_token());
                    consume_token();
                    state = 3;
                }
                else {
                    EXPECTED("an identifier");
                    state = 102;
                }
                break;

            case 3:
                TRACE_STATE(state);
                if(TOK_COMMA == TTYPE) {
                    consume_token();
                    state = 4;
                }
                else {
                    EXPECTED("a ','");
                    state = 102;
                }
                break;

            case 4:
                TRACE_STATE(state);
                if(NULL != (str = parse_formatted_strg(pstate)))
                    state = 5;
                else {
                    EXPECTED("a formatted string");
                    state = 102;
                }
                break;

            case 5:
                TRACE_STATE(state);
                if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("a ')'");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_raise_statement_t*)create_ast_node(AST_RAISE_STATEMENT);
                finished = true;
                break;

            case 101:
                // not a match, not an error
                TRACE_STATE(state);
                reset_token_queue(post);
                finished = true;
                break;

            case 102:
                // error found
                TRACE_STATE(state);
                recover_error();
                finished = true;
                break;

            default:
                FATAL("unknown state: %d", state);
        }
    }

    RETURN(node);
}

