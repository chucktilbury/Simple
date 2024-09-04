/**
 *
 * @file parser.c
 *
 * @brief Parser external interface implementation.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "ast.h"
#include "parser.h"
#include "tokens.h"

#include "cmdline.h"

parser_state_t* init_parser(void) {

    parser_state_t* pstate = _ALLOC_DS(parser_state_t);
    pstate->mode = create_link_list();
    ParserMode mode = PMODE_NORMAL;
    push_link_list(pstate->mode, _DUP_DS(&mode, ParserMode));

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

ParserMode peek_parser_mode(parser_state_t* state) {

    ParserMode* mode = peek_link_list(state->mode);
    return *mode;
}

ast_module_t* parse(void) {

    parser_state_t* pstate = init_parser();

    ast_module_t* module = parse_module(pstate);
    return module;
}

