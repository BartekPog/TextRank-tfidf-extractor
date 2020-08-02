/** @file */

#include <stdlib.h>
#include <stdio.h>

#include "handle_input.h"
#include "hashmap.h"
#include "token.h"
#include "count_import.h"
#include "rewrite.h"
#include "files_test.h"

int main(int argc, char *argv[])
{
    if (!areParamsOk(argc, argv))
    {
        printf("ERR: Invalid input parameters!\n\n");
        printf("To set custom parameters use:\n -i\tSet input file\n -o\tSet output file\n -k Set number of keywords to extract per algorithm\n -w Set TextRank adjacency window size\n\n");
        return 0;
    }

    struct inputParameters *params = handleInput(argc, argv);

    if (!isInputFileOk(params->inFile))
    {
        printf("ERR: Wrong input file!\n\n");
        printf("Input file shall be a CSV file with forced quoting consisting of three columns HEADING, ARTICLE, TOKENS without headers line\n\n");
        freeInputParameters(params);
        return 0;
    }

    FILE *inFile = fopen(params->inFile, "r");

    if (!inFile)
    {
        printf("ERR: cannot open input file\n");
        fclose(inFile);
        freeInputParameters(params);
        return 0;
    }

    printf("Counting words and documents\n");
    struct countData *cntData = getCountData(inFile);

    FILE *outFile = fopen(params->outFile, "w");

    printf("Rewriting with keywords\n");
    rewriteWithKeywords(inFile, outFile, cntData, params->keywordNum, params->adjacencyWidnow);

    printf("Cleaning memory\n");
    fclose(outFile);
    fclose(inFile);
    freeCountData(&cntData);
    freeInputParameters(params);

    printf("Done\n");

    return 0;
}