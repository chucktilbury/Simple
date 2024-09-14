/**
 *
 * @file ast.h
 *
 * @brief AST traverse public interface.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#ifndef _AST_H_
#define _AST_H_

#include "tokens.h"

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
    AST_EXPR_OPERATOR,
    AST_EXPR_OPERAND,
    AST_EXPRESSION_LIST,
    AST_NAMESPACE_DEFINITION,
    AST_CLASS_DEFINITION,
    AST_CLASS_BODY_ITEM,
    AST_CLASS_BODY,
    AST_CLASS_INHERITANCE_ITEM,
    AST_CLASS_INHERITANCE_LIST,
    AST_FUNCTION_DEFINITION,
    AST_CREATE_DEFINITION,
    AST_DESTROY_DEFINITION,
    AST_FUNCTION_BODY,
    AST_FUNCTION_BODY_ELEMENT,
    AST_LOOP_BODY,
    AST_LOOP_BODY_ELEMENT,
    AST_ASSIGN_EQ_ITEM,
    AST_ASSIGN_INC_ITEM,
    AST_ASSIGNMENT,
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
    AST_ALIAS_DEFINITION,
    AST_FUNC_PARM_DECL,
    AST_FUNC_PARM_DECL_LIST,
    AST_FUNCTION_MEMBERSHIP,
} AstNodeType;

typedef struct _ast_node_ {
    AstNodeType type;
} ast_node_t;

/**
 *
 * Grammar production:
 *
 * module
 *     : ( module_item )+
 *     ;
 */
typedef struct _ast_module_ {
    ast_node_t node;
    PtrLst* list;
} ast_module_t;

/**
 *
 * Grammar production:
 *
 * module_item
 *     : namespace_item
 *     | import_statement
 *     | include_statement
 *     | start_definition
 *     ;
 */
typedef struct _ast_module_item_ {
    ast_node_t node;
    ast_node_t* ptr;
} ast_module_item_t;

/**
 *
 * Grammar production:
 *
 * namespace_definition
 *     : 'namespace' IDENT '{' ( namespace_item )+ '}'
 *     ;
 */
typedef struct _ast_namespace_definition_ {
    ast_node_t node;
    Token* name;
    // list of namespace items
    PtrLst* items;
} ast_namespace_definition_t;

/**
 *
 * Grammar production:
 *
 * start_definition
 *     : 'start' function_body
 *     ;
 */
typedef struct _ast_start_definition_ {
    ast_node_t node;
    struct _ast_function_body_* body;
} ast_start_definition_t;


/**
 *
 * Grammar production:
 *
 * class_inheritance_item
 *     : (scope_operator)? compound_name 'as' IDENT
 *     ;
 */
typedef struct _ast_class_inheritance_item_ {
    ast_node_t node;
    struct _ast_scope_operator_* scope; // defaults to private
    Token* ident;
    struct _ast_compound_name_* name;
} ast_class_inheritance_item_t;

/**
 *
 * Grammar production:
 *
 * class_inheritance_list
 *     : '(' ( class_inheritance_item (',' class_inheritance_item)* )? ')'
 *     ;
 */
typedef struct _ast_class_inheritance_list_ {
    ast_node_t node;
    PtrLst* list;
} ast_class_inheritance_list_t;

/**
 *
 * Grammar production:
 *
 * class_definition
 *   : 'class' IDENT ( class_inheritance_list )? class_definition_body
 *   ;
 */
typedef struct _ast_class_definition_ {
    ast_node_t node;
    Token* name;
    struct _ast_class_inheritance_list_* inher;
    struct _ast_class_body_* body;
} ast_class_definition_t;


/**
 *
 * Grammar production:
 *
 * class_definition
 *   : '{' ( class_body_item )+ '}'
 *   ;
 */
typedef struct _ast_class_body_ {
    ast_node_t node;
    // list of class body items
    PtrLst* list;
} ast_class_body_t;

