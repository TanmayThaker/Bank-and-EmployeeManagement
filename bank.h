//Including all the necessary header files
#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include "logger.h"
using namespace std;
mutex m;

/*loan functions*/
//void show();
void loanf();
//void pay();
void loanMenu();

//class Bank
class Bank
{
    //Private members of Bank class
private:
    char type[10];
    string username;
    int password;
    int balance; //total money available in the bank
    int amount;  // User's amount details
    int accountNumber;

public:
    //Bank Constructor
    Bank()
    {
        balance = 0;
    }

    ~Bank()
    {
        cout << "\nThanks for visiting our bank." << endl;
    }

    //Function to get Account Type
    char *getAccountType()
    {
        Logger::Info("Account Type function called: Returns the type of account");
        return type;
    }
    //Function to getUsername
    string getUsername()
    {
        Logger::Info("Account Number function called");
        return username;
    }
    //Function to get Total available balance
    int getTotalAvailableBalance()
    {
        Logger::Info("Returns Total available balance: \"getTotalAvailableBalance\" called");
        return balance;
    }
    //Function to set Total available balance
    void setTotalAvailableBalance(int bal)
    {
        Logger::Info("Setting Total Available Balance");
        balance = bal;
    }
    //Function to deposit total amount of Money
    void deposit()
    {
        Logger::Info("Deposit function called");
        cout << "\nEnter amount to be Deposited\n";
        cin >> amount;
        balance += amount;
    }
    //Function to get Account Number
    int getAccountNumber()
    {
        Logger::Info("Account Number function called");
        cout << "Account Number: " << accountNumber;
        Logger::Info("Successfully returned account number");
        return accountNumber;
    }
    //Function to withdraw money from Bank
    void withdrawMoney()
    {
        Logger::Info("Withdraw Money Function called");
        m.lock();
        float withdrawAmount, availablebalance;
        cout << "Enter amount to withdraw\n";
        cin >> withdrawAmount;
        availablebalance = getTotalAvailableBalance();
        //Try catech block for Exception Handling
        try
        {
            if (withdrawAmount <= 0 || (availablebalance - withdrawAmount) <= 0)
            {
                Logger::Critical("Invalid amount is entered");
                throw withdrawAmount;
            }
            availablebalance = availablebalance - withdrawAmount;
            setTotalAvailableBalance(availablebalance);
            cout << "Amount of rupees " << withdrawAmount << " has been withdrawn";
            Logger::Info("Successfully completed withdrawl");
        }
        catch (float withdrawAmount)
        {
            Logger::Error("Exception Occured while withdrawing money");
            cout << "Please Enter the valid amount" << endl;
        }
        m.unlock();
        Logger::Info("Successfully completed withdrawl");
    }
    // //Function to get User's Balance
    int getUserAmount()
    {
        Logger::Info("User Amount Function Called");
        return amount;
    }
    //Function to Show Balance of user
    void showBalance()
    {
        Logger::Info("Showing Total Balance");
        cout << "\nTotal balance is: " << balance;
    }
    //Function to get all the details about the user
    void getData(void)
    {
        Logger::Info("Taking data from the User");
        cin.ignore();
        cout << "\nEnter username:";

        getline(cin, username);
        cout << "\nEnter 4-digit "
             << "password:";
        cin >> password;
        while (password < 1000 && password > 9999)
        {
            cout << "ERROR: Invalid Pin: " << endl;
            cout << "Enter your 4 digit pin please: ";
            cin >> password;
        }
        cin.ignore();
        cout << "\nEnter initial"
             << " balance:";

        cin >> balance;
        cout << "\nEnter Account number: ";
        cin >> accountNumber;
        ofstream MyFile("final.txt"); //Creating an output file object and opening "final.txt"
        MyFile << accountNumber;      //Appending accountNumber into the file
        MyFile.close();
        cout << "\nEnter Account type: ";
        cin >> type;
        cin.ignore();
    }
    //Function to show data about bank
    void showBankData()
    {
        Logger::Info("Bank Data function called");
        Bank b;
        cout << "Name:" << username << endl;
        cout << "Account No:" << accountNumber << endl;
        cout << "Account type:" << type << endl;
        cout << "Balance:" << balance << endl;
    } /*
    void menu()
    {
        Logger::Info("Bank Menu Called");
        system("cls");
        while (true)
        {
            int choice;
            cout << "\n\n\t\t ATM Management";
            cout << "\n\n 1. Create an account";
            cout << "\n 2. Withdraw Amount";
            cout << "\n 3. Deposit Amount";
            cout << "\n 4. Show Balance";
            cout << "\n 5. Show Bank Data";
            cout << "\n 6. Loan Applications";
            cout << "\n 7. Exit";
            cout << "\n\n Enter Your Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                getData();
                break;
            case 2:
                withdrawMoney();
                break;
            case 3:
                deposit();
                break;
            case 4:
                showBalance();
                break;
            case 5:
                showBankData();
                break;
            case 6:
                loanMenu();
                break;
            case 7:
                exit(1);
                break;
            default:
                cout << "\n\n Invalid Value...Please Try Again";
            }
        }

        //getch();
    }*/
};
//Function to show Bank menu
void bankMenu()
{
    Logger::Info("Bank Menu Called");
    system("cls");
    Bank bank;
    /*
        thread t1(withdrawMoney, 0);
        thread t2(withdrawMoney,0);
        t1.join();
        t2.join();*/
    while (true)
    {
        int choice;
        cout << "\n\n\t\t ATM Management";
        cout << "\n\n 1. Create an account";
        cout << "\n 2. Withdraw Amount";
        cout << "\n 3. Deposit Amount";
        cout << "\n 4. Show Balance";
        cout << "\n 5. Show Bank Data";
        cout << "\n 6. Loan Applications";
        cout << "\n 7. Exit";
        cout << "\n\n Enter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            bank.getData();
            break;
        case 2:
            bank.withdrawMoney();
            break;
        case 3:
            bank.deposit();
            break;
        case 4:
            bank.showBalance();
            break;
        case 5:
            bank.showBankData();
            break;
        case 6:
            loanMenu();
            break;
        case 7:
            exit(1);
            break;
        default:
            cout << "\n\n Invalid Value...Please Try Again";
        }
    }

    //getch();
}
float loanAmount;
//Loan class
class Loan : public Bank
{
private:
    float interest;
    int time;

public:
    float lon;
    //Loan Constructor
    Loan()
    {
        lon = 0;
        //loanAmount = 0;
        time = 10;
        interest = 0.4;
    }
    //Function to get Loan Amount
    int getLoanAmount()
    {
        Logger::Info("Getting Loan Amount: Loan Amount Function called");
        return loanAmount;
    }
    //Function to get Loan Interest
    int getInterest()
    {
        Logger::Info("Getting Interest: Interest Function called");
        return interest;
    }
    /*
    void payLoan()
    {
        Loan loan;
        int m;
        if (lon == 0)
            cout << "\n\n\t You have no loan.";
        else
        {
            cout << "\n\n\t You have to pay " << lon;
            cout << "\n\nEnter your payment";
            cin >> m;
            lon = lon - m;
            if (lon <= 0)
            {
                cout << "\n\n\tok your loan paid.";
                lon = 0;
            }
            else
                cout << "loan to be paid= " << lon;
        }
    }*/
    //Function to get Loan
    void getLoan()
    {
        Bank b;
        float l;
        if (loanAmount == 0)
        {
            cout << "Enter loan:";
            cin >> l;

            cout << "\nYou can get loan";
            loanAmount = l;
            cout << "\nLoan sanctioned: " << loanAmount;
        }
        else
        {
            cout << "\nYou have previous loan.";
        }
    }
    //void getLoanDetails();
    void output()
    {
        //Logger::Info("Getting details about Loan");
        Bank b;
        Loan loan;
        cout << "\n\n Loan Amount: " << loanAmount;
        cout << "\n\n Interest:" << interest;
    }
};

//Non member function to get Loan
void loanf()
{
    Logger::Info("Getting Loan: Get Loan Function called");
    Bank b;
    Loan a;
    //fstream file;
    //file.open("final.text", ios::ate | ios::in | ios::out | ios::binary);
    int i;
    bool found = false;
    cout << "\n\naccount no:";
    cin >> i;
    ifstream myFile;
    myFile.open("final.txt");
    int line = 0;
    myFile >> line;
    myFile.close();
    if (i == line)
    {
        a.getLoan();
        found = true;
    }
    else
    {
        found = false;
        cout << "\n\n\t This account is not exist in file.";
        bankMenu();
    }
}
