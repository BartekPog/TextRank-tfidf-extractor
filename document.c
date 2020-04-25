#include <document.h>

struct docData *createDocDataFromFile(FILE *fileStream)
{
    if (fileStream)
    {
        struct docData *data = malloc(sizeof(struct docData));
    }
    else
        return NULL;
}

void addToDocListHead(struct docLinkedListElem **pHead, struct document *doc);

void deleteDocData(struct docData *data);