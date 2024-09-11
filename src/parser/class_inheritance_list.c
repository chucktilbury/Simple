/**
 * @file class_inheritance_list.c
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
 * @brief Parse the class inheritance list
 * 
 * class_inheritance_list
 *     : '(' ( class_inheritance_item (',' class_inheritance_item)* )? ')'
 *     ;
 * 
 * @param pstate 
 * @return ast_class_inheritance_list_t* 
 */
ast_class_inheritance_list_t* parse_class_inheritance_list(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_class_inheritance_list_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_class_inheritance_item_t* item = NULL;
    PtrLst* list = create_ptr_lst();

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_OPAREN == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else 
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                if(NULL != (item = parse_class_inheritance_item(pstate))) {
                    append_ptr_lst(list, item);
                    state = 2;
                }
                else    
                    state = 4;
                break;

            case 2:
                TRACE_STATE;
                if(TOK_COMMA == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else if(TOK_CPAREN) {
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("a ')' or a ','");
                    state = 102;
                }
                break;

            case 4:
                // mandatory ')'
                TRACE_STATE;
                if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("a ')'");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_class_inheritance_list_t*)create_ast_node(AST_CLASS_INHERITANCE_LIST);
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



