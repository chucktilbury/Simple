/**
 *
 * @file compound_name.c
 *
 * @brief Parse grammar production compound_name.
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
 * compound_name
 *     : IDENT ( '.' IDENT )*
 *     ;
 */
ast_compound_name_t* parse_compound_name(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_compound_name_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* tok;
    PtrLst* list = create_ptr_lst();

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    tok = copy_token(get_token());
                    append_ptr_lst(list, tok);
                    consume_token();
                    state = 1;
                }
                else
                    state = 101; // not a match
                break;

            case 1:
                // optional '.'
                TRACE_STATE;
                if(TOK_DOT == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else
                    state = 100; // finished
                break;

            case 2:
                // required identifier
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    tok = copy_token(get_token());
                    append_ptr_lst(list, tok);
                    consume_token();
                    state = 1;
                }
                else {
                    EXPECTED("a valid identifier");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_compound_name_t*)create_ast_node(AST_COMPOUND_NAME);
                node->list = list;
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

