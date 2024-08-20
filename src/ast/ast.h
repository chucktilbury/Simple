
#ifndef _AST_H_
#define _AST_H_

typedef enum {
    AST_MODULE,
    AST_MODULE_ITEM,
    AST_START_DEFINITION,
    AST_IMPORT_STATEMENT,
    AST_INCLUDE_STATEMENT,
    AST_NAMESPACE_ITEM,
    AST_SCOPE_OPERATOR,
    AST_LITERAL_TYPE_NAME,
    AST_TYPE_NAME,
    AST_TYPE_NAME_LIST,
    AST_FORMATTED_STRG,
    AST_STRING_LITERAL,
    AST_LITERAL_VALUE,
    AST_VAR_DECL,
    AST_VAR_DECL_LIST,
    AST_FUNCTION_ASSIGNMENT,
    AST_ASSIGNMENT_ITEM,
    AST_VAR_DEFINITION,
    AST_LIST_INIT_STR,
    AST_LIST_INIT_ELEMENT,
    AST_LIST_INIT,
    AST_ARRAY_PARAM_ITEM,
    AST_ARRAY_PARAM,
    AST_ARRAY_PARAM_LIST,
    AST_ARRAY_REFERENCE,
    AST_FUNCTION_REFERENCE,
    AST_CREATE_REFERENCE,
    AST_DESTROY_REFERENCE,
    AST_COMPOUND_NAME,
    AST_COMPOUND_NAME_LIST,
    AST_COMPOUND_REF_ITEM,
    AST_COMPOUND_REFERENCE,
    AST_CAST_STATEMENT,
    AST_EXPRESSION,
    AST_EXPR_OR,
    AST_EXPR_AND,
    AST_EXPR_EQUALITY,
    AST_EXPR_COMPARE,
    AST_EXPR_TERM,
    AST_EXPR_FACTOR,
    AST_EXPR_UNARY,
    AST_EXPR_PRIMARY,
    AST_EXPRESSION_LIST,
    AST_NAMESPACE_DEFINITION,
    AST_CLASS_DEFINITION,
    AST_CLASS_ITEM,
    AST_FUNCTION_DECLARATION,
    AST_CREATE_DECLARATION,
    AST_DESTROY_DECLARATION,
    AST_FUNCTION_DEFINITION,
    AST_CREATE_NAME,
    AST_CREATE_DEFINITION,
    AST_DESTROY_NAME,
    AST_DESTROY_DEFINITION,
    AST_FUNCTION_BODY,
    AST_ASSIGN_EQ_ITEM,
    AST_ASSIGN_INC_ITEM,
    AST_ASSIGNMENT,
    AST_FUNCTION_BODY_ELEMENT,
    AST_BREAK_STATEMENT,
    AST_CONTINUE_STATEMENT,
    AST_YIELD_STATEMENT,
    AST_TYPE_STATEMENT,
    AST_RETURN_STATEMENT,
    AST_RAISE_STATEMENT,
    AST_TRACE_STATEMENT,
    AST_PRINT_STATEMENT,
    AST_EXIT_STATEMENT,
    AST_WHILE_DEFINITION,
    AST_WHILE_CLAUSE,
    AST_DO_CLAUSE,
    AST_FOR_CLAUSE,
    AST_IF_CLAUSE,
    AST_ELSE_CLAUSE,
    AST_FINAL_ELSE_CLAUSE,
    AST_TRY_CLAUSE,
    AST_EXCEPT_CLAUSE,
    AST_FINAL_CLAUSE,
} AstNodeType;

typedef struct _ast_node_ {
    AstNodeType type;
} AstNode;

/*
    Production being parsed:

 */
typedef struct _ast_module_ {
    AstNode node;

} ast_module_t;

/*
    Production being parsed:

 */
typedef struct _ast_module_item_ {
    AstNode node;

} ast_module_item_t;

/*
    Production being parsed:

 */
typedef struct _ast_start_definition_ {
    AstNode node;

} ast_start_definition_t;

/*
    Production being parsed:

 */
typedef struct _ast_import_statement_ {
    AstNode node;

} ast_import_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_include_statement_ {
    AstNode node;

} ast_include_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_namespace_item_ {
    AstNode node;

} ast_namespace_item_t;

