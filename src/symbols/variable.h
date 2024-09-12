/**
 * @file variable.h
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include "ast.h"
#include "symbols.h"

typedef struct {
    symbol_t sym;
    ast_var_definition_t* node;
} sym_variable_t;

sym_variable_t* create_variable_symbol(ast_var_definition_t* node);

#endif /* _VARIABLE_H_ */

