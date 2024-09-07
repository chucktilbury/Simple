/**
 *
 * @file create_name.c
 *
 * @brief Parse grammar production create_name.
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
 * create_name
 *     : IDENT ('.' IDENT)? '.' 'create'
 *     ;
 */
ast_create_name_t* parse_create_name(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_create_name_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    PtrLst* ident = create_ptr_lst();
    Token* ptr = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    ptr = copy_token(get_token());
                    consume_token();
                    append_ptr_lst(ident, ptr);
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                // if we have a dot then proceed. otherwise, not a match.
                TRACE_STATE;
                if(TOK_DOT == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else 
                    state = 101;
                break;

            case 2:
                // After the dot, must have a TOK_IDENT or TOK_CREATE. If 
                // it's not then it's not a match. A syntax error may be 
                // caught during another production. 
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    ptr = copy_token(get_token());
                    consume_token();
                    append_ptr_lst(ident, ptr);
                    state = 1;
                }
                else if(TOK_CREATE == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_create_name_t*)create_ast_node(AST_CREATE_NAME);
                node->ident = ident;
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

