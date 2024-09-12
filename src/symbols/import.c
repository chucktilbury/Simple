/**
 * @file import.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "common.h"
#include "import.h"

sym_import_t* create_import_symbol(ast_import_statement_t* node) {

    ASSERT(node != NULL);
    ENTER;
    sym_import_t* sym = _ALLOC_DS(sym_import_t);
    init_symbol(&(sym->sym), SYM_IMPORT, node->ident->str);
    sym->node = node;

    RETURN(sym);
}

