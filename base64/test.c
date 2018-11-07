#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "base64.h"

int main(int argc, char **argv)
{
    if(argc != 3){
        printf("number of parameter error:\n");
        printf("\t./base64 -d(e) text\n");
        exit(EXIT_FAILURE);
    }

    int argv_e = strcmp(argv[1], "-e");
    int argv_d = strcmp(argv[1], "-d");

    if( !argv_e ){//text encrypt
        base64_encrypt_text(argv[2], strlen(argv[2]));
    }
    else if( !argv_d ){//text decrypt
        base64_decrypt_text(argv[2], strlen(argv[2]));
    }
    else{
        printf("type of parameter error:\n");
        printf("\t./base64 -d(e) text\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

