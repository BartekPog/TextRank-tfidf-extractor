/** @file */

#ifndef HANDLE_INPUT
#define HANDLE_INPUT

#include <stdlib.h>
#include <string.h>

#define DEFAULT_IN_FILE "../data/prepared.csv"
#define DEFAULT_OUT_FILE "../data/sample_out.csv"
#define DEFAULT_KEYWORD_NUM 3
#define DEFAULT_ADJACENCY_WINDOW 2

/** Program input parameters*/
struct inputParameters
{
    char *inFile;        ///< Input file name
    char *outFile;       ///< Output file name
    int keywordNum;      ///< Number of keywords to extract
    int adjacencyWidnow; ///< Textrank tokens adjacency window
};

/**
 * @brief Handle input parameters 
 * 
 * @param argc Number of input arguments
 * @param argv Input arguments array
 * @return struct inputParameters* Pointer to input parameters  
 */
struct inputParameters *handleInput(int argc, char *argv[]);

/**
 * @brief Frees memory taken by the input parameters instance
 * 
 * @param params pointer to the parameters structure
 */
void freeInputParameters(struct inputParameters *params);

#endif