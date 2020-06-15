#ifndef DNA_H
#define DNA_H
#define MAX_HEADER_LENGTH 256
typedef enum {A=0, C=1, G=2, T=3} Nucleic_acid;
void zip(const char* unzipped_file, const char* zipped_file);
void unzip(const char* zipped_file, const char* unzipped_file);
unsigned int dna_seq_length(const char* unzipped_file);
Nucleic_acid toNA(unsigned char c);
unsigned char toChar(Nucleic_acid c);
#endif /* DNA_H */
