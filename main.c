#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"
#include "token.h"
#include "count_import.h"
#include "rewrite.h"

#define DEFAULT_IN_FILE "data/prepared.csv"
#define DEFAULT_OUT_FILE "data/sample_out.csv"

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
 * - Write Tf-idf algorithm
 * - Update Rewrite.c - Test writing to file on tf-idf
 * - Write textrank
 * - test both
 * - handle start parameters 
 * - handle errors
 * - write documentation
 * 
 * @return int 
 */

int main()
{
    printf("test\n");

    FILE *inFile = fopen(DEFAULT_IN_FILE, "r");

    if (!inFile)
    {
        printf("ERR: cannot open file\n");
        fclose(inFile);
        return 0;
    }

    printf("Counting words and documents\n");
    struct countData *cntData = getCountData(inFile);

    FILE *outFile = fopen(DEFAULT_OUT_FILE, "w");

    printf("Rewriting with keywords\n");
    rewriteWithKeywords(inFile, outFile, cntData, 3);

    printf("Cleaning memory\n");
    fclose(outFile);
    fclose(inFile);
    freeCountData(&cntData);

    return 0;
}