#include "CrippleMD.h"

int parse_md(FILE *inFile, FILE *outFile){
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));
    Md_block *tracker_blocks = calloc(sizeof(Md_block), SINGLETON_AMOUNT);
    if (buffer == NULL || tracker_blocks == NULL){
	return 1;
    }
    fill_blocks(tracker_blocks);

    int elements_read = BUFFER_SIZE;
    char last_char = '\n';

    while (elements_read == BUFFER_SIZE){
	elements_read = read_clean_buffer(inFile, buffer);

	for (int i = 0; i < BUFFER_SIZE; ++i){
	    char current_char = buffer[i];

	    switch (current_char){
		case '#':
		    parse_heading(current_char, last_char, tracker_blocks);
		    break;
		case '*':
		    parse_bold(current_char, last_char, tracker_blocks);
		    break;
		case '_':
		    parse_italic(current_char, last_char, tracker_blocks);
		    break;
		case '\n':
		    end_all_blocks(current_char, last_char, tracker_blocks);
		    break;
		case '\\': // Runs through to default and prints next character
		    ++i;
		default:
		    fprintf(outFile, "%c", buffer[i]);
	    }
	}
    }

    return 0;
}

/*int parse_md(FILE *inFile, FILE *outFile){*/
    /*char *buffer = calloc(BUFFER_SIZE, sizeof(char));*/
    /*Md_block *blocks = calloc(sizeof(Md_block), SINGLETON_AMOUNT);*/
    /*if (buffer == NULL || blocks == NULL){*/
	/*return 1;*/
    /*}*/
    /*fill_blocks(blocks);*/

    /*int elements_read = BUFFER_SIZE;*/
    /*char last_char = '\n';*/

    /*while (elements_read == BUFFER_SIZE){*/

	/*elements_read = read_clean_buffer(inFile, buffer);*/

	/*for(int i = 0; i < BUFFER_SIZE && CUR_CHAR != '\0'; ++i){*/
	    /*if ((CUR_CHAR == '#' && last_char == '\n') || (CUR_CHAR == '#' && last_char == '#') || (blocks[HEADING_INDEX].level != 0)){*/
		/*blocks[HEADING_INDEX].level += 1;*/
		/*if (CUR_CHAR == ' '){*/
		    /*blocks[HEADING_INDEX].level -= 1;*/
		    /*fprintf(outFile, "<h%d>", blocks[HEADING_INDEX].level);*/
		    /*blocks[HEADING_INDEX].set = 1; */
		    /*last_char = CUR_CHAR;*/

		    /*sprintf(blocks[HEADING_INDEX].html_close, "</h%d>", blocks[HEADING_INDEX].level);*/
		    /*blocks[HEADING_INDEX].level = 0;*/
		    /*continue;*/
		/*}*/
	    /*}*/
	    /*if (CUR_CHAR != '#' && last_char == '\n'){*/
		/*fprintf(outFile, "%s", blocks[PARAGRAPH_INDEX].html_open);*/
		/*blocks[PARAGRAPH_INDEX].set = 1;*/
		/*last_char = CUR_CHAR;*/
	    /*}*/
	    /*if (CUR_CHAR == '*' && blocks[BOLD_INDEX].set == 0){*/
		/*blocks[BOLD_INDEX].set = 1;*/
		/*fprintf(outFile, "%s", blocks[BOLD_INDEX].html_open);*/
		/*last_char = CUR_CHAR;*/
		/*continue;*/
	    /*}*/
	    /*else if (CUR_CHAR == '*' && blocks[BOLD_INDEX].set == 1){*/
		/*blocks[BOLD_INDEX].set = 0;*/
		/*fprintf(outFile, "%s", blocks[BOLD_INDEX].html_close);*/
		/*last_char = CUR_CHAR;*/
		/*continue;*/
	    /*}*/
	    /*if (CUR_CHAR == '_' && blocks[ITALIC_INDEX].set == 0){*/
		/*blocks[ITALIC_INDEX].set = 1;*/
		/*fprintf(outFile, "%s", blocks[ITALIC_INDEX].html_open);*/
		/*last_char = CUR_CHAR;*/
		/*continue;*/
	    /*}*/
	    /*else if (CUR_CHAR == '_' && blocks[ITALIC_INDEX].set == 1){*/
		/*blocks[ITALIC_INDEX].set = 0;*/
		/*fprintf(outFile, "%s", blocks[ITALIC_INDEX].html_close);*/
		/*last_char = CUR_CHAR;*/
		/*continue;*/
	    /*}*/
	    /*if (CUR_CHAR == '\n'){*/
		/*for(int i = 0; i < SINGLETON_AMOUNT; ++i){*/
		    /*if (blocks[i].set == 1){*/
			/*fprintf(outFile, "%s\n", blocks[i].html_close);*/
			/*blocks[i].level = 0;*/
			/*blocks[i].set = 0;*/
		    /*}*/
		/*}*/
		/*last_char = CUR_CHAR;*/
		/*continue;*/
	    /*}*/
	    /*if (CUR_CHAR != '#'){*/
		/*fprintf(outFile, "%c", CUR_CHAR);*/
	    /*}*/
	/*}*/
    /*}*/

    /*free(buffer);*/

    /*return 0;*/
