/**
 *
 * @file create_reference.c
 *
 * @brief Parse grammar production create_reference.
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
 * create_reference
 *     : IDENT ( '.' IDENT )* '.' 'create' expression_list
 *     ;
 */
ast_create_reference_t* parse_create_reference(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_create_reference_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    PtrLst* name = create_ptr_lst();
    ast_expression_list_t* inp = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    append_ptr_lst(name, copy_token(get_token()));
                    consume_token();
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                // mandatory '.'
                TRACE_STATE;
                if(TOK_DOT == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else 
                    state = 101;
                break;
                
            case 2:
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    append_ptr_lst(name, copy_token(get_token()));
                    consume_token();
                    state = 1;
                }
                else if(TOK_CREATE == TTYPE) {
                    consume_token();
                    state = 3;
                }
                else 
                    state = 101;
                break;
                
            case 3:
                TRACE_STATE;
                if(NULL != (inp = parse_expression_list(pstate))) 
                    state = 100;
                else {
                    EXPECTED("an list of expressions");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_create_reference_t*)create_ast_node(AST_CREATE_REFERENCE);
                node->name = name;
                node->inp = inp;
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

