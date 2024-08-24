/**
 *
 * @file expression_list.c
 *
 * @brief Parse grammar production expression_list.
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
 * expression_list
 *     : '(' (expression ( ',' expression )*)? ')'
 *     ;
 */
ast_expression_list_t* parse_expression_list(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_expression_list_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    PtrLst* list = create_ptr_lst();
    ast_expression_t* expr;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE(state);
                if(TOK_OPAREN == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else 
                    state = 101;
                break;

            case 1:
                TRACE_STATE(state);
                if(NULL != (expr = parse_expression(pstate))) {
                    append_ptr_lst(list, expr);
                    state = 2;
                }
                else 
                    state = 10;
                break;

            case 2:
                TRACE_STATE(state);
                if(TOK_COMMA == TTYPE) {
                    consume_token();
                    state = 3;
                }
                else if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("a ',' or ')'");
                    state = 102;
                }
                break;

            case 3:
                TRACE_STATE(state);
                if(NULL != (expr = parse_expression(pstate))) {
                    append_ptr_lst(list, expr);
                    state = 2;
                }
                else {
                    EXPECTED("an expression");
                    state = 102;
                }
                break;

            case 10:
                TRACE_STATE(state);
                if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else 
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_expression_list_t*)create_ast_node(AST_EXPRESSION_LIST);
                node->list = list;
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

