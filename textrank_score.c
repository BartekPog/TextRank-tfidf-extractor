#include "textrank_score.h"

void processTextRankIterations(struct textRankNodeListElem *graph, int iterations)
{
    if (!graph)
    {
        printf("ERR: Cannot process TextRank scores out of an empty graph\n");
        return;
    }

    for (int i = 0; i < iterations; i++)
    {
        struct textRankNodeListElem *graphRunner = graph;

        while (graphRunner)
        {
            donateTextRankScore(graphRunner->node);
            graphRunner = graphRunner->pNext;
        }

        updateScores(graph);
    }
}

void donateTextRankScore(struct textRankNode *giverNode)
{
    double donatedValue = (giverNode->currentScore) / (giverNode->adjacentNum);

    struct textRankNodeListElem *adjacentRunner = giverNode->adjacentHead;

    while (adjacentRunner)
    {
        adjacentRunner->node->nextScore += donatedValue;
        adjacentRunner = adjacentRunner->pNext;
    }
}

void updateScores(struct textRankNodeListElem *graph)
{
    while (graph)
    {
        graph->node->currentScore = graph->node->nextScore;
        graph->node->nextScore = 0;
        graph = graph->pNext;
    }
}