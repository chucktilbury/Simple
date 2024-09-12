/**
 * @file class.h
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _CLASS_H_
#define _CLASS_H_

#include "ast.h"
#include "symbols.h"

typedef struct {
    symbol_t sym;
    ast_class_definition_t* node;
} sym_class_t;

sym_class_t* create_class_symbol(ast_class_definition_t* node);


#endif /* _CLASS_H_ */

