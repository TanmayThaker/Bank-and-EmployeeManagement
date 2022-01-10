// Including all the necessary header files
#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <bits/stdc++.h>
#include "logger.h"
using namespace std;
// mutex m;

// void show();
// void loanf();

void loanMenu();
void bankMenu();
// class Bank
class Bank
{
    // Private members of Bank class
private:
    vector<string> type;
    vector<string> username;
    int password;
    int balance;   // total money available in the bank
    int amount;    // User's amount details
    int accNumber; // accNumber of the user
    vector<int> accountNumber;

public:
    // Bank Constructor
    Bank()
    {
        balance = 0;
    }
    int countDigits(int n)
    {
        int count = 0;
        while (n != 0)
        {
            n = n / 10;
            ++count;
        }
        return count;
    }
    // Function to export data about the bank account
    void exportDataAsCSV()
    {
        Logger::Info("Exporting Data of bank in csv format");
        fstream fout;
        int n = type.size();
        int m = username.size();
        int z = accountNumber.size();
        fout.open("bankData.csv", ios::out | ios::app);
        fout << accountNumber[z - 1] << ","
             << username[m - 1] << ","
             << amount << ","
             << type[n - 1] << "\n";
    }

    // Function to display employment details
    void getBankDetails(int id)
    {
        Logger::Info("Getting account details from CSV");
        fstream fin;
        fin.open("bankData.csv", ios::in);
        int ID, sal;
        int count = 0;
        string name, department, word, line;
        vector<string> row;
        while (fin.good())
        {
            row.clear();

            // read an entire row and
            // store it in a string variable 'line'
            getline(fin, line);

            // used for breaking words
            stringstream s(line);

            // read every column data of a row and
            // store it in a string variable, 'word'
            while (getline(s, word, ','))
            {

                // add all the column data
                // of a row to a vector
                row.push_back(word);
            }
            // convert string to integer for comparision
            ID = stoi(row[0]);

            // Compare the account Number
            if (ID == id)
            {

                // Print the found data
                count = 1;
                cout << "Details of Account Number " << row[0] << ": \n";
                cout << "Name: " << row[1] << "\n";
                cout << "Balance: " << row[2] << "\n";
                cout << "Account Type: " << row[3] << "\n";
                break;
            }
        }

        if (count == 0)
            cout << "Record not found\n";
    }
    // Function to get Account Type
    string getAccountType()
    {
        Logger::Info("Account Type function called: Returns the type of account");
        int n = type.size();
        return type[n - 1];
    }
    // Function to getUsername
    string getUsername()
    {
        Logger::Info("Account Number function called");
        int m = username.size();
        return username[m - 1];
    }
    // Function to get Total available balance
    int getTotalAvailableBalance()
    {
        Logger::Info("Returns Total available balance: \"getTotalAvailableBalance\" called");
        return balance;
    }
    // Function to set Total available balance
    void setTotalAvailableBalance(int bal)
    {
        Logger::Info("Setting Total Available Balance");
        amount = bal;
    }
    // Function to deposit total amount of Money
    void deposit()
    {
        Logger::Info("Deposit function called");
        cout << "\nEnter amount to be Deposited\n";
        int amt;
        cin >> amt;
        try
        {
            if (amt > 0)
            {
                amount += amt;
                balance += amt;
            }
            while (amt < 0)
            {
                Logger::Critical("Negative amount is entered");
                throw amt;
            }
        }
        catch (int amt)
        {
            Logger::Error("Exception occured while depositing money");
            cout << "Negative amount not allowed" << endl;
        }
        /*
        if(amt<0)
        {
            cout<<"Please enter a valid amount to deposit";

        }
        amount = amount + amt;
        balance += amt;*/
    }
    // Function to get Account Number
    int getAccountNumber()
    {
        Logger::Info("Account Number function called");
        int z = accountNumber.size();
        cout << "Account Number: " << accountNumber[z - 1];
        Logger::Info("Successfully returned account number");
        return accountNumber[z - 1];
    }
    // Function to withdraw money from Bank
    void withdrawMoney()
    {
        Logger::Info("Withdraw Money Function called");
        // m.lock();
        cout << "Your available balance is " << amount << endl;
        float withdrawAmount, availablebalance;
        cout << "Enter amount to withdraw\n";
        cin >> withdrawAmount;
        // availablebalance = balance;
        availablebalance = amount;
        // Try catch block for Exception Handling
        try
        {
            if (withdrawAmount <= 0 || (availablebalance - withdrawAmount) <= 0)
            {
                Logger::Critical("Invalid amount is entered");
                throw withdrawAmount;
            }
            availablebalance = availablebalance - withdrawAmount;
            balance -= withdrawAmount;
            setTotalAvailableBalance(availablebalance);
            cout << "Amount of rupees " << withdrawAmount << " has been withdrawn";
        }
        catch (float withdrawAmount)
        {
            Logger::Error("Exception Occured while withdrawing money");
            cout << "Please Enter the valid amount" << endl;
        }
        // m.unlock();
    }
    // Function to get User's Balance
    int getUserAmount()
    {
        Logger::Info("User Amount Function Called");
        return amount;
    }
    // Function to Show Balance of user
    void showBalance()
    {
        Logger::Info("Showing Total Balance");
        cout << "\nTotal balance is: " << balance;
    }
    // Function to get all the details about the user
    void getData(void)
    {
        Logger::Info("Taking data from the User");
        cin.ignore();
        string User;
        cout << "\nEnter username:";
        cin >> User;
        username.push_back(User);
        cin.ignore();
        cout << "\nEnter 4-digit "
             << "password:";
        cin >> password;
        if (countDigits(password) > 5 || countDigits(password) < 4)
        {
            cout << "ERROR: Invalid Pin: " << endl;
            cout << "Enter your 4 digit pin please: ";
            cin >> password;
        }
        cin.ignore();
        cout << "\nEnter initial"
             << " balance:";

        cin >> amount;
        balance += amount;
        cout << "\nEnter Account number: ";
        cin >> accNumber;
        accountNumber.push_back(accNumber);
        int z = accountNumber.size();
        ofstream MyFile("final.txt", ios::app); // Creating an output file object and opening "final.txt"
        if (accountNumber.size() == 1)
        {
            MyFile << accountNumber[z - 1] << " "; // Appending accountNumber into the file
        }
        else
        {
            MyFile << " " << accountNumber[z - 1] << " ";
        }
        MyFile.close();
        string Type;
        cout << "\nEnter Account type: ";
        cin >> Type;
        type.push_back(Type);
        cin.ignore();
    }
    // Function to show data about bank
    void showBankData()
    {
        Logger::Info("Bank Data function called");
        Bank b;
        int n = type.size();
        int m = username.size();
        int z = accountNumber.size();
        cout << "Name:" << username[m - 1] << endl;
        cout << "Account No:" << accountNumber[z - 1] << endl;
        cout << "Account type:" << type[n - 1] << endl;
        cout << "Balance:" << amount << endl;
    }
};

