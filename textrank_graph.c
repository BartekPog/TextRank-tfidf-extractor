#include "textrank_graph.h"

struct textRankNodeListElem *generateTextRankGraph(struct tokenListElem *tokenHead, int adjacencyWindow)
{
    struct textRankNodeListElem *graph = NULL;

    while (tokenHead)
    {
        struct textRankNode *current = getOrCreateTextRankNode(&graph, tokenHead->token);

        struct tokenListElem *pRunner = tokenHead->pNext;

        for (int i = 0; (i < adjacencyWindow) && (pRunner); i++)
        {
            struct textRankNode *neighbouring = getOrCreateTextRankNode(&graph, pRunner->token);

            connectTextRankNodes(&current, &neighbouring);

            pRunner = pRunner->pNext;
        }
        tokenHead = tokenHead->pNext;
    }

    return graph;
}

// /**
//  * @brief Creates a connection between words in graph
//  *
//  * @param token1 first word to connect
//  * @param token2 second word to connect
//  * @param nodesHead head of the nodes list
//  */
// void addTextRankWordConection(char *token1, char *token2, struct textRankNodeListElem *nodesHead);

void connectTextRankNodes(struct textRankNode *node1, struct textRankNode *node2)
{
    node1->adjacentNum++;
    struct textRankNodeListElem *connection12 = malloc(sizeof(struct textRankNodeListElem));
    connection12->node = node2;
    connection12->pNext = node1->adjacentHead;
    node1->adjacentHead = connection12;

    node2->adjacentNum++;
    struct textRankNodeListElem *connection21 = malloc(sizeof(struct textRankNodeListElem));
    connection21->node = node1;
    connection21->pNext = node2->adjacentHead;
    node2->adjacentHead = connection21;
}

/**
 * @brief Create an empty Text Rank Node 
 * 
 * @param graphHead pointer to the graph head pointer
 * @param token word stored in the new node
 * @return struct textRankNode* newly created text rank node
 */
struct textRankNode *getOrCreateTextRankNode(struct textRankNodeListElem **graphHead, char *token)
{
    //TODO
    if (!(*graphHead))
    {
        // *graphHead = malloc(sizeof)
    }
}