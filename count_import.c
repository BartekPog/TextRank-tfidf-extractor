#include "count_import.h"

struct countData *getCountData(FILE *file)
{
    if (!file)
    {
        printf("ERR: Cannot open file\n");
        return NULL;
    }
    fpos_t fileStart;
    fgetpos(file, &fileStart);

    int shallContinue = 1;

    struct countData *data = malloc(sizeof(struct countData));

    data->documentsNumber = 0;
    data->occurences = initTokenHashmap();

    int character;

    while (shallContinue)
    {
        for (int i = 0; (i < 2) && (shallContinue); i++)
        {

            //skip random spaces
            do
            {
                character = getc(file);

                if (character == EOF)
                    shallContinue = 0;
            } while ((character != '"') && (shallContinue));

            //go through the text
            do
            {
                character = getc(file);

                if (character == EOF)
                    shallContinue = 0;
            } while ((character != '"') && (shallContinue));

            if (!shallContinue)
                break;

            // skip comma
            character = getc(file);

            if (character == EOF)
                shallContinue = 0;
            else if (character != ',')
            {
                printf("ERR: Missing comma, found %c\n", character);
                shallContinue = 0;
            }
        }

        ///Reading the tokens
        struct occurenceListElem *docOccurencesHead = NULL;

        if ((shallContinue) && (getc(file) == '"'))
        {
            do
            {
                char *word = readOneWord(file);
                addToOccurenceList(&docOccurencesHead, word);
                free(word);

                character = getc(file);
                if (character == EOF)
                    shallContinue = 0;

            } while (character != '"' && shallContinue);
        }

        ///Resaving the tokens to the hashmap

        if (shallContinue)
        {
            struct occurenceListElem *occurSubPtr = docOccurencesHead;

            while (occurSubPtr)
            {
                addOccurenceToMap(data->occurences, occurSubPtr->token);
                occurSubPtr = occurSubPtr->pNext;
            }
            (data->documentsNumber)++;
        }

        freeOccurenceList(&docOccurencesHead);

        //Skipping trailing spaces
        while ((shallContinue) && (character = getc(file) != '\n'))
            if (character == EOF)
                shallContinue = 0;
    }

    fsetpos(file, &fileStart);
    return data;
}

void freeCountData(struct countData **data)
{
    freeHashmap((*data)->occurences);
    free(*data);
    *data = NULL;
}