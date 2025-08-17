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
    
    fclose(employeeFile);
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

int main(int argc, const char * argv[]) {
    printf("Payslip App.\n");
    struct EmployeeType employee;
    
    ReadEmployeeFile(&employee, "emp.txt");
    
    printf("First Name: %s", employee.FirstName);
    
    printf("\n");
    
    return 0;
}
