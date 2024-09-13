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
#include "cmdline.h"

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
    (type == AST_CLASS_BODY)? sizeof(ast_class_body_t) :
    (type == AST_CLASS_BODY_ITEM)? sizeof(ast_class_body_item_t) :
    (type == AST_CLASS_INHERITANCE_ITEM)? sizeof(ast_class_inheritance_item_t) :
    (type == AST_CLASS_INHERITANCE_LIST)? sizeof(ast_class_inheritance_list_t) :
    (type == AST_FUNCTION_DECLARATION)? sizeof(ast_function_declaration_t) :
    (type == AST_CREATE_DECLARATION)? sizeof(ast_create_declaration_t) :
    (type == AST_DESTROY_DECLARATION)? sizeof(ast_destroy_declaration_t) :
    (type == AST_FUNCTION_DEFINITION)? sizeof(ast_function_definition_t) :
    (type == AST_CREATE_NAME)? sizeof(ast_create_name_t) :
    (type == AST_CREATE_DEFINITION)? sizeof(ast_create_definition_t) :
    (type == AST_DESTROY_NAME)? sizeof(ast_destroy_name_t) :
    (type == AST_DESTROY_DEFINITION)? sizeof(ast_destroy_definition_t) :
    (type == AST_FUNCTION_BODY)? sizeof(ast_function_body_t) :
    (type == AST_FUNCTION_BODY_ELEMENT)? sizeof(ast_function_body_element_t) :
    (type == AST_LOOP_BODY)? sizeof(ast_loop_body_t) :
    (type == AST_LOOP_BODY_ELEMENT)? sizeof(ast_loop_body_element_t) :
    (type == AST_ASSIGN_EQ_ITEM)? sizeof(ast_assign_eq_item_t) :
    (type == AST_ASSIGN_INC_ITEM)? sizeof(ast_assign_inc_item_t) :
    (type == AST_ASSIGNMENT)? sizeof(ast_assignment_t) :
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
    (type == AST_ALIAS_DEFINITION)? sizeof(ast_alias_definition_t) :
    0; // error if we reach here
}

ast_node_t* create_ast_node(AstNodeType type) {

    ast_node_t* node = _ALLOC(node_size(type));
    node->type = type;
    return node;
}

void traverse_ast(ast_module_t* node, AstFuncPtr pre, AstFuncPtr post) {

    if(get_cmdline("ta"))
        PUSH_TRACE_STATE(TRACE_ON);
    else
        PUSH_TRACE_STATE(TRACE_OFF);

    traverse_module(node, pre, post);

    POP_TRACE_STATE();
}

AstNodeType nterm_type(ast_node_t* node) {

    return node->type;
}

