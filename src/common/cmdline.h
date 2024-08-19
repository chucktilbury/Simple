/**
 * @file cmdline.h
 *
 * @brief
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 2024-06-10
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _CMDLINE_H_
#define _CMDLINE_H_

#include "str.h"
#include <stdbool.h>

typedef void (*cmdline_callback)(void);
#include "cmderrors.h"
#include "cmdparse.h"

/**
 * Note that this structure of types and conditions allows for a fairly complex
 * interactions. Most of these are not checked to flag developer errors. For
 * example, if an arg is a type of num, but it takes no args, that does not
 * really make sense, but it is accepted by this functionality. The result
 * would always be a command line error when you try to provide an arg where
 * none is expected. So these flags cannot be combined willnilly.
 */
typedef enum {
    // needed by getarg()
    CMD_NARG = 0x00, // no args required
    CMD_RARG = 0x01, // args are required if the item is on the command line
    CMD_OARG = 0x02, // args are optional

    // data type helpers
    CMD_STR  = 0x04, // type is a string
    CMD_NUM  = 0x10, // type is a number
    CMD_BOOL = 0x20, // type is bool
    CMD_LIST = 0x08, // a list is accepted by the arg

    // internal flags, do not use
    CMD_REQD = 0x40,
    CMD_SEEN = 0x80,
} CmdType;

#define ALLOW_NOPT 0
#define REJECT_NOPT 1

void init_cmdline(const char* intro, const char* outtro, const char* name, const char* version);
void uninit_cmdline(void);
void add_cmdline(int short_opt,
                 const char* long_opt,
                 const char* name,
                 const char* help,
                 const char* def_val,
                 cmdline_callback cb,
                 CmdType flag);
void parse_cmdline(int argc, char** argv, int flag);
const char* get_cmdline(const char* name);
// int get_cmdline_as_num(const char* name);
// bool get_cmdline_as_bool(const char* name);
// const char* get_cmdline_as_str(const char* name);
const char* iterate_cmdline(const char* name, int* post);

void show_help(void);
void show_version(void);

#endif  /* _CMDLINE_H_ */
