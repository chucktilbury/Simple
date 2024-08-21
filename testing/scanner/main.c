#include "common.h"
#include "scanner.h"
#include "tokens.h"

void print_token(Token* tok) {

}

int main(int argc, char** argv) {

    //printf("file: %s\n", argv[0]);
    init_scanner("../testing/scanner/test_input1.txt");

    Token* tok = get_token();

    while(true) {
        print_token(tok);
        tok = consume_token();
        if(tok->type == TOK_END_OF_INPUT)
            break;
    }

    return 0;
}

