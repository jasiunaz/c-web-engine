#include "CrippleMD.h"

int parse_md(FILE *inFile, FILE *outFile){
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL){
	return 1;
    }

    int elements_read = BUFFER_SIZE;

    while (elements_read == BUFFER_SIZE){
	elements_read = fread(buffer, sizeof(char), BUFFER_SIZE, inFile);

	if (*(buffer + BUFFER_SIZE - 1) != ' ' || *(buffer + BUFFER_SIZE - 1) != '\n' && elements_read == BUFFER_SIZE){
	    partial_read_cleanup(inFile, buffer);
	}
	if(elements_read != BUFFER_SIZE){			    // Jeigu paskutinis bufferis, kad no garbage
	    *(buffer + elements_read) = '\0';
	}

	// TODO Literally everything else

	printf("%s", buffer);
    }

    free(buffer);

    return 0;
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
