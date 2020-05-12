#include "tf_idf.h"

struct tokenListElem *getTfIdfKeywords(int expectedKeywords, struct tokenListElem *tokenHead, struct countData *cntData)
{
    struct occurenceListElem *occHead = getOccurencesFromTokens(tokenHead);

    int length = getOccurenceListLength(occHead);

    struct tfIdfToken *scoresArr = getTfIdfScoresArray(occHead, length, cntData);

    freeOccurenceList(&occHead);

    //sorting
    qsort(scoresArr, length, sizeof(struct tfIdfToken), tfIdfSortingComparator);

    struct tokenListElem *keywordHead = NULL;

    //adding to list the N best where N is expected keywords
    for (int i = 0; i < expectedKeywords; i++)
    {
        if (i < length)
            addToTokenList(&keywordHead, scoresArr[i].token);
        else
            addToTokenList(&keywordHead, " ");
    }

    freeTfIdfScoresArray(&scoresArr, length);

    return keywordHead;
}

struct occurenceListElem *getOccurencesFromTokens(struct tokenListElem *tokenHead)
{
    struct occurenceListElem *occHead = NULL;
    while (tokenHead)
    {
        addToOccurenceList(&occHead, tokenHead->token);
        tokenHead = tokenHead->pNext;
    }
    return occHead;
}

double getOneTfIdfScore(char *token, int inDocOccurences, int docLength, struct countData *cntData)
{
    if (docLength == 0)
        return 0;
    double tf = inDocOccurences * 1.0 / docLength;

    int numberOfDocsWithToken = getOccurenceFromMap(cntData->occurences, token);

    if (numberOfDocsWithToken == 0)
    {
        printf("ERR: internal error, token %s seems to be nonexistent in all documents set\n", token);
        return 0;
    }

    double idf = log(cntData->documentsNumber * 1.0 / numberOfDocsWithToken);

    return tf * idf;
}

struct tfIdfToken *getTfIdfScoresArray(struct occurenceListElem *occurenceHead, int occurenceLength, struct countData *cntData)
{
    struct tfIdfToken *scoresArr = malloc(sizeof(struct tfIdfToken) * occurenceLength);

    for (int i = 0; i < occurenceLength; i++)
    {
        scoresArr[i].token = strdup(occurenceHead->token);
        scoresArr[i].score = getOneTfIdfScore(occurenceHead->token, occurenceHead->count, occurenceLength, cntData);
        occurenceHead = occurenceHead->pNext;
    }

    return scoresArr;
}

void freeTfIdfScoresArray(struct tfIdfToken **scoresArr, int length)
{
    for (int i = 0; i < length; i++)
        free((*scoresArr)[i].token);
    free(*scoresArr);
    *scoresArr = NULL;
}

int tfIdfSortingComparator(const void *a, const void *b)
{
    double _a = ((struct tfIdfToken *)a)->score;
    double _b = ((struct tfIdfToken *)b)->score;
    if (_a < _b)
        return 1;
    else if (_a == _b)
        return 0;
    else
        return -1;
}
