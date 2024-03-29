/**
 * @file string.c
 * 
 * @brief 
 * 
 * @author Charles Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 02-26-2024
 * @copyright Copyright (c) 2024
 */
#define USE_TRACE 1
#include "util.h"
#include "parse.h"

/**
 * @brief 
 * 
 *  string_literal
 *      = LITERAL_SSTRG
 *      / formatted_strg
 *      
 * @return ast_string_literal* 
 * 
 */
ast_string_literal* parse_string_literal() {

    ENTER;
    ast_string_literal* node = NULL;

    RETV(node);
}

/**
 * @brief 
 * 
 *  string_expr_item
 *      = string_literal
 *      / compound_reference
 *      / literal_value
 *      
 * @return ast_string_expr_item* 
 * 
 */
ast_string_expr_item* parse_string_expr_item() {

    ENTER;
    ast_string_expr_item* node = NULL;

    RETV(node);
}

/**
 * @brief 
 * 
 *  string_expr
 *      = string_expr_item ( '+' string_expr_item )*
 *      
 * @return ast_string_expr* 
 * 
 */
ast_string_expr* parse_string_expr() {

    ENTER;
    ast_string_expr* node = NULL;

    RETV(node);
}


