/** @file */
#ifndef TOKEN
#define TOKEN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Element of the text token linked list*/
struct tokenListElem
{
    char *token;                 ///< Word token
    struct tokenListElem *pNext; ///< Pointer to the next element
};

/** List of the tokens that were present at least once in the document*/
struct occurenceListElem
{
    char *token;                     ///< String containing the token
    int count;                       ///< Occurence counter
    struct occurenceListElem *pNext; ///< Pointer to the next element
};

/**
 * @brief Adds token to token list on head position
 * 
 * @param pHead Pointer to the list head pointer
 * @param token Text token
 */
void addToTokenList(struct tokenListElem **pHead, char *token);

/**
 * @brief Frees the memory taken by the list and nullifies pointer
 * 
 * @param pHead Pointer to the list head pointer
 */
void freeTokenList(struct tokenListElem **pHead);

/**
 * @brief Increments the word occurence counter or creates new one 
 * 
 * @param pHead Pointer to the list head pointer
 * @param token Text token
 */
void addToOccurenceList(struct occurenceListElem **pHead, char *token);

/**
 * @brief Frees the memory taken by the list and nullifies pointer
 * 
 * @param pHead Pointer to the list head pointer
 */
void freeOccurenceList(struct occurenceListElem **pHead);

#endif