/**
 * @file func.c
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
 *  function_reference
 *      = compound_name
 *          ( expression_list )+
 *          '(' ( compound_name ( ',' compound_name )* )+ ')'
 *      
 * @return ast_function_reference* 
 * 
 */
ast_function_reference* parse_function_reference() {

    ENTER;
    ast_function_reference* node = NULL;

    RETV(node);
}

/**
 * @brief 
 * 
 *  func_decl
 *      = 'function' SYMBOL 
 *          '(' ( var_decl_list )* ')' 
 *          '(' ( var_decl_list )* ')'
 *      / 'create' 
 *          '(' ( var_decl_list )* ')'
 *      / 'destroy'
 *      
 * @return ast_func_decl* 
 * 
 */
ast_func_decl* parse_func_decl() {

    ENTER;
    ast_func_decl* node = NULL;

    RETV(node);
}

/**
 * @brief 
 * 
 *  func_definition
 *      = 'function' compound_name
 *          '(' ( var_decl_list )* ')' 
 *          '(' ( var_decl_list )* ')' function_body
 *      / 'function' compound_name '.' 'create' 
 *          '(' ( var_decl_list )* ')' function_body
 *      / 'function' compound_name '.' 'destroy' function_body
 *      
 * @return ast_func_definition* 
 * 
 */
ast_func_definition* parse_func_definition() {

    ENTER;
    ast_func_definition* node = NULL;

    RETV(node);
}

/**
 * @brief 
 * 
 *  function_body
 *      = '{' ( function_body_element )* '}'
 *      
 * @return ast_function_body* 
 * 
 */
ast_function_body* parse_function_body() {

    ENTER;
    ast_function_body* node = NULL;

    RETV(node);
}

/**
 * @brief 
 * 
 *  start_function
 *      = 'start' function_body
 *      
 * @return ast_start_function* 
 * 
 */
ast_start_function* parse_start_function() {

    ENTER;
    ast_start_function* node = NULL;

    RETV(node);
}