// Loan class
class Loan : public Bank
{
public:
    float loan;
    float interest;
    int time;
    // float lon;
    float loanAmount = 0;

    // Loan Constructor
    Loan()
    {
        // loanAmount = 0;
        //  loanAmount = 0;
        time = 10;
        interest = 0.4;
    }
    // Function to get Loan Amount
    int getLoanAmount()
    {
        Logger::Info("Getting Loan Amount: Loan Amount Function called");
        return loanAmount;
    }
    // Function to get Loan Interest
    int getInterest()
    {
        Logger::Info("Getting Interest: Interest Function called");
        return interest;
    }
    // Function to get Loan
    void getLoan()
    {
        Bank b;
        // float l;
        if (loanAmount == 0)
        {
            cout << "Enter loan:";
            cin >> loan;

            cout << "\nYou can get loan";
            loanAmount = loan;
            cout << loanAmount;
            cout << "\nLoan sanctioned: " << loanAmount;
        }
        else
        {
            cout << "\nYou have previous loan.";
        }
    }
    // void getLoanDetails();
    void output()
    {
        Logger::Info("Getting details about Loan");
        cout << "\nLoan Amount: " << getLoanAmount();
        cout << "\nInterest:" << interest;
    }
    void loanf()
    {
        Logger::Info("Getting Loan: Get Loan Function called");
        // fstream file;
        // file.open("final.text", ios::ate | ios::in | ios::out | ios::binary);
        int i;
        bool found = false;
        cout << "\n\naccount no:";
        cin >> i;
        ifstream myFile;
        myFile.open("final.txt");
        int line = 0;
        myFile >> line;
        cout << line;
        if (i == line)
        {
            getLoan();
            found = true;
        }
        else
        {
            found = false;
            cout << "\n This account is not exist in file.";
            bankMenu();
        }
        myFile.close();
    }
};

// Non member function to get Loan

/*
void loanf()
{
    Logger::Info("Getting Loan: Get Loan Function called");
    Bank b;
    Loan a;
    string i;
    bool found = false;
    cout << "\n\naccount no:";
    cin >> i;
    fstream fin; // i have converted myFile to fin
    fin.open("final.txt", ios::in);
    vector<string> row;
    string line, word;
    fin >> line;
    while (fin.good())
    {
        row.clear();

        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);

        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ' '))
        {

            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }
        // convert string to integer for comparision
        // ID = stoi(row[0]);

        // Compare the account Number
        if (strstr(row[0].c_str(), i.c_str()))
        {
            a.getLoan();
            found = true;
        }
        else
        {
            found = false;
            cout << "\n This account is not exist in file.";
            bankMenu();
        }
        fin.close();

        if (i == line)
        {
            a.getLoan();
            found = true;
        }
        else
        {
            found = false;
            cout << "\n This account is not exist in file.";
            bankMenu();
        }
    }
}*/