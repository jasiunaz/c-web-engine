#include "CrippleMD.h"

int parse_md(FILE *inFile, FILE *outFile){
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL){
	return 1;
    }

    int elements_read = BUFFER_SIZE;
    int escape;

    while (elements_read == BUFFER_SIZE){

	elements_read = read_clean_buffer(inFile, buffer);

	for(int i = 0; i < elements_read; ++i){

	    switch (buffer[i]){				// Galimai reikia parse funkcijas 
		case '#':
		    parse_heading(buffer, i);
		    break;
		case '\n':
		    parse_paragraph(buffer, i);
		    break;
		case ' ':
		    parse_line_break(buffer, i);
		    break;
		case '1':
		    parse_ordered_list(buffer, i);
		    break;
		case '-':
		    parse_list(buffer, i);
		    break;
		case '<':
		    parse_link(buffer, i);
		    break;
		case '[':
		    parse_formated_link(buffer, i);	// Markdowne vienoda sintakse ir nuotraukoms ir linkams
		    parse_image(buffer, i);		// Turbut reikia padaryti kazka kad atpazinti tekste image extensiona
		    break;
		case '_':
		    parse_bold(buffer, i);
		    break;
		case '*':
		    parse_italic(buffer, i);
		    break;
		case '\\':
		    ++i;			// Escape char, kad galetum deti # ir kitus special chars
		default:
		    fprintf(outFile, "%c", buffer[i]);
		    break;
	    }
	}
    }

    free(buffer);

    return 0;
}

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

int parse_paragraph(char *buffer, int index){
    return 0;
}

int parse_line_break(char *buffer, int index){
    return 0;
}

int parse_ordered_list(char *buffer, int index){
    return 0;
}

int parse_list(char *buffer, int index){
    return 0;
}

int parse_heading(char *buffer, int index){
    return 0;
}

int parse_link(char *buffer, int index){
    return 0;
}

int parse_formated_link(char *buffer, int index){
    return 0;
}

int parse_image(char *buffer, int index){
    return 0;
}

int parse_bold(char *buffer, int index){
    return 0;
}

int parse_italic(char *buffer, int index){
    return 0;
}
