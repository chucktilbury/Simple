/**
 * @file local.h
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _LOCAL_H_
#define _LOCAL_H_

#include "ast.h"
#include "symbols.h"

typedef struct {
    symbol_t sym;
    AstNodeType node_type;
    ast_node_t* node;
} sym_local_t;

sym_local_t* create_local_symbol(ast_node_t* node);

#endif /* _LOCAL_H_ */

