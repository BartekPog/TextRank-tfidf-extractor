#include "tf_idf.h"

/**
 * @brief Gets the Tf-Idf keywords list 
 * 
 * @param expectedKeywords Number of keywords to extract
 * @param tokenHead list of tokens - tokenized article
 * @param cntData occurence data of all words
 * @return struct tokenListElem* head of keywords list 
 */
struct tokenListElem *getTfIdfKeywords(int expectedKeywords, struct tokenListElem *tokenHead, struct countData *cntData)
{
    struct occurenceListElem *occHead = getOccurencesFromTokens(tokenHead);

    int length = getOccurenceListLength(occHead);

    struct tfIdfToken *scoresArr = getTfIdfScores(occHead, length, cntData);

    freeOccurenceList(&occHead);

    //sorting
    struct tokenListElem *keywordHead = NULL;
    //adding to list the N best where N is expected keywords

    free(scoresArr);

    return keywordHead;
}

/**
 * @brief Generates occurence list from token list, makes copy of string
 * 
 * @param tokenHead pointer to head of token list
 * @return struct occurenceListElem* pointer to new occurence list
 */
struct occurenceListElem *getOccurencesFromTokens(struct tokenListElem *tokenHead)
{
    struct occurenceListElem *occHead = NULL;
    while (tokenHead)
    {
        ///TODO
    }
}

/**
 * @brief Calculates Tf-Idf scores and saves them in an array with length of occurence list 
 * 
 * @param occurenceHead Pointer to the head of occurence list
 * @param occurenceLength Length of occurence list
 * @param cntData occurence data of all words
 * @return struct tfIdfToken* array of tfidf scores with proper tokens
 */
struct tfIdfToken *getTfIdfScores(struct occurenceListElem *occurenceHead, int occurenceLength, struct countData *cntData);