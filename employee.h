#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include "bank.h"
using namespace std;
float managerSalary;
float cashierSalary;
/*
struct employee
{
    string name;
    long int code;
    string designation;
    int exp;
    int age;
};
*/
class Employee : public Bank
{

private:
    int EmpID;
    char EmpName[50], Department[10];

    string Post;

public:
    float Salary;
    //int managerSalary;
    void setSalary(int sal)
    {
        Logger::Info("Setting Salary Of Employee");
        Salary = sal;
    }
    virtual int getSalary()
    {
        Logger::Info("Getting Salary Of Employee");
        cout << "Salary is: " << Salary;
        return Salary;
    }
    void ReadData()
    {
        Logger::Info("Writing data about Employee");
        cout << endl
             << "Employee ID:";
        cin >> EmpID;
        cout << "Employee Name:";
        cin >> EmpName;
        cout << "Employee's Post:";
        cin >> Post;
        if (Post == "Manager")
        {
            cout << "Manager's Salary: ";
            cin >> managerSalary;
            cout << "Manager Salary input: " << managerSalary;
        }
        else if (Post == "Cashier")
        {
            cout << "Cashier's Salary: ";
            cin >> cashierSalary;
            cout << "Cashier Salary input: " << cashierSalary;
        }
        else
        {
            cout << "Salary:";
            cin >> Salary;
        }
        cout << "\n Employee's Department:";
        cin >> Department;
    }
    void exportData()
    {
        Logger::Info("Exporting Data of Employee");
        ofstream MyFile("employeeData.txt");
        //MyFile << GetID();
        MyFile << EmpID << " " << EmpName << " " << Post << " " << Department << " " << Salary;
        MyFile.close();
    }
    int getManagerSalary()
    {
        Logger::Info("Getting Salary Of Manager");
        return managerSalary;
    }
    int GetID()
    {
        Logger::Info("Getting ID Of Employee");
        cout << "Employment ID: " << EmpID;
        return EmpID;
    }
    void DisplayRecord()
    {
        Logger::Info("Displaying record about Employee");
        cout << endl
             << "_______________________________";
        cout << endl
             << setw(5) << EmpID << setw(15) << EmpName << setw(15) << Post << setw(15) << Department << setw(8) << Salary;
    }
    char *GetDepartment()
    {
        Logger::Info("Getting department of Employee");
        cout << "Department: " << Department;
        return Department;
    }
};

class Manager : public Employee
{
public:
    int getSalary()
    {
        Logger::Info("Getting salary of Manager");
        cout << "Manager salary is: " << managerSalary;
        return managerSalary;
    }
};

class Cashier : public Employee
{
public:
    int getSalary()
    {
        Logger::Info("Getting salary of Cashier");
        cout << "Cashier salary is: " << cashierSalary;
        return cashierSalary;
    }
};