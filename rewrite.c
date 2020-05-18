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
    if (!inFile)
    {
        printf("ERR: Cannot read input file\n");
        return 1;
    }
    if (!outFile)
    {
        printf("ERR: Cannot write to output file\n");
        return 1;
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

        struct tokenListElem *tfIdfTokenHead = getTfIdfKeywords(keywordNum, tokenHead, cntData);

        writeList(outFile, tfIdfTokenHead); // TF-IDF
        freeTokenList(&tfIdfTokenHead);

        fputc(',', outFile);

        struct tokenListElem *textRankTokenHead = getTextRankfKeywords(keywordNum, tokenHead, cntData, 0, 2, 20);
        writeList(outFile, textRankTokenHead); // TextRank
        freeTokenList(&textRankTokenHead);

        fputc(',', outFile);

        struct tokenListElem *textRankIDFTokenHead = getTextRankfKeywords(keywordNum, tokenHead, cntData, 1, 2, 20);
        writeList(outFile, textRankIDFTokenHead); // TextRankIDF
        freeTokenList(&textRankIDFTokenHead);

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

int writeList(FILE *outFile, struct tokenListElem *tokenHead)
{
    if (!outFile)
        return 1;
    if (!tokenHead)
        return 0;

    fprintf(outFile, "\"%s\"", tokenHead->token);

    tokenHead = tokenHead->pNext;

    while (tokenHead)
    {
        fprintf(outFile, ",\"%s\"", tokenHead->token);
        tokenHead = tokenHead->pNext;
    }

    return 0;
}