/** @file */

#ifndef DOCUMENT
#define DOCUMENT

#include <stdio.h>
#include <stdlib.h>
#include <token.h>

/** Structure containing a single document*/
struct document
{
    fpos_t headerPos;                       ///< Header of the document position
    int headerLenght;                       ///< Length of the header
    fpos_t textPos;                         ///< Position of the beginning of the article in file
    int textLenght;                         ///< Lenght of the raw article
    struct tokenListElem *tokenHead;        ///< Pointer to the head of the token list
    struct tokenListElem *TextRankKeywords; ///< Pointer to the head of textrank keywords lsit
    struct tokenListElem *TFIDFKeywords;    ///< Pointer to the head of TF-IDF keywords list
};

/** Document one way linked list*/
struct docLinkedListElem
{
    struct document *docPtr;         ///< Pointer to the stored document
    struct docLinkedListElem *pNext; ///< Pointer to the next element of linked list
};

/** Array of pointers to documents ant its size*/
struct docData
{
    struct document **documentPointers; ///< Array of pointers to documents
    int size;                           ///< Size of the docArray
    // struct allTokensListElem *occurrencesHead; ///<Head of the word occurance list
};

/**
 * @brief Create a document array from a given file stream
 * 
 * @param fileStream filestream on which the document array shall be created
 * @return struct docArray* Pointer to the document array
 */
struct docData *createDocDataFromFile(FILE *fileStream);

/**
 * @brief Adds document to the document list at the head position.
 * 
 * @param pHeadPointer pointer to list head pointer
 * @param doc pointer to the added document
 */
void addToDocListHead(struct docLinkedListElem **pHead, struct document *doc);

/**
 * @brief Frees memory taken by the docData
 * 
 * @param data pointer to the docData instance
 */
void deleteDocData(struct docData *data);

#endif