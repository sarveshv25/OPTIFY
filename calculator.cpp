#include <iostream>
using namespace std;

int main() {
    int choice;
    double num1, num2, result;

    while (true) {
        // Display the menu
        cout << "\nBasic Calculator" << endl;
        cout << "----------------" << endl;
        cout << "1. Addition" << endl;
        cout << "2. Subtraction" << endl;
        cout << "3. Multiplication" << endl;
        cout << "4. Division" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Check if the user wants to exit
        if (choice == 5) {
            cout << "Exiting the calculator. Goodbye!" << endl;
            break;
        }

        // Get user input for the numbers
        cout << "Enter the first number: ";
        cin >> num1;
        cout << "Enter the second number: ";
        cin >> num2;

        // Perform the chosen operation using if-else
        if (choice == 1) {
            result = num1 + num2;
            cout << "Result: " << result << endl;
        } else if (choice == 2) {
            result = num1 - num2;
            cout << "Result: " << result << endl;
        } else if (choice == 3) {
            result = num1 * num2;
            cout << "Result: " << result << endl;
        } else if (choice == 4) {
            if (num2 != 0) {
                result = num1 / num2;
                cout << "Result: " << result << endl;
            } else {
                cout << "Error: Division by zero is not allowed." << endl;
            }
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}


