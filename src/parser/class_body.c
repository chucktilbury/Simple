/**
 * @file class_body.c
 * @author your name (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-10
 * 
 * @copyright Copyright (c) 2024
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
 * class_body
 *    : '{' ( class_body_item )+ '}'
 *    ;
*/
ast_class_body_t* parse_class_body(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_class_body_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_class_body_item_t* item = NULL;
    PtrLst* list = create_ptr_lst();

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_OCBRACE == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else 
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                if(NULL == (item = parse_class_body_item(pstate))) {
                    if(TOK_CCBRACE == TTYPE) {
                        consume_token();
                        state = 100;
                    }
                    else {
                        EXPECTED("a class item or a '}'");
                        state = 102;
                    }
                }
                else 
                    append_ptr_lst(list, item);
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_class_body_t*)create_ast_node(AST_CLASS_BODY);
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

