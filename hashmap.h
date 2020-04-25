/** @file */

#ifndef HASHMAP
#define HASHMAP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HASHMAP_SIZE
#define HASHMAP_SIZE 10000
#endif

struct hashTokenListElem
{
    char *token;                     ///< String containing the token
    int count;                       ///< In how many documents has occured
    struct hashTokenListElem *pNext; ///< Pointer to the next element
};

struct tokenHashmap
{
    struct hashTokenListElem *array[HASHMAP_SIZE]; ///< Array of hashmap elements
    int size;                                      ///< Size of the hashmap array
};

/**
 * @brief Initializes a hashmap of tokens
 * 
 * @return struct tokenHashmap* pointer to a fresh token hashmap instance 
 */
struct tokenHashmap *initTokenHashmap();

/**
 * @brief Gets the index in hashmap of the element
 * 
 * @param token Element of which the index will be found 
 * @return int Index in hashmap
 */
int hash(char *token);

/**
 * @brief Adds token occurence to the hashmap
 * 
 * @param hashmap Hashmap of the tokens
 * @param token Token whose occurence will be incremented 
 */
void addOccurenceToMap(struct tokenHashmap *hashmap, char *token);

/**
 * @brief Get the occurence count of particular token from hashmap
 * 
 * @param hashmap Hashmap of the tokens
 * @param token Token whose occurence will be returned
 * @return int Occurence count of the token
 */
int getOccurenceFromMap(struct tokenHashmap *hashmap, char *token);

/**
 * @brief Frees the memory taken by the hashmap
 * 
 * @param hashmap pointer to the hashmap instance
 */
void freeHashmap(struct tokenHashmap *hashmap);

/**
 * @brief Frees the memory taken by the list and nullifies pointer
 *
 * @param pHead
 */
void freeHashTokenList(struct hashTokenListElem **pHead);

#endif