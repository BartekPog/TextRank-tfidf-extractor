#include "handle_input.h"

struct inputParameters *handleInput(int argc, char *argv[])
{
    struct inputParameters *params = malloc(sizeof(struct inputParameters));
    params->adjacencyWidnow = DEFAULT_ADJACENCY_WINDOW;
    params->keywordNum = DEFAULT_KEYWORD_NUM;
    params->inFile = NULL;
    params->outFile = NULL;

    for (int i = 0; i < argc - 1; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
            params->inFile = strdup(argv[i + 1]);

        if (strcmp(argv[i], "-o") == 0)
            params->outFile = strdup(argv[i + 1]);

        if (strcmp(argv[i], "-k") == 0)
            params->keywordNum = atoi(argv[i + 1]);

        if (strcmp(argv[i], "-w") == 0)
            params->adjacencyWidnow = atoi(argv[i + 1]);
    }

    if (!params->inFile)
        params->inFile = strdup(DEFAULT_IN_FILE);

    if (!params->outFile)
        params->outFile = strdup(DEFAULT_OUT_FILE);

    return params;
}

void freeInputParameters(struct inputParameters *params)
{
    free(params->inFile);
    free(params->outFile);
    free(params);
}
