/**
 * @file func_parm_decl_list.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-09-13
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
 * func_parm_decl_list
 *     : '(' ( func_parm_decl ( ',' func_parm_decl )* )? ')'
 *     ;
 */
ast_func_parm_decl_list_t* parse_func_parm_decl_list(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_func_parm_decl_list_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_func_parm_decl_t* item = NULL;
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
                TRACE_STATE:
                if(NULL != (item = parse_func_parm_decl(pstate)))
                    state = 2;
                else
                    state = 101;
                break;

            case 2:
                TRACE_STATE;
                if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else if(TOK_COMMA == TTYPE) {
                    consume_token();
                    state = 3;
                }
                else {
                    EXPECTED("a ',' or a ')'");
                    state = 102;
                }
                break;

            case 3:
                TRACE_STATE;
                if(NULL != (item = parse_func_parm_decl(pstate)))
                    state = 2;
                else {
                    EXPECTED("a function parameter declaration");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_func_parm_decl_list_t*)create_ast_node(AST_FUNC_PARM_DECL_LIST);
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

