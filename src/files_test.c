#include "files_test.h"

int areParamsOk(int argc, char *argv[])
{
    if (argc % 2 == 0)
        return 0;

    for (int i = 1; i < argc; i += 2)
    {
        if (argv[i][0] != '-')
            return 0;

        switch (argv[i][1])
        {
        case 'i':
        case 'o':
        case 'k':
        case 'w':
            break;

        default:
            return 0;
        }
    }
    return 1;
}

int isInputFileOk(char *inputFileName)
{
    if (strlen(inputFileName) < 5)
        return 0;

    char *extension = inputFileName + strlen(inputFileName) - 4;
    char *extCopy = strdup(extension);

    for (int i = 0; i < strlen(extCopy); i++)
        extCopy[i] = tolower(extCopy[i]);

    if (strcmp(extension, ".csv") != 0)
        return 0;

    free(extCopy);

    FILE *inFile = fopen(inputFileName, "r");

    if (!inFile)
        return 0;

    int quotes = 0;
    char c;

    while (feof(inFile) != 0)
        if (fgetc(inFile) == '"')
            quotes++;

    fclose(inFile);

    if (quotes % 6 != 0)
        return 0;

    return 1;
}