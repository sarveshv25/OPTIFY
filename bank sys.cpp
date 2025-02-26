#include <iostream>
#include <unordered_map>
#include <string>

class BankAccount {
private:
    std::string username;
    std::string password;
    double balance;

public:
    // Default constructor (required for unordered_map)
    BankAccount() : username(""), password(""), balance(0.0) {}

    // Parameterized constructor
    BankAccount(const std::string& user, const std::string& pass)
        : username(user), password(pass), balance(0.0) {}

    bool authenticate(const std::string& pass) const {
        return password == pass;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited: $" << amount << "\n";
        } else {
            std::cout << "Invalid amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrawn: $" << amount << "\n";
        } else {
            std::cout << "Insufficient funds or invalid amount.\n";
        }
    }

    void checkBalance() const {
        std::cout << "Current Balance: $" << balance << "\n";
    }
};

// Global account storage
std::unordered_map<std::string, BankAccount> accounts;

void createAccount() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cin.ignore(); // Ignore leftover newline

    if (accounts.find(username) != accounts.end()) {
        std::cout << "Account already exists.\n";
        return;
    }

    std::cout << "Enter password: ";
    std::getline(std::cin, password); // Use getline for passwords

    accounts[username] = BankAccount(username, password);
    std::cout << "Account created successfully!\n";
}

void accessAccount() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cin.ignore(); // Ignore leftover newline

    if (accounts.find(username) == accounts.end()) {
        std::cout << "Account not found.\n";
        return;
    }

    std::cout << "Enter password: ";
    std::getline(std::cin, password); // Use getline for passwords

    if (!accounts[username].authenticate(password)) {
        std::cout << "Incorrect password.\n";
        return;
    }

    int choice;
    do {
        std::cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Logout\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                double amount;
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                accounts[username].deposit(amount);
                break;
            }
            case 2: {
                double amount;
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                accounts[username].withdraw(amount);
                break;
            }
            case 3:
                accounts[username].checkBalance();
                break;
            case 4:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

int main() {
    int choice;
    do {
        std::cout << "\n1. Create Account\n2. Access Account\n3. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                accessAccount();
                break;
            case 3:
                std::cout << "Exiting system...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}


