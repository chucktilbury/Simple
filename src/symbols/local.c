/**
 * @file local.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-09-12
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "local.h"
#include "common.h"

sym_local_t* create_local_symbol(ast_node_t* node) {

    ASSERT(node != NULL);
    ENTER;
    sym_local_t* sym = _ALLOC_DS(sym_local_t);
    init_symbol(&(sym->sym), SYM_LOCAL, generate_uuid());
    // node could be a function_body or a loop_body
    sym->node = node;
    sym->node_type = nterm_type(node);

    RETURN(sym);
}
