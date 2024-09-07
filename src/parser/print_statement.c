/**
 *
 * @file print_statement.c
 *
 * @brief Parse grammar production print_statement.
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
 * print_statement
 *     : 'print' ( expression_list )?
 *     ;
 */
ast_print_statement_t* parse_print_statement(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_print_statement_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_expression_list_t* ptr = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_PRINT == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                if(NULL != (ptr = parse_expression_list(pstate)))
                    state = 100;
                else {
                    EXPECTED("an expression list");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_print_statement_t*)create_ast_node(AST_PRINT_STATEMENT);
                node->ptr = ptr;
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

