//Including necessary files
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

//Employee class
class Employee : public Bank
{

private:
    int EmpID;
    char EmpName[50], Department[10];

    string Post;

public:
    float Salary;
    //int managerSalary;
    //Function to set Salary of employee
    void setSalary(int sal)
    {
        Logger::Info("Setting Salary Of Employee");
        Salary = sal;
    }
    /*Virtual Function to get salary of Employee*/
    virtual int getSalary()
    {
        Logger::Info("Getting Salary Of Employee");
        cout << "Salary is: " << Salary;
        return Salary;
    }

    /*Function to Read data about Employee*/
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
    //Function to export data of employee
    void exportData()
    {
        Logger::Info("Exporting Data of Employee");
        ofstream MyFile("employeeData.txt");
        //MyFile << GetID();
        MyFile << EmpID << " " << EmpName << " " << Post << " " << Department << " " << Salary;
        MyFile.close();
    }
    //Function to get Salary of Manager
    int getManagerSalary()
    {
        Logger::Info("Getting Salary Of Manager");
        return managerSalary;
    }
    //Function to get ID of Employee
    int GetID()
    {
        Logger::Info("Getting ID Of Employee");
        cout << "Employment ID: " << EmpID;
        return EmpID;
    }
    //Function to display record of Employee
    void DisplayRecord()
    {
        Logger::Info("Displaying record about Employee");
        cout << endl
             << "_______________________________";
        cout << endl
             << setw(5) << EmpID << setw(15) << EmpName << setw(15) << Post << setw(15) << Department << setw(8) << Salary;
    }
    //Functiont to get department of Employee
    char *GetDepartment()
    {
        Logger::Info("Getting department of Employee");
        cout << "Department: " << Department;
        return Department;
    }
};

//Class Manager
class Manager : public Employee
{
public:
    //Overriden function to get salary of Manager
    int getSalary()
    {
        Logger::Info("Getting salary of Manager");
        cout << "Manager salary is: " << managerSalary;
        return managerSalary;
    }
};
//class Cashier
class Cashier : public Employee
{
public:
    //Overriden function to get salary of Cashier
    int getSalary()
    {
        Logger::Info("Getting salary of Cashier");
        cout << "Cashier salary is: " << cashierSalary;
        return cashierSalary;
    }
};