#ifndef FILES_TEST
#define FILES_TEST

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Checks whether input parameters are semantically correct
 * 
 * @param argc Number of input parameters
 * @param argv Array of parameters
 * @return int 1 if all correct, 0 if error found
 */
int areParamsOk(int argc, char *argv[]);

/**
 * @brief Checks whether input file has a correct format
 * 
 * @param inputFileName Name of the file to test
 * @return int 1 if all correct, 0 if error found
 */
int isInputFileOk(char *inputFileName);

#endif