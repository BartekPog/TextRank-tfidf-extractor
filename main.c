#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"
#include "token.h"
#include "count_import.h"

#define DEFAULT_IN_FILE "data/prepared.csv"

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
 * @return int 
 */

int main()
{
    printf("test\n");

    FILE *inFile = fopen(DEFAULT_IN_FILE, "r");

    if (!inFile)
    {
        printf("ERR: cannot open file\n");
        return 0;
    }

    printf("Counting words and documents\n");
    struct countData *cntData = getCountData(inFile);

    printf("Cleaning memory\n");
    freeCountData(&cntData);

    // struct tokenHashmap *map = initTokenHashmap();

    // addOccurenceToMap(map, "one");
    // addOccurenceToMap(map, "two");
    // addOccurenceToMap(map, "one");
    // addOccurenceToMap(map, "one");

    // printf("%s: %d\n", "one", getOccurenceFromMap(map, "one"));
    // printf("%s: %d\n", "two", getOccurenceFromMap(map, "two"));
    // printf("%s: %d\n", "three", getOccurenceFromMap(map, "three"));

    // freeHashmap(map);

    return 0;
}