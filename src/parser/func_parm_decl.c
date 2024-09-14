/**
 * @file func_parm_decl.c
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
 * func_parm_decl
 *     : type_name ( IDENT )?
 *     ;
 */
ast_func_parm_decl_t* parse_func_parm_decl(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_func_parm_decl_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* ident = NULL;
    ast_type_name_t* type = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(NULL != (type = parse_type_name(pstate)))
                    state = 1;
                else
                    state = 101;
                break;

            case 1:
                // optional IDENT
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    ident = copy_token(get_token());
                    consume_token();
                }
                state = 100;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_func_parm_decl_t*)create_ast_node(AST_FUNC_PARM_DECL);
                node->ident = ident;
                node->type = type;
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

