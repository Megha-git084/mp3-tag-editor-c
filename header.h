#ifndef HEADER_H   //if not defined to avoid multiple inclusion of header file
#define HEADER_H
#include<stdio.h> //includes standard input ouput library
#include<stdlib.h> //for dynamic memory allocation
#include<string.h> //include string handling functions

#define SUCCESS 0 //macro definition
#define FAILURE 1 //macro definition
//function declartions
int view_tags(char *mp3_file);
int edit_tags(int argc, char *argv[]);//because edit require multiple options  so we use command line arguments
void print_help(void); //which return a guide menu does'nt return anything
unsigned int convert_size(unsigned char size[4]);//size stored in 4 seperate bytes// unsigned char is used to store raw byte data

#endif