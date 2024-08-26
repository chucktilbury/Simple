/**
 *
 * @file compound_ref_item.c
 *
 * @brief Parse grammar production compound_ref_item.
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
 * compound_ref_item
 *     : IDENT
 *     | array_reference
 *     ;
 */
ast_compound_ref_item_t* parse_compound_ref_item(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_compound_ref_item_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* name = NULL;
    ast_array_reference_t* ref = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    name = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(NULL != (ref = parse_array_reference(pstate))) 
                    state = 100;
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_compound_ref_item_t*)create_ast_node(AST_COMPOUND_REF_ITEM);
                node->name = name;
                node->ref = ref;
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

