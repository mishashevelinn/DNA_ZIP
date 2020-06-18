#include "dna.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************/
//switch-case, translates char to Nuclear Acid according to ENUM
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
//switch case translates nuclear acid(number) to Char
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
//calculates the number of characters in dna code sequence
unsigned int dna_seq_length(const char *unzipped_file) {
    int counter = 0;
    char c;
    char buffer[MAX_HEADER_LENGTH]; //defining a buffer to store the header
    FILE *file_ptr; //opening file for reading
    file_ptr = fopen(unzipped_file, "r");
    if (file_ptr == NULL) {
        printf("FILE NOT FOUND");
        exit(0);
    }

    fgets(buffer, MAX_HEADER_LENGTH, file_ptr); //skip the first line in counting - the name & description of gene
    //counting chars, skipping the
    while ((c = getc(file_ptr)) != EOF) {
        if (c != '\n')  //skipping '/n while counting characters
            counter++;
    }
    fclose(file_ptr);
    return counter;
}

/******************************************************************************/
void zip(const char *unzipped_file, const char *zipped_file) {
    unsigned char buff = 0; //buffer to store a binary value
    char c;                 //buffer to store a character while reading from text file
    char *header = NULL;    //buffer to store the header as text
    unsigned int seq_len;   //store the sequence length here
    Nucleic_acid NA;        //buffer to store the Nuclear Acid type object after translation
    FILE *file, *bfile;

    size_t header_size;     //preparing to getline call
    ssize_t line_length;

    file = fopen(unzipped_file, "r");   //opening text file for reading
    bfile = fopen(zipped_file, "wb");   //opening binary file for writing
    if (file == NULL) {
        printf("FILE NOT FOUND");
        exit(0);
    }

    line_length = getline(&header, &header_size, file);     //reading the header and storing its length to line_length
    fwrite(&line_length, sizeof(unsigned char), 1, bfile);  //writing header length
    fprintf(bfile, header, "%s");                           //writing header itself

    seq_len = dna_seq_length(unzipped_file);               //computing the length of DNA sequence
    fwrite(&seq_len, sizeof(unsigned int), 1, bfile);     //writing sequence length

    int i, j;
    //loops though the sequence and for each 4 characters, translates it to two-bits-long code, according to Nuclear_Acid
    //Enum, defined in dna.h, stores each two bits in buff(binary) and writes it to bin. file
    for (j = 0; j < seq_len; j += 4) {
        for (i = 0; i <= 6; i += 2) {
            if ((c = getc(file)) != EOF) {
                {
                    if (c == '\n') {
                        if ((c = getc(file)) == EOF)
                            break;
                    }
                    NA = toNA(c);//translate character to Nuclear_Acid
                    NA <<= i;    //shift its bits i times left
                    buff |= NA;   //logical and with buff, which is zero in first iteration, stores in buff each iteration
                }                  //the binary code of certain Nuclear_Acid
            }
        }
        fwrite(&buff, sizeof(unsigned char), 1, bfile);//after 4 inner iterations all 8 bits of buff are full
        buff = 0;                               //so write it to bin. file and nullify the buffer for next outer iteration
    }
    fclose(file);
    fclose(bfile);
    free(header);   //since getline allocates memory, free it
}


/******************************************************************************/
void unzip(const char *zipped_file, const char *unzipped_file) {
    Nucleic_acid c = 0;
    unsigned int seq_len = 0;
    int header_size = 0;
    FILE *file, *bfile;

    unsigned char buff = 0;
    unsigned char mask = 0b11;
    unsigned char temp = 0;

    bfile = fopen(zipped_file, "rb");
    file = fopen(unzipped_file, "w");

    fread(&header_size, sizeof(unsigned char), 1, bfile); //reading from binary file the header size and store it.

    char header[header_size];               //define buffer for header using size, computed in line above
    header[header_size] = '\0';               //make sure there is an end of the line

    fread(header, sizeof(unsigned char), header_size, bfile);  //now reading to header the header itself from bin. file

    fread(&seq_len, sizeof(unsigned int), 1, bfile);    //reading the length of gene sequence

    fputs(header, file);                                //writing the header to txt file
    int i, j;
    for (i = 0; i < seq_len; i += 4) {
        if ((i != 0) && (i % 80 == 0))                 //printing /n each 80 chars
            fputc('\n', file);
        fread(&buff, sizeof(unsigned char), 1, bfile);  //reading 8 bits in each external iteration
        for (j = 0; j <= 6; j += 2) {

            mask <<= j;                                 //mask looks like 00 00 00 11, left shift it j times
            c = mask & buff;            //logical and with buff gives the two least significant bits of buff
            c >>= j;                    //now let's take it back j times
            fputc(toChar(c), file);     //translate Nuclear_Acid to char and print write it to file
            mask = 0b11;                //take the mask to its primal value in the end of each iteration
        }
    }

}











