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

/**
 *
 * Grammar production:
 *
 * function_definition
 *     : ('iterator' )? compound_name var_decl_list var_decl_list function_body
 *     ;
 */
ast_function_definition_t* parse_function_definition(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_function_definition_t* node = NULL;
    int state = 1;
    bool finished = false;
    void* post = post_token_queue();

    bool is_iter = false;
    ast_compound_name_t* name = NULL;
    ast_var_decl_list_t* inp = NULL;
    ast_var_decl_list_t* outp = NULL;
    ast_function_body_t* body = NULL;

    while(!finished) {
        switch(state) {
            // case 0:
            //     TRACE_STATE;
            //     if(TOK_ITERATOR == TTYPE) {
            //         is_iter = true;
            //         consume_token();
            //     }
            //     state = 1;
            //     break;

            case 1:
                TRACE_STATE;
                if(NULL != (name = parse_compound_name(pstate))) 
                    state = 2;
                else
                    state = 101;
                break;

            case 2:
                TRACE_STATE;
                if(NULL != (inp = parse_var_decl_list(pstate))) 
                    state = 3;
                else 
                    state = 101;
                break;

            case 3:
                TRACE_STATE;
                if(NULL != (outp = parse_var_decl_list(pstate))) 
                    state = 4;
                else {
                    EXPECTED("a variable declaration list");
                    state = 102;
                }
                break;

            case 4:
                TRACE_STATE;
                if(NULL != (body = parse_function_body(pstate)))
                    state = 100;
                else {
                    EXPECTED("a function body");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_function_definition_t*)create_ast_node(AST_FUNCTION_DEFINITION);
                node->is_iter = is_iter;
                node->name = name;
                node->inp = inp;
                node->outp = outp;
                node->body = body;
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

