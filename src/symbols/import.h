/**
 * @file import.h
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _IMPORT_H_
#define _IMPORT_H_

#include "ast.h"
#include "symbols.h"

typedef struct {
    symbol_t sym;
    ast_import_statement_t* node;
} sym_import_t;

sym_import_t* create_import_symbol(ast_import_statement_t* node);

#endif /* _IMPORT_H_ */

