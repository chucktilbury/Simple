/**
 *
 * @file literal_value.c
 *
 * @brief Parse grammar production literal_value.
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
 * literal_value
 *     : LITERAL_FLOAT
 *     | LITERAL_INTEGER
 *     | LITERAL_BOOL
 *     | string_literal
 *     ;
 */
ast_literal_value_t* parse_literal_value(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_literal_value_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* literal;
    ast_string_literal_t* str;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(TOK_LITERAL_FLOAT == TTYPE) {
                    literal = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(TOK_LITERAL_INTEGER == TTYPE) {
                    literal = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(TOK_LITERAL_BOOL == TTYPE) {
                    literal = copy_token(get_token());
                    consume_token();                    
                    state = 100;
                }
                else if(NULL != (str = parse_string_literal(pstate))) 
                    state = 100;
                else 
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_literal_value_t*)create_ast_node(AST_LITERAL_VALUE);
                node->literal = literal;
                node->str = str;
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

