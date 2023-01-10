#include <stdio.h>
#include <stdlib.h>
#include "../include/CrippleMD.h"

int main(){

    FILE *inFile = fopen("example.md", "r");
    FILE *outFile = stdout;
    /*FILE *outFile = fopen("out.html", "w");*/

    if (inFile == NULL){
	printf("No input file\n");
	return 1;
    }


    Metadata *metadata = malloc(sizeof(Metadata));

    if (parse_md_metadata(inFile, outFile, metadata) == 1){
	printf("Incorrect format\n");
	return 1;
    }

    parse_md(inFile, outFile);

    free(metadata);
    fclose(inFile);
    fclose(outFile);

    return 0;
}
