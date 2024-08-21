#include <stdio.h>

#include "token_defs.h"

int main(void) {

    token_database_t* result;

    result = find_keyword("include");
    if(result != NULL)
        printf("%s\n", result->str);
    else
        printf("not found\n");

    result = find_keyword("as");
    if(result != NULL)
        printf("%s\n", result->str);
    else
        printf("not found\n");

    result = find_keyword("yield");
    if(result != NULL)
        printf("%s\n", result->str);
    else
        printf("not found\n");

    result = find_keyword("flarp");
    if(result != NULL)
        printf("%s\n", result->str);
    else
        printf("not found\n");

    return 0;
}
