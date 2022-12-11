#ifndef CRIPPLE_MD_H
#define CRIPPLE_MD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100
#define SINGLETON_AMOUNT 4
#define ITALIC_INDEX 0
#define BOLD_INDEX 1
#define HEADING_INDEX 2
#define PARAGRAPH_INDEX 3
#define CUR_CHAR buffer[i]

typedef struct Md_block {
    int set;
    char html_open[5];
    char html_close[6];
    int level;
} Md_block;
  
int parse_md(FILE *inFile, FILE *outFile);
int read_clean_buffer(FILE *inFIle, char *buffer);
void partial_read_cleanup(FILE *inFile, char *buffer);
void fill_blocks(Md_block *blocks);

#endif
