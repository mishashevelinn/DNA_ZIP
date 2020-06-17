#   iqoni                                               clude "dna.h"
#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    if(argc != 4) {
        fprintf(stderr, "\nUsage: %s [--zip|--unzip] <file1> <file2>\n\n", argv[0]);
        return 1;
    }

    if(!strcmp(argv[1], "--zip"))  {
        zip(argv[2], argv[3]);
    }
    else if(!strcmp(argv[1], "--unzip"))  {
        unzip(argv[2], argv[3]);
    }
    else  {
        fprintf(stderr, "\nError: wrong choice, %s\n\n", argv[1]);
        return 1;
    }
    return 0;
}
