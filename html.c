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

/** USER SPACE METHODS  **/

void InitHtmlDocument(struct HtmlDocumentType *htmlDocument)
{
    assert(htmlDocument && "You need to allocate memory for HtmlDocument struct to use this method.");
    
    if (UNALLOCATED(htmlDocument->Body))
        htmlDocument->Body = (struct HtmlElementType *)malloc(sizeof(struct HtmlElementType));
    
    if (UNALLOCATED(htmlDocument->Header))
        htmlDocument->Header = (struct HtmlElementType *)malloc(sizeof(struct HtmlElementType));
    
}

void FreeHtmlDocument(struct HtmlDocumentType *htmlDocument)
{
    assert(htmlDocument && "Cannot free memory on NULL HtmlDocument.");
    
    if (ALLOCATED(htmlDocument->Header))
        free(&(htmlDocument->Header));
    
    if (ALLOCATED(htmlDocument->Footer))
        free(&(htmlDocument->Footer));
    
    if (ALLOCATED(htmlDocument->Body))
        free(&(htmlDocument->Body));
        
    free(htmlDocument);
}

void WriteHtmlDocumentToFile(const char *filePath)
{
    assert(filePath && "No html output file path provided.");
    
    FILE *outputFile = fopen(filePath, "w");
    
    assert(outputFile && "Could not create output html file");
    
    char *htmlDocument = html_document("<h1>Hello world</h1>");
    
    fputs(htmlDocument, outputFile);
    fclose(outputFile);
    free(htmlDocument);
}

char *html_document(char *html)
{
    unsigned long documentSize = (strlen(html) + 13)  * sizeof(char);
    char *result = (char *)malloc(documentSize);
    
    snprintf(result, documentSize, "<html>%s</html>", html);
    
    return result;
}

/** /END/ USER SPACE METHODS  **/

/** LOCAL  METHODS  **/

/** /END/ LOCAL  METHODS  **/
