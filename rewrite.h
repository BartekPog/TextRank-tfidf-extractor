/** @file */

#ifndef REWRITE
#define REWRITE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "count_import.h"
#include "token.h"

/**
 * @brief Writes the HEADING, ARTICLE and set of found keywords to the outputFile
 * 
 * @param inFile Pointer to the input file stream set on start position
 * @param outFile Pointer to the output file stream set on start position
 * @param cntData Count data necessary for IDF 
 * @param keywordNum Number of keywords to find
 * @return int returns 0 if there were no errors
 */
int rewriteWithKeywords(FILE *inFile, FILE *outFile, struct countData *cntData, int keywordNum);

/**
 * @brief reqrites one character and returns the rewritten character
 * 
 * @param inFile Pointer to the input file stream
 * @param outFile Pointer to the output file stream
 * @return int rewritten character
 */
int rewriteChar(FILE *inFile, FILE *outFile);

/**
 * @brief Rewrtes one field to output file. 
 * One symbol after quotation marh will be rewritten as well.
 * 
 * For example it may rewrite:
 * "lorem ipsum dolor",
 * both with quotes and comma
 * 
 * @param inFile Pointer to the input file stream
 * @param outfile Pointer to the output file stream
 * @return int 0 if no errors, 1 if found EOF, 2 if found Error
 */
int rewriteField(FILE *inFile, FILE *outFile);

/**
 * @brief Creates a token list based on a TOKENS field 
 * 
 * @param inFile 
 * @return struct tokenListElem* 
 */
struct tokenListElem *tokenizeField(FILE *inFile);

#endif