/**
 * @file symbols.c
 * @author your name (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "symbols.h"

/**
 * @brief Create a symbol object.
 * 
 * @param node 
 * @return symbol_t* 
 */
symbol_t* create_symbol(ast_node_t* node) {

    ENTER;
    ASSERT(node != NULL);
    symbol_t* sym = _ALLOC_DS(symbol_t);

    RETURN(sym);
}

/**
 * @brief Add the symbol to the parser state.
 * 
 * @param pstate 
 * @param sym 
 */
void add_global_symbol(parser_state_t* pstate, symbol_t* sym) {

    ENTER;
    ASSERT(pstate != NULL);
    ASSERT(sym != NULL);
    RET;
}

/**
 * @brief Set the symbol context in the parser state. This is called when
 * a namespace or a class is parsed.
 * 
 * @param pstate 
 * @param sym 
 */
void set_symbol_context(parser_state_t* pstate, symbol_t* sym) {

    ENTER;
    ASSERT(pstate != NULL);
    ASSERT(sym != NULL);
    RET;
}

/**
 * @brief Look up a symbol that is supposed to be a compound name in the 
 * global context.
 * 
 * @param name 
 * @return symbol_t* 
 */
symbol_t* lookup_symbol_name(ast_compound_name_t* name) {

    ENTER;
    ASSERT(name != NULL);
    symbol_t* sym = _ALLOC_DS(symbol_t);

    RETURN(sym);
}

/**
 * @brief Look up a symbol that is supposed to be a compound reference in
 * the global context.
 * 
 * @param name 
 * @return symbol_t* 
 */
symbol_t* lookup_symbol_ref(ast_compound_reference_t* name) {

    ENTER;
    ASSERT(name != NULL);
    symbol_t* sym = _ALLOC_DS(symbol_t);

    RETURN(sym);
}

/**
 * @brief Add a local symbol into the function context.
 * 
 * @param func 
 * @param sym 
 */
void add_local_symbol(ast_function_definition_t* func, symbol_t* sym) {

    ENTER;
    ASSERT(func != NULL);
    ASSERT(sym != NULL);

    RET;
}

/**
 * @brief Look up a symbol in the function context.
 * 
 * @param func 
 * @param name 
 * @return symbol_t* 
 */
symbol_t* lookup_local_symbol(ast_function_definition_t* func, const char* name) {

    ENTER;
    ASSERT(func != NULL);
    ASSERT(name != NULL);
    symbol_t* sym = _ALLOC_DS(symbol_t);

    RETURN(sym);
}

/**
 * @brief Return the decorated name of the function declaration. This simply 
 * uses the type names.
 * 
 * @param func 
 * @return const char* 
 */
const char* decorate_func_decl(ast_function_declaration_t* func) {

    ENTER;
    ASSERT(func != NULL);
    String* str = create_string(NULL);

    RETURN(_DUP_STR(raw_string(str)));
}

/**
 * @brief Return the decorated name of a function reference. This has to 
 * look up the types of the parameters to know the name of the function.
 * 
 * @param func 
 * @return const char* 
 */
const char* decorate_func_ref(ast_function_reference_t* func) {

    ENTER;
    ASSERT(func != NULL);
    String* str = create_string(NULL);

    RETURN(_DUP_STR(raw_string(str)));
}

/**
 * @brief Return the decorated name of the function, but using var 
 * definitions instead of simple type names.
 * 
 * @param func 
 * @return const char* 
 */
const char* decorate_func_def(ast_function_definition_t* func) {

    ENTER;
    ASSERT(func != NULL);
    String* str = create_string(NULL);

    RETURN(_DUP_STR(raw_string(str)));
}


