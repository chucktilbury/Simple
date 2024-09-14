/**
 * @file namespace.h
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-09-12
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _NAMESPACE_H_
#define _NAMESPACE_H_

#include "ast.h"
#include "symbols.h"

typedef struct {
    symbol_t sym;
    ast_namespace_definition_t* node;
} sym_namespace_t;

sym_namespace_t* create_namespace_symbol(ast_namespace_definition_t* node);

#endif /* _NAMESPACE_H_ */
