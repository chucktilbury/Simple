/**
 *
 * @file class_definition.c
 *
 * @brief Parse grammar production class_definition.
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
 * class_definition
 *     : 'class' IDENT ( class_inheritance_list )? class_body
 *     ;
 *
 */
ast_class_definition_t* parse_class_definition(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_class_definition_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* name = NULL;
    ast_class_inheritance_list_t* inher = NULL;
    ast_class_body_t* body = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(TOK_CLASS == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                if(TOK_IDENT == TTYPE) {
                    name = copy_token(get_token());
                    consume_token();
                    state = 2;
                }
                else {
                    EXPECTED("a name for the class definition");
                    state = 102;
                }
                break;

            case 2:
                TRACE_STATE;
                inher = parse_class_inheritance_list(pstate);
                state = 3;
                break;

            case 3:
                TRACE_STATE;
                if(NULL != (body = parse_class_body(pstate))) 
                    state = 100;
                else {
                    EXPECTED("a class body");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_class_definition_t*)create_ast_node(AST_CLASS_DEFINITION);
                node->name = name;
                node->inher = inher;
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

