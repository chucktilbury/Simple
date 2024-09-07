/**
 *
 * @file except_clause.c
 *
 * @brief Parse grammar production except_clause.
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
 * except_clause
 *     : 'except' '(' IDENT ',' IDENT ')' function_body
 *     ;
 */
ast_except_clause_t* parse_except_clause(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_except_clause_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* id1 = NULL;
    Token* id2 = NULL;
    ast_function_body_t* body = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_EXCEPT == TTYPE) {
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
                TRACE_STATE;
                if(TOK_COMMA == TTYPE) {
                    consume_token();
                    state = 4;
                }
                else {
                    EXPECTED("a ','");
                    state = 102;
                }
                break;

            case 4:
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    id2 = copy_token(get_token());
                    consume_token();
                    state = 5;
                }
                else {
                    EXPECTED("an identifier");
                    state = 102;
                }
                break;

            case 5:
                TRACE_STATE;
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
                node = (ast_except_clause_t*)create_ast_node(AST_EXCEPT_CLAUSE);
                node->id1= id1;
                node->id2= id2;
                node->body= body;
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

