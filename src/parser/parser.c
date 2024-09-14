/**
 *
 * @file parser.c
 *
 * @brief Parser external interface implementation.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "parser.h"
#include "ast.h"
#include "common.h"
#include "tokens.h"

#include "cmdline.h"

parser_state_t* init_parser(void) {

    parser_state_t* pstate = _ALLOC_DS(parser_state_t);

    pstate->mode = create_link_list();
    ParserMode mode = PMODE_NORMAL;
    push_link_list(pstate->mode, _DUP_DS(&mode, ParserMode));

    pstate->scope = create_link_list();
    ScopeType scope = SCOPE_PRIVATE;
    push_link_list(pstate->scope, _DUP_DS(&scope, ScopeType));

    init_scanner(get_cmdline("list of files"));

    return pstate;
}

void push_parser_mode(parser_state_t* state, ParserMode mode) {

    push_link_list(state->mode, _DUP_DS(&mode, ParserMode));
}

ParserMode pop_parser_mode(parser_state_t* state) {

    ParserMode* mode = pop_link_list(state->mode);
    return *mode;
}

ParserMode get_parser_mode(parser_state_t* state) {

    ParserMode* mode = peek_link_list(state->mode);
    return *mode;
}

void push_parser_scope(parser_state_t* state, ScopeType scope) {

    push_link_list(state->scope, _DUP_DS(&scope, ScopeType));
}

void set_parser_scope(parser_state_t* state, ScopeType scope) {

    pop_link_list(state->scope);
    push_link_list(state->scope, _DUP_DS(&scope, ScopeType));
}

ScopeType pop_parser_scope(parser_state_t* state) {

    ScopeType* scope = pop_link_list(state->scope);
    return *scope;
}

ScopeType get_parser_scope(parser_state_t* state) {

    ScopeType* scope = peek_link_list(state->scope);
    return *scope;
}

ast_module_t* parse(void) {

    if(get_cmdline("tp"))
        PUSH_TRACE_STATE(TRACE_ON);
    else
        PUSH_TRACE_STATE(TRACE_OFF);

    parser_state_t* pstate = init_parser();

    ast_module_t* module = parse_module(pstate);

    POP_TRACE_STATE();

    return module;
}
