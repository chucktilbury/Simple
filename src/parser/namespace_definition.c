/**
 *
 * @file namespace_definition.c
 *
 * @brief Parse grammar production namespace_definition.
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
 * namespace_definition
 *     : 'namespace' IDENT '{' ( namespace_item )+ '}'
 *     ;
 */
ast_namespace_definition_t* parse_namespace_definition(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_namespace_definition_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    PtrLst* items = create_ptr_lst();
    Token* name;
    ast_namespace_item_t* item;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE(state);
                if(TOK_NAMESPACE == TTYPE) {
                    consume_token();
                    state = 1;
                }
                else 
                    state = 101;
                break;

            case 1:
                TRACE_STATE(state);
                if(TOK_IDENT == TTYPE) {
                    name = copy_token(get_token());
                    consume_token();
                    state = 2;
                }
                else {
                    EXPECTED("an identifier");
                    state = 102;
                }
                break;

            case 2:
                TRACE_STATE(state);
                if(TOK_OCBRACE == TTYPE) {
                    consume_token();
                    state = 3;
                }
                else {
                    EXPECTED("a '{'");
                    state = 102;
                }
                break;

            case 3:
                // one or more loop
                TRACE_STATE(state);
                if(NULL != (item = parse_namespace_item(pstate))) {
                    append_ptr_lst(items, item);
                    state = 4;
                }
                else {
                    EXPECTED("a namespace item");
                    state = 102;
                }
                break;

            case 4:
                TRACE_STATE(state);
                if(TOK_CCBRACE == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else if(NULL != (item = parse_namespace_item(pstate))) {
                    append_ptr_lst(items, item);
                    state = 4;
                }
                else {
                    EXPECTED("a namespace item");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_namespace_definition_t*)create_ast_node(AST_NAMESPACE_DEFINITION);
                node->items = items;
                node->name = name;
                finished = true;
                break;

            case 101:
                // not a match, not an error
                TRACE_STATE(state);
                reset_token_queue(post);
                finished = true;
                break;

            case 102:
                // error found
                TRACE_STATE(state);
                recover_error();
                finished = true;
                break;

            default:
                FATAL("unknown state: %d", state);
        }
    }

    RETURN(node);
}