/**
 *
 * Grammar production:
 *
 * class_body_item
 *     : scope_operator
 *     | var_decl
 *     | function_definition
 *     | create_definition
 *     | destroy_definition
 *     ;
 */
typedef struct _ast_class_item_ {
    ast_node_t node;
    ast_node_t* ptr;
} ast_class_body_item_t;

/**
 *
 * Grammar production:
 *
 * function_membership
 *     : compound_name ':'
 *     ;
 */
typedef struct _ast_function_membership_ {
    ast_node_t node;
    struct _ast_compound_name_* name;
} ast_function_membership_t;

/**
 *
 * Grammar production:
 *
 * function_definition
 *     : ( function_membership )? IDENT func_parm_decl_list func_parm_decl_list ( function_body )?
 *     ;
 */
typedef struct _ast_function_definition_ {
    ast_node_t node;
    bool is_iter;
    struct _ast_function_membership_* member;
    Token* name;
    struct _ast_func_parm_decl_list_* inp;
    struct _ast_func_parm_decl_list_* outp;
    struct _ast_function_body_* body;
} ast_function_definition_t;

/**
 *
 * Grammar production:
 *
 * create_definition
 *     : ( function_membership )? 'create' func_parm_decl_list ( function_body )?
 *     ;
 */
typedef struct _ast_create_definition_ {
    ast_node_t node;
    struct _ast_function_membership_* member;
    struct _ast_func_parm_decl_list_* inp;
    struct _ast_function_body_* body;
} ast_create_definition_t;

/**
 *
 * Grammar production:
 *
 * destroy_definition
 *     : ( function_membership )? 'destroy' ( function_body )?
 *     ;
 */
typedef struct _ast_destroy_definition_ {
    ast_node_t node;
    struct _ast_function_membership_* member;
    struct _ast_function_body_* body;
} ast_destroy_definition_t;

/**
 *
 * Grammar production:
 *
 * var_definition
 *     : ( 'const' )? var_decl ( '=' assignment_item )?
 *     ;
 */
typedef struct _ast_var_definition_ {
    ast_node_t node;
    bool is_const;
    struct _ast_var_decl_* decl;
    // NULL if there is no assignment
    struct _ast_assignment_item_* item;
} ast_var_definition_t;

/**
 *
 * Grammar production:
 *
 * import_statement
 *     : 'import' formatted_strg 'as' IDENT
 *     ;
 */
typedef struct _ast_import_statement_ {
    ast_node_t node;
    struct _ast_formatted_strg_* str;
    Token* ident;
} ast_import_statement_t;

/**
 *
 * Grammar production:
 *
 * include_statement
 *     : 'include' formatted_strg
 *     ;
 */
typedef struct _ast_include_statement_ {
    ast_node_t node;
    struct _ast_formatted_strg_* str;
} ast_include_statement_t;

/**
 * Grammar production:
 *
 * alias_definition
 *      : compound_name 'as' IDENT
 *      ;
 */
typedef struct _ast_alias_definition_ {
    ast_node_t node;
    struct _ast_compound_name_* target;
    Token* ident;
} ast_alias_definition_t;

/**
 *
 * Grammar production:
 *
 * namespace_item
 *     : scope_operator
 *     | namespace_definition
 *     | class_definition
 *     | function_definition
 *     | create_definition
 *     | destroy_definition
 *     | var_definition
 *     | alias_definition
 *     ;
 */
typedef struct _ast_namespace_item_ {
    ast_node_t node;
    ast_node_t* ptr;
} ast_namespace_item_t;

/**
 *
 * Grammar production:
 *
 * scope_operator
 *     : 'private'
 *     | 'public'
 *     | 'protected'
 *     ;
 */
typedef struct _ast_scope_operator_ {
    ast_node_t node;
    Token* tok;
} ast_scope_operator_t;

/**
 *
 * Grammar production:
 *
 * literal_type_name
 *     : 'float'
 *     | 'integer'
 *     | 'string'
 *     | 'boolean'
 *     | 'nothing'
 *     | 'list'
 *     | 'dict'
 *     ;
 */
