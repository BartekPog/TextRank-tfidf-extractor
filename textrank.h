/** @file */

#ifndef TEXTRANK
#define TEXTRANK

#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "hashmap.h"
#include "count_import.h"
#include "textrank_graph.h"

#define ADJACENT_WINDOW 3

/**
 * @brief Get the Text Rankf Keywords list
 * 
 * @param expectedKeywords number of keywords to extract
 * @param tokenHead list of tokens - tokenized article
 * @param cntData occurence data of all words
 * @param idf 1 if scores shall be multiplied by the idf factor, 0 otherwise
 * @return struct tokenListElem* list of keywords
 */
struct tokenListElem *getTextRankfKeywords(int expectedKeywords, struct tokenListElem *tokenHead, struct countData *cntData, int idf);

// TODO

#endif