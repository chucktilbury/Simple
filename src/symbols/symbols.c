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
#include <time.h>

/**
 * @brief Create a symbol object.
 *
 * @param node
 * @return symbol_t*
 */
void init_symbol(symbol_t* sym, SymbolType type, String* name) {

    ENTER;
    sym->type = type;
    sym->name = copy_string(name);

    sym->children = create_hashtable();
    sym->parent = NULL;
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
 * @brief Generate a name suitable for storage in the hash table from a
 * ast_compound_name_t data structure. This is used by the variable functions.
 * The function decorator has it's own version.
 *
 * @param name
 * @return String*
 */
String* decorate_compound_name(ast_compound_name_t* name) {

    ENTER;
    ASSERT(name != NULL);

    int mark = 0;
    String* str = create_string(NULL);

    Token* item = iterate_ptr_lst(name->list, &mark);
    if(item != NULL) {
        append_string_string(str, item->str);

        while(NULL != (item = iterate_ptr_lst(name->list, &mark))) {
            append_string_char(str, '.');
            append_string_string(str, item->str);
        }
    }

    RETURN(str);
}

/**
 * @brief Generate a cheap UUID from rand()
 *
 * @return String*
 */
String* generate_uuid(void) {

    ENTER;
    srand(time(NULL));

    // Generate four 32-bit random numbers
    unsigned int num1 = rand();
    unsigned int num2 = rand();
    unsigned int num3 = rand();
    unsigned int num4 = rand();

    // Convert the random numbers to a string
    String* str = create_string(NULL);
    append_string_fmt(str, "%08x-%04x-%04x-%04x-%08x%04x", num1, num2 >> 16,
                      num2 & 0xFFFF, num3 >> 16, num3 & 0xFFFF, num4);

    TRACE("UUID = %s", raw_string(str));
    RETURN(str);
}
