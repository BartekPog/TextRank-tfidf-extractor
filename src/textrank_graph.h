/** @file */

#ifndef TEXTRANK_GRAPH
#define TEXTRANK_GRAPH

#include <stdlib.h>
#include <string.h>

#include "token.h"

/** element of nodes list */
struct textRankNodeListElem
{
    struct textRankNode *node;          ///< Node stored in the list
    struct textRankNodeListElem *pNext; ///< Pointer to the next node
};

/** Stores one node data */
struct textRankNode
{
    char *token;                               ///< Word stored in a node
    double currentScore;                       ///< Current score of the node
    double nextScore;                          ///< Score at the end of iteration
    int adjacentNum;                           ///< Number of connected nodes
    struct textRankNodeListElem *adjacentHead; ///< Head of the connected nodes list
};

/**
 * @brief Generates a TextRank graph based on token list
 * 
 * @param tokenHead list of tokens
 * @param adjacencyWindow number of tokens on one side concidered as neighbouring
 * @return struct textRankNodeListElem* pointer to the head of graph list 
 */
struct textRankNodeListElem *generateTextRankGraph(struct tokenListElem *tokenHead, int adjacencyWindow);

/**
 * @brief Connects two nodes - adds each other to lists of adjacent 
 * 
 * @param node1 pointer to first node to connect
 * @param node2 pointer to the second node to connect
 */
void connectTextRankNodes(struct textRankNode *node1, struct textRankNode *node2);

/**
 * @brief Create an empty Text Rank Node 
 * 
 * @param graphHead pointer to the graph head pointer
 * @param token word stored in the new node
 * @return struct textRankNode* newly created text rank node
 */
struct textRankNode *getOrCreateTextRankNode(struct textRankNodeListElem **graphHead, char *token);

/**
 * @brief Get the Text Rank Node Count 
 * 
 * @param graph Pointer to the graph head
 * @return int 
 */
int getTextRankNodeCount(struct textRankNodeListElem *graph);

/**
 * @brief Transforms graph to array of node pointers
 * 
 * @param graph Pointer to the graph head
 * @param nodeCount Number of nodes in the graph
 * @return struct extRankNode* array Array of graph node pointers
 */
struct textRankNode **textRankGraphToArray(struct textRankNodeListElem *graph, int nodeCount);

/**
 * @brief Free memory taken by the node arrray 
 * 
 * @param nodeArray Array of nodes
 * @param length length of array
 */
void freeTextRankNodesArray(struct textRankNode **nodeArray, int length);

#endif