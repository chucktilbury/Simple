/*
 * Public interface to the AST system.
 */
#ifndef _AST_H_
#define _AST_H_

#include "ptr_lst.h"
#include "str.h"

typedef enum {
    // defined by the grammar grammar
    AST_TERMINAL = 100,
    AST_NON_TERMINAL,
    AST_ZERO_OR_ONE,
    AST_ONE_OR_MORE,
    AST_ZERO_OR_MORE,
    AST_GROUP,
    // defined in the target grammar
    AST_GRAMMAR,
    AST_RULE,
    AST_PRODUCTION_LIST,
    AST_PRODUCTION,
    AST_PROD_ELEM,
} AstNodeType;


typedef struct _ast_node_ {
    AstNodeType type;
} AstNode;

typedef struct _ast_terminal_ {
    AstNode type;
    String* tok;
    String* name;
} ast_terminal_t;

typedef struct _ast_non_terminal_ {
    AstNode type;
    String* tok;
    String* name;
} ast_non_terminal_t;

typedef struct _ast_zero_or_one_ {
    AstNode type;
    struct _ast_group_* group;
} ast_zero_or_one_t;

typedef struct _ast_one_or_more_ {
    AstNode type;
    struct _ast_group_* group;
} ast_one_or_more_t;

typedef struct _ast_zero_or_more_ {
    AstNode type;
    struct _ast_group_* group;
} ast_zero_or_more_t;

typedef struct _ast_group_ {
    AstNode type;
    // list of one or more ast_prod_elem_t
    struct _ast_production_* prod;
} ast_group_t;

typedef struct _ast_grammar_ {
    AstNode type;
    // List of rules.
    PtrLst* list;
} ast_grammar_t;

typedef struct _ast_rule_ {
    AstNode type;
    // a rule definition
    String* name;
    struct _ast_production_list_* list;
} ast_rule_t;

typedef struct _ast_production_list_ {
    AstNode type;
    // list of productions
    PtrLst* list;
} ast_production_list_t;

typedef struct _ast_production_ {
    AstNode type;
    // list of ast_prod_elem_t
    PtrLst* list;
} ast_production_t;

typedef struct _ast_prod_elem_ {
    AstNode type;
    // a single item that could be a repetition function, another
    // non-terminal or a terminal
    AstNode* node;
} ast_prod_elem_t;

typedef int (*AstPassFunc)(AstNode*);

void traverse_ast(AstPassFunc pre, AstPassFunc post);
AstNode* create_ast_node(AstNodeType type);

void ast_terminal(ast_terminal_t* node, AstPassFunc pre, AstPassFunc post);
void ast_non_terminal(ast_non_terminal_t* node, AstPassFunc pre, AstPassFunc post);
void ast_grammar(ast_grammar_t* node, AstPassFunc pre, AstPassFunc post);
void ast_rule(ast_rule_t* node, AstPassFunc pre, AstPassFunc post);
void ast_production_list(ast_production_list_t* node, AstPassFunc pre, AstPassFunc post);
void ast_production(ast_production_t* node, AstPassFunc pre, AstPassFunc post);
void ast_prod_elem(ast_prod_elem_t* node, AstPassFunc pre, AstPassFunc post);
void ast_zero_or_one(ast_zero_or_one_t* node, AstPassFunc pre, AstPassFunc post);
void ast_one_or_more(ast_one_or_more_t* node, AstPassFunc pre, AstPassFunc post);
void ast_zero_or_more(ast_zero_or_more_t* node, AstPassFunc pre, AstPassFunc post);
void ast_group(ast_group_t* node, AstPassFunc pre, AstPassFunc post);

#endif /* _AST_H_ */
