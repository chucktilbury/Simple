/**
 * @file variable.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "common.h"
#include "variable.h"

sym_variable_t* create_variable_symbol(ast_var_definition_t* node) {

    ASSERT(node != NULL);
    ENTER;
    sym_variable_t* sym = _ALLOC_DS(sym_variable_t);
    init_symbol(&(sym->sym), SYM_VARIABLE, node->decl->ident->str);
    sym->node = node;

    RETURN(sym);
}