typedef struct _ast_literal_type_name_ {
    ast_node_t node;
    Token* tok;
} ast_literal_type_name_t;

/**
 *
 * Grammar production:
 *
 * type_name
 *     : literal_type_name
 *     | compound_name
 *     ;
 */
typedef struct _ast_type_name_ {
    ast_node_t node;
    ast_node_t* ptr;
} ast_type_name_t;

/**
 *
 * Grammar production:
 *
 * formatted_strg
 *     : LITERAL_DSTR ( expression_list )?
 *     ;
 */
typedef struct _ast_formatted_strg_ {
    ast_node_t node;
    Token* str;
    struct _ast_expression_list_* exprs;
} ast_formatted_strg_t;

/**
 *
 * Grammar production:
 *
 * string_literal
 *     : LITERAL_SSTR
 *     | formatted_strg
 *     ;
 */
typedef struct _ast_string_literal_ {
    ast_node_t node;
    // One of these must be NULL
    Token* lstr;
    struct _ast_formatted_strg_* fstr;
} ast_string_literal_t;

/**
 *
 * Grammar production:
 *
 * literal_value
 *     : LITERAL_FLOAT
 *     | LITERAL_INTEGER
 *     | LITERAL_BOOL
 *     | string_literal
 *     ;
 */
typedef struct _ast_literal_value_ {
    ast_node_t node;
    // one of these must be NULL;
    Token* literal;
    struct _ast_string_literal_* str;
} ast_literal_value_t;

/**
 *
 * Grammar production:
 *
 * var_decl
 *     : type_name IDENT
 *     ;
 */
typedef struct _ast_var_decl_ {
    ast_node_t node;
    struct _ast_type_name_* type;
    Token* ident;
} ast_var_decl_t;

/**
 *
 * Grammar production:
 *
 * func_parm_decl
 *     : type_name ( IDENT )?
 *     ;
 */
typedef struct _ast_func_parm_decl_ {
    ast_node_t node;
    struct _ast_type_name_* type;
    Token* ident; // could be NULL
} ast_func_parm_decl_t;

/**
 *
 * Grammar production:
 *
 * func_parm_decl_list
 *     : '(' ( func_parm_decl ( ',' func_parm_decl )* )? ')'
 *     ;
 */
typedef struct _ast_func_parm_decl_list_ {
    ast_node_t node;
    // list of struct ast_func_parm_decl_t
    bool inout;
    PtrLst* list;
} ast_func_parm_decl_list_t;

/**
 *
 * Grammar production:
 *
 * assignment_item
 *     : expression
 *     | list_init
 *     ;
 */
typedef struct _ast_assignment_item_ {
    ast_node_t node;
    ast_node_t* ptr;
} ast_assignment_item_t;

/**
 *
 * Grammar production:
 *
 * list_init_str
 *     : LITERAL_DSTR
 *     | LITERAL_SSTR
 *     ;
 */
typedef struct _ast_list_init_str_ {
    ast_node_t node;
    Token* str;
} ast_list_init_str_t;

/**
 *
 * Grammar production:
 *
 * list_init_element
 *     : list_init_str ':' assignment_item
 *     | assignment_item
 *     ;
 */
typedef struct _ast_list_init_element_ {
    ast_node_t node;
    struct _ast_assignment_item_* item;
    // this is NULL if there is no str
    struct _ast_list_init_str_* str;
} ast_list_init_element_t;

/**
 *
 * Grammar production:
 *
 * list_init
 *     : '[' list_init_element ( ',' list_init_element )* ']'
 *     ;
 */
typedef struct _ast_list_init_ {
    ast_node_t node;
    // list of ast_list_init_element_t
    PtrLst* list;
} ast_list_init_t;

/**
 *
 * Grammar production:
 *
 * array_param_item
 *     : expression
 *     | string_literal
 *     ;
 */
typedef struct _ast_array_param_item_ {
    ast_node_t node;
    ast_node_t* ptr;
} ast_array_param_item_t;

