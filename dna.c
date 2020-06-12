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
	if(c!=0 &&  c!=1 && c!=2 && c!=3 ){
	    printf("Undefined Value Error\n");
	    exit(1);
	}
    return (unsigned char) c;
}

/******************************************************************************/
unsigned int dna_seq_length(const char* unzipped_file) {
	// YOUR CODE HERE
}

/******************************************************************************/
void zip(const char* unzipped_file, const char* zipped_file) {
	// YOUR CODE HERE
}

/******************************************************************************/
void unzip(const char* zipped_file, const char* unzipped_file) {
	// YOUR CODE HERE
}
