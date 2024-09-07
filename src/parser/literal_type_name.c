/**
 *
 * @file literal_type_name.c
 *
 * @brief Parse grammar production literal_type_name.
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
 * literal_type_name
 *     : 'float'
 *     | 'integer'
 *     | 'string'
 *     | 'boolean'
 *     | 'nothing'
 *     | 'list'
 *     | 'dict'
 *     ;
 */
ast_literal_type_name_t* parse_literal_type_name(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_literal_type_name_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* tok = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_FLOAT == TTYPE) {
                    tok = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(TOK_INTEGER == TTYPE) {
                    tok = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(TOK_STRING == TTYPE) {
                    tok = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(TOK_BOOLEAN == TTYPE) {
                    tok = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(TOK_NOTHING == TTYPE) {
                    tok = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(TOK_LIST == TTYPE) {
                    tok = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(TOK_DICT == TTYPE) {
                    tok = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else 
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_literal_type_name_t*)create_ast_node(AST_LITERAL_TYPE_NAME);
                node->tok = tok;
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

