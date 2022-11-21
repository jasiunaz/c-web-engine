#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CrippledMD.h"


#define BUFFER_SIZE 1024

int readIntoBuffer(FILE *inFile, FILE *outFile){
    char *readingBuffer = calloc(BUFFER_SIZE, sizeof(char));
    char *extraBuffer = calloc(BUFFER_SIZE, sizeof(char));

    if (readingBuffer == NULL || extraBuffer == NULL){
	return 1;
    }

    int offset = 0, elementsRead = 0;
    int partialRead = 0;

    while ((elementsRead == BUFFER_SIZE || elementsRead == offset) && elementsRead != 0){

	if (partialRead == 1){
	    memcpy(readingBuffer, extraBuffer, sizeof(char) * (BUFFER_SIZE - offset));
	    elementsRead = fread(readingBuffer + (BUFFER_SIZE - offset), sizeof(char), offset, inFile);
	} else{
	    elementsRead = fread(readingBuffer, sizeof(char), BUFFER_SIZE, inFile);
	}

	if (readingBuffer[BUFFER_SIZE - 1] != ' '){
	    offset = (strrchr(readingBuffer, ' ') - readingBuffer) + 1;
	    memcpy(extraBuffer, readingBuffer + offset, sizeof(char) * (BUFFER_SIZE - offset));
	    *(extraBuffer + BUFFER_SIZE - offset + 1) = '\0';
	    *(readingBuffer + offset) = '\0';
	    partialRead = 1;
	} else{
	    partialRead = 0;
	}

	if (feof(inFile)){
	    *(readingBuffer + BUFFER_SIZE - offset + elementsRead - 1) = '\0';
	}
    }
    
    free(readingBuffer);
    free(extraBuffer);
    return 0;
}
