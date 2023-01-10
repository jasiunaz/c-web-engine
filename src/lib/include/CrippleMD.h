#ifndef CRIPPLE_MD_H
#define CRIPPLE_MD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define BLOCK_COUNT 4

enum block_indexes {italic, bold, heading, paragraph};


/*
 *To track which of the md blocks are open
 *and store their html tags
 */
typedef struct Md_block {
    int open;
    char html_open[6];
    char html_close[6];
    int level;
} Md_block;

typedef struct Metadata {
    char title[256];
    char category[256];
    int year;
    int month;
    int day;
} Metadata;

int parse_md_metadata(FILE *inFile, FILE *outFile, Metadata *metadata);
int parse_md(FILE *inFile, FILE *outFile);

void parse_bold(Md_block *tracker_blocks, FILE *outFile);
void parse_italic(Md_block *tracker_blocks, FILE *outFile);
void parse_heading(char current_char, char last_char, Md_block *tracker_blocks, FILE *outFile);
void parse_paragraph(Md_block *tracker_blocks, FILE *outFile);
void end_all_blocks(char current_char, char last_char, Md_block *tracker_blocks, FILE *outFile);

int read_clean_buffer(FILE *inFile, char *buffer);
void partial_read_cleanup(FILE *inFile, char *buffer);
void fill_blocks(Md_block *blocks);

#endif
