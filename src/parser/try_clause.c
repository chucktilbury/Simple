/**
 *
 * @file try_clause.c
 *
 * @brief Parse grammar production try_clause.
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
 * try_clause
 *     : 'try' function_body ( except_clause )* ( final_clause )?
 *     ;
 *
 * If there are no except clauses and no final clause then that is a syntax
 * error. However there may be either one without the other.
 *
 */
ast_try_clause_t* parse_try_clause(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_try_clause_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    // function required body
    ast_function_body_t* body;
    // zero or more final clauses
    ast_final_clause_t* fin = NULL;
    // list of except clauses
    PtrLst* list = create_ptr_lst();
    ast_except_clause_t* exc;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_TRY == TTYPE) {
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
                if(NULL != (exc = parse_except_clause(pstate))) 
                    append_ptr_lst(list, exc);
                else if(NULL != (fin = parse_final_clause(pstate))) 
                    state = 100;
                else 
                    state = 100;
                break;


            case 100:
                // production recognized
                TRACE_STATE;
                if(length_ptr_lst(list) != 0 || fin != NULL) {
                    node = (ast_try_clause_t*)create_ast_node(AST_TRY_CLAUSE);
                    node->body = body;
                    node->fin = fin;
                    node->list = list;
                    finished = true;
                }
                else {
                    EXPECTED("an exception or a final clause");
                    state = 102;
                }
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

