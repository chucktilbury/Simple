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

// parser includes the ast and common headers
#include "parser.h"

typedef enum {
    SYM_NAMESPACE,
    SYM_CLASS,
    SYM_VARIABLE,
    SYM_FUNCTION,
    SYM_IMPORT,
    SYM_LOCAL,
} SymbolType;

typedef struct _symbol_t_ {
    SymbolType type;
    String* name;
    HashTable* children;
    struct _symbol_t_* parent;
} symbol_t;

void init_symbol(symbol_t* sym, SymbolType type, String* name);

void add_global_symbol(parser_state_t* pstate, symbol_t* sym);
void set_symbol_context(parser_state_t* pstate, symbol_t* sym);
symbol_t* lookup_symbol_name(ast_compound_name_t* name);
symbol_t* lookup_symbol_ref(ast_compound_reference_t* name);
void add_local_symbol(ast_function_definition_t* func, symbol_t* sym);
symbol_t* lookup_local_symbol(ast_function_definition_t* func, const char* name);
const char* decorate_func_decl(ast_function_declaration_t* func);
const char* decorate_func_ref(ast_function_reference_t* func);
String* decorate_func_def(ast_function_definition_t* func);

String* decorate_compound_name(ast_compound_name_t* name);
String* generate_uuid(void);

#endif /* _SYMBOLS_H_ */

