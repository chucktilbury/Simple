/**
 * @file class.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-09-12
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "class.h"
#include "common.h"

sym_class_t* create_class_symbol(ast_class_definition_t* node) {

    ASSERT(node != NULL);
    ENTER;
    sym_class_t* sym = _ALLOC_DS(sym_class_t);
    init_symbol(&(sym->sym), SYM_CLASS, node->name->str);
    sym->node = node;

    RETURN(sym);
}
