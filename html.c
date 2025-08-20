//
//  html.c
//  test
//
//  Created by Adhir Ramjiawan on 2025/08/18.
//

#include "html.h"
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "memory.h"

/** LOCAL METHOD PROTOTYPES **/
unsigned long _getDocumentHtmlLength(void);
/** /END/ LOCAL METHOD PROTOTYPES **/

/** USER SPACE METHODS  **/

void InitHtmlDocument(struct HtmlDocumentType *htmlDocument)
{
    assert(htmlDocument && "You need to allocate memory for HtmlDocument struct to use this method.");
    
    if (UNALLOCATED(htmlDocument->Body))
        htmlDocument->Body = (struct HtmlElementType *)malloc(sizeof(struct HtmlElementType));
    
    if (UNALLOCATED(htmlDocument->Header))
        htmlDocument->Header = (struct HtmlElementType *)malloc(sizeof(struct HtmlElementType));
    
    if (UNALLOCATED((htmlDocument->Footer)))
        htmlDocument->Footer = (struct HtmlElementType *)malloc(sizeof(struct HtmlElementType));
    
    _documentState = htmlDocument;
}

void FreeHtmlDocument(void)
{
    assert(_documentState && "Cannot free memory on NULL HtmlDocument.");
    
    if (ALLOCATED(_documentState->Header))
        free(&(_documentState->Header));
    
    if (ALLOCATED(_documentState->Footer))
        free(&(_documentState->Footer));
    
    if (ALLOCATED(_documentState->Body))
        free(&(_documentState->Body));
        
    free(_documentState);
    
}

void WriteHtmlDocumentToFile(const char *filePath)
{
    assert(filePath && "No html output file path provided.");
    
    FILE *outputFile = fopen(filePath, "w");
    
    assert(outputFile && "Could not create output html file");
    
    char *result = HtmlDocument();
    
    fputs(result, outputFile);
    fclose(outputFile);
    free(result);
}

char *HtmlDocument(void)
{
    unsigned long documentSize = (_getDocumentHtmlLength() + 13)  * sizeof(char);
    char *result = (char *)malloc(documentSize);
    
    snprintf(result, documentSize, "<html>%s%s%s</html>", _documentState->Header->InnerHtml, _documentState->Body->InnerHtml, _documentState->Footer->InnerHtml);
    
    return result;
}

/** /END/ USER SPACE METHODS  **/

/** LOCAL  METHODS  **/

unsigned long _getDocumentHtmlLength(void)
{
    return
        strlen(_documentState->Header->InnerHtml) +
        strlen(_documentState->Body->InnerHtml) +
        strlen(_documentState->Footer->InnerHtml);
}

/** /END/ LOCAL  METHODS  **/
