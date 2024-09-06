/**
 *
 * @file string_literal.c
 *
 * @brief Parse grammar production string_literal.
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
 * string_literal
 *     : LITERAL_SSTR
 *     | formatted_strg
 *     ;
 */
ast_string_literal_t* parse_string_literal(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_string_literal_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* lstr = NULL;
    ast_formatted_strg_t* fstr = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_LITERAL_SSTR == TTYPE) {
                    lstr = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else if(NULL != (fstr = parse_formatted_strg(pstate)))
                    state = 100;
                else 
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_string_literal_t*)create_ast_node(AST_STRING_LITERAL);
                node->lstr = lstr;
                node->fstr = fstr;
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

