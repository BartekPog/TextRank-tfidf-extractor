#include <stdlib.h>
#include <stdio.h>

#include "handle_input.h"
#include "hashmap.h"
#include "token.h"
#include "count_import.h"
#include "rewrite.h"

/**
 * @brief main algorithm
 * 
 * Reading and counting the number of documents and word occurences (via hashmap)
 * 
 * reading once again and counting TF_IDF and TEXTRANK
 *  with rewriting to output file 
 * 
 * freeing the memory
 * 
 * EXTRA:
 * - Update hashmap to fit in tf-idf
 * 
 * 
 * NOTES:
 * - columns: HEADING, TEXT, PREPARED_TEXT
 * 
 * TODO:
 * - handle start parameters 
 * - handle errors
 * - write documentation
 * 
 * @return int 
 */

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

    return 0;
}