/**
 * @file function.h
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "ast.h"
#include "symbols.h"

typedef struct {
    symbol_t sym;
    ast_function_definition_t* node;
} sym_function_t;

sym_function_t* create_function_symbol(ast_function_definition_t* node);

#endif /* _FUNCTION_H_ */

