/**
 *
 * @file expression.c
 *
 * @brief Parse grammar production expression. The expressions are parsed
 * using the shunting yard algorithm and the productions in the grammar are
 * not being used.
 *
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "tokens.h"
#include "errors.h"
#include "parser.h"

// This is used to detect unary operators. If it is true, and an operator is
// found then it could be unary. Only the '!' and the '-' can be unary, all
// others are errors if the flag is set.
static bool flag = true;

/**
 * @brief Get the oper type object
 *
 * @param oper
 * @return TokenType
 */
static inline TokenType get_oper_type(ast_expr_operator_t* oper) {

    return oper->oper->type;
}

/**
 * @brief Get the precedence of an operator
 *
 * @param oper
 * @return int
 */
static int get_prec(ast_expr_operator_t* oper) {

    int prec = 0;

    switch(get_oper_type(oper)) {
        case TOK_OR:
        case TOK_PIPE:
            prec = 10;
            break;
        case TOK_AND:
        case TOK_AMPERSAND:
            prec = 20;
            break;
        case TOK_EQU:
        case TOK_NEQU:
        case TOK_EQUAL_EQUAL:
        case TOK_BANG_EQUAL:
            prec = 30;
            break;
        case TOK_LTE:
        case TOK_GTE:
        case TOK_OPBRACE_EQUAL:
        case TOK_CPBRACE_EQUAL:
        case TOK_LT:
        case TOK_GT:
        case TOK_OPBRACE:
        case TOK_CPBRACE:
            prec = 40;
            break;
        case TOK_PLUS:
        case TOK_MINUS:
            prec = 50;
            break;
        case TOK_SLASH:
        case TOK_STAR:
        case TOK_PERCENT:
            prec = 60;
            break;
        case TOK_CARAT:
            prec = 70;
            break;
        case TOK_NOT:
        case TOK_BANG:
        case TOK_UNARY_MINUS:
            prec = 80;
            break;
        default:
            // no precedence
            TRACE("no precedence");
            prec = 0;
            break;
    }
    TRACE("prec: %d", prec);
    return prec;
}

/**
 * @brief Get the assoc object
 *
 * @param oper
 * @return bool
 */
static bool get_assoc(ast_expr_operator_t* oper) {

    switch(get_oper_type(oper)) {
        case TOK_NOT:
        case TOK_BANG:
        case TOK_UNARY_MINUS:
        case TOK_CARAT:
            return false;   // right to left
        default:
            return true;    // left to right
    }
}

/**
 * @brief Edit the operator for unary condition and check for invalid unary.
 *
 * @param oper
 * @return ast_expr_operator_t*
 */
static ast_expr_operator_t* check_operator(ast_expr_operator_t* oper) {

    switch(get_oper_type(oper)) {
        case TOK_CPAREN:
            flag = false;
            break;
        case TOK_MINUS:
            if(flag)
                oper->oper->type = TOK_UNARY_MINUS;
            break;
        case TOK_BANG:
        case TOK_NOT:
            if(flag)
                oper->oper->type = TOK_UNARY_NOT;
            break;
        default:
            if(flag) {
                SYNTAX("the \"%s\" operator cannot be unary",
                    token_type_to_str(get_oper_type(oper)));
                return NULL;
            }
    }

    if(!flag)
        flag = true;

    return oper;
}

/**
 * @brief Parse an expression using the shunting yard algorithm.
 *
 * Shunting yard pseudo code:
 *
 * While the token read is an operator or an operand:
 *   If it's a operand add it to output queue
 *   If it's an operator:
 *     If the operator is right associative:
 *       While there's an operator on the stack with equal or greater precedence:
 *         Pop operators from the stack onto the output queue
 *     Else:
 *       While there's an operator on the stack with greater precedence:
 *         Pop operators from the stack onto the output queue
 *     Push the current operator onto the stack
 *   If it's a left bracket push it onto the operator stack
 *   If it's a right bracket
 *     While there's not a left bracket at the top of the stack:
 *       Pop operators from the stack onto the output queue.
 *     Pop the left bracket from the stack and discard it
 * While there are operators on the stack, pop them to the queue
 *
 * @return ast_expression_t*
 */
