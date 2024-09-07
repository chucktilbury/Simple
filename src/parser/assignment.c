/**
 *
 * @file assignment.c
 *
 * @brief Parse grammar production assignment.
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
 * assignment
 *     : compound_reference '=' assign_eq_item
 *     | compound_reference '+=' assign_inc_item
 *     | compound_reference '-=' expression
 *     | compound_reference '*=' expression
 *     | compound_reference '/=' expression
 *     | compound_reference '%=' expression
 *     ;
 */
ast_assignment_t* parse_assignment(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_assignment_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_compound_reference_t* lhs = NULL;
    Token* oper = NULL;
    ast_node_t* rhs = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(NULL != (lhs = parse_compound_reference(pstate)))
                    state = 1;
                else
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                switch(TTYPE) {
                    case TOK_EQUAL:
                        oper = copy_token(get_token());
                        consume_token();
                        state = 2;
                        break;
                    case TOK_PLUS_EQUAL:
                        oper = copy_token(get_token());
                        consume_token();
                        state = 3;
                        break;
                    case TOK_MINUS_EQUAL:
                    case TOK_STAR_EQUAL:
                    case TOK_SLASH_EQUAL:
                    case TOK_PERCENT_EQUAL:
                        oper = copy_token(get_token());
                        consume_token();
                        state = 4;
                        break;
                    default:
                        // not a match
                        state = 101;
                }
                break;

            case 2:
                TRACE_STATE;
                if(NULL != (rhs = (ast_node_t*)parse_assign_eq_item(pstate)))
                    state = 100;
                else {
                    EXPECTED("a valid assignment item");
                    state = 102;
                }
                break;

            case 3:
                TRACE_STATE;
                if(NULL != (rhs = (ast_node_t*)parse_assign_inc_item(pstate)))
                    state = 100;
                else {
                    EXPECTED("an expression or a string");
                    state = 102;
                }
                break;

            case 4:
                TRACE_STATE;
                if(NULL != (rhs = (ast_node_t*)parse_expression(pstate)))
                    state = 100;
                else {
                    EXPECTED("an expression");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_assignment_t*)create_ast_node(AST_ASSIGNMENT);
                node->oper = oper;
                node->lhs = lhs;
                node->rhs = rhs;
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

