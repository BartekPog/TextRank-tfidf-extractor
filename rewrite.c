#include "rewrite.h"

/** TESTING TODO
 * @brief Writes the HEADING, ARTICLE and set of found keywords to the outputFile
 * 
 * @param inFile Pointer to the input file stream set on start position
 * @param outFile Pointer to the output file stream set on start position
 * @param cntData Count data necessary for IDF 
 * @param keywordNum Number of keywords to find
 * @return int returns 0 if there were no errors
 */
int rewriteWithKeywords(FILE *inFile, FILE *outFile, struct countData *cntData, int keywordNum)
{
    // int DEBUG_ARTICLE_INDEX = 0;

    if (!inFile)
    {
        printf("ERR: Cannot read input file\n");
        return 1;
    }
    if (!outFile)
    {
        printf("ERR: Cannot write to output file\n");
    }

    int shallContinue = 1;
    int fieldStatus;
    while (shallContinue)
    {
        for (int col = 0; ((col < 2) && (shallContinue)); col++)
        {
            fieldStatus = rewriteField(inFile, outFile);
            if (fieldStatus == 1)
            {
                shallContinue = 0;
            }
            else if (fieldStatus == 2)
            {
                printf("ERR: input file has incorrect format\n");
                shallContinue = 0;
            }
        }
        if (!shallContinue)
            break;

        struct tokenListElem *tokenHead = tokenizeField(inFile);

        ///TESTONG
        ///TODO
        // fprintf(outFile, "raz, dwa, trzeci");
        // fprintf(stdout, "%s, %p, trzeci\n", tokenHead->token, tokenHead->pNext);

        // struct tokenListElem *pRunner = tokenHead;

        // int count = 0;
        // while (pRunner)
        // {
        //     count++;
        //     pRunner = pRunner->pNext;
        // }
        // if (count < 50)
        // {
        //     printf("TINY ARTICLE %d: %d\n", DEBUG_ARTICLE_INDEX, count);
        //     struct tokenListElem *pRunner = tokenHead;

        //     while (pRunner)
        //     {
        //         printf("%s ", pRunner->token);
        //         pRunner = pRunner->pNext;
        //     }
        //     printf("\n");
        //     getchar();
        // }

        // Do the thing

        freeTokenList(&tokenHead);
        fputc('\n', outFile);
    }
}

int rewriteChar(FILE *inFile, FILE *outFile)
{
    int c = getc(inFile);
    if (c != EOF)
        putc(c, outFile);
    return c;
}

int rewriteField(FILE *inFile, FILE *outFile)
{
    if ((!inFile) || (!outFile))
        return 2;

    int character = rewriteChar(inFile, outFile);

    if (character == EOF)
        return 1;
    if (character != '"')
        return 2;

    do
    {
        character = rewriteChar(inFile, outFile);
    } while ((character != EOF) && (character != '"'));

    if (character == EOF)
    {
        printf("ERR: Unexpected End Of File\n");
        return 2;
    }

    character = rewriteChar(inFile, outFile);

    if (character == EOF)
        return 1;

    return 0;
}

struct tokenListElem *tokenizeField(FILE *inFile)
{
    struct tokenListElem *tokenHead = NULL;
    int character = getc(inFile);

    if (character != '"')
    {
        printf("ERR: Unexpected End Of File\n");
        return NULL;
    }

    do
    {
        char *word = readOneWord(inFile);
        int len = strlen(word);

        if (len)
            addToTokenList(&tokenHead, word);
        else
            free(word);

        character = getc(inFile);
        if (character == EOF)
        {
            printf("ERR: Unexpected End Of File\n");
            return tokenHead;
        }
    } while (character != '"');

    //Skipping trailing spaces
    do
    {
        character = getc(inFile);
    } while ((character != '\n') && (character != ',') && (character != EOF));

    return tokenHead;
}