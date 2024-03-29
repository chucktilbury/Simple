/**
 * @file literals.c
 * 
 * @brief 
 * 
 * @author Charles Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 02-25-2024
 * @copyright Copyright (c) 2024
 */
#define USE_TRACE 1
#include "util.h"
#include "ast.h"

/**
 * @brief 
 * 
 *  scope_operator
 *      = 'private'
 *      / 'public'
 *      / 'protected'
 *      
 * @param node 
 * 
 */
void traverse_scope_operator(ast_scope_operator* node) {

    ENTER;
    RET;
}

/**
 * @brief 
 * 
 *  literal_type_name
 *      = 'float'
 *      / 'unsigned'
 *      / 'signed'
 *      / 'string'
 *      / 'boolean'
 *      / 'nothing'
 *      / 'list'
 *      / 'dict'
 *      / 'function'
 *      
 * @param node 
 * 
 */
void traverse_literal_type_name(ast_literal_type_name* node) {

    ENTER;
    RET;
}

/**
 * @brief 
 * 
 *  literal_value
 *      = LITERAL_FLOAT
 *      / LITERAL_UNSIGNED
 *      / LITERAL_SIGNED
 *      / LITERAL_BOOL
 *      
 * @param node 
 * 
 */
void traverse_literal_value(ast_literal_value* node) {

    ENTER;
    RET;
}

/**
 * @brief 
 * 
 *  type_name
 *      = literal_type_name
 *      / compound_name
 *      
 * @param node 
 * 
 */
void traverse_type_name(ast_type_name* node) {

    ENTER;
    RET;
}


