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
    
}

/** /END/ USER SPACE METHODS  **/

/** LOCAL  METHODS  **/

/** /END/ LOCAL  METHODS  **/
