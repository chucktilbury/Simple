/*
 * All of the ast node functions.
 */
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "memory.h"

#ifdef USE_AST_TRACE
#define AST_TRACE(fmt, ...)           \
    do {                              \
        printf((fmt), ##__VA_ARGS__); \
        fputc('\n', stdout);          \
    } while(0)
#else
#define AST_TRACE(fmt, ...)
#endif

#define CALL_PRE(n)              \
    do {                         \
        if((pre) != NULL)        \
            (*pre)((AstNode*)n); \
    } while(0)

#define CALL_POST(n)              \
    do {                          \
        if((post) != NULL)        \
            (*post)((AstNode*)n); \
    } while(0)

#define NODE_TYPE(n) (((AstNode*)(n))->type)

extern AstNode* root_node;
int state_count = 0;

#ifdef USE_AST_TRACE
static inline const char* ast_node_type_to_str(AstNodeType type) {

    return (type == AST_TERMINAL)         ? "AST_TERMINAL" :
            (type == AST_NON_TERMINAL) ? "AST_NON_TERMINAL" :
            (type == AST_ZERO_OR_ONE)     ? "AST_ZERO_OR_ONE" :
            (type == AST_ONE_OR_MORE)     ? "AST_ONE_OR_MORE" :
            (type == AST_ZERO_OR_MORE)    ? "AST_ZERO_OR_MORE" :
            (type == AST_GROUP)           ? "AST_GROUP" :
            (type == AST_GRAMMAR)         ? "AST_GRAMMAR" :
            (type == AST_RULE)            ? "AST_RULE" :
            (type == AST_PRODUCTION_LIST) ? "AST_PRODUCTION_LIST" :
            (type == AST_PRODUCTION)      ? "AST_PRODUCTION" :
            (type == AST_PROD_ELEM)       ? "AST_PROD_ELEM" :
                                            "UNKNOWN AST TYPE";
}
#endif

static inline size_t get_struct_size(AstNodeType type) {

    return (type == AST_TERMINAL)         ? sizeof(struct _ast_terminal_) :
            (type == AST_NON_TERMINAL) ? sizeof(struct _ast_non_terminal_) :
            (type == AST_GRAMMAR)         ? sizeof(struct _ast_grammar_) :
            (type == AST_RULE)            ? sizeof(struct _ast_rule_) :
            (type == AST_PRODUCTION_LIST) ? sizeof(struct _ast_production_list_) :
            (type == AST_PRODUCTION)      ? sizeof(struct _ast_production_) :
            (type == AST_PROD_ELEM)       ? sizeof(struct _ast_prod_elem_) :
            (type == AST_ZERO_OR_ONE)     ? sizeof(struct _ast_zero_or_one_) :
            (type == AST_ONE_OR_MORE)     ? sizeof(struct _ast_one_or_more_) :
            (type == AST_ZERO_OR_MORE)    ? sizeof(struct _ast_zero_or_more_) :
            (type == AST_GROUP)           ? sizeof(struct _ast_group_) :
                                            0;
}

AstNode* create_ast_node(AstNodeType type) {

    AstNode* ptr = (AstNode*)_ALLOC(get_struct_size(type));
    ptr->type    = type;

    return ptr;
}

void ast_terminal(ast_terminal_t* node, AstPassFunc pre, AstPassFunc post) {

    CALL_PRE(node);

    AST_TRACE("%s", ast_node_type_to_str(node->type.type));
    AST_TRACE("> %s as %s", raw_string(node->tok), node->name? node->name: "NULL");
    state_count++;

    CALL_POST(node);
}

void ast_non_terminal(ast_non_terminal_t* node, AstPassFunc pre, AstPassFunc post) {

    CALL_PRE(node);

    AST_TRACE("%s", ast_node_type_to_str(node->type.type));
    AST_TRACE("> %s as %s", raw_string(node->tok), node->name? node->name: "NULL");
    state_count++;

    CALL_POST(node);
}

void ast_grammar(ast_grammar_t* node, AstPassFunc pre, AstPassFunc post) {

    CALL_PRE(node);

    AST_TRACE("%s", ast_node_type_to_str(node->type.type));
    int mark = 0;
    struct _ast_rule_* rule;
    while(NULL != (rule = iterate_ptr_lst(node->list, &mark)))
        ast_rule(rule, pre, post);
    state_count++;

    CALL_POST(node);
}

void ast_rule(ast_rule_t* node, AstPassFunc pre, AstPassFunc post) {

    CALL_PRE(node);

    AST_TRACE("%s", ast_node_type_to_str(node->type.type));
    AST_TRACE("> name: %s", raw_string(node->name));
    ast_production_list(node->list, pre, post);
    state_count++;

    CALL_POST(node);
}

void ast_production_list(ast_production_list_t* node, AstPassFunc pre, AstPassFunc post) {

    CALL_PRE(node);

    AST_TRACE("%s", ast_node_type_to_str(node->type.type));
    int mark = 0;
    struct _ast_production_* prod;
    while(NULL != (prod = iterate_ptr_lst(node->list, &mark)))
        ast_production(prod, pre, post);
    state_count++;

    CALL_POST(node);
}

void ast_production(ast_production_t* node, AstPassFunc pre, AstPassFunc post) {

    CALL_PRE(node);

    AST_TRACE("%s", ast_node_type_to_str(node->type.type));
    int mark = 0;
    struct _ast_prod_elem_* elem;
    while(NULL != (elem = iterate_ptr_lst(node->list, &mark)))
        ast_prod_elem(elem, pre, post);
    state_count++;

    CALL_POST(node);
}

void ast_prod_elem(ast_prod_elem_t* node, AstPassFunc pre, AstPassFunc post) {

    CALL_PRE(node);

    AST_TRACE("%s", ast_node_type_to_str(node->type.type));
    switch(node->node->type) {
        case AST_TERMINAL:
            ast_terminal((ast_terminal_t*)node->node, pre, post);
            break;
        case AST_NON_TERMINAL:
            ast_non_terminal((ast_non_terminal_t*)node->node, pre, post);
            break;
        case AST_ZERO_OR_MORE:
            ast_zero_or_more((ast_zero_or_more_t*)node->node, pre, post);
            break;
        case AST_ONE_OR_MORE:
            ast_one_or_more((ast_one_or_more_t*)node->node, pre, post);
            break;
        case AST_ZERO_OR_ONE:
            ast_zero_or_one((ast_zero_or_one_t*)node->node, pre, post);
            break;
        case AST_GROUP:
            ast_group((ast_group_t*)node->node, pre, post);
            break;
        default:
            fprintf(stderr, "FATAL: invalid state in %s: %d\n", __func__,
                    node->type.type);
            abort();
    }
    state_count++;

    CALL_POST(node);
}

void ast_zero_or_one(ast_zero_or_one_t* node, AstPassFunc pre, AstPassFunc post) {

    CALL_PRE(node);

    AST_TRACE("%s", ast_node_type_to_str(node->type.type));
    ast_group(node->group, pre, post);
    state_count++;

    CALL_POST(node);
}

void ast_one_or_more(ast_one_or_more_t* node, AstPassFunc pre, AstPassFunc post) {

    CALL_PRE(node);

    AST_TRACE("%s", ast_node_type_to_str(node->type.type));
    ast_group(node->group, pre, post);
    state_count++;

    CALL_POST(node);
}

void ast_zero_or_more(ast_zero_or_more_t* node, AstPassFunc pre, AstPassFunc post) {

    CALL_PRE(node);

    AST_TRACE("%s", ast_node_type_to_str(node->type.type));
    ast_group(node->group, pre, post);
    state_count++;

    CALL_POST(node);
}

void ast_group(ast_group_t* node, AstPassFunc pre, AstPassFunc post) {

    CALL_PRE(node);

    AST_TRACE("%s", ast_node_type_to_str(node->type.type));
    ast_production(node->prod, pre, post);
    state_count++;

    CALL_POST(node);
}

void traverse_ast(AstPassFunc pre, AstPassFunc post) {

    state_count = 0;

    if(root_node != NULL) {
        ast_grammar((ast_grammar_t*)root_node, pre, post);
    }
    else {
        fprintf(stderr, "FATAL: root node is NULL");
        abort();
    }

    printf("state count: %d\n", state_count);
}
