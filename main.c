#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"
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
 * @return int 
 */

int main()
{
    printf("test\n");
    struct tokenHashmap *map = initTokenHashmap();

    addOccurenceToMap(map, "one");
    addOccurenceToMap(map, "two");
    addOccurenceToMap(map, "one");
    addOccurenceToMap(map, "one");

    printf("%s: %d\n", "one", getOccurenceFromMap(map, "one"));
    printf("%s: %d\n", "two", getOccurenceFromMap(map, "two"));
    printf("%s: %d\n", "three", getOccurenceFromMap(map, "three"));

    freeHashmap(map);
    return 0;
}