#include <stdio.h>
#include <stdlib.h>
#include "CrippleMD.h"

int main(){

    FILE *inFile = fopen("in.txt", "r");
    FILE *outFile = stdout;
    /*FILE *outFile = fopen("out.txt", "w");*/


    Metadata *metadata = malloc(sizeof(Metadata));

    if (parse_md_metadata(inFile, outFile, metadata) == 1){
	printf("Incorrect format\n");
	return 1;
    }

    printf("\n[METADATA START]\n");
    printf("%s\n%s\n%d-%d-%d", metadata->title, metadata->category, metadata->year, metadata->month, metadata->day);
    printf("\n[METADATA END]\n");


    parse_md(inFile, outFile);

    free(metadata);

    return 0;
}
