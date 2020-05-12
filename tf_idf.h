/** @file */

#ifndef TF_IDF
#define TF_IDF

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
 * @brief Calculate tf-idf score for one token
 * 
 * @param token char string containing the token
 * @param inDocOccurences How many times has the word occured in a document
 * @param docLength number of tokens in a document
 * @param cntData pointer to structure with number of documents and token popularity hashmap
 * @return double 
 */
double getOneTfIdfScore(char *token, int inDocOccurences, int docLength, struct countData *cntData);

/**
 * @brief Calculates Tf-Idf scores and saves them in an array with length of occurence list 
 * 
 * @param occurenceHead Pointer to the head of occurence list
 * @param occurenceLength Length of occurence list
 * @param cntData occurence data of all words
 * @return struct tfIdfToken* array of tfidf scores with proper tokens
 */
struct tfIdfToken *getTfIdfScoresArray(struct occurenceListElem *occurenceHead, int occurenceLength, struct countData *cntData);

/**
 * @brief Frees the memory taken by the scores array
 * 
 * @param scoresArr pointer to the first element pointer
 * @param length length of the array
 */
void freeTfIdfScoresArray(struct tfIdfToken **scoresArr, int length);

/**
 * @brief Compares two tf-idf tokens by their score
 * 
 * @param a first tf-idf token
 * @param b second tf-idf token
 * @return int 1 if first is lower, -1 if bigger and 0 if same score 
 */
int tfIdfSortingComparator(const void *a, const void *b);

#endif