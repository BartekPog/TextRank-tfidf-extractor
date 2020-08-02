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

            connectTextRankNodes(current, neighbouring);

            pRunner = pRunner->pNext;
        }
        tokenHead = tokenHead->pNext;
    }

    return graph;
}

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

struct textRankNode *getOrCreateTextRankNode(struct textRankNodeListElem **graphHead, char *token)
{
    if (!(*graphHead))
    {
        *graphHead = malloc(sizeof(struct textRankNodeListElem));
        (*graphHead)->pNext = NULL;

        struct textRankNode *newNode = malloc(sizeof(struct textRankNode));
        newNode->token = strdup(token);
        newNode->currentScore = 1;
        newNode->nextScore = 0;
        newNode->adjacentNum = 0;
        newNode->adjacentHead = NULL;

        (*graphHead)->node = newNode;
        return newNode;
    }

    struct textRankNodeListElem *graphRunner = *graphHead;

    while (graphRunner->pNext)
    {
        if (strcmp(graphRunner->node->token, token) == 0)
            return graphRunner->node;

        graphRunner = graphRunner->pNext;
    }

    if (strcmp(graphRunner->node->token, token) == 0)
        return graphRunner->node;

    graphRunner->pNext = malloc(sizeof(struct textRankNodeListElem));
    graphRunner->pNext->pNext = NULL;

    struct textRankNode *newNode = malloc(sizeof(struct textRankNode));
    newNode->token = strdup(token);
    newNode->currentScore = 1;
    newNode->nextScore = 0;
    newNode->adjacentNum = 0;
    newNode->adjacentHead = NULL;

    graphRunner->pNext->node = newNode;
    return newNode;
}

int getTextRankNodeCount(struct textRankNodeListElem *graph)
{
    int count = 0;
    while (graph)
    {
        count++;
        graph = graph->pNext;
    }

    return count;
}

struct textRankNode **textRankGraphToArray(struct textRankNodeListElem *graph, int nodeCount)
{
    struct textRankNode **nodeArray = malloc(sizeof(struct textRankNode *) * nodeCount);

    struct textRankNodeListElem *graphSub;
    for (int i = 0; i < nodeCount; i++)
    {
        nodeArray[i] = graph->node;

        graphSub = graph->pNext;
        free(graph);
        graph = graphSub;
    }
    return nodeArray;
}

void freeTextRankNodesArray(struct textRankNode **nodeArray, int length)
{
    for (int i = 0; i < length; i++)
    {
        struct textRankNodeListElem *adjRunner = nodeArray[i]->adjacentHead;
        struct textRankNodeListElem *adjRunnerSub;
        while (adjRunner)
        {
            adjRunnerSub = adjRunner->pNext;
            free(adjRunner);
            adjRunner = adjRunnerSub;
        }

        free(nodeArray[i]->token);
        free(nodeArray[i]);
    }
    free(nodeArray);
}