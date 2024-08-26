/**
 *
 * @file if_clause.c
 *
 * @brief Parse grammar production if_clause.
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
 * if_clause
 *     : 'if' '(' expression ')' function_body ( else_clause )* ( final_else_clause )?
 *     ;
 */
ast_if_clause_t* parse_if_clause(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_if_clause_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    // this could be NULL
    ast_final_else_clause_t* fecl = NULL;
    ast_expression_t* expr = NULL;
    ast_function_body_t* body = NULL;
    // list of else clauses
    PtrLst* ecl = create_ptr_lst();
    ast_else_clause_t* ec; 

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_IF == TTYPE) {
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
                if(NULL != (expr = parse_expression(pstate)))
                    state = 3;
                else {
                    EXPECTED("an expression");
                    state = 102;
                }
                break;

            case 3:
                TRACE_STATE;
                if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 4;
                }
                else {
                    EXPECTED("a ')'");
                    state = 102;
                }
                break;

            case 4:
                TRACE_STATE;
                if(NULL != (body = parse_function_body(pstate)))
                    state = 5;
                else {
                    EXPECTED("a function body");
                    state = 102;
                }
                break;

            case 5:
                // optional list of else clauses
                TRACE_STATE;
                if(NULL != (ec = parse_else_clause(pstate))) 
                    append_ptr_lst(ecl, ec); // no state change
                else
                    state = 6;
                break;

            case 6:
                // optional single final else clause
                TRACE_STATE;
                fecl = parse_final_else_clause(pstate);
                state = 100;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_if_clause_t*)create_ast_node(AST_IF_CLAUSE);
                // this could be NULL
                node->fecl = fecl;
                node->expr = expr;
                node->body = body;
                // list of else clauses
                node->ecl = ecl;
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

