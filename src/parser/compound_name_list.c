/**
 *
 * @file compound_name_list.c
 *
 * @brief Parse grammar production compound_name_list.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "errors.h"
#include "parser.h"
#include "tokens.h"

/**
 *
 * Grammar production:
 *
 * compound_name_list
 *     : '(' ( compound_name (',' compound_name )* )? ')'
 *     ;
 */
ast_compound_name_list_t* parse_compound_name_list(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_compound_name_list_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    PtrLst* list = create_ptr_lst();
    ast_compound_name_t* ptr = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // required OPAREN or not a match
                TRACE_STATE;
                if(TOK_OPAREN == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else
                    state = 101;
                break;

            case 1:
                // optional first compound name
                TRACE_STATE;
                if(NULL != (ptr = parse_compound_name(pstate))) {
                    append_ptr_lst(list, ptr);
                    state = 2;
                }
                else
                    state = 4;
                break;

            case 2:
                // comma or close paren
                TRACE_STATE;
                if(TOK_COMMA == TTYPE) {
                    consume_token();
                    state = 3;
                }
                else if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("a ',' or a ')'");
                    state = 102;
                }
                break;

            case 3:
                // required compound name
                TRACE_STATE;
                if(NULL != (ptr = parse_compound_name(pstate))) {
                    append_ptr_lst(list, ptr);
                    state = 2;
                }
                else {
                    EXPECTED("a compound name");
                    state = 102;
                }
                break;

            case 4:
                // required CPAREN
                TRACE_STATE;
                if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("a ')'");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_compound_name_list_t*)create_ast_node(AST_COMPOUND_NAME_LIST);
                node->list = list;
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
