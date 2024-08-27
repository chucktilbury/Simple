/**
 *
 * @file scope_operator.c
 *
 * @brief Parse grammar production scope_operator.
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
 * scope_operator
 *     : 'private'
 *     | 'public'
 *     | 'protected'
 *     ;
 */
ast_scope_operator_t* parse_scope_operator(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_scope_operator_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* tok;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_PRIVATE == TTYPE) {
                    tok = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(TOK_PUBLIC == TTYPE) {
                    tok = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(TOK_PROTECTED == TTYPE) {
                    tok = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else 
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_scope_operator_t*)create_ast_node(AST_SCOPE_OPERATOR);
                node->tok = tok;
                finished = true;
                break;

            case 101:
                // not a match, not an error
                TRACE_STATE;
                reset_token_queue(post);
                finished = true;
                break;

            case 102:
                // error found
                TRACE_STATE;
                recover_error();
                finished = true;
                break;

            default:
                FATAL("unknown state: %d", state);
        }
    }

    RETURN(node);
}

