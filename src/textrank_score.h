/** @file */

#ifndef TEXTRANK_SCORE
#define TEXTRANK_SCORE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "token.h"
#include "hashmap.h"
#include "count_import.h"
#include "textrank_graph.h"

/**
 * @brief Process TextRank scores 
 * 
 * @param graph Pointer to the graph
 * @param iterations Number of algorithm iterations
 */
void processTextRankIterations(struct textRankNodeListElem *graph, int iterations);

/**
 * @brief Gives score of one node to all set as adjacent proportionally to the "weight" of connection
 * 
 * @param giverNode Pointer to the node that gives its score
 */
void donateTextRankScore(struct textRankNode *giverNode);

/**
 * @brief Iterates over all nodes and updates its scores (nextScore becomes currentScore)
 * 
 * @param graph Pointer to the graph
 */
void updateTextRankScores(struct textRankNodeListElem *graph);

/**
 * @brief Multiplies each node score by inverse document frequency of a node
 * 
 * @param graph pointer to graph
 * @param cntData pointer to count data
 */
void multiplyTextRankScoresByIdf(struct textRankNodeListElem *graph, struct countData *cntData);

#endif