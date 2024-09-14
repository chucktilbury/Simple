/**
 *
 * @file final_else_clause.c
 *
 * @brief Parse grammar production final_else_clause.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "errors.h"
#include "parser.h"
#include "tokens.h"

/**
 *
 * Grammar production:
 *
 * final_else_clause
 *     : 'else' ( '(' ')' )? function_body
 *     ;
 */
ast_final_else_clause_t* parse_final_else_clause(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_final_else_clause_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_function_body_t* body = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_ELSE == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                if(TOK_OPAREN == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else
                    state = 3;
                break;

            case 2:
                TRACE_STATE;
                if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 3;
                }
                else
                    state = 101;
                break;

            case 3:
                TRACE_STATE;
                if(NULL != (body = parse_function_body(pstate)))
                    state = 100;
                else {
                    EXPECTED("a function body");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_final_else_clause_t*)create_ast_node(AST_FINAL_ELSE_CLAUSE);
                node->body = body;
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
