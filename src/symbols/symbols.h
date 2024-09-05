/**
 * @file symbols.h
 * @author your name (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include "parser.h"

typedef struct _symbol_t_ {
    String* name;
    HashTable* children;
    struct _symbol_t_* parent;
    ParserScope scope;
    AstNodeType type;
    ast_node_t* definition;
} symbol_t;

/*
parser_context_t* create_context(parser_context_t* crnt, String* name);
void push_parser_context(parser_state_t* state, parser_context_t* context);
parser_context_t* pop_parser_context(parser_state_t* state);
parser_context_t* get_parser_context(parser_state_t* state);
String* get_parser_context_string(parser_state_t* state);
*/

#endif /* _SYMBOLS_H_ */

