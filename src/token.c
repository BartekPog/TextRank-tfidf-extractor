#include "token.h"

void addToTokenList(struct tokenListElem **pHead, char *token)
{
    struct tokenListElem *newElem = malloc(sizeof(struct tokenListElem));
    newElem->token = strdup(token);
    newElem->pNext = *pHead;
    *pHead = newElem;
}

void addToOccurenceList(struct occurenceListElem **pHead, char *token)
{
    if (*pHead == NULL)
    {
        struct occurenceListElem *newElem = malloc(sizeof(struct occurenceListElem));
        newElem->token = strdup(token);
        newElem->count = 1;
        newElem->pNext = NULL;
        *pHead = newElem;
    }
    else
    {
        struct occurenceListElem *runnerPtr = *pHead;
        int shallContinue = 1;
        while (shallContinue)
        {
            if (strcmp(runnerPtr->token, token) == 0)
            {
                runnerPtr->count++;
                shallContinue = 0;
            }
            else if (runnerPtr->pNext == NULL)
            {
                struct occurenceListElem *newElem = malloc(sizeof(struct occurenceListElem));
                newElem->token = strdup(token);
                newElem->count = 1;
                newElem->pNext = NULL;
                runnerPtr->pNext = newElem;
                shallContinue = 0;
            }
            else
                runnerPtr = runnerPtr->pNext;
        }
    }
}

void freeTokenList(struct tokenListElem **pHead)
{
    struct tokenListElem *pSub;

    while (*pHead)
    {
        pSub = (*pHead)->pNext;
        free((*pHead)->token);
        free(*pHead);
        *pHead = pSub;
    }

    *pHead = NULL;
    return;
}

int getOccurenceListLength(struct occurenceListElem *pHead)
{
    int cnt = 0;
    while (pHead)
    {
        pHead = pHead->pNext;
        cnt++;
    }
    return cnt;
}

void freeOccurenceList(struct occurenceListElem **pHead)
{
    struct occurenceListElem *pSub;

    while (*pHead)
    {
        pSub = (*pHead)->pNext;
        free((*pHead)->token);
        free(*pHead);
        *pHead = pSub;
    }

    *pHead = NULL;
    return;
}