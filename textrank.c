#include "textrank.h"

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
struct tokenListElem *getTextRankfKeywords(int expectedKeywords, struct tokenListElem *tokenHead, struct countData *cntData, int idf, int adjacencyWindow, int iterations)
{
    if ((!tokenHead) || (expectedKeywords < 1) || (iterations < 1) || (adjacencyWindow < 1))
        return NULL;

    struct textRankNodeListElem *graph = generateTextRankGraph(tokenHead, adjacencyWindow);

    processTextRankIterations(graph, iterations);

    // Multyply by IDF
    if (idf)
        multiplyTextRankScoresByIdf(graph, cntData);

    int nodeCount = getTextRankNodeCount(graph);

    struct textRankNode **nodeArray = textRankGraphToArray(graph, nodeCount);

    // Sorting
    qsort(nodeArray, nodeCount, sizeof(struct textRankNode *), textRankSortingComparator);

    // Adding Keywords
    struct tokenListElem *keywordHead = NULL;

    for (int i = 0; i < expectedKeywords; i++)
    {
        if (i < nodeCount)
            addToTokenList(&keywordHead, nodeArray[i]->token);
        else
            addToTokenList(&keywordHead, " ");
    }

    // Freeing memory
    freeTextRankNodesArray(nodeArray, nodeCount);

    return keywordHead;
}

int textRankSortingComparator(const void *a, const void *b)
{
    double _a = (*((struct textRankNode **)a))->currentScore;
    double _b = (*((struct textRankNode **)b))->currentScore;
    if (_a < _b)
        return 1;
    else if (_a == _b)
        return 0;
    else
        return -1;
}