/**
 *
 * @file function_definition.c
 *
 * @brief Parse grammar production function_definition.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "tokens.h"
#include "errors.h"
#include "parser.h"

String* decorate_func_def(ast_function_definition_t* func);
/**
 *
 * Grammar production:
 *
 * function_definition
 *     : ( compound_name ':' )? IDENT func_parm_decl_list func_parm_decl_list ( function_body )?
 *     ;
 */
ast_function_definition_t* parse_function_definition(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_function_definition_t* node = NULL;
    int state = 1;
    bool finished = false;
    void* post = post_token_queue();

    Token* name;
    ast_function_membership_t* member = NULL;
    ast_func_parm_decl_list_t* inp = NULL;
    ast_func_parm_decl_list_t* outp = NULL;
    ast_function_body_t* body = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // optional membership
                TRACE_STATE;
                member = parse_function_membership(pstate);
                state = 1;
                break;

            case 1:
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    name = copy_token(get_token());
                    consume_token();
                    state = 2;
                }
                else
                    state = 101;
                break;

            case 2:
                TRACE_STATE;
                if(NULL != (inp = parse_func_parm_decl_list(pstate)))
                    state = 3;
                else
                    if(member == NULL)
                        state = 101; // an id by itself is not an error yet.
                    else {
                        EXPECTED("a function parameter list");
                        state = 102;
                    }
                break;

            case 3:
                TRACE_STATE;
                if(NULL != (outp = parse_func_parm_decl_list(pstate)))
                    state = 4;
                else {
                    EXPECTED("a function parameter list");
                    state = 102;
                }
                break;

            case 4:
                // optional function body
                TRACE_STATE;

                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_function_definition_t*)create_ast_node(AST_FUNCTION_DEFINITION);
                node->member = member;
                node->name = name;
                node->inp = inp;
                node->outp = outp;
                node->body = body;
                decorate_func_def(node);
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

