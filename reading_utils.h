/** @file */
#ifndef READING_UTILS
#define READING_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Reads one word from file
 * 
 * @param file pointer to the file
 * @return char** pointer to the first letter of the string
 */
char *readOneWord(FILE *file);

#endif