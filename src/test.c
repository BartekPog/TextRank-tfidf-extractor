#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "hashmap.h"
#include "token.h"
#include "count_import.h"
#include "rewrite.h"
#include "files_test.h"

#define INPUT_FILE "data/prepared.csv"

int main()
{
    printf("\nTesting\n");

    struct tokenListElem *tokenHead = NULL;
    addToTokenList(&tokenHead, "one");
    addToTokenList(&tokenHead, "two");

    assert(!strcmp(tokenHead->token, "two"));
    assert(!strcmp(tokenHead->pNext->token, "one"));

    freeTokenList(&tokenHead);
    assert(tokenHead == NULL);

    assert(isalpha('o'));
    assert(isalnum('o'));

    struct occurenceListElem *occHead = NULL;
    addToOccurenceList(&occHead, "one");
    addToOccurenceList(&occHead, "one");
    addToOccurenceList(&occHead, "one");
    addToOccurenceList(&occHead, "two");

    assert(getOccurenceListLength(occHead) == 2);

    freeOccurenceList(&occHead);
    assert(occHead == NULL);

    char *word = strdup("word");
    assert(strcmp(word, "word") == 0);
    free(word);

    assert(isInputFileOk(INPUT_FILE));
    assert(isInputFileOk("asdf") == 0);

    printf("Done\n");
    return 0;
}