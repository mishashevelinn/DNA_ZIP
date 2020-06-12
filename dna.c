#include "dna.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {A=0, C=1, G=2, T=3} Nucleic_acid;

/******************************************************************************/
Nucleic_acid toNA(unsigned char c) {
	// YOUR CODE HERE
}

/******************************************************************************/
unsigned char toChar(Nucleic_acid c) {
	// YOUR CODE HERE
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
