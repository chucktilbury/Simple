/**
 *
 * @file expr_operator.c
 *
 * @brief Parse grammar production operator.
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
 expr_operator
 *     : '+' | '-' | '*' | '/' | '%' | '|' | '&' | '!'
 *     | '==' | '!=' | '<' | '>' | '<=' | '>='
 *     | 'or' | 'and' | 'not' | 'equ' | 'nequ'
 *     | 'lt' | 'gt' | 'lte' | 'gte' | '(' | ')'
 *     ;
 *
 */
ast_expr_operator_t* parse_expr_operator(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_expr_operator_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    Token* tok = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE(state);
                switch(TTYPE) {
                    case TOK_PLUS:
                    case TOK_MINUS:
                    case TOK_STAR:
                    case TOK_SLASH:
                    case TOK_PERCENT:
                    case TOK_PIPE:
                    case TOK_AMPERSAND:
                    case TOK_BANG:
                    case TOK_EQUAL_EQUAL:
                    case TOK_BANG_EQUAL:
                    case TOK_OPBRACE:
                    case TOK_CPBRACE:
                    case TOK_OPBRACE_EQUAL:
                    case TOK_CPBRACE_EQUAL:
                    case TOK_OR:
                    case TOK_AND:
                    case TOK_NOT:
                    case TOK_EQU:
                    case TOK_NEQU:
                    case TOK_LT:
                    case TOK_GT:
                    case TOK_LTE:
                    case TOK_GTE:
                    case TOK_OPAREN:
                    case TOK_CPAREN:
                        tok = copy_token(get_token());
                        state = 100;
                        break;
                    default:
                        state = 101;
                        break;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_expr_operator_t*)create_ast_node(AST_EXPR_OPERATOR);
                node->oper = tok;
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

