#include "hashmap.h"

struct tokenHashmap *initTokenHashmap()
{
    struct tokenHashmap *newMap = malloc(sizeof(struct tokenHashmap));

    newMap->size = HASHMAP_SIZE;

    for (int i = 0; i < HASHMAP_SIZE; i++)
        newMap->array[i] = NULL;

    return newMap;
}

int hash(char *token)
{
    long hash = 0;
    for (int i = 0; i < strlen(token); i++)
        hash += (token[i] * (i + 1)) % HASHMAP_SIZE;
    return hash % HASHMAP_SIZE;
}

void addOccurenceToMap(struct tokenHashmap *hashmap, char *token)
{
    struct hashTokenListElem **headPtr = &(hashmap->array[hash(token)]);

    if (*headPtr == NULL)
    {
        struct hashTokenListElem *newElem = malloc(sizeof(struct hashTokenListElem));
        newElem->token = strdup(token);
        newElem->count = 1;
        newElem->pNext = NULL;
        *headPtr = newElem;
    }
    else
    {
        struct hashTokenListElem *runnerPtr = *headPtr;
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
                struct hashTokenListElem *newElem = malloc(sizeof(struct hashTokenListElem));
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

int getOccurenceFromMap(struct tokenHashmap *hashmap, char *token)
{
    struct hashTokenListElem *pRunner = (hashmap->array[hash(token)]);

    while (pRunner)
    {
        if (strcmp(token, pRunner->token) == 0)
            return pRunner->count;

        pRunner = pRunner->pNext;
    }

    return 0;
}

void freeHashmap(struct tokenHashmap *hashmap)
{
    for (int i = 0; i < hashmap->size; i++)
        freeHashTokenList(&(hashmap->array[i]));

    free(hashmap);
}

void freeHashTokenList(struct hashTokenListElem **pHead)
{
    struct hashTokenListElem *pSub;

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