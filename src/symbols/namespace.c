/**
 * @file namespace.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-09-12
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "namespace.h"
#include "common.h"

sym_namespace_t* create_namespace_symbol(ast_namespace_definition_t* node) {

    ASSERT(node != NULL);
    ENTER;
    sym_namespace_t* sym = _ALLOC_DS(sym_namespace_t);
    init_symbol(&(sym->sym), SYM_NAMESPACE, node->name->str);
    sym->node = node;

    RETURN(sym);
}
