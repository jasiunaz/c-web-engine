#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_BUFFER_SIZE 1024

int parse_md(FILE *input, FILE *output);
int readBuffer(FILE *input, char *buffer);
