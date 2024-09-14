/**
 *
 * @file parser.h
 *
 * @brief Parse grammar public interface.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#ifndef _PARSER_H_
#define _PARSER_H_

#include "ast.h"
#include "common.h"

typedef enum {
    PMODE_NORMAL,
    PMODE_INCLUDE,
    PMODE_IMPORT,
} ParserMode;

typedef enum {
    SCOPE_PRIVATE,
    SCOPE_PUBLIC,
    SCOPE_PROTECTED,
} ScopeType;

typedef struct {
    LinkList* mode;
    LinkList* scope;
    struct _symbol_t_* sym_tab;
    struct _symbol_t_* crnt_sym;
} parser_state_t;

//#include "symbols.h"
#include "parser_prototypes.h"

#ifdef USE_TRACE
#include "trace.h"
#define TRACE_STATE                \
    do {                           \
        TRACE("state: %d", state); \
    } while(0)
#else
#define TRACE_STATE
#endif

ast_module_t* parse(void);

void push_parser_mode(parser_state_t* state, ParserMode mode);
ParserMode pop_parser_mode(parser_state_t* state);
ParserMode get_parser_mode(parser_state_t* state);

void push_parser_scope(parser_state_t* state, ScopeType scope);
void set_parser_scope(parser_state_t* state, ScopeType scope);
ScopeType pop_parser_scope(parser_state_t* state);
ScopeType get_parser_scope(parser_state_t* state);

#endif /* _PARSER_H_ */
