#include "CrippleMD.h"

void fill_blocks(Md_block *blocks){
    for(int i = 0; i < 4; ++i){
	blocks[i].set = 0;
	blocks[i].level = 0;
    }
    strncpy(blocks[ITALIC_INDEX].html_open, "<em>", 4);
    strncpy(blocks[ITALIC_INDEX].html_close, "<\\em>", 5);
    strncpy(blocks[BOLD_INDEX].html_open, "<b>", 4);
    strncpy(blocks[BOLD_INDEX].html_close, "<\\b>", 5);
    strncpy(blocks[HEADING_INDEX].html_open, "<em%d>", 4);
    strncpy(blocks[HEADING_INDEX].html_close, "<\\em%d>", 5);
    strncpy(blocks[PARAGRAPH_INDEX].html_open, "<p>", 4);
    strncpy(blocks[PARAGRAPH_INDEX].html_close, "<\\p>", 5);
}
