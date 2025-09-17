//BANKING SYSTEM 
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// ---------- Transaction Class ----------
class Transaction {
    string type;       // Deposit, Withdraw, Transfer
    double amount;
    string timestamp;
    string details;    // Extra info (e.g., recipient for transfer)
public:
    Transaction(string t, double amt, string det = "") {
        type = t;
        amount = amt;
        details = det;

        // Record timestamp
        time_t now = time(0);
        timestamp = ctime(&now);
        timestamp.pop_back(); // remove newline
    }

    void display() const {
        cout << "[" << timestamp << "] " << type << " of $" << amount;
        if (!details.empty()) cout << " (" << details << ")";
        cout << endl;
    }
};

// ---------- Account Class ----------
class Account {
    int accountNumber;
    double balance;
    vector<Transaction> history;
public:
    Account(int accNo, double initialBalance = 0.0) {
        accountNumber = accNo;
        balance = initialBalance;
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit amount must be positive!\n";
            return;
        }
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
        cout << "Deposited $" << amount << " successfully.\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount));
        cout << "Withdrew $" << amount << " successfully.\n";
    }

    void transfer(Account &to, double amount) {
        if (amount > balance) {
            cout << "Insufficient balance for transfer!\n";
            return;
        }
        balance -= amount;
        to.balance += amount;

        history.push_back(Transaction("Transfer Sent", amount, "to Account " + to_string(to.getAccountNumber())));
        to.history.push_back(Transaction("Transfer Received", amount, "from Account " + to_string(accountNumber)));

        cout << "Transferred $" << amount << " to Account " << to.getAccountNumber() << " successfully.\n";
    }

    void showHistory() const {
        cout << "\nTransaction History for Account " << accountNumber << ":\n";
        if (history.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        for (const auto &t : history) {
            t.display();
        }
    }

    void displayInfo() const {
        cout << "\nAccount Number: " << accountNumber << "\nBalance: $" << balance << endl;
    }
};

// ---------- Customer Class ----------
class Customer {
    string name;
    int customerId;
    vector<Account> accounts;
public:
    Customer(string n, int id) {
        name = n;
        customerId = id;
    }

    string getName() const { return name; }
    int getId() const { return customerId; }

    void addAccount(int accNo, double initialBalance = 0.0) {
        accounts.push_back(Account(accNo, initialBalance));
        cout << "Account " << accNo << " created for " << name << " with initial balance $" << initialBalance << ".\n";
    }

    Account* getAccount(int accNo) {
        for (auto &acc : accounts) {
            if (acc.getAccountNumber() == accNo)
                return &acc;
        }
        return nullptr;
    }

    void displayAccounts() const {
        cout << "\nCustomer: " << name << " (ID: " << customerId << ")\nAccounts:\n";
        for (const auto &acc : accounts) {
            acc.displayInfo();
        }
    }
};

// ---------- Main Program ----------
int main() {
    // Creating Customers
    Customer c1("Alice", 101);
    Customer c2("Bob", 102);

    // Creating Accounts
    c1.addAccount(1001, 500);
    c2.addAccount(2001, 1000);

    // Perform Transactions
    Account* acc1 = c1.getAccount(1001);
    Account* acc2 = c2.getAccount(2001);

    if (acc1 && acc2) {
        acc1->deposit(200);
        acc1->withdraw(100);
        acc1->transfer(*acc2, 250);
    }

    // Show Info
    c1.displayAccounts();
    acc1->showHistory();

    c2.displayAccounts();
    acc2->showHistory();

    return 0;
}