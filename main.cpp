#include <iostream>
#include <string>
using namespace std;

// =========================
// BASE CLASS (ABSTRACTION)
// =========================
class BankAccount {
private: // ENCAPSULATION
    string name;
    int accountNumber;
    double balance;

public:
    BankAccount(string n, int acc, double bal) {
        name = n;
        accountNumber = acc;
        balance = bal;
    }

    // Deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << " into account #" << accountNumber << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    // Withdraw money
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount!" << endl;
            return false;
        } else if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return false;
        } else {
            balance -= amount;
            cout << "Withdrew $" << amount << " from account #" << accountNumber << endl;
            return true;
        }
    }

    // Transfer money to another account
    bool transferTo(BankAccount &other, double amount) {
        if (withdraw(amount)) { // Withdraw from this account first
            other.deposit(amount);
            cout << "Transferred $" << amount << " to account #" << other.getAccountNumber() << endl;
            return true;
        } else {
            cout << "Transfer failed!" << endl;
            return false;
        }
    }

    // Getters
    string getName() { return name; }
    int getAccountNumber() { return accountNumber; }
    double getBalance() { return balance; }

    // POLYMORPHISM: pure virtual function for interest
    virtual void calculateInterest() = 0;

    virtual void displayInfo() {
        cout << "Account Holder: " << name << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
    }
};

// =========================
// DERIVED CLASSES (INHERITANCE)
// =========================
class SavingsAccount : public BankAccount {
public:
    SavingsAccount(string n, int acc, double bal) : BankAccount(n, acc, bal) {}

    void calculateInterest() override {
        double interest = getBalance() * 0.03; // 3% interest
        deposit(interest);
        cout << "Savings interest added: $" << interest << endl;
    }

    void displayInfo() override {
        cout << "--- Savings Account ---" << endl;
        BankAccount::displayInfo();
    }
};

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(string n, int acc, double bal) : BankAccount(n, acc, bal) {}

    void calculateInterest() override {
        cout << "Checking accounts do not earn interest." << endl;
    }

    void displayInfo() override {
        cout << "--- Checking Account ---" << endl;
        BankAccount::displayInfo();
    }
};

// =========================
// MAIN PROGRAM / MENU
// =========================
int main() {
    // Sample accounts
    SavingsAccount s("Kynze", 1111, 500.0);
    CheckingAccount c("Martin", 2222, 200.0);

    int choice;
    double amount;

    do {
        cout << "\n--- Bank Menu ---\n";
        cout << "1. View Savings Account\n";
        cout << "2. View Checking Account\n";
        cout << "3. Deposit into Savings\n";
        cout << "4. Withdraw from Savings\n";
        cout << "5. Deposit into Checking\n";
        cout << "6. Withdraw from Checking\n";
        cout << "7. Add Interest to Savings\n";
        cout << "8. Transfer from Savings to Checking\n";
        cout << "9. Transfer from Checking to Savings\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                s.displayInfo();
                break;
            case 2:
                c.displayInfo();
                break;
            case 3:
                cout << "Enter amount to deposit into Savings: $";
                cin >> amount;
                s.deposit(amount);
                break;
            case 4:
                cout << "Enter amount to withdraw from Savings: $";
                cin >> amount;
                s.withdraw(amount);
                break;
            case 5:
                cout << "Enter amount to deposit into Checking: $";
                cin >> amount;
                c.deposit(amount);
                break;
            case 6:
                cout << "Enter amount to withdraw from Checking: $";
                cin >> amount;
                c.withdraw(amount);
                break;
            case 7:
                s.calculateInterest();
                break;
            case 8:
                cout << "Enter amount to transfer from Savings to Checking: $";
                cin >> amount;
                s.transferTo(c, amount);
                break;
            case 9:
                cout << "Enter amount to transfer from Checking to Savings: $";
                cin >> amount;
                c.transferTo(s, amount);
                break;
            case 0:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option!" << endl;
        }
    } while (choice != 0);

    return 0;
}

