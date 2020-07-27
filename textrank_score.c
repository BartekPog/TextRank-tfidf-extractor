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

        updateTextRankScores(graph);
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

void updateTextRankScores(struct textRankNodeListElem *graph)
{
    while (graph)
    {
        graph->node->currentScore = graph->node->nextScore;
        graph->node->nextScore = 0;
        graph = graph->pNext;
    }
}

void multiplyTextRankScoresByIdf(struct textRankNodeListElem *graph, struct countData *cntData)
{
    while (graph)
    {
        char *token = graph->node->token;

        int numberOfDocsWithToken = getOccurenceFromMap(cntData->occurences, token);

        if (numberOfDocsWithToken == 0)
            graph->node->currentScore = 0;

        double idf = log((cntData->documentsNumber) * 1.0 / numberOfDocsWithToken);

        graph->node->currentScore *= idf;

        graph = graph->pNext;
    }
}