/**
 *
 * Grammar production:
 *
 * array_param
 *     : '[' array_param_item ']'
 *     ;
 */
typedef struct _ast_array_param_ {
    ast_node_t node;
    struct _ast_array_param_item_* item;
} ast_array_param_t;

/**
 *
 * Grammar production:
 *
 * array_param_list
 *     : array_param (array_param)*
 *     ;
 */
typedef struct _ast_array_param_list_ {
    ast_node_t node;
    // list of ast_array_param_t
    PtrLst* ptr;
} ast_array_param_list_t;

/**
 *
 * Grammar production:
 *
 * array_reference
 *     : IDENT array_param_list
 *     ;
 */
typedef struct _ast_array_reference_ {
    ast_node_t node;
    Token* ident;
    struct _ast_array_param_list_* list;
} ast_array_reference_t;

/**
 *
 * Grammar production:
 *
 * function_reference
 *     : compound_reference expression_list compound_name_list
 *     ;
 */
typedef struct _ast_function_reference_ {
    ast_node_t node;
    struct _ast_compound_reference_* name;
    struct _ast_expression_list_* inp;
    struct _ast_compound_name_list_* outp;
} ast_function_reference_t;

/**
 *
 * Grammar production:
 *
 * create_reference
 *     : IDENT ( '.' IDENT )* '.' 'create' expression_list
 *     ;
 */
typedef struct _ast_create_reference_ {
    ast_node_t node;
    PtrLst* name;
    struct _ast_expression_list_* inp;
} ast_create_reference_t;

/**
 *
 * Grammar production:
 *
 * destroy_reference
 *     : IDENT ( '.' IDENT )* '.' 'destroy'
 *     ;
 */
typedef struct _ast_destroy_reference_ {
    ast_node_t node;
    PtrLst* name;
} ast_destroy_reference_t;

/**
 *
 * Grammar production:
 *
 * compound_name
 *     : IDENT ( '.' IDENT )*
 *     ;
 */
typedef struct _ast_compound_name_ {
    ast_node_t node;
    // list of Tokens
    PtrLst* list;
} ast_compound_name_t;

/**
 *
 * Grammar production:
 *
 * compound_name_list
 *     : '(' ( compound_name (',' compound_name )* )? ')'
 *     ;
 */
typedef struct _ast_compound_name_list_ {
    ast_node_t node;
    // list of ast_compound_name_t
    PtrLst* list;
} ast_compound_name_list_t;

/**
 *
 * Grammar production:
 *
 * compound_ref_item
 *     : IDENT
 *     | array_reference
 *     ;
 */
typedef struct _ast_compound_ref_item_ {
    ast_node_t node;
    // one of these elements must be NULL
    Token* name;
    struct _ast_array_reference_* ref;
} ast_compound_ref_item_t;

/**
 *
 * Grammar production:
 *
 * compound_reference
 *     : compound_ref_item ( '.' compound_ref_item )*
 *     ;
 */
typedef struct _ast_compound_reference_ {
    ast_node_t node;
    // list of ast_compound_ref_item_t
    PtrLst* list;
} ast_compound_reference_t;

/**
 *
 * Grammar production:
 *
 * cast_statement
 *     : type_name ':' expression
 *     ;
 */
typedef struct _ast_cast_statement_ {
    ast_node_t node;
    struct _ast_type_name_* type;
    struct _ast_expression_* expr;
} ast_cast_statement_t;

/**
 *
 * Grammar production:
 * Note that the expressions are parsed separately using the shunting
 * yard algorithm. The result is a list of operations.
 *
 * expression
 *     : EXPRESSION
 *     ;
 */
typedef struct _ast_expression_ {
    ast_node_t node;
    // list contains ast_ext_operand_t and ast_ast_operator_t
    PtrLst* list;
    // type information here as well.
    int result_type;
} ast_expression_t;

/**
 *
 * Grammar production:
 *
 * expr_operator
 *     : '+' | '-' | '*' | '/' | '%' | '|' | '&' | '!'
 *     | '==' | '!=' | '<' | '>' | '<=' | '>='
 *     | 'or' | 'and' | 'not' | 'equ' | 'nequ'
 *     | 'lt' | 'gt' | 'lte' | 'gte'
 *     ;
 *
 */