/*
    Production being parsed:

 */
typedef struct _ast_scope_operator_ {
    AstNode node;

} ast_scope_operator_t;

/*
    Production being parsed:

 */
typedef struct _ast_literal_type_name_ {
    AstNode node;

} ast_literal_type_name_t;

/*
    Production being parsed:

 */
typedef struct _ast_type_name_ {
    AstNode node;

} ast_type_name_t;

/*
    Production being parsed:

 */
typedef struct _ast_type_name_list_ {
    AstNode node;

} ast_type_name_list_t;

/*
    Production being parsed:

 */
typedef struct _ast_formatted_strg_ {
    AstNode node;

} ast_formatted_strg_t;

/*
    Production being parsed:

 */
typedef struct _ast_string_literal_ {
    AstNode node;

} ast_string_literal_t;

/*
    Production being parsed:

 */
typedef struct _ast_literal_value_ {
    AstNode node;

} ast_literal_value_t;

/*
    Production being parsed:

 */
typedef struct _ast_var_decl_ {
    AstNode node;

} ast_var_decl_t;

/*
    Production being parsed:

 */
typedef struct _ast_var_decl_list_ {
    AstNode node;

} ast_var_decl_list_t;

/*
    Production being parsed:

 */
typedef struct _ast_function_assignment_ {
    AstNode node;

} ast_function_assignment_t;

/*
    Production being parsed:

 */
typedef struct _ast_assignment_item_ {
    AstNode node;

} ast_assignment_item_t;

/*
    Production being parsed:

 */
typedef struct _ast_var_definition_ {
    AstNode node;

} ast_var_definition_t;

/*
    Production being parsed:

 */
typedef struct _ast_list_init_str_ {
    AstNode node;

} ast_list_init_str_t;

/*
    Production being parsed:

 */
typedef struct _ast_list_init_element_ {
    AstNode node;

} ast_list_init_element_t;

/*
    Production being parsed:

 */
typedef struct _ast_list_init_ {
    AstNode node;

} ast_list_init_t;

/*
    Production being parsed:

 */
typedef struct _ast_array_param_item_ {
    AstNode node;

} ast_array_param_item_t;

/*
    Production being parsed:

 */
typedef struct _ast_array_param_ {
    AstNode node;

} ast_array_param_t;

/*
    Production being parsed:

 */
typedef struct _ast_array_param_list_ {
    AstNode node;

} ast_array_param_list_t;

/*
    Production being parsed:

 */
typedef struct _ast_array_reference_ {
    AstNode node;

} ast_array_reference_t;

/*
    Production being parsed:

 */
typedef struct _ast_function_reference_ {
    AstNode node;

} ast_function_reference_t;

/*
    Production being parsed:

 */
typedef struct _ast_create_reference_ {
    AstNode node;

} ast_create_reference_t;

/*
    Production being parsed:

 */
typedef struct _ast_destroy_reference_ {
    AstNode node;

} ast_destroy_reference_t;

/*
    Production being parsed:

 */
typedef struct _ast_compound_name_ {
    AstNode node;

} ast_compound_name_t;

/*
    Production being parsed:

 */
typedef struct _ast_compound_name_list_ {
    AstNode node;

} ast_compound_name_list_t;

/*
    Production being parsed:

 */
typedef struct _ast_compound_ref_item_ {
    AstNode node;

} ast_compound_ref_item_t;

/*
    Production being parsed:

 */
typedef struct _ast_compound_reference_ {
    AstNode node;

} ast_compound_reference_t;

/*
    Production being parsed:

 */
typedef struct _ast_cast_statement_ {
    AstNode node;

} ast_cast_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_expression_ {
    AstNode node;

} ast_expression_t;

/*
    Production being parsed:

 */
typedef struct _ast_expr_or_ {
    AstNode node;

} ast_expr_or_t;

/*
    Production being parsed:

 */
typedef struct _ast_expr_and_ {
    AstNode node;

} ast_expr_and_t;

/*
    Production being parsed:

 */
typedef struct _ast_expr_equality_ {
    AstNode node;

} ast_expr_equality_t;

