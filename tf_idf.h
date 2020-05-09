/** @file */

#ifndef TF_IDF
#define TF_IDF

#include "token.h"
#include "hashmap.h"
#include "count_import.h"

/** Structure contains token with its Tf-Idf score*/
struct tfIdfToken
{
    char *token;  ///< Potential keyword
    double score; ///< Tf-Idf score
};

/**
 * @brief Gets the Tf-Idf keywords list 
 * 
 * @param expectedKeywords Number of keywords to extract
 * @param tokenHead list of tokens - tokenized article
 * @param cntData occurence data of all words
 * @return struct tokenListElem* head of keywords list 
 */
struct tokenListElem *getTfIdfKeywords(int expectedKeywords, struct tokenListElem *tokenHead, struct countData *cntData);

/**
 * @brief Generates occurence list from token list, makes copy of string
 * 
 * @param tokenHead pointer to head of token list
 * @return struct occurenceListElem* pointer to new occurence list
 */
struct occurenceListElem *getOccurencesFromTokens(struct tokenListElem *tokenHead);

/**
 * @brief Calculates Tf-Idf scores and saves them in an array with length of occurence list 
 * 
 * @param occurenceHead Pointer to the head of occurence list
 * @param occurenceLength Length of occurence list
 * @param cntData occurence data of all words
 * @return struct tfIdfToken* array of tfidf scores with proper tokens
 */
struct tfIdfToken *getTfIdfScores(struct occurenceListElem *occurenceHead, int occurenceLength, struct countData *cntData);

#endif