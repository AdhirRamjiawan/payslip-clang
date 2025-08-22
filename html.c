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
unsigned long _getDocumentHtmlLength(struct HtmlDocumentType *htmlDocument);
/** /END/ LOCAL METHOD PROTOTYPES **/

/** USER SPACE METHODS  **/

void InitHtmlElement(struct HtmlElementType *html)
{
    assert(html && "You need to allocate memory for HtmlElement to use this method");

    if (html)
        html->InnerHtml = (char *)malloc(sizeof(char) * MAX_HTML_CONTENT);

    if (!html->InnerHtml)
    {
        printf("failed to allocate memory for HtmlElementType");
        exit(-1);
    }
}

void FreeHtmlElement(struct HtmlElementType *html)
{
    assert(html && "Cannot free memory on NULL HtmlElement");

    if (html && html->InnerHtml)
        free(html->InnerHtml);

    free(html);
}

void InitHtmlDocument(struct HtmlDocumentType *htmlDocument)
{
    assert(htmlDocument && "You need to allocate memory for HtmlDocument struct to use this method.");
    
    if (UNALLOCATED(htmlDocument->Body))
        htmlDocument->Body = (struct HtmlElementType *)malloc(sizeof(struct HtmlElementType));

    if (UNALLOCATED(htmlDocument->Header))
        htmlDocument->Header = (struct HtmlElementType *)malloc(sizeof(struct HtmlElementType));
    
    if (UNALLOCATED((htmlDocument->Footer)))
        htmlDocument->Footer = (struct HtmlElementType *)malloc(sizeof(struct HtmlElementType));
        

    InitHtmlElement(htmlDocument->Header);
    InitHtmlElement(htmlDocument->Body);
    InitHtmlElement(htmlDocument->Footer);
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

void WriteHtmlDocumentToFile(const char *filePath, struct HtmlDocumentType *htmlDocument)
{
    assert(filePath && "No html output file path provided.");
    
    FILE *outputFile = fopen(filePath, "w");
    
    assert(outputFile && "Could not create output html file");
    
    char *result = HtmlDocument(htmlDocument);
    
    fputs(result, outputFile);
    fclose(outputFile);
    free(result);
}

char *HtmlDocument(struct HtmlDocumentType *htmlDocument)
{
    unsigned long documentSize = (_getDocumentHtmlLength(htmlDocument) + 13)  * sizeof(char);
    char *result = (char *)malloc(documentSize);
    
    snprintf(result, documentSize, "<html>%s%s%s</html>",
        htmlDocument->Header->InnerHtml,
        htmlDocument->Body->InnerHtml,
        htmlDocument->Footer->InnerHtml);
    
    return result;
}

void HtmlHead(char *dest, char *html)
{
    unsigned long htmlSize = (strlen(html) + 5 + 8) * sizeof(char);

    snprintf(dest, htmlSize, "<head>%s</head>", html);
}

void HtmlBody(char *dest, char *html)
{
    unsigned long htmlSize = (strlen(html) + 5 + 8);

    snprintf(dest, htmlSize, "<body>%s</body>", html);
}

void HtmlH1(struct HtmlElementType *dest, char *html)
{
    unsigned long htmlSize = (strlen(html) + 5 + 4) * sizeof(char);

    snprintf(dest->InnerHtml, htmlSize, "<h1>%s</h1>", html);
}
/** /END/ USER SPACE METHODS  **/

/** LOCAL  METHODS  **/

unsigned long _getDocumentHtmlLength(struct HtmlDocumentType *htmlDocument)
{
    return
        strlen(htmlDocument->Header->InnerHtml) +
        strlen(htmlDocument->Body->InnerHtml) +
        strlen(htmlDocument->Footer->InnerHtml);
}

/** /END/ LOCAL  METHODS  **/
