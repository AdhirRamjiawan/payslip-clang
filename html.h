//
//  html.h
//  test
//
//  Created by Adhir Ramjiawan on 2025/08/18.
//


#ifndef HTML_H
#define HTML_H

#define MAX_HTML_CONTENT 1024 * 100

// HTML_TAG_SYNTAX_LENGTH is meant to count the
// angle brackets of both opening and closing tags,
// as well as forward slash on the closing tag.
// <..></..>
#define HTML_TAG_SYNTAX_LENGTH 5 

struct HtmlElementType
{
    char *InnerHtml;//[MAX_HTML_CONTENT];
};

struct HtmlDocumentType
{
    struct HtmlElementType *Header;
    struct HtmlElementType *Body;
    struct HtmlElementType *Footer;
};

typedef struct HtmlElementType HtmlElement;


char *HtmlDocument(struct HtmlDocumentType *htmlDocument);
void HtmlBody(char *dest, char *html);
void HtmlHead(char *dest, char *html);
void HtmlFooter(char *dest, char *html);

void HtmlP(struct HtmlElementType *dest, char *html);
void HtmlDiv(struct HtmlElementType *dest, char *html);
void HtmlSpan(struct HtmlElementType *dest, char *html);
void HtmlStrong(struct HtmlElementType *dest, char *html);
void HtmlB(struct HtmlElementType *dest, char *html);
void HtmlTable(struct HtmlElementType *dest, char *html);
void HtmlThead(struct HtmlElementType *dest, char *html);
void HtmlTbody(struct HtmlElementType *dest, char *html);
void HtmlTh(struct HtmlElementType *dest, char *html);
void HtmlTr(struct HtmlElementType *dest, char *html);
void HtmlTd(struct HtmlElementType *dest, char *html);

void HtmlH1(struct HtmlElementType *dest, char *html);
void HtmlH2(struct HtmlElementType *dest, char *html);
void HtmlH3(struct HtmlElementType *dest, char *html);

unsigned long HtmlCalcHtmlLen(HtmlElement *element1, HtmlElement *element2);
unsigned long HtmlCalcHtmlLenWithTagName(char *str1, char *str2, unsigned short tagNameLength);

void HtmlConcatElements(char *temp, unsigned long tempHtmlSize, HtmlElement *element1, HtmlElement *element2);

void InitHtmlElement(struct HtmlElementType *html);
void FreeHtmlElement(struct HtmlElementType *html);

void InitHtmlDocument(struct HtmlDocumentType *htmlDocument);
void WriteHtmlDocumentToFile(const char *filePath, struct HtmlDocumentType *htmlDocument);
void FreeHtmlDocument(struct HtmlDocumentType *htmlDocument);


#endif
