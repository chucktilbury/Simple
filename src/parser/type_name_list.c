/**
 *
 * @file type_name_list.c
 *
 * @brief Parse grammar production type_name_list.
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
 * type_name_list
 *     : '(' ( type_name (',' type_name )* )? ')'
 *     ;
 */
ast_type_name_list_t* parse_type_name_list(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_type_name_list_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    PtrLst* list = create_ptr_lst();
    ast_type_name_t* name;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
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
                if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else if(NULL != (name = parse_type_name(pstate))) {
                    append_ptr_lst(list, name);
                    state = 2;
                }
                else {
                    EXPECTED("a type name or a ')'");
                    state = 102;
                }
                break;

            case 2:
                // a ',' or a ')' is expected after a type name
                TRACE_STATE;
                if(TOK_COMMA == TTYPE) {
                    consume_token();
                    state = 3;
                }
                else if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("a ')' or a ','");
                    state = 102;
                }
                break;

            case 3:
                // type name is required after a ','
                TRACE_STATE;
                if(NULL != (name = parse_type_name(pstate))) {
                    append_ptr_lst(list, name);
                    state = 2;
                }
                else {
                    EXPECTED("a type name");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_type_name_list_t*)create_ast_node(AST_TYPE_NAME_LIST);
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

