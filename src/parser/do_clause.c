/**
 *
 * @file do_clause.c
 *
 * @brief Parse grammar production do_clause.
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
 * do_clause
 *     : 'do' function_body while_definition
 *     ;
 */
ast_do_clause_t* parse_do_clause(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_do_clause_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_while_definition_t* expr = NULL;
    ast_function_body_t* body = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_DO == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                if(NULL != (body = parse_function_body(pstate)))
                    state = 2;
                else {
                    EXPECTED("a function body");
                    state = 102;
                }
                break;

            case 2:
                TRACE_STATE;
                if(NULL != (expr = parse_while_definition(pstate)))
                    state = 100;
                else {
                    EXPECTED("a while clause");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_do_clause_t*)create_ast_node(AST_DO_CLAUSE);
                node->expr = expr;
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
