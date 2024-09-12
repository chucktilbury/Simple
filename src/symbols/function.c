/**
 * @file function.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "common.h"
#include "function.h"
#include "errors.h"

String* decorate_var_decl(ast_var_decl_t* decl) {

    ast_node_t* type = ((ast_type_name_t*)(decl->type))->ptr;
    if(nterm_type(type) == AST_LITERAL_TYPE_NAME) 
        return create_string(raw_string(((ast_literal_type_name_t*)(type))->tok->str));
    else if(nterm_type(type) == AST_COMPOUND_NAME) 
        return decorate_compound_name((ast_compound_name_t*)(type));
    else // should not happen
        FATAL("invalid non-terminal type: %d", nterm_type(type));

    return NULL; // never can happen
}

String* decorate_var_decl_list(ast_var_decl_list_t* lst) {

    String* str = create_string(NULL);
    int mark = 0;

    ast_var_decl_t* decl = iterate_ptr_lst(lst->list, &mark);
    if(decl != NULL) {
        append_string_string(str, decorate_var_decl(decl));

        while(NULL != (decl = iterate_ptr_lst(lst->list, &mark))) {
            append_string_char(str, ',');
            append_string_string(str, decorate_var_decl(decl));
        }
    }

    return str; // could be empty
}

/**
 * @brief Return the decorated name of the function, but using var 
 * definitions instead of simple type names.
 * 
 * @param func 
 * @return const char* 
 */
String* decorate_func_def(ast_function_definition_t* func) {

    ENTER;
    ASSERT(func != NULL);
    String* str = create_string(NULL);

    append_string_string(str, decorate_compound_name(func->name));
    append_string_char(str, '(');
    // func->inp is the input parameters of type ast_var_decl_list_t*
    append_string_string(str, decorate_var_decl_list(func->inp));
    append_string_char(str, ')');

    append_string_char(str, '(');
    // func->outp is the input parameters of type ast_var_decl_list_t*
    append_string_string(str, decorate_var_decl_list(func->outp));
    append_string_char(str, ')');

    TRACE("decorated function name: %s", raw_string(str));
    RETURN(str);
}

/**
 * @brief Create a function symbol object
 * 
 * @param node 
 * @return sym_function_t* 
 */
sym_function_t* create_function_symbol(ast_function_definition_t* node) {

    ASSERT(node != NULL);
    ENTER;
    sym_function_t* sym = _ALLOC_DS(sym_function_t);
    init_symbol(&(sym->sym), SYM_FUNCTION, decorate_func_def(node));
    sym->node = node;

    RETURN(sym);
}

