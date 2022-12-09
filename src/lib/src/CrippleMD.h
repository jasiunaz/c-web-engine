#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100
  
int parse_md(FILE *inFile, FILE *outFile);
void partial_read_cleanup(FILE *inFile, char *buffer);