/*
    Production being parsed:

 */
typedef struct _ast_expr_compare_ {
    AstNode node;

} ast_expr_compare_t;

/*
    Production being parsed:

 */
typedef struct _ast_expr_term_ {
    AstNode node;

} ast_expr_term_t;

/*
    Production being parsed:

 */
typedef struct _ast_expr_factor_ {
    AstNode node;

} ast_expr_factor_t;

/*
    Production being parsed:

 */
typedef struct _ast_expr_unary_ {
    AstNode node;

} ast_expr_unary_t;

/*
    Production being parsed:

 */
typedef struct _ast_expr_primary_ {
    AstNode node;

} ast_expr_primary_t;

/*
    Production being parsed:

 */
typedef struct _ast_expression_list_ {
    AstNode node;

} ast_expression_list_t;

/*
    Production being parsed:

 */
typedef struct _ast_namespace_definition_ {
    AstNode node;

} ast_namespace_definition_t;

/*
    Production being parsed:

 */
typedef struct _ast_class_definition_ {
    AstNode node;

} ast_class_definition_t;

/*
    Production being parsed:

 */
typedef struct _ast_class_item_ {
    AstNode node;

} ast_class_item_t;

/*
    Production being parsed:

 */
typedef struct _ast_function_declaration_ {
    AstNode node;

} ast_function_declaration_t;

/*
    Production being parsed:

 */
typedef struct _ast_create_declaration_ {
    AstNode node;

} ast_create_declaration_t;

/*
    Production being parsed:

 */
typedef struct _ast_destroy_declaration_ {
    AstNode node;

} ast_destroy_declaration_t;

/*
    Production being parsed:

 */
typedef struct _ast_function_definition_ {
    AstNode node;

} ast_function_definition_t;

/*
    Production being parsed:

 */
typedef struct _ast_create_name_ {
    AstNode node;

} ast_create_name_t;

/*
    Production being parsed:

 */
typedef struct _ast_create_definition_ {
    AstNode node;

} ast_create_definition_t;

/*
    Production being parsed:

 */
typedef struct _ast_destroy_name_ {
    AstNode node;

} ast_destroy_name_t;

/*
    Production being parsed:

 */
typedef struct _ast_destroy_definition_ {
    AstNode node;

} ast_destroy_definition_t;

/*
    Production being parsed:

 */
typedef struct _ast_function_body_ {
    AstNode node;

} ast_function_body_t;

/*
    Production being parsed:

 */
typedef struct _ast_assign_eq_item_ {
    AstNode node;

} ast_assign_eq_item_t;

/*
    Production being parsed:

 */
typedef struct _ast_assign_inc_item_ {
    AstNode node;

} ast_assign_inc_item_t;

/*
    Production being parsed:

 */
typedef struct _ast_assignment_ {
    AstNode node;

} ast_assignment_t;

/*
    Production being parsed:

 */
typedef struct _ast_function_body_element_ {
    AstNode node;

} ast_function_body_element_t;

/*
    Production being parsed:

 */
typedef struct _ast_break_statement_ {
    AstNode node;

} ast_break_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_continue_statement_ {
    AstNode node;

} ast_continue_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_yield_statement_ {
    AstNode node;

} ast_yield_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_type_statement_ {
    AstNode node;

} ast_type_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_return_statement_ {
    AstNode node;

} ast_return_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_raise_statement_ {
    AstNode node;

} ast_raise_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_trace_statement_ {
    AstNode node;

} ast_trace_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_print_statement_ {
    AstNode node;

} ast_print_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_exit_statement_ {
    AstNode node;

} ast_exit_statement_t;

/*
    Production being parsed:

 */
typedef struct _ast_while_definition_ {
    AstNode node;

} ast_while_definition_t;

/*
    Production being parsed:

 */
typedef struct _ast_while_clause_ {
    AstNode node;

} ast_while_clause_t;

/*
    Production being parsed:

 */
typedef struct _ast_do_clause_ {
    AstNode node;

} ast_do_clause_t;

/*
    Production being parsed:

 */
typedef struct _ast_for_clause_ {
    AstNode node;

} ast_for_clause_t;

