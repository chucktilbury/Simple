/**
 *
 * @file compound_reference.c
 *
 * @brief Parse grammar production compound_reference.
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
 * compound_reference
 *     : compound_ref_item ( '.' compound_ref_item )*
 *     ;
 */
ast_compound_reference_t* parse_compound_reference(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_compound_reference_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    PtrLst* list = create_ptr_lst();
    ast_compound_ref_item_t* item = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(NULL != (item = parse_compound_ref_item(pstate))) {
                    append_ptr_lst(list, item);
                    state = 1;
                }
                else 
                    state = 101;
                break;

            case 1:
                // if a '.' then another follows, else finished
                TRACE_STATE;
                if(TOK_DOT == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else
                    state = 100; // finished 
                break;

            case 2:
                TRACE_STATE;
                if(NULL != (item = parse_compound_ref_item(pstate))) {
                    append_ptr_lst(list, item);
                    state = 1;
                }
                else {
                    //EXPECTED("a compound reference item");
                    // could be a reference to create or destroy
                    state = 101;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_compound_reference_t*)create_ast_node(AST_COMPOUND_REFERENCE);
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

