//
//  html.h
//  test
//
//  Created by Adhir Ramjiawan on 2025/08/18.
//


#ifndef HTML_H
#define HTML_H

#define MAX_HTML_CONTENT 1024 * 100
#define MAX_HTML_ELEMENT_CHILDREN 100

struct HtmlElementType
{
    char TagName[100];
    char InnerHtml[MAX_HTML_CONTENT];
    struct HtmlElementType *Children[MAX_HTML_ELEMENT_CHILDREN];
};

struct HtmlDocumentType
{
    struct HtmlElementType *Header;
    struct HtmlElementType *Body;
    struct HtmlElementType *Footer;
};

void InitHtmlDocument(struct HtmlDocumentType *htmlDocument);
void WriteHtmlDocumentToFile(const char *filePath);
void FreeHtmlDocument(struct HtmlDocumentType *htmlDocument);
#endif
