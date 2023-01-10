#include <stdio.h>
#include <stdlib.h>
#include "CrippleMD.h"

int main(){

    FILE *inFile = fopen("in.txt", "r");
    FILE *outFile = stdout;
    /*FILE *outFile = fopen("out.txt", "w");*/

    parse_md(inFile, outFile);

    return 0;
}
