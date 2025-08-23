//
//  main.c
//  test
//
//  Created by Adhir Ramjiawan on 2025/08/16.
//

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#include "html.h"

#define EMPLOYEE_FILE_MAX_LINE 200

struct DateType
{
    short Day;
    short Month;
    uint Year;
};

struct EmployeeType
{
    char FirstName[50];
    char LastName[50];
    char IdNumber[13];
    char Address[100];
    char EmployeeNumber[10];
    struct DateType StartDate;
    char UifRef[10];
    float Salary;
    char Occupation[100];
};


void ExitWithPrematureFileEnding(void)
{
    printf("Employee file ended prematurely.\n");
    exit(-1);
}

void ReadAndCopyNextLine(FILE *employeeFile, char *dest)
{
    char temp[EMPLOYEE_FILE_MAX_LINE];
    char *result = 0;
    
    memset(temp, '\0', EMPLOYEE_FILE_MAX_LINE);
    
    result = fgets(temp, EMPLOYEE_FILE_MAX_LINE - 1, employeeFile);
    strcpy(dest, temp);
    
    if (result == NULL)
        ExitWithPrematureFileEnding();
}

void ReadEmployeeFile(struct EmployeeType *employee, const char *employeeName)
{
    char employeeFileName[200] = "employee_\0";
    strcat(employeeFileName, employeeName);
    FILE *employeeFile = fopen(employeeFileName, "r");
    
    if (employeeFile == NULL)
    {
        printf("Cannot find employee file %s\n", employeeFileName);
        exit(-1);
    }
    
    ReadAndCopyNextLine(employeeFile, employee->FirstName);
    ReadAndCopyNextLine(employeeFile, employee->LastName);
    
    fclose(employeeFile);
}

void PrintEmployeeDetails(struct EmployeeType employee)
{
    printf("First Name: %s", employee.FirstName);
    printf("Last Name: %s", employee.LastName);
    printf("Address: %s", employee.Address);
}

void BuildEmployerSectionHtml(HtmlElement *parent)
{
    HtmlElement *container  = InitHtmlElement();
    HtmlElement *table      = InitHtmlElement();
    HtmlElement *row1       = InitHtmlElement();
    HtmlElement *row2       = InitHtmlElement();
    HtmlElement *td1Row1    = InitHtmlElement();
    HtmlElement *td2Row1    = InitHtmlElement();
    HtmlElement *td1Row2    = InitHtmlElement();
    HtmlElement *td2Row2    = InitHtmlElement();

    HtmlTd(td1Row1, "Employer:");
    HtmlTd(td2Row1, "****:");
    
    HtmlTd(td1Row2, "Address:");
    HtmlTd(td2Row2, "****:");
 
    // Build Row 1
    unsigned long tempHtmlSize = HtmlCalcHtmlLen(td1Row1, td2Row1);
    char *temp = (char *)malloc(tempHtmlSize);
    HtmlConcatElements(temp, tempHtmlSize, td1Row1, td2Row1);
    HtmlTr(row1, temp);

    // Build Row 2
    tempHtmlSize = HtmlCalcHtmlLen(td1Row2, td2Row2);
    temp = (char *)malloc(tempHtmlSize);
    HtmlConcatElements(temp, tempHtmlSize, td1Row2, td2Row2);
    HtmlTr(row2, temp);

    // Build Table
    tempHtmlSize = HtmlCalcHtmlLen(row1, row2);
    temp = (char *)malloc(tempHtmlSize);
    HtmlConcatElements(temp, tempHtmlSize, row1, row2);
    HtmlTable(table, temp);
    
    HtmlDiv(container, table->InnerHtml); 
    HtmlDiv(parent, container->InnerHtml); 

    free(temp);
    free(row1);
    free(row2);
    free(td1Row1);
    free(td2Row1);
    free(td1Row2);
    free(td2Row2);
}

void BuildPayslipHtml(void)
{
    struct HtmlDocumentType *htmlDocument = (struct HtmlDocumentType *)malloc(sizeof(struct HtmlDocumentType));
    HtmlElement *body = InitHtmlElement();
    
    InitHtmlDocument(htmlDocument);
    HtmlHead(htmlDocument->Header->InnerHtml, "<title>My Payslip</title>");
    
    BuildEmployerSectionHtml(body);

    HtmlBody(htmlDocument->Body->InnerHtml, body->InnerHtml);
    
    WriteHtmlDocumentToFile("payslip.html", htmlDocument);
    
    FreeHtmlDocument(htmlDocument);
    FreeHtmlElement(body); 
}

int main(int argc, const char * argv[]) {
    struct EmployeeType employee;
    
    printf("Payslip App.\n");
    
    ReadEmployeeFile(&employee, "emp.txt");
    PrintEmployeeDetails(employee);

    BuildPayslipHtml();

    printf("\n");
    return 0;
}
