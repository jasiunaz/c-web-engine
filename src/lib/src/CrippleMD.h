#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024
  
int parse_md(FILE *inFile, FILE *outFile);
int readBuffer(FILE *inFile, char *buffer);
