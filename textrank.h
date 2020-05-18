/** @file */

#ifndef TEXTRANK
#define TEXTRANK

#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "hashmap.h"
#include "count_import.h"
#include "textrank_graph.h"
#include "textrank_score.h"

/**
 * @brief Get the Text Rankf Keywords list
 * 
 * @param expectedKeywords number of keywords to extract
 * @param tokenHead list of tokens - tokenized article
 * @param cntData occurence data of all words
 * @param idf 1 if scores shall be multiplied by the idf factor, 0 otherwise
 * @param adjacencyWindow How far can a word be from the other to be concidered "close"
 * @param iterations Number of algotithm iterations
 * @return struct tokenListElem* list of keywords
 */
struct tokenListElem *getTextRankfKeywords(int expectedKeywords, struct tokenListElem *tokenHead, struct countData *cntData, int idf, int adjacencyWindow, int iterations);

/**
 * @brief Compares two TextRank nodes by their score
 * 
 * @param a first TextRank node
 * @param b second TextRank node
 * @return int 1 if first is lower, -1 if bigger and 0 if same score 
 */
int textRankSortingComparator(const void *a, const void *b);

#endif