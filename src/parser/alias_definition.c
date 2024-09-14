/**
 * @file alias_definition.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-09-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "common.h"
#include "errors.h"
#include "parser.h"
#include "tokens.h"

/**
 * Grammar production:
 *
 * alias_definition
 *      : compound_name 'as' IDENT
 *      ;
 */
ast_alias_definition_t* parse_alias_definition(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_alias_definition_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_compound_name_t* target = NULL;
    Token* ident = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(NULL != (target = parse_compound_name(pstate)))
                    state = 1;
                else
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                if(TOK_AS == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else
                    state = 101;
                break;

            case 2:
                TRACE_STATE;
                TRACE_TOKEN;
                if(TOK_IDENT == TTYPE) {
                    ident = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("an identifier");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_alias_definition_t*)create_ast_node(AST_ALIAS_DEFINITION);
                node->target = target;
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
