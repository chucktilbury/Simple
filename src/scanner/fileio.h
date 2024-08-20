/**
 * @file fileio.h
 *
 * @brief
 *
 * @author Charles Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 03-29-2024
 * @copyright Copyright (c) 2024
 */
#ifndef __FILEIO_H__
#define __FILEIO_H__

#define END_OF_FILE -1
#define END_OF_INPUT -2

void push_input_file(const char* fname);
void pop_input_file(void);
int get_char(void);
int consume_char(void);

int get_line_no(void);
int get_col_no(void);
const char* get_fname(void);

#endif /* __FILEIO_H__ */
