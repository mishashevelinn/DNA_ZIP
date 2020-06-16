#include "dna.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/******************************************************************************/
Nucleic_acid toNA(unsigned char c) {
    switch (c) {
        case 'A' :
            return A;
        case 'C' :
            return C;
        case 'G' :
            return G;
        case 'T' :
            return T;
        default:
            printf("Format Error");
            exit(1);
    }
}

/******************************************************************************/
unsigned char toChar(Nucleic_acid c) {
    switch (c) {
        case 0:
            return 'A';
        case 1:
            return 'C';
        case 2:
            return 'G';
        case 3:
            return 'T';
        default:
            printf("Undefined Value Error\n");
            exit(1);
    }
}

/******************************************************************************/
unsigned int dna_seq_length(const char *unzipped_file) {
    int counter = 0;
    char c;
    char buffer[MAX_HEADER_LENGTH];
    FILE *file_ptr;
    file_ptr = fopen(unzipped_file, "r");
    if (file_ptr == NULL) {
        printf("FILE NOT FOUND");
        exit(0);
    }

    fgets(buffer, MAX_HEADER_LENGTH, file_ptr); //skip the first line in counting
    while ((c = getc(file_ptr)) != EOF) {
        if (c != '\n')
            counter++;
    }
    fclose(file_ptr);
    return counter;
}

/******************************************************************************/
void zip(const char *unzipped_file, const char *zipped_file) {
    unsigned char buff = 0;
    char c;
    char *header = NULL;
    unsigned int seq_len;
    Nucleic_acid NA;
    FILE *file, *bfile;

    size_t header_size;
    ssize_t line_length;

    file = fopen(unzipped_file, "r");
    bfile = fopen(zipped_file, "wb");
    if (file == NULL) {
        printf("FILE NOT FOUND");
        exit(0);
    }

    line_length = getline(&header, &header_size, file);
    fwrite(&line_length, sizeof(unsigned char), 1, bfile);//writing header length
    fprintf(bfile, header, "%s");                          //writing header itself

    seq_len = dna_seq_length(unzipped_file);
    fwrite(&seq_len, sizeof(unsigned int ), 1, bfile);   //writing sequence length


    for (int j = 0; j < seq_len; j += 4) {
        for (int i = 0; i <= 6; i += 2) {
            if ((c = getc(file)) != EOF) {
                {
                    if (c == '\n') {
                        if ((c = getc(file)) == EOF)
                            break;
                    }
                    NA = toNA(c);
                    NA <<= i;
                    buff |= NA;
                }
            }
        }
        fwrite(&buff, sizeof(unsigned char), 1, bfile);
        buff = 0;
    }
    fclose(file);
    fclose(bfile);
}


/******************************************************************************/
void unzip(const char *zipped_file, const char *unzipped_file) {
    Nucleic_acid c = 0;
    unsigned int seq_len;
    int header_size=0;
    FILE *file, *bfile;

    unsigned char buff=0;
    unsigned char mask = 0b11;
    unsigned char temp = 0;

    bfile = fopen(zipped_file, "rb");
    file = fopen(unzipped_file, "w");

    fread(&header_size, sizeof(unsigned char), 1, bfile);
    char header[header_size];
    header[header_size]='\0';

    fread(header, sizeof(unsigned char), header_size , bfile);

    fread(&seq_len, sizeof(unsigned int), 1, bfile);

    fputs(header, file);

    for (int i = 0; i < seq_len; i += 4) {
        if((i!=0)&&(i%80==0))
                fputc('\n', file);
        fread(&buff, sizeof(unsigned char), 1, bfile);
        for (int j = 0; j<=6; j+=2){

            mask<<=j;
            mask &= buff;
            mask>>=j;
            fputc(toChar(mask), file);
            mask=0b11;
        }
    }

}











