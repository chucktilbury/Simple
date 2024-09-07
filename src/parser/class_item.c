/**
 *
 * @file class_item.c
 *
 * @brief Parse grammar production class_item.
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
 * class_item
 *     : scope_operator
 *     | var_decl
 *     | function_declaration
 *     | create_declaration
 *     | destroy_declaration
 *     ;
 */
ast_class_item_t* parse_class_item(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_class_item_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_node_t* ptr = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(NULL != (ptr = (ast_node_t*)parse_scope_operator(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_var_decl(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_function_declaration(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_create_declaration(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_destroy_declaration(pstate)))
                    state = 100;
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_class_item_t*)create_ast_node(AST_CLASS_ITEM);
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

