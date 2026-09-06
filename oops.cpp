#include <iostream>
#include <string>
using namespace std;

// ======================================================
// BASE CLASS - ABSTRACTION + ENCAPSULATION
// ======================================================

class BankAccount
{
private:
    int accountNumber;
    string accountHolder;
    double balance;

protected:
    // Protected function can be accessed by derived classes
    void updateBalance(double amount)
    {
        balance += amount;
    }

public:

    // Constructor
    BankAccount(int accNo, string name, double bal)
    {
        accountNumber = accNo;
        accountHolder = name;
        balance = bal;

        cout << "\nBank Account Created!\n";
    }

    // Destructor
    virtual ~BankAccount()
    {
        cout << "Bank Account Object Destroyed.\n";
    }

    // Getters - Encapsulation
    int getAccountNumber()
    {
        return accountNumber;
    }

    string getAccountHolder()
    {
        return accountHolder;
    }

    double getBalance()
    {
        return balance;
    }

    // Function Overloading
    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Rs. " << amount << " deposited successfully.\n";
        }
        else
        {
            cout << "Invalid amount!\n";
        }
    }

    void deposit(double amount, string source)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Rs. " << amount
                 << " deposited through " << source << ".\n";
        }
        else
        {
            cout << "Invalid amount!\n";
        }
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid amount!\n";
        }
        else if (amount > balance)
        {
            cout << "Insufficient balance!\n";
        }
        else
        {
            balance -= amount;
            cout << "Rs. " << amount << " withdrawn successfully.\n";
        }
    }

    // Virtual Function - Runtime Polymorphism
    virtual void calculateInterest() = 0;

    // Virtual function for displaying account type
    virtual void displayAccountType()
    {
        cout << "Account Type: Bank Account\n";
    }

    // Display account details
    void displayDetails()
    {
        cout << "\n========== ACCOUNT DETAILS ==========\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Holder : " << accountHolder << endl;
        cout << "Balance        : Rs. " << balance << endl;
        displayAccountType();
        cout << "=====================================\n";
    }

    // Friend function
    friend void showBalance(const BankAccount &account);
};


// ======================================================
// FRIEND FUNCTION
// ======================================================

void showBalance(const BankAccount &account)
{
    cout << "\nCurrent Balance: Rs. "
         << account.balance << endl;
}


// ======================================================
// DERIVED CLASS - INHERITANCE
// ======================================================

class SavingsAccount : public BankAccount
{
private:
    double interestRate;

public:

    SavingsAccount(int accNo, string name, double bal,
                   double rate)
        : BankAccount(accNo, name, bal)
    {
        interestRate = rate;
    }

    // Function Overriding
    void calculateInterest() override
    {
        double interest = getBalance() * interestRate / 100;

        cout << "\nSavings Account Interest: Rs. "
             << interest << endl;

        updateBalance(interest);

        cout << "Interest added successfully.\n";
    }

    void displayAccountType() override
    {
        cout << "Account Type: Savings Account\n";
        cout << "Interest Rate: " << interestRate << "%\n";
    }
};


// ======================================================
// DERIVED CLASS - INHERITANCE
// ======================================================

class CurrentAccount : public BankAccount
{
private:
    double minimumBalance;

public:

    CurrentAccount(int accNo, string name, double bal,
                   double minBal)
        : BankAccount(accNo, name, bal)
    {
        minimumBalance = minBal;
    }

    // Function Overriding
    void calculateInterest() override
    {
        cout << "\nCurrent Account does not provide interest.\n";
    }

    void displayAccountType() override
    {
        cout << "Account Type: Current Account\n";
        cout << "Minimum Balance: Rs. "
             << minimumBalance << endl;
    }

    // Additional functionality
    void checkMinimumBalance()
    {
        if (getBalance() < minimumBalance)
        {
            cout << "Warning: Balance is below minimum balance!\n";
        }
        else
        {
            cout << "Minimum balance requirement satisfied.\n";
        }
    }
};


// ======================================================
// MAIN FUNCTION
// ======================================================

int main()
{
    int accountNumber;
    string name;
    double initialBalance;

    cout << "========================================\n";
    cout << "       BANK MANAGEMENT SYSTEM\n";
    cout << "========================================\n";

    // USER INPUT
    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    cin.ignore();

    cout << "Enter Account Holder Name: ";
    getline(cin, name);

    cout << "Enter Initial Balance: ";
    cin >> initialBalance;

    if (initialBalance < 0)
    {
        cout << "Invalid initial balance!\n";
        return 0;
    }

    // Choose account type
    int choice;

    cout << "\nSelect Account Type:\n";
    cout << "1. Savings Account\n";
    cout << "2. Current Account\n";
    cout << "Enter choice: ";
    cin >> choice;


    // ==================================================
    // POLYMORPHISM
    // ==================================================

    BankAccount *account = nullptr;

    if (choice == 1)
    {
        double rate;

        cout << "Enter Interest Rate (%): ";
        cin >> rate;

        account = new SavingsAccount(
            accountNumber,
            name,
            initialBalance,
            rate
        );
    }
    else if (choice == 2)
    {
        double minimumBalance;

        cout << "Enter Minimum Balance: ";
        cin >> minimumBalance;

        account = new CurrentAccount(
            accountNumber,
            name,
            initialBalance,
            minimumBalance
        );
    }
    else
    {
        cout << "Invalid choice!\n";
        return 0;
    }


    // ==================================================
    // MENU
    // ==================================================

    int option;

    do
    {
        cout << "\n\n========== BANK MENU ==========\n";
        cout << "1. Display Account Details\n";
        cout << "2. Deposit Money\n";
        cout << "3. Deposit Money with Source\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Check Balance\n";
        cout << "6. Calculate Interest\n";
        cout << "7. Exit\n";
        cout << "===============================\n";

        cout << "Enter your choice: ";
        cin >> option;


        switch (option)
        {
        case 1:
            account->displayDetails();
            break;


        case 2:
        {
            double amount;

            cout << "Enter amount to deposit: ";
            cin >> amount;

            account->deposit(amount);

            break;
        }


        case 3:
        {
            double amount;
            string source;

            cout << "Enter amount: ";
            cin >> amount;

            cin.ignore();

            cout << "Enter source (ATM/UPI/Cheque): ";
            getline(cin, source);

            account->deposit(amount, source);

            break;
        }


        case 4:
        {
            double amount;

            cout << "Enter amount to withdraw: ";
            cin >> amount;

            account->withdraw(amount);

            break;
        }


        case 5:
            showBalance(*account);
            break;


        case 6:
            account->calculateInterest();
            break;


        case 7:
            cout << "\nThank you for using Bank Management System!\n";
            break;


        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (option != 7);


    // Destructor called
    delete account;

    return 0;
}