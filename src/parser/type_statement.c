/**
 *
 * @file type_statement.c
 *
 * @brief Parse grammar production type_statement.
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
 * type_statement
 *     : 'type' '(' compound_reference ')'
 *     ;
 */
ast_type_statement_t* parse_type_statement(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_type_statement_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_compound_reference_t* arg = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_TYPE == TTYPE) {
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
                else {
                    EXPECTED("a '('");
                    state = 102;
                }
                break;

            case 2:
                TRACE_STATE;
                if(NULL != (arg = parse_compound_reference(pstate)))
                    state = 3;
                else {
                    EXPECTED("a compound reference");
                    state = 102;
                }
                break;

            case 3:
                TRACE_STATE;
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
                TRACE_STATE;
                node = (ast_type_statement_t*)create_ast_node(AST_TYPE_STATEMENT);
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

