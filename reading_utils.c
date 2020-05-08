#include "reading_utils.h"

char *readOneWord(FILE *file)
{
    // Get word length
    fpos_t wordStart;
    fgetpos(file, &wordStart);
    int length = 0;

    while (isalpha(getc(file)))
        length++;

    // Create string
    char *word = malloc(sizeof(char) * (length + 1));

    // Read again
    fsetpos(file, &wordStart);

    for (int i = 0; i < length; i++)
        word[i] = getc(file);

    word[length] = '\0';

    return word;
}
