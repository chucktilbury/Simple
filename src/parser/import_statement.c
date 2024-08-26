/**
 *
 * @file import_statement.c
 *
 * @brief Parse grammar production import_statement.
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
 * import_statement
 *     : 'import' formatted_strg 'as' IDENT
 *     ;
 */
ast_import_statement_t* parse_import_statement(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_import_statement_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_formatted_strg_t* str;
    Token* ident;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(TOK_IMPORT == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else 
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                if(NULL != (str = parse_formatted_strg(pstate)))
                    state = 2;
                else {
                    EXPECTED("a formatted string");
                    state = 102;
                }
                break;

            case 2:
                TRACE_STATE;
                if(TOK_AS == TTYPE) {
                    consume_token();
                    state = 3;
                }
                else {
                    EXPECTED("'as' keyword");
                    state = 102;
                }
                break;

            case 3:
                TRACE_STATE;
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
                node = (ast_import_statement_t*)create_ast_node(AST_IMPORT_STATEMENT);
                node->str = str;
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

