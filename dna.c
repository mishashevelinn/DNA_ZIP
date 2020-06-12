#include "dna.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {A=0, C=1, G=2, T=3} Nucleic_acid;

/******************************************************************************/
Nucleic_acid toNA(unsigned char c) {
    if(c!=A &&  c!=C && c!=G && c!=T) {
        printf("Gene Format Error\n");
        exit(1);
    }
    return (Nucleic_acid) c;
    }


/******************************************************************************/
unsigned char toChar(Nucleic_acid c) {
    switch (c) {
        case 0: return 'A';
        case 1: return  'C';
        case 2: return 'G';
        case 3: return 'T';
        default: printf("Undefined Value Error\n");
    }
}

/******************************************************************************/
unsigned int dna_seq_length(const char* unzipped_file) {
    int counter = 0;
    char c;
    char buffer[MAX_HEADER_LENGTH];
    FILE *file_ptr;

    file_ptr=fopen(unzipped_file, "r");
    fgets(buffer, MAX_HEADER_LENGTH, file_ptr); //skip the first line in counting
    if (file_ptr==NULL){
        printf("FILE NOT FOUND");
        exit(0);
    }
    while((c = getc(file_ptr)) != EOF){
        if(c != '\n')
            counter++;
    }
    fclose(unzipped_file);
    return counter;
}

/******************************************************************************/
void zip(const char* unzipped_file, const char* zipped_file) {
	// YOUR CODE HERE
}

/******************************************************************************/
void unzip(const char* zipped_file, const char* unzipped_file) {
	// YOUR CODE HERE
}
