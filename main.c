/** @file */

#include <stdlib.h>
#include <stdio.h>

#include "handle_input.h"
#include "hashmap.h"
#include "token.h"
#include "count_import.h"
#include "rewrite.h"

int main(int argc, char *argv[])
{
    struct inputParameters *params = handleInput(argc, argv);

    FILE *inFile = fopen(params->inFile, "r");

    if (!inFile)
    {
        printf("ERR: cannot open file\n");
        fclose(inFile);
        return 0;
    }

    printf("Counting words and documents\n");
    struct countData *cntData = getCountData(inFile);

    FILE *outFile = fopen(params->outFile, "w");

    printf("Rewriting with keywords\n");
    rewriteWithKeywords(inFile, outFile, cntData, params->keywordNum);

    printf("Cleaning memory\n");
    fclose(outFile);
    fclose(inFile);
    freeCountData(&cntData);
    freeInputParameters(params);

    printf("Done\n");

    return 0;
}