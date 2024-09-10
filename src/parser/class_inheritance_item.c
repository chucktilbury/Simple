/**
 * @file class_inheritance_item.c
 * @author your name (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "common.h"
#include "tokens.h"
#include "errors.h"
#include "parser.h"

/**
 * @brief Parse the class inheritance item
 * 
 * class_inheritance_item
 *     : (scope_operator)? compound_name 'as' IDENT
 *     ;
 * 
 * @param pstate 
 * @return ast_class_inheritance_item_t* 
 */
ast_class_inheritance_item_t* parse_class_inheritance_item(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_class_inheritance_item_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_scope_operator_t* scope = NULL; // defaults to private
    Token* ident = NULL;
    ast_compound_name_t* name = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                scope = parse_scope_operator(pstate);
                state = 1;
                break;

            case 1:
                TRACE_STATE;
                if(NULL == (name = parse_compound_name(pstate))) {
                    if(scope != NULL) {
                        EXPECTED("a compound name");
                        state = 102;
                    }
                    else 
                        state = 101;
                }
                else 
                    state = 2;
                break;

            case 2:
                TRACE_STATE;
                if(TOK_AS == TTYPE) {
                    consume_token();
                    state = 3;
                }
                else {
                    EXPECTED("an 'as' keyword");
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
                node = (ast_class_inheritance_item_t*)create_ast_node(AST_CLASS_INHERITANCE_ITEM);
                // default scope is always PRIVATE.
                if(scope == NULL) {
                    scope = (ast_scope_operator_t*)create_ast_node(AST_SCOPE_OPERATOR);
                    scope->tok = copy_token(get_token());
                    scope->tok->str = create_string("private");
                    scope->tok->type = TOK_PRIVATE;
                    scope->tok->line_no = 0;
                    scope->tok->col_no = 0;
                    scope->tok->fname = _DUP_STR("internal");
                }
                node->scope = scope; 
                node->ident = ident;
                node->name = name;
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


