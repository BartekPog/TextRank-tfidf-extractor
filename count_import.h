/** @file */
#ifndef COUNT_IMPORT
#define COUNT_IMPORT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "token.h"
#include "reading_utils.h"

/** Structure returned after first reading of the document */
struct countData
{
    int documentsNumber;             ///< Number of documents in a file
    struct tokenHashmap *occurences; ///< Hashmap containing the number of documents with particular token
};

/**
 * @brief Get the countData object pointer, Does not change the file pointer
 * 
 * @param file pointer to the file
 * @return struct countData* pointer to newly created object containing basic info about document 
 */
struct countData *getCountData(FILE *file);

/**
 * @brief Frees the memory taken by countData
 * 
 * @param data pointer to the data pointer
 */
void freeCountData(struct countData **data);

#endif