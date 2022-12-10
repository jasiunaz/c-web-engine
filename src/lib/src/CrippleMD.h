#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100
  
int parse_md(FILE *inFile, FILE *outFile);
int read_clean_buffer(FILE *inFIle, char *buffer);
void partial_read_cleanup(FILE *inFile, char *buffer);
int parse_heading();
int parse_paragraph();
int parse_line_break();
int parse_ordered_list();
int parse_list();
int parse_link();
int parse_formated_link();
int parse_image();
int parse_bold();
int parse_italic();