const char* nterm_type_to_str(ast_node_t* node) {

    AstNodeType type = nterm_type(node);

    return (type == AST_MODULE)? "AST_MODULE" :
        (type == AST_MODULE_ITEM)? "AST_MODULE_ITEM" :
        (type == AST_START_DEFINITION)? "AST_START_DEFINITION" :
        (type == AST_IMPORT_STATEMENT)? "AST_IMPORT_STATEMENT" :
        (type == AST_INCLUDE_STATEMENT)? "AST_INCLUDE_STATEMENT" :
        (type == AST_NAMESPACE_ITEM)? "AST_NAMESPACE_ITEM" :
        (type == AST_SCOPE_OPERATOR)? "AST_SCOPE_OPERATOR" :
        (type == AST_LITERAL_TYPE_NAME)? "AST_LITERAL_TYPE_NAME" :
        (type == AST_TYPE_NAME)? "AST_TYPE_NAME" :
        (type == AST_TYPE_NAME_LIST)? "AST_TYPE_NAME_LIST" :
        (type == AST_FORMATTED_STRG)? "AST_FORMATTED_STRG" :
        (type == AST_STRING_LITERAL)? "AST_STRING_LITERAL" :
        (type == AST_LITERAL_VALUE)? "AST_LITERAL_VALUE" :
        (type == AST_VAR_DECL)? "AST_VAR_DECL" :
        (type == AST_VAR_DECL_LIST)? "AST_VAR_DECL_LIST" :
        (type == AST_FUNCTION_ASSIGNMENT)? "AST_FUNCTION_ASSIGNMENT" :
        (type == AST_ASSIGNMENT_ITEM)? "AST_ASSIGNMENT_ITEM" :
        (type == AST_VAR_DEFINITION)? "AST_VAR_DEFINITION" :
        (type == AST_LIST_INIT_STR)? "AST_LIST_INIT_STR" :
        (type == AST_LIST_INIT_ELEMENT)? "AST_LIST_INIT_ELEMENT" :
        (type == AST_LIST_INIT)? "AST_LIST_INIT" :
        (type == AST_ARRAY_PARAM_ITEM)? "AST_ARRAY_PARAM_ITEM" :
        (type == AST_ARRAY_PARAM)? "AST_ARRAY_PARAM" :
        (type == AST_ARRAY_PARAM_LIST)? "AST_ARRAY_PARAM_LIST" :
        (type == AST_ARRAY_REFERENCE)? "AST_ARRAY_REFERENCE" :
        (type == AST_FUNCTION_REFERENCE)? "AST_FUNCTION_REFERENCE" :
        (type == AST_CREATE_REFERENCE)? "AST_CREATE_REFERENCE" :
        (type == AST_DESTROY_REFERENCE)? "AST_DESTROY_REFERENCE" :
        (type == AST_COMPOUND_NAME)? "AST_COMPOUND_NAME" :
        (type == AST_COMPOUND_NAME_LIST)? "AST_COMPOUND_NAME_LIST" :
        (type == AST_COMPOUND_REF_ITEM)? "AST_COMPOUND_REF_ITEM" :
        (type == AST_COMPOUND_REFERENCE)? "AST_COMPOUND_REFERENCE" :
        (type == AST_CAST_STATEMENT)? "AST_CAST_STATEMENT" :
        (type == AST_EXPRESSION)? "AST_EXPRESSION" :
        (type == AST_EXPR_OPERATOR)? "AST_EXPR_OPERATOR" :
        (type == AST_EXPR_OPERAND)? "AST_EXPR_OPERAND" :
        (type == AST_EXPRESSION_LIST)? "AST_EXPRESSION_LIST" :
        (type == AST_NAMESPACE_DEFINITION)? "AST_NAMESPACE_DEFINITION" :
        (type == AST_CLASS_DEFINITION)? "AST_CLASS_DEFINITION" :
        (type == AST_CLASS_BODY_ITEM)? "AST_CLASS_BODY_ITEM" :
        (type == AST_CLASS_BODY)? "AST_CLASS_BODY" :
        (type == AST_CLASS_INHERITANCE_ITEM)? "AST_CLASS_INHERITANCE_ITEM" :
        (type == AST_CLASS_INHERITANCE_LIST)? "AST_CLASS_INHERITANCE_LIST" :
        (type == AST_FUNCTION_DECLARATION)? "AST_FUNCTION_DECLARATION" :
        (type == AST_CREATE_DECLARATION)? "AST_CREATE_DECLARATION" :
        (type == AST_DESTROY_DECLARATION)? "AST_DESTROY_DECLARATION" :
        (type == AST_FUNCTION_DEFINITION)? "AST_FUNCTION_DEFINITION" :
        (type == AST_CREATE_NAME)? "AST_CREATE_NAME" :
        (type == AST_CREATE_DEFINITION)? "AST_CREATE_DEFINITION" :
        (type == AST_DESTROY_NAME)? "AST_DESTROY_NAME" :
        (type == AST_DESTROY_DEFINITION)? "AST_DESTROY_DEFINITION" :
        (type == AST_FUNCTION_BODY)? "AST_FUNCTION_BODY" :
        (type == AST_FUNCTION_BODY_ELEMENT)? "AST_FUNCTION_BODY_ELEMENT" :
        (type == AST_LOOP_BODY)? "AST_LOOP_BODY" :
        (type == AST_LOOP_BODY_ELEMENT)? "AST_LOOP_BODY_ELEMENT" :
        (type == AST_ASSIGN_EQ_ITEM)? "AST_ASSIGN_EQ_ITEM" :
        (type == AST_ASSIGN_INC_ITEM)? "AST_ASSIGN_INC_ITEM" :
        (type == AST_ASSIGNMENT)? "AST_ASSIGNMENT" :
        (type == AST_FUNCTION_BODY_ELEMENT)? "AST_FUNCTION_BODY_ELEMENT" :
        (type == AST_BREAK_STATEMENT)? "AST_BREAK_STATEMENT" :
        (type == AST_CONTINUE_STATEMENT)? "AST_CONTINUE_STATEMENT" :
        (type == AST_YIELD_STATEMENT)? "AST_YIELD_STATEMENT" :
        (type == AST_TYPE_STATEMENT)? "AST_TYPE_STATEMENT" :
        (type == AST_RETURN_STATEMENT)? "AST_RETURN_STATEMENT" :
        (type == AST_RAISE_STATEMENT)? "AST_RAISE_STATEMENT" :
        (type == AST_TRACE_STATEMENT)? "AST_TRACE_STATEMENT" :
        (type == AST_PRINT_STATEMENT)? "AST_PRINT_STATEMENT" :
        (type == AST_EXIT_STATEMENT)? "AST_EXIT_STATEMENT" :
        (type == AST_WHILE_DEFINITION)? "AST_WHILE_DEFINITION" :
        (type == AST_ALIAS_DEFINITION)? "AST_ALIAS_DEFINITION" :
        (type == AST_WHILE_CLAUSE)? "AST_WHILE_CLAUSE" :
        (type == AST_DO_CLAUSE)? "AST_DO_CLAUSE" :
        (type == AST_FOR_CLAUSE)? "AST_FOR_CLAUSE" :
        (type == AST_IF_CLAUSE)? "AST_IF_CLAUSE" :
        (type == AST_ELSE_CLAUSE)? "AST_ELSE_CLAUSE" :
        (type == AST_FINAL_ELSE_CLAUSE)? "AST_FINAL_ELSE_CLAUSE" :
        (type == AST_TRY_CLAUSE)? "AST_TRY_CLAUSE" :
        (type == AST_EXCEPT_CLAUSE)? "AST_EXCEPT_CLAUSE" :
        (type == AST_FINAL_CLAUSE)? "AST_FINAL_CLAUSE" : "UNKNOWN";

}

