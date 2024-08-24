/**
 *
 * @file final_clause.c
 *
 * @brief AST implementation.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

static size_t node_size(AstNodeType type) {

    return
    (type == AST_MODULE)? sizeof(ast_module_t) :
    (type == AST_MODULE_ITEM)? sizeof(ast_module_item_t) :
    (type == AST_START_DEFINITION)? sizeof(ast_start_definition_t) :
    (type == AST_IMPORT_STATEMENT)? sizeof(ast_import_statement_t) :
    (type == AST_INCLUDE_STATEMENT)? sizeof(ast_include_statement_t) :
    (type == AST_NAMESPACE_ITEM)? sizeof(ast_namespace_item_t) :
    (type == AST_SCOPE_OPERATOR)? sizeof(ast_scope_operator_t) :
    (type == AST_LITERAL_TYPE_NAME)? sizeof(ast_literal_type_name_t) :
    (type == AST_TYPE_NAME)? sizeof(ast_type_name_t) :
    (type == AST_TYPE_NAME_LIST)? sizeof(ast_type_name_list_t) :
    (type == AST_FORMATTED_STRG)? sizeof(ast_formatted_strg_t) :
    (type == AST_STRING_LITERAL)? sizeof(ast_string_literal_t) :
    (type == AST_LITERAL_VALUE)? sizeof(ast_literal_value_t) :
    (type == AST_VAR_DECL)? sizeof(ast_var_decl_t) :
    (type == AST_VAR_DECL_LIST)? sizeof(ast_var_decl_list_t) :
    (type == AST_FUNCTION_ASSIGNMENT)? sizeof(ast_function_assignment_t) :
    (type == AST_ASSIGNMENT_ITEM)? sizeof(ast_assignment_item_t) :
    (type == AST_VAR_DEFINITION)? sizeof(ast_var_definition_t) :
    (type == AST_LIST_INIT_STR)? sizeof(ast_list_init_str_t) :
    (type == AST_LIST_INIT_ELEMENT)? sizeof(ast_list_init_element_t) :
    (type == AST_LIST_INIT)? sizeof(ast_list_init_t) :
    (type == AST_ARRAY_PARAM_ITEM)? sizeof(ast_array_param_item_t) :
    (type == AST_ARRAY_PARAM)? sizeof(ast_array_param_t) :
    (type == AST_ARRAY_PARAM_LIST)? sizeof(ast_array_param_list_t) :
    (type == AST_ARRAY_REFERENCE)? sizeof(ast_array_reference_t) :
    (type == AST_FUNCTION_REFERENCE)? sizeof(ast_function_reference_t) :
    (type == AST_CREATE_REFERENCE)? sizeof(ast_create_reference_t) :
    (type == AST_DESTROY_REFERENCE)? sizeof(ast_destroy_reference_t) :
    (type == AST_COMPOUND_NAME)? sizeof(ast_compound_name_t) :
    (type == AST_COMPOUND_NAME_LIST)? sizeof(ast_compound_name_list_t) :
    (type == AST_COMPOUND_REF_ITEM)? sizeof(ast_compound_ref_item_t) :
    (type == AST_COMPOUND_REFERENCE)? sizeof(ast_compound_reference_t) :
    (type == AST_CAST_STATEMENT)? sizeof(ast_cast_statement_t) :
    (type == AST_EXPRESSION)? sizeof(ast_expression_t) :
    (type == AST_EXPR_OPERATOR)? sizeof(ast_expr_operator_t) :
    (type == AST_EXPR_OPERAND)? sizeof(ast_expr_operand_t) :
    (type == AST_EXPRESSION_LIST)? sizeof(ast_expression_list_t) :
    (type == AST_NAMESPACE_DEFINITION)? sizeof(ast_namespace_definition_t) :
    (type == AST_CLASS_DEFINITION)? sizeof(ast_class_definition_t) :
    (type == AST_CLASS_ITEM)? sizeof(ast_class_item_t) :
    (type == AST_FUNCTION_DECLARATION)? sizeof(ast_function_declaration_t) :
    (type == AST_CREATE_DECLARATION)? sizeof(ast_create_declaration_t) :
    (type == AST_DESTROY_DECLARATION)? sizeof(ast_destroy_declaration_t) :
    (type == AST_FUNCTION_DEFINITION)? sizeof(ast_function_definition_t) :
    (type == AST_CREATE_NAME)? sizeof(ast_create_name_t) :
    (type == AST_CREATE_DEFINITION)? sizeof(ast_create_definition_t) :
    (type == AST_DESTROY_NAME)? sizeof(ast_destroy_name_t) :
    (type == AST_DESTROY_DEFINITION)? sizeof(ast_destroy_definition_t) :
    (type == AST_FUNCTION_BODY)? sizeof(ast_function_body_t) :
    (type == AST_ASSIGN_EQ_ITEM)? sizeof(ast_assign_eq_item_t) :
    (type == AST_ASSIGN_INC_ITEM)? sizeof(ast_assign_inc_item_t) :
    (type == AST_ASSIGNMENT)? sizeof(ast_assignment_t) :
    (type == AST_FUNCTION_BODY_ELEMENT)? sizeof(ast_function_body_element_t) :
    (type == AST_BREAK_STATEMENT)? sizeof(ast_break_statement_t) :
    (type == AST_CONTINUE_STATEMENT)? sizeof(ast_continue_statement_t) :
    (type == AST_YIELD_STATEMENT)? sizeof(ast_yield_statement_t) :
    (type == AST_TYPE_STATEMENT)? sizeof(ast_type_statement_t) :
    (type == AST_RETURN_STATEMENT)? sizeof(ast_return_statement_t) :
    (type == AST_RAISE_STATEMENT)? sizeof(ast_raise_statement_t) :
    (type == AST_TRACE_STATEMENT)? sizeof(ast_trace_statement_t) :
    (type == AST_PRINT_STATEMENT)? sizeof(ast_print_statement_t) :
    (type == AST_EXIT_STATEMENT)? sizeof(ast_exit_statement_t) :
    (type == AST_WHILE_DEFINITION)? sizeof(ast_while_definition_t) :
    (type == AST_WHILE_CLAUSE)? sizeof(ast_while_clause_t) :
    (type == AST_DO_CLAUSE)? sizeof(ast_do_clause_t) :
    (type == AST_FOR_CLAUSE)? sizeof(ast_for_clause_t) :
    (type == AST_IF_CLAUSE)? sizeof(ast_if_clause_t) :
    (type == AST_ELSE_CLAUSE)? sizeof(ast_else_clause_t) :
    (type == AST_FINAL_ELSE_CLAUSE)? sizeof(ast_final_else_clause_t) :
    (type == AST_TRY_CLAUSE)? sizeof(ast_try_clause_t) :
    (type == AST_EXCEPT_CLAUSE)? sizeof(ast_except_clause_t) :
    (type == AST_FINAL_CLAUSE)? sizeof(ast_final_clause_t) :
    0; // error if we reach here
}

ast_node_t* create_ast_node(AstNodeType type) {

    ast_node_t* node = _ALLOC(node_size(type));
    node->type = type;
    return node;
}

void traverse_ast(ast_module_t* node, AstFuncPtr pre, AstFuncPtr post) {

    traverse_module(node, pre, post);
}

