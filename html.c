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
#include <string.h>

/** LOCAL METHOD PROTOTYPES **/
unsigned long _getDocumentHtmlLength(struct HtmlDocumentType *htmlDocument);
/** /END/ LOCAL METHOD PROTOTYPES **/

/** USER SPACE METHODS  **/

HtmlElement *InitHtmlElement()
{
    HtmlElement *element = malloc(sizeof(HtmlElement));
    element->InnerHtml = malloc(sizeof(char) * MAX_HTML_CONTENT);

    if (element->InnerHtml == 0x0)
    {
        printf("failed to allocate memory for HtmlElementType");
        exit(-1);
    }

    return element;
}

void FreeHtmlElement(struct HtmlElementType *html)
{
    if (html != 0x0 && html->InnerHtml != 0x0)
        free(html->InnerHtml);

    free(html);
}

void InitHtmlDocument(struct HtmlDocumentType *htmlDocument)
{
    if (htmlDocument->Body != 0x0)
        FreeHtmlElement(htmlDocument->Body);

    if (htmlDocument->Header != 0x0)
        FreeHtmlElement(htmlDocument->Header);
    
    if (htmlDocument->Footer != 0x0)
        FreeHtmlElement(htmlDocument->Footer);
        

    htmlDocument->Header  = InitHtmlElement();
    htmlDocument->Body    = InitHtmlElement();
    htmlDocument->Footer  = InitHtmlElement();
}

void FreeHtmlDocument(struct HtmlDocumentType *htmlDocument)
{
    if (htmlDocument == 0x0)
    {
        printf("Unable to free memory on HtmlDocumentType");
        abort();
    }

    FreeHtmlElement(htmlDocument->Header);
    FreeHtmlElement(htmlDocument->Footer);
    FreeHtmlElement(htmlDocument->Body);
        
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
    unsigned long documentSize = (_getDocumentHtmlLength(htmlDocument) + 13)  * sizeof(char*);
    char *result = (char *)malloc(documentSize);
    
    snprintf(result, documentSize, "<html>%s%s%s</html>",
        htmlDocument->Header->InnerHtml,
        htmlDocument->Body->InnerHtml,
        htmlDocument->Footer->InnerHtml);
    
    return result;
}

void HtmlHead(char *dest, char *html)
{
    unsigned long htmlSize = (strlen(html) + HTML_TAG_SYNTAX_LENGTH  + 8) * sizeof(char*);

    snprintf(dest, htmlSize, "<head>%s</head>", html);
}

void HtmlBody(char *dest, char *html)
{
    unsigned long htmlSize = (strlen(html) + HTML_TAG_SYNTAX_LENGTH + 8);

    snprintf(dest, htmlSize, "<body>%s</body>", html);
}

void HtmlTable(struct HtmlElementType *dest, char *html)
{
    unsigned long htmlSize = (strlen(html) + HTML_TAG_SYNTAX_LENGTH + 10) * sizeof(char);

    snprintf(dest->InnerHtml, htmlSize, "<table>%s</table>", html);

}

void HtmlThead(struct HtmlElementType *dest, char *html)
{

}

void HtmlTbody(struct HtmlElementType *dest, char *html)
{

}

void HtmlTh(struct HtmlElementType *dest, char *html)
{

}

void HtmlTr(struct HtmlElementType *dest, char *html)
{
    unsigned long htmlSize = (strlen(html) + HTML_TAG_SYNTAX_LENGTH + 4) * sizeof(char);

    snprintf(dest->InnerHtml, htmlSize, "<tr>%s</tr>", html);
}

void HtmlTd(struct HtmlElementType *dest, char *html)
{
    unsigned long htmlSize = (strlen(html) + HTML_TAG_SYNTAX_LENGTH + 4 + 1) * sizeof(char);

    snprintf(dest->InnerHtml, htmlSize, "<td>%s</td>", html);
}


void HtmlDiv(struct HtmlElementType *dest, char *html)
{
    unsigned long htmlSize = (strlen(html) +  HTML_TAG_SYNTAX_LENGTH + 6) * sizeof(char);

    snprintf(dest->InnerHtml, htmlSize, "<div>%s</div>", html);
}

void HtmlH1(struct HtmlElementType *dest, char *html)
{
    unsigned long htmlSize = (strlen(html) + HTML_TAG_SYNTAX_LENGTH + 4) * sizeof(char);

    snprintf(dest->InnerHtml, htmlSize, "<h1>%s</h1>", html);
}

unsigned long HtmlCalcHtmlLenWithTagName(char *str1, char *str2, unsigned short tagNameLength)
{
    return 0;
}

unsigned long HtmlCalcHtmlLen(HtmlElement *element1, HtmlElement *element2)
{
    return (strlen(element1->InnerHtml) + strlen(element2->InnerHtml) + 1) * sizeof(char);
}

void HtmlConcatElements(char **temp, HtmlElement *element1, HtmlElement *element2)
{
    unsigned long tempHtmlSize = HtmlCalcHtmlLen(element1, element2);
    *temp = (char *)malloc(tempHtmlSize);
    snprintf(*temp, tempHtmlSize, "%s%s", element1->InnerHtml, element2->InnerHtml);
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
