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
    int Year;
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
    ReadAndCopyNextLine(employeeFile, employee->IdNumber);
    ReadAndCopyNextLine(employeeFile, employee->EmployeeNumber);
    ReadAndCopyNextLine(employeeFile, employee->Occupation);
    ///ReadAndCopyNextLine(employeeFile, employee->StartDate);
    ReadAndCopyNextLine(employeeFile, employee->UifRef);
    
    fclose(employeeFile);
}

void PrintEmployeeDetails(struct EmployeeType employee)
{
    printf("First Name: %s", employee.FirstName);
    printf("Last Name: %s", employee.LastName);
    printf("Address: %s", employee.Address);
}

void BuildTableRow(HtmlElement *parent, char *str1, char *str2)
{
    HtmlElement *td1 = InitHtmlElement();
    HtmlElement *td2 = InitHtmlElement();   
    HtmlTd(td1, str1);
    HtmlTd(td2, str2);
   
    // in order to preserve the memory of the allocated char *,
    // we need to create a char * handle (char **)
    char **temp = (char **)calloc(1, sizeof(char *));
    HtmlConcatElements(temp, td1, td2);
    HtmlTr(parent, *temp);

    free(*temp);
    free(temp);
    free(td1);
    free(td2);
}

void BuildEmployerSectionHtml(HtmlElement *parent, struct EmployeeType *employee)
{
    HtmlElement *container  = InitHtmlElement();
    HtmlElement *table      = InitHtmlElement();
    HtmlElement *row1       = InitHtmlElement();
    HtmlElement *row2       = InitHtmlElement();

    BuildTableRow(row1, "Employer:", "Adhir Ramjiawan");
    BuildTableRow(row2, "Address:", employee->Address);

    // Build Table
    // in order to preserve the memory of the allocated char *,
    // we need to create a char * handle (char **)
    char **temp = (char **)calloc(1, sizeof(char *));
    HtmlConcatElements(temp, row1, row2);
    HtmlTable(table, *temp);
    
    HtmlDiv(container, table->InnerHtml); 
    HtmlDiv(parent, container->InnerHtml); 

    free(*temp);
    free(temp);
    free(row1);
    free(row2);
}

void BuildEmployeeSectionHtml(HtmlElement *parent, struct EmployeeType *employee)
{
    HtmlElement *container  = InitHtmlElement();
    HtmlElement *table      = InitHtmlElement();
    HtmlElement **rows = calloc(7, sizeof(HtmlElement));
    HtmlElement **rowsStart = rows;

    for (int i = 0; i < 6; i++)
        *rows++ = InitHtmlElement();

    rows = rowsStart;
    
    BuildTableRow(*rows,      "Employee:",        employee->FirstName);
    BuildTableRow(*++rows,    "ID. No:",          employee->IdNumber);
    BuildTableRow(*++rows,    "Employee Number:", employee->EmployeeNumber);
    BuildTableRow(*++rows,    "Occupation:",      employee->Occupation);

    char startDate[10];
    snprintf(startDate, 10, "%d-%d-%d", employee->StartDate.Day, employee->StartDate.Month, employee->StartDate.Year);
    BuildTableRow(*++rows, "Start Date:", startDate);

    BuildTableRow(*++rows, "UIF Ref.:", employee->UifRef);
    BuildTableRow(*rows, "Pay Period:", "September 2025");

    rows = rowsStart;

    int tableHtmlSize = 0;
    
    for (int i = 0; i < 6; i++)
        tableHtmlSize += strlen((*rows++)->InnerHtml);

    rows = rowsStart;

    char *temp = malloc(sizeof(char *) + tableHtmlSize);

    for (int i =0; i < 6; i++)
    {
        int tempSize = strlen(temp) + strlen((*rows)->InnerHtml);
        snprintf(temp, tempSize, "%s%s", temp, (*rows++)->InnerHtml);
    }

    rows = rowsStart;

    free(rows);

    HtmlTable(table, temp);

    HtmlDiv(container, table->InnerHtml); 
    HtmlDiv(parent, container->InnerHtml); 
}


void BuildPayslipHtml(struct EmployeeType *employee)
{
    struct HtmlDocumentType htmlDocument = {
        .Header = InitHtmlElement(),
        .Body = InitHtmlElement(),
        .Footer = InitHtmlElement()
    };
    HtmlElement *employerSection = InitHtmlElement();
    HtmlElement *employeeSection = InitHtmlElement();
    
    InitHtmlDocument(&htmlDocument);
    HtmlHead((&htmlDocument)->Header->InnerHtml, "<title>My Payslip</title>");
    
    BuildEmployerSectionHtml(employerSection, employee);
    BuildEmployeeSectionHtml(employeeSection, employee);

    int bodyHtmlLength = strlen(employerSection->InnerHtml) + strlen(employeeSection->InnerHtml);
    char *body = malloc(sizeof(char *) * bodyHtmlLength);
    snprintf(body, bodyHtmlLength, "%s%s", employerSection->InnerHtml, employeeSection->InnerHtml);

    HtmlBody((&htmlDocument)->Body->InnerHtml, body);
    
    WriteHtmlDocumentToFile("payslip.html", &htmlDocument);
    
    //FreeHtmlDocument(&htmlDocument);
    FreeHtmlElement(employerSection); 
}

int main(int argc, const char * argv[]) {
    struct EmployeeType employee = 
    {  
        .FirstName = "",
        .LastName = "",
        .IdNumber = "",
        .Address = "",
        .EmployeeNumber = "",
        .StartDate = {1, 1, 1111},
        .UifRef = "",
        .Salary = 0.0,
        .Occupation = ""
    };
    
    printf("Payslip App.\n");
    
    ReadEmployeeFile(&employee, "emp.txt");
    PrintEmployeeDetails(employee);

    BuildPayslipHtml(&employee);

    printf("\n");
    return 0;
}
