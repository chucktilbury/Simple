/**
 *
 * @file cast_statement.c
 *
 * @brief Parse grammar production cast_statement.
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
 * cast_statement
 *     : type_name ':' expression
 *     ;
 */
ast_cast_statement_t* parse_cast_statement(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_cast_statement_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_type_name_t* type;
    ast_expression_t* expr;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(NULL != (type = parse_type_name(pstate)))
                    state = 1;
                else
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                if(TOK_COLON == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else
                    state = 101;
                break;

            case 2:
                // initial state
                TRACE_STATE;
                if(NULL != (expr = parse_expression(pstate)))
                    state = 100;
                else {
                    EXPECTED("an expression");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_cast_statement_t*)create_ast_node(AST_CAST_STATEMENT);
                node->type = type;
                node->expr = expr;
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

