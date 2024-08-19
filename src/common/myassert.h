/**
 * @file myassert.h
 *
 * @brief My asserts allow a message to be printed. If USE_ASSERTS has not
 * been defined then these statements disappear from the code.
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 2024-06-10
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _MYASSERT_H_
#define _MYASSERT_H_

#ifdef USE_ASSERTS

#include <stdio.h>
#include <stdlib.h>

#define ASSERT_MSG(e, m, ...)                                                              \
    do {                                                                                   \
        if(!(e)) {                                                                         \
            fprintf(stderr, "ASSERT: %s: %d: %s: %s: ", __FILE__, __LINE__, __func__, #e); \
            fprintf(stderr, m __VA_OPT__(, ) __VA_ARGS__);                                 \
            fprintf(stderr, "\n");                                                         \
            abort();                                                                       \
        }                                                                                  \
    } while(0)

#define ASSERT(e)                                                       \
    do {                                                                \
        if(!(e)) {                                                      \
            fprintf(stderr, "ASSERT: %s: %d: %s: %s: Assert failed.\n", \
                    __FILE__, __LINE__, __func__, #e);                  \
            abort();                                                    \
        }                                                               \
    } while(0)

#else

#define ASSERT(e)
#define ASSERT_MSG(e, m, ...)

#endif

#endif /* _MYASSERT_H_ */