/*
    Production being parsed:

 */
typedef struct _ast_if_clause_ {
    AstNode node;

} ast_if_clause_t;

/*
    Production being parsed:

 */
typedef struct _ast_else_clause_ {
    AstNode node;

} ast_else_clause_t;

/*
    Production being parsed:

 */
typedef struct _ast_final_else_clause_ {
    AstNode node;

} ast_final_else_clause_t;

/*
    Production being parsed:

 */
typedef struct _ast_try_clause_ {
    AstNode node;

} ast_try_clause_t;

/*
    Production being parsed:

 */
typedef struct _ast_except_clause_ {
    AstNode node;

} ast_except_clause_t;

/*
    Production being parsed:

 */
typedef struct _ast_final_clause_ {
    AstNode node;

} ast_final_clause_t;

#define CALL_NODE_FUNC(f) do { \
        if((f) != NULL) { \
            (*f)((AstNode*)node); \
        }\
    } while(0)

typedef void (*AstFuncPtr)(AstNode* node);
AstNode* create_ast_node(AstNodeType type);

void traverse_module(ast_module_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_module_item(ast_module_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_start_definition(ast_start_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_import_statement(ast_import_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_include_statement(ast_include_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_namespace_item(ast_namespace_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_scope_operator(ast_scope_operator_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_literal_type_name(ast_literal_type_name_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_type_name(ast_type_name_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_type_name_list(ast_type_name_list_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_formatted_strg(ast_formatted_strg_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_string_literal(ast_string_literal_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_literal_value(ast_literal_value_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_var_decl(ast_var_decl_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_var_decl_list(ast_var_decl_list_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_function_assignment(ast_function_assignment_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_assignment_item(ast_assignment_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_var_definition(ast_var_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_list_init_str(ast_list_init_str_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_list_init_element(ast_list_init_element_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_list_init(ast_list_init_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_array_param_item(ast_array_param_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_array_param(ast_array_param_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_array_param_list(ast_array_param_list_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_array_reference(ast_array_reference_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_function_reference(ast_function_reference_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_create_reference(ast_create_reference_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_destroy_reference(ast_destroy_reference_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_compound_name(ast_compound_name_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_compound_name_list(ast_compound_name_list_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_compound_ref_item(ast_compound_ref_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_compound_reference(ast_compound_reference_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_cast_statement(ast_cast_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expression(ast_expression_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expr_or(ast_expr_or_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expr_and(ast_expr_and_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expr_equality(ast_expr_equality_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expr_compare(ast_expr_compare_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expr_term(ast_expr_term_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expr_factor(ast_expr_factor_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expr_unary(ast_expr_unary_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expr_primary(ast_expr_primary_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expression_list(ast_expression_list_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_namespace_definition(ast_namespace_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_class_definition(ast_class_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_class_item(ast_class_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_function_declaration(ast_function_declaration_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_create_declaration(ast_create_declaration_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_destroy_declaration(ast_destroy_declaration_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_function_definition(ast_function_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_create_name(ast_create_name_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_create_definition(ast_create_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_destroy_name(ast_destroy_name_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_destroy_definition(ast_destroy_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_function_body(ast_function_body_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_assign_eq_item(ast_assign_eq_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_assign_inc_item(ast_assign_inc_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_assignment(ast_assignment_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_function_body_element(ast_function_body_element_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_break_statement(ast_break_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_continue_statement(ast_continue_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_yield_statement(ast_yield_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_type_statement(ast_type_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_return_statement(ast_return_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_raise_statement(ast_raise_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_trace_statement(ast_trace_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_print_statement(ast_print_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_exit_statement(ast_exit_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_while_definition(ast_while_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_while_clause(ast_while_clause_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_do_clause(ast_do_clause_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_for_clause(ast_for_clause_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_if_clause(ast_if_clause_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_else_clause(ast_else_clause_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_final_else_clause(ast_final_else_clause_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_try_clause(ast_try_clause_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_except_clause(ast_except_clause_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_final_clause(ast_final_clause_t* node, AstFuncPtr pre, AstFuncPtr post);

#endif /* _AST_H_ */

