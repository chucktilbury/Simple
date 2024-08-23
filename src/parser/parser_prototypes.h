/**
 *
 * @file parser_prototypes.h
 *
 * @brief Internal prototypes for parser.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#ifndef _PARSER_PROTOTYPES_H_
#define _PARSER_PROTOTYPES_H_

ast_module_t* parse_module(parser_state_t* pstate);
ast_module_item_t* parse_module_item(parser_state_t* pstate);
ast_start_definition_t* parse_start_definition(parser_state_t* pstate);
ast_import_statement_t* parse_import_statement(parser_state_t* pstate);
ast_include_statement_t* parse_include_statement(parser_state_t* pstate);
ast_namespace_item_t* parse_namespace_item(parser_state_t* pstate);
ast_scope_operator_t* parse_scope_operator(parser_state_t* pstate);
ast_literal_type_name_t* parse_literal_type_name(parser_state_t* pstate);
ast_type_name_t* parse_type_name(parser_state_t* pstate);
ast_type_name_list_t* parse_type_name_list(parser_state_t* pstate);
ast_formatted_strg_t* parse_formatted_strg(parser_state_t* pstate);
ast_string_literal_t* parse_string_literal(parser_state_t* pstate);
ast_literal_value_t* parse_literal_value(parser_state_t* pstate);
ast_var_decl_t* parse_var_decl(parser_state_t* pstate);
ast_var_decl_list_t* parse_var_decl_list(parser_state_t* pstate);
ast_function_assignment_t* parse_function_assignment(parser_state_t* pstate);
ast_assignment_item_t* parse_assignment_item(parser_state_t* pstate);
ast_var_definition_t* parse_var_definition(parser_state_t* pstate);
ast_list_init_str_t* parse_list_init_str(parser_state_t* pstate);
ast_list_init_element_t* parse_list_init_element(parser_state_t* pstate);
ast_list_init_t* parse_list_init(parser_state_t* pstate);
ast_array_param_item_t* parse_array_param_item(parser_state_t* pstate);
ast_array_param_t* parse_array_param(parser_state_t* pstate);
ast_array_param_list_t* parse_array_param_list(parser_state_t* pstate);
ast_array_reference_t* parse_array_reference(parser_state_t* pstate);
ast_function_reference_t* parse_function_reference(parser_state_t* pstate);
ast_create_reference_t* parse_create_reference(parser_state_t* pstate);
ast_destroy_reference_t* parse_destroy_reference(parser_state_t* pstate);
ast_compound_name_t* parse_compound_name(parser_state_t* pstate);
ast_compound_name_list_t* parse_compound_name_list(parser_state_t* pstate);
ast_compound_ref_item_t* parse_compound_ref_item(parser_state_t* pstate);
ast_compound_reference_t* parse_compound_reference(parser_state_t* pstate);
ast_cast_statement_t* parse_cast_statement(parser_state_t* pstate);
ast_expression_t* parse_expression(parser_state_t* pstate);
ast_expr_operator_t* parse_expr_operator(parser_state_t* pstate);
ast_expr_operand_t* parse_expr_operand(parser_state_t* pstate);
ast_expression_list_t* parse_expression_list(parser_state_t* pstate);
ast_namespace_definition_t* parse_namespace_definition(parser_state_t* pstate);
ast_class_definition_t* parse_class_definition(parser_state_t* pstate);
ast_class_item_t* parse_class_item(parser_state_t* pstate);
ast_function_declaration_t* parse_function_declaration(parser_state_t* pstate);
ast_create_declaration_t* parse_create_declaration(parser_state_t* pstate);
ast_destroy_declaration_t* parse_destroy_declaration(parser_state_t* pstate);
ast_function_definition_t* parse_function_definition(parser_state_t* pstate);
ast_create_name_t* parse_create_name(parser_state_t* pstate);
ast_create_definition_t* parse_create_definition(parser_state_t* pstate);
ast_destroy_name_t* parse_destroy_name(parser_state_t* pstate);
ast_destroy_definition_t* parse_destroy_definition(parser_state_t* pstate);
ast_function_body_t* parse_function_body(parser_state_t* pstate);
ast_assign_eq_item_t* parse_assign_eq_item(parser_state_t* pstate);
ast_assign_inc_item_t* parse_assign_inc_item(parser_state_t* pstate);
ast_assignment_t* parse_assignment(parser_state_t* pstate);
ast_function_body_element_t* parse_function_body_element(parser_state_t* pstate);
ast_break_statement_t* parse_break_statement(parser_state_t* pstate);
ast_continue_statement_t* parse_continue_statement(parser_state_t* pstate);
ast_yield_statement_t* parse_yield_statement(parser_state_t* pstate);
ast_type_statement_t* parse_type_statement(parser_state_t* pstate);
ast_return_statement_t* parse_return_statement(parser_state_t* pstate);
ast_raise_statement_t* parse_raise_statement(parser_state_t* pstate);
ast_trace_statement_t* parse_trace_statement(parser_state_t* pstate);
ast_print_statement_t* parse_print_statement(parser_state_t* pstate);
ast_exit_statement_t* parse_exit_statement(parser_state_t* pstate);
ast_while_definition_t* parse_while_definition(parser_state_t* pstate);
ast_while_clause_t* parse_while_clause(parser_state_t* pstate);
ast_do_clause_t* parse_do_clause(parser_state_t* pstate);
ast_for_clause_t* parse_for_clause(parser_state_t* pstate);
ast_if_clause_t* parse_if_clause(parser_state_t* pstate);
ast_else_clause_t* parse_else_clause(parser_state_t* pstate);
ast_final_else_clause_t* parse_final_else_clause(parser_state_t* pstate);
ast_try_clause_t* parse_try_clause(parser_state_t* pstate);
ast_except_clause_t* parse_except_clause(parser_state_t* pstate);
ast_final_clause_t* parse_final_clause(parser_state_t* pstate);

#endif  /* _PARSER_PROTOTYPES_H_ */

