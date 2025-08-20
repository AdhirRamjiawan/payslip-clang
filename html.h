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

char *html_document(char *html);
char *html_body(char *html);
char *html_head(char *html);
char *html_footer(char *html);

char *html_p(char *html);
char *html_div(char *html);
char *html_span(char *html);
char *html_strong(char *html);
char *html_b(char *html);
char *html_table(char *html);
char *html_thead(char *html);
char *html_tbody(char *html);
char *html_th(char *html);
char *html_tr(char *html);
char *html_td(char *html);


char *html_h1(char *html);
char *html_h2(char *html);
char *html_h3(char *html);


void InitHtmlDocument(struct HtmlDocumentType *htmlDocument);
void WriteHtmlDocumentToFile(const char *filePath);
void FreeHtmlDocument(struct HtmlDocumentType *htmlDocument);
#endif