typedef struct _ast_expr_operator_ {
    ast_node_t node;
    Token* oper;
} ast_expr_operator_t;

/**
 *
 * Grammar production:
 *
 * expr_operand
 *     : literal_value
 *     | compound_reference
 *     | cast_statement
 *     ;
 */
typedef struct _ast_expr_operand_ {
    ast_node_t node;
    ast_node_t* ptr;
} ast_expr_operand_t;

/**
 *
 * Grammar production:
 *
 * expression_list
 *     : '(' (expression ( ',' expression )*)? ')'
 *     ;
 */
typedef struct _ast_expression_list_ {
    ast_node_t node;
    // list of expressions
    PtrLst* list;
} ast_expression_list_t;

/**
 *
 * Grammar production:
 *
 * function_body
 *     : '{' ( function_body_element )* '}'
 *     ;
 */
typedef struct _ast_function_body_ {
    ast_node_t node;
    // list of function body elements
    PtrLst* list;
} ast_function_body_t;

/**
 *
 * Grammar production:
 *
 * loop_body
 *     : '{' ( loop_body_element )* '}'
 *     ;
 */
typedef struct _ast_loop_body_ {
    ast_node_t node;
    // list of function body elements
    PtrLst* list;
} ast_loop_body_t;

/**
 *
 * Grammar production:
 *
 * assign_eq_item
 *     : assignment_item
 *     | compound_reference
 *     ;
 */
typedef struct _ast_assign_eq_item_ {
    ast_node_t node;
    ast_node_t* ptr;
} ast_assign_eq_item_t;

/**
 *
 * Grammar production:
 *
 * assign_inc_item
 *     : expression
 *     | string_literal
 *     ;
 */
typedef struct _ast_assign_inc_item_ {
    ast_node_t node;
    ast_node_t* ptr;
} ast_assign_inc_item_t;

/**
 *
 * Grammar production:
 *
 * assignment
 *     : compound_reference '=' assign_eq_item
 *     | compound_reference '+=' assign_inc_item
 *     | compound_reference '-=' expression
 *     | compound_reference '*=' expression
 *     | compound_reference '/=' expression
 *     | compound_reference '%=' expression
 *     ;
 */
typedef struct _ast_assignment_ {
    ast_node_t node;
    Token* oper;
    struct _ast_compound_reference_* lhs;
    ast_node_t* rhs;
} ast_assignment_t;

/**
 *
 * Grammar production:
 *
 * function_body_element
 *     : var_definition
 *     | function_reference
 *     | create_reference
 *     | destroy_reference
 *     | assignment
 *     | while_clause
 *     | do_clause
 *     | for_clause
 *     | if_clause
 *     | try_clause
 *     | switch_clause
 *     | INLINE
 *     | type_statement
 *     | return_statement
 *     | raise_statement
 *     | trace_statement
 *     | print_statement
 *     | exit_statement
 *     | function_body
 *     ;
 */
typedef struct _ast_function_body_element_ {
    ast_node_t node;
    ast_node_t* ptr;
    Token* inl;
} ast_function_body_element_t;

/**
 *
 * Grammar production:
 *
 * loop_body_element
 *     : function_body_element
 *     | break_statement
 *     | continue_statement
 *     | yield_statement
 *     | loop_body
 *     ;
 */
typedef struct _ast_loop_body_element_ {
    ast_node_t node;
    ast_node_t* ptr;
    Token* inl;
} ast_loop_body_element_t;

/**
 *
 * Grammar production:
 *
 * break_statement
 *     : 'break'
 *     ;
 */
typedef struct _ast_break_statement_ {
    ast_node_t node;
} ast_break_statement_t;

/**
 *
 * Grammar production:
 *
 * continue_statement
 *     : 'continue'
 *     ;
 */
typedef struct _ast_continue_statement_ {
    ast_node_t node;
} ast_continue_statement_t;