/*}*/

int read_clean_buffer(FILE *inFile, char *buffer){
	int elements_read = fread(buffer, sizeof(char), BUFFER_SIZE, inFile);

	if (*(buffer + BUFFER_SIZE - 1) != ' ' || *(buffer + BUFFER_SIZE - 1) != '\n' && elements_read == BUFFER_SIZE){
	    partial_read_cleanup(inFile, buffer);
	}
	if(elements_read != BUFFER_SIZE){			    // Jeigu paskutinis bufferis, kad no garbage
	    *(buffer + elements_read) = '\0';
	}

	return elements_read;
}

void partial_read_cleanup(FILE *inFile, char *buffer){
    int offset;
    if (strrchr(buffer, ' ') > strrchr(buffer, '\n')){		    // Suranda paskutini space arba newline
	offset = BUFFER_SIZE - (strrchr(buffer, ' ') - buffer + 1);
    }
    else{
	offset = BUFFER_SIZE - (strrchr(buffer, '\n') - buffer + 1);
    }

    *(buffer + BUFFER_SIZE - offset) = '\0';			    // Uzbaigia bufferi ties \n arba space
    fseek(inFile, -(offset), SEEK_CUR);				    // Pastumia cursoriu atgal
    return;
}

void parse_bold(char current_char, char last_char, Md_block *tracker_blocks){

}

void parse_italic(char current_char, char last_char, Md_block *tracker_blocks){

}

void parse_heading(char current_char, char last_char, Md_block *tracker_blocks){

}

void end_all_blocks(char current_char, char last_char, Md_block *tracker_blocks){

}

void fill_blocks(Md_block *blocks){
    for(int i = 0; i < 4; ++i){
	blocks[i].set = 0;
	blocks[i].level = 0;
    }
    strncpy(blocks[ITALIC_INDEX].html_open, "<em>", 6);
    strncpy(blocks[ITALIC_INDEX].html_close, "</em>", 6);
    strncpy(blocks[BOLD_INDEX].html_open, "<b>", 6);
    strncpy(blocks[BOLD_INDEX].html_close, "</b>", 6);
    strncpy(blocks[HEADING_INDEX].html_open, "<h%d>", 6);
    strncpy(blocks[HEADING_INDEX].html_close, "</h%d>", 6);
    strncpy(blocks[PARAGRAPH_INDEX].html_open, "<p>", 6);
    strncpy(blocks[PARAGRAPH_INDEX].html_close, "</p>", 6);
}

/*void fill_blocks(Md_block *blocks){*/
    /*for(int i = 0; i < 4; ++i){*/
	/*blocks[i].set = 0;*/
	/*blocks[i].level = 0;*/
    /*}*/
    /*strncpy(blocks[ITALIC_INDEX].html_open, "<em>", 6);*/
    /*strncpy(blocks[ITALIC_INDEX].html_close, "</em>", 6);*/
    /*strncpy(blocks[BOLD_INDEX].html_open, "<b>", 6);*/
    /*strncpy(blocks[BOLD_INDEX].html_close, "</b>", 6);*/
    /*strncpy(blocks[HEADING_INDEX].html_open, "<h\%d>", 6);*/
    /*strncpy(blocks[HEADING_INDEX].html_close, "", 6);*/
    /*strncpy(blocks[PARAGRAPH_INDEX].html_open, "<p>", 6);*/
    /*strncpy(blocks[PARAGRAPH_INDEX].html_close, "</p>", 6);*/
/*}*/

