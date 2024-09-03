/**
 *
 * @file for_clause.c
 *
 * @brief Parse grammar production for_clause.
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
 * for_clause
 *     : 'for' ( '(' ( expression 'as' IDENT )? ')' )? function_body
 *     ;
 */
ast_for_clause_t* parse_for_clause(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_for_clause_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* ident = NULL;
    ast_expression_t* expr = NULL;
    ast_function_body_t* body = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_FOR == TTYPE) {
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
                    state = 6;
                break;

            case 2:
                TRACE_STATE;
                if(NULL != (expr = parse_expression(pstate)))
                    state = 3; // not empty
                else 
                    state = 5; // is empty
                break;

            case 3:
                TRACE_STATE;
                if(TOK_AS == TTYPE) {
                    consume_token();
                    state = 4;
                }
                else {
                    EXPECTED("'as' keyword");
                    state = 102;
                }
                break;

            case 4:
                // required ident
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    ident = copy_token(get_token());
                    consume_token();
                    state = 5;
                }
                else {
                    EXPECTED("an identifier");
                    state = 102;
                } 
                break;

            case 5:
                // optional ident
                if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 6;
                }
                else {
                    EXPECTED("a ')'");
                    state = 102;
                }
                break;

            case 6:
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
                node = (ast_for_clause_t*)create_ast_node(AST_FOR_CLAUSE);
                node->ident = ident;
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

