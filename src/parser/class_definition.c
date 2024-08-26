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
 *     : 'class' IDENT ( '(' ( type_name )? ')' )? '{' ( class_item )+ '}'
 *     ;
 */
ast_class_definition_t* parse_class_definition(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_class_definition_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* name;
    ast_type_name_t* inher;
    PtrLst* list = create_ptr_lst();
    ast_class_item_t* item;

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
                // optional parentheses
                TRACE_STATE;
                if(TOK_OPAREN == TTYPE) {
                    consume_token();
                    state = 3;
                }
                else
                    state = 5;
                break;

            case 3:
                // optional compound name
                TRACE_STATE;
                if(NULL != (inher = parse_type_name(pstate)))
                    state = 4;
                else
                    state = 4; // yep. they at the same
                break;

            case 4:
                // required close paren
                TRACE_STATE;
                if(TOK_CPAREN == TTYPE) {
                    consume_token();
                    state = 5;
                }
                else {
                    EXPECTED("a ')'");
                    state = 102;
                }
                break;

            case 5:
                // required open curly brace
                TRACE_STATE;
                if(TOK_OCBRACE == TTYPE) {
                    consume_token();
                    state = 6;
                }
                else {
                    EXPECTED("a '{'");
                    state = 102;
                }
                break;

            case 6:
                // required first class item
                TRACE_STATE;
                if(NULL != (item = parse_class_item(pstate))) {
                    append_ptr_lst(list, item);
                    state = 7;
                }
                else {
                    EXPECTED("a valid class item");
                    state = 102;
                }
                break;

            case 7:
                // optional additional class items
                TRACE_STATE;
                if(NULL != (item = parse_class_item(pstate)))
                    append_ptr_lst(list, item);
                else
                    state = 8;
                break;

            case 8:
                // required close curly brace
                TRACE_STATE;
                if(TOK_CCBRACE == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else {
                    EXPECTED("a '}'");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_class_definition_t*)create_ast_node(AST_CLASS_DEFINITION);
                node->name = name;
                node->inher = inher;
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