ast_expression_t* parse_expression(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    PtrLst* stack = create_ptr_lst();
    PtrLst* queue = create_ptr_lst();
    ast_expr_operator_t* operator;
    ast_expr_operand_t* operand;
    flag = true;

    ast_expression_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE(state);
                if(NULL != (operand = parse_expr_operand(pstate))) {
                    flag = false;
                    state = 1;
                }
                else if(NULL != (operator = parse_expr_operator(pstate))) {
                    if(NULL == check_operator(operator))
                        state = 102;
                    else
                        state = 2;
                }
                else {
                    // not a match
                    state = 101;
                }
                break;

            case 1:
                // dispatch operator
                TRACE_STATE(state);
                append_ptr_lst(queue, operand);
                state = 0;
                break;

            case 2:
                // find the associativity
                TRACE_STATE(state);
                if(TOK_OPAREN == get_oper_type(operator)) {
                    // open paren
                    push_ptr_lst(stack, operator);
                    state = 0;
                }
                else if(TOK_CPAREN == get_oper_type(operator)) {
                    // close paren
                    state = 5;
                }
                else {
                    // get associativity
                    if(get_assoc(operator))
                        state = 3; // operator is left associative
                    else
                        state = 4; // operator it right associative
                }
                break;

            case 3:
                TRACE_STATE(state);
                while(get_prec(peek_ptr_lst(stack)) > get_prec(operator)) {
                    // if we find an OPAREN, then imbalanced parens
                    ast_expr_operator_t* tmp = pop_ptr_lst(stack);
                    if(TOK_OPAREN == get_oper_type(tmp)) {
                        SYNTAX("imbalanced parenthesis");
                        state = 102;
                        goto case_3_error;
                    }
                    append_ptr_lst(queue, tmp);
                }
                push_ptr_lst(stack, operator);
                state = 6;
                case_3_error:
                break;

            case 4:
                TRACE_STATE(state);
                while(get_prec(peek_ptr_lst(stack)) >= get_prec(operator)) {
                    // if we find an OPAREN, then imbalanced parens
                    ast_expr_operator_t* tmp = pop_ptr_lst(stack);
                    if(TOK_OPAREN == get_oper_type(tmp)) {
                        SYNTAX("imbalanced parenthesis");
                        state = 102;
                        goto case_4_error;
                    }
                    append_ptr_lst(queue, tmp);
                }
                push_ptr_lst(stack, operator);
                state = 6;
                case_4_error:
                break;

            case 5:
                // handle close paren
                TRACE_STATE(state);
                while(TOK_OPAREN != get_oper_type(peek_ptr_lst(stack))) {
                    // if we run out of tokens, then parens are imbalanced
                    ast_expr_operator_t* tmp = pop_ptr_lst(stack);
                    if(NULL == tmp) {
                        SYNTAX("imbalanced parenthesis");
                        state = 102;
                        goto case_5_error;
                    }
                }
                pop_ptr_lst(stack); // discard the OPAREN
                state = 6;
                case_5_error:
                break;

            case 6:
                // repeat the token read
                TRACE_STATE(state);
                if(NULL != (operand = parse_expr_operand(pstate))) {
                    flag = false;
                    state = 1;
                }
                else if(NULL != (operator = parse_expr_operator(pstate))) {
                    if(NULL == check_operator(operator))
                        state = 102;
                    else
                        state = 2;
                }
                else {
                    // not a match marks end of the production
                    state = 100;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                while(NULL != peek_ptr_lst(stack)) {
                    ast_expr_operator_t* tmp = pop_ptr_lst(stack);
                    if(TOK_OPAREN == get_oper_type(tmp)) {
                        SYNTAX("imbalanced parenthesis");
                        state = 102;
                        goto case_100_error;
                    }
                    append_ptr_lst(queue, tmp);
                }

                node = (ast_expression_t*)create_ast_node(AST_EXPRESSION);
                node->list = queue;
                finished = true;
                case_100_error:
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

