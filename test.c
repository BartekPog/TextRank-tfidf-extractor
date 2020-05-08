#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hashmap.h"
#include "token.h"
#include "count_import.h"
#include "rewrite.h"

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

    printf("Done\n");
    return 0;
}