/** @file */
#ifndef TOKEN
#define TOKEN

#include <stdio.h>
#include <stdlib.h>

/** Element of the text token linked list*/
struct tokenListElem
{
    char *token;                 ///< Word token
    struct tokenListElem *pNext; ///< Pointer to the next element
};

/** List of the tokens that were present at least once in the document*/
struct localTokensListElem
{
    char *token;                       ///< String containing the token
    struct localTokensListElem *pNext; ///< Pointer to the next element
};

struct allTokensListElem
{
    char *token;                     ///< String containing the token
    int count;                       ///< In how many documents has occured
    struct allTokensListElem *pNext; ///< Pointer to the next element
};

/**
 * @brief Adds token to token list
 * 
 * @param pHead Pointer to the list head pointer
 * @param token Text token
 */
void addToTokenList(struct tokenListElem **pHead, char *token);

/**
 * @brief Adds token to local token list
 * 
 * @param pHead Pointer to the list head pointer
 * @param token Text token
 */
void addToLocalTokenList(struct localTokensListElem **pHead, char *token);

/**
 * @brief Increments the count of documents with this token or creates a new element if one does not exist
 * 
 * @param pHead Pointer to the list head pointer
 * @param token Text token
 */
void addOccurence(struct allTokensListElem **pHead, char *token);

/**
 * @brief Frees the memory taken by the list and nullifies pointer
 * 
 * @param pHead 
 */
void freeTokenList(struct tokenListElem **pHead);

/**
 * @brief Frees the memory taken by the list and nullifies pointer
 * 
 * @param pHead 
 */
void freeLocalTokenList(struct localTokensList **pHead);

/**
 * @brief Frees the memory taken by the list and nullifies pointer
 * 
 * @param pHead 
 */
void freeAllTokensList(struct allTokensListElem **pHead);

#endif