/**
 *
 * Grammar production:
 *
 * yield_statement
 *     : 'yield' '(' compound_reference ')'
 *     ;
 */
typedef struct _ast_yield_statement_ {
    ast_node_t node;
    struct _ast_compound_reference_* arg;
} ast_yield_statement_t;

/**
 *
 * Grammar production:
 *
 * type_statement
 *     : 'type' '(' compound_reference ')'
 *     ;
 */
typedef struct _ast_type_statement_ {
    ast_node_t node;
    struct _ast_compound_reference_* arg;
} ast_type_statement_t;

/**
 *
 * Grammar production:
 *
 * return_statement
 *     : 'return'
 *     ;
 */
typedef struct _ast_return_statement_ {
    ast_node_t node;
} ast_return_statement_t;

/**
 *
 * Grammar production:
 *
 * raise_statement
 *     : 'raise' '(' IDENT ',' string_literal ')'
 *     ;
 */
typedef struct _ast_raise_statement_ {
    ast_node_t node;
    Token* id;
    struct _ast_string_literal_* str;
} ast_raise_statement_t;

/**
 *
 * Grammar production:
 *
 * trace_statement
 *     : 'trace' '(' string_literal ')'
 *     ;
 */
typedef struct _ast_trace_statement_ {
    ast_node_t node;
    struct _ast_string_literal_* str;
} ast_trace_statement_t;

/**
 *
 * Grammar production:
 *
 * print_statement
 *     : 'print' ( expression_list )?
 *     ;
 */
typedef struct _ast_print_statement_ {
    ast_node_t node;
    // list of expressions.
    struct _ast_expression_list_* ptr;
} ast_print_statement_t;

/**
 *
 * Grammar production:
 *
 * exit_statement
 *     : 'exit'
 *     ;
 */
typedef struct _ast_exit_statement_ {
    ast_node_t node;
} ast_exit_statement_t;

/**
 *
 * Grammar production:
 *
 * while_definition
 *     : 'while' ( '(' ( expression )? ')' )?
 *     ;
 */
typedef struct _ast_while_definition_ {
    ast_node_t node;
    // a NULL expression equates to 'true'
    struct _ast_expression_* expr;
} ast_while_definition_t;

/**
 *
 * Grammar production:
 *
 * while_clause
 *     : while_definition function_body
 *     ;
 */
typedef struct _ast_while_clause_ {
    ast_node_t node;
    struct _ast_while_definition_* expr;
    struct _ast_loop_body_* body;
} ast_while_clause_t;

/**
 *
 * Grammar production:
 *
 * do_clause
 *     : 'do' function_body while_definition
 *     ;
 */
typedef struct _ast_do_clause_ {
    ast_node_t node;
    struct _ast_while_definition_* expr;
    struct _ast_function_body_* body;
} ast_do_clause_t;

/**
 *
 * Grammar production:
 *
 * for_clause
 *     : 'for' ( '(' ( expression 'as' IDENT )? ')' )? function_body
 *     ;
 */
typedef struct _ast_for_clause_ {
    ast_node_t node;
    Token* ident;
    struct _ast_expression_* expr;
    struct _ast_loop_body_* body;
} ast_for_clause_t;

/**
 *
 * Grammar production:
 *
 * if_clause
 *     : 'if' '(' expression ')' function_body ( else_clause )* ( final_else_clause )?
 *     ;
 */
typedef struct _ast_if_clause_ {
    ast_node_t node;
    struct _ast_expression_* expr;
    struct _ast_function_body_* body;
    // list of else clauses
    PtrLst* ecl;
    // this could be NULL
    struct _ast_final_else_clause_* fecl;
} ast_if_clause_t;

/**
 *
 * Grammar production:
 *
 * else_clause
 *     : 'else' '(' expression ')' function_body
 *     ;
 */
typedef struct _ast_else_clause_ {
    ast_node_t node;
    struct _ast_expression_* expr;
    struct _ast_function_body_* body;
} ast_else_clause_t;

/**
 *
 * Grammar production:
 *
 * final_else_clause
 *     : 'else' ( '(' ')' )? function_body
 *     ;
 */
typedef struct _ast_final_else_clause_ {
    ast_node_t node;
    struct _ast_function_body_* body;
} ast_final_else_clause_t;

/**
 *
 * Grammar production:
 *
 * try_clause
 *     : 'try' function_body ( except_clause )+ ( final_clause )?
 *     ;
 */
typedef struct _ast_try_clause_ {
    ast_node_t node;
    struct _ast_function_body_* body;
    // list of except clauses
    PtrLst* list;
    // zero or more final clauses
    struct _ast_final_clause_* fin;
} ast_try_clause_t;

/**
 *
 * Grammar production:
 *
 * except_clause
 *     : 'except' '(' IDENT ',' IDENT ')' function_body
 *     ;
 */
typedef struct _ast_except_clause_ {
    ast_node_t node;
    Token* id1;
    Token* id2;
    struct _ast_function_body_* body;
} ast_except_clause_t;

/**
 *
 * Grammar production:
 *
 * final_clause
 *     : 'final' '(' IDENT ')' function_body
 *     ;
 */
typedef struct _ast_final_clause_ {
    ast_node_t node;
    Token* id1;
    struct _ast_function_body_* body;
} ast_final_clause_t;

#define CALL_NODE_FUNC(f) do { \
        if((f) != NULL) { \
            (*f)((ast_node_t*)node); \
        }\
    } while(0)

#define TRACE_TERMINAL(t) do { \
        if((t) != NULL) { \
            TRACE("%s is %s '%s': %d: %d: %s", #t, token_type_to_str(t), \
                    raw_string(t->str), \
                    t->line_no, t->col_no, t->fname); \
        } \
        else { \
            TRACE("%s is a NULL TERMINAL", #t); \
        } \
    } while (0)

typedef void (*AstFuncPtr)(ast_node_t* node);
ast_node_t* create_ast_node(AstNodeType type);
void traverse_ast(ast_module_t* node, AstFuncPtr pre, AstFuncPtr post);
const char* nterm_type_to_str(ast_node_t* node);
AstNodeType nterm_type(ast_node_t* node);

void traverse_module(ast_module_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_module_item(ast_module_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_start_definition(ast_start_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_import_statement(ast_import_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_include_statement(ast_include_statement_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_namespace_item(ast_namespace_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_scope_operator(ast_scope_operator_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_literal_type_name(ast_literal_type_name_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_type_name(ast_type_name_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_formatted_strg(ast_formatted_strg_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_string_literal(ast_string_literal_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_literal_value(ast_literal_value_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_var_decl(ast_var_decl_t* node, AstFuncPtr pre, AstFuncPtr post);
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
void traverse_expr_operand(ast_expr_operand_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expr_operator(ast_expr_operator_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_expression_list(ast_expression_list_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_namespace_definition(ast_namespace_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_class_definition(ast_class_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_class_body_item(ast_class_body_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_class_body(ast_class_body_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_class_inheritance_item(ast_class_inheritance_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_class_inheritance_list(ast_class_inheritance_list_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_function_definition(ast_function_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_create_definition(ast_create_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_destroy_definition(ast_destroy_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_function_body(ast_function_body_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_function_body_element(ast_function_body_element_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_loop_body(ast_loop_body_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_loop_body_element(ast_loop_body_element_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_assign_eq_item(ast_assign_eq_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_assign_inc_item(ast_assign_inc_item_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_assignment(ast_assignment_t* node, AstFuncPtr pre, AstFuncPtr post);
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
void traverse_alias_definition(ast_alias_definition_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_func_parm_decl(ast_func_parm_decl_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_func_parm_decl_list(ast_func_parm_decl_list_t* node, AstFuncPtr pre, AstFuncPtr post);
void traverse_function_membership(ast_function_membership_t* node, AstFuncPtr pre, AstFuncPtr post);

#endif  /* _AST_H_ */
