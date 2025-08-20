//
//  html.h
//  test
//
//  Created by Adhir Ramjiawan on 2025/08/18.
//


#ifndef HTML_H
#define HTML_H

#define MAX_HTML_CONTENT 1024 * 100

struct HtmlElementType
{
    char TagName[100];
    char InnerHtml[MAX_HTML_CONTENT];
};

struct HtmlDocumentType
{
    struct HtmlElementType *Header;
    struct HtmlElementType *Body;
    struct HtmlElementType *Footer;
};

static struct HtmlDocumentType *_documentState;

char *HtmlDocument(void);
char *HtmlBody(char *html);
char *HtmlHead(char *html);
char *HtmlFooter(char *html);

char *HtmlP(char *html);
char *HtmlDiv(char *html);
char *HtmlSpan(char *html);
char *HtmlStrong(char *html);
char *HtmlB(char *html);
char *HtmlTable(char *html);
char *HtmlThead(char *html);
char *HtmlTbody(char *html);
char *HtmlTh(char *html);
char *HtmlTr(char *html);
char *HtmlTd(char *html);


char *HtmlH1(char *html);
char *HtmlH2(char *html);
char *HtmlH3(char *html);


void InitHtmlDocument(struct HtmlDocumentType *htmlDocument);
void WriteHtmlDocumentToFile(const char *filePath);
void FreeHtmlDocument(void);


#endif
