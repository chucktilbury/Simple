/**
 *
 * @file final_clause.c
 *
 * @brief Parse grammar production final_clause.
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
 * final_clause
 *     : 'final' '(' IDENT ')' function_body
 *     ;
 */
ast_final_clause_t* parse_final_clause(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_final_clause_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* id1;
    ast_function_body_t* body;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE(state);
                if(TOK_FINAL == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else 
                    state = 101;
                break;

            case 1:
                TRACE_STATE(state);
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
                TRACE_STATE(state);
                if(TOK_IDENT == TTYPE) {
                    id1 = copy_token(get_token());
                    consume_token();
                    state = 3;
                }
                else {
                    EXPECTED("an identifier");
                    state = 102;
                }
                break;

            case 3:
                TRACE_STATE(state);
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
                TRACE_STATE(state);
                if(NULL == (body = parse_function_body(pstate))) 
                    state = 100;
                else {
                    EXPECTED("a '('");
                    state = 102;
                }
                break;
            
            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_final_clause_t*)create_ast_node(AST_FINAL_CLAUSE);
                node->id1 = id1;
                node->body = body;
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

