/**
 *
 * @file var_decl.c
 *
 * @brief Parse grammar production var_decl.
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
 * var_decl
 *     : type_name IDENT
 *     ;
 */
ast_var_decl_t* parse_var_decl(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_var_decl_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_type_name_t* type = NULL;
    Token* ident = NULL;

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
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    ident = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else 
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_var_decl_t*)create_ast_node(AST_VAR_DECL);
                node->type = type;
                node->ident = ident;
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

