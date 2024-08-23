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
#include "errors.h"

void recover_error(void) {

    //SYNTAX("Syntax error");
    fprintf(stderr, "Syntax Error\n");
    exit(1);
}

ast_module_t* parse(void) {

    parser_state_t* pstate = _ALLOC_DS(parser_state_t);
    pstate->mode = 0;
    ast_module_t* module = parse_module(pstate);
    return module;
}

