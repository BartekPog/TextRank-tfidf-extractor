/** @file */

#ifndef TEXTRANK_GRAPH
#define TEXTRANK_GRAPH

#include <stdlib.h>

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
 * @brief Creates a connection between words in graph
 * 
 * @param token1 first word to connect
 * @param token2 second word to connect
 * @param nodesHead head of the nodes list
 */
void addTextRankWordConection(char *token1, char *token2, struct textRankNodeListElem *nodesHead);

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

#endif