#include <stdio.h>  // Standard input-output functions
#include <string.h> // String handling functions

#define NUM_ACCOUNTS 5 // Total number of bank accounts

// Structure to store account details
typedef struct {
    int accountNumber;  // Unique account number
    char *password;     // Pointer to password string
    char *name;         // Pointer to account holder's name
    float balance;      // Account balance
    int status;         // 1 = Active, 0 = Inactive
} Account;

// Function prototypes for banking operations
void checkBalance(float *balance);
void depositMoney(float *balance);
void withdrawMoney(float *balance);

int main() {
    // Array of account structures
    Account accounts[NUM_ACCOUNTS] = {
        {1001, "pass123", "Alice Johnson", 1500.50, 1},
        {1002, "abc456", "Bob Smith", 2300.75, 1},
        {1003, "secure99", "Charlie Brown", 540.25, 0},  // Inactive account
        {1004, "mypwd", "David Lee", 10000.00, 1},
        {1005, "bank2024", "Emma Watson", 725.80, 1}
    };

    int enteracc, choice; // Variables for user input
    char pass[20]; // Array to store entered password
    int found = -1; // Index of logged-in account (-1 means not found)

    // Ask for login details
    printf("Enter account number: ");
    scanf("%d", &enteracc);
    printf("Enter password: ");
    scanf("%s", pass);

    // Check if account exists and credentials are correct
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        if (accounts[i].accountNumber == enteracc && strcmp(accounts[i].password, pass) == 0) {
            printf("\n✅ Login Successful!\n");
            printf("Welcome, %s!\n", accounts[i].name);
            found = i; // Save the account index
            break;
        }
    }

    // If no matching account is found, show an error and exit
    if (found == -1) {
        printf("\n❌ Incorrect account number or password!\n");
        return 0;
    }

    // Show menu options in a loop
    do {
        printf("\n📋 Bank Menu:\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform action based on user choice
        switch (choice) {
            case 1:
                checkBalance(&accounts[found].balance); // Pass address of balance
                break;
            case 2:
                depositMoney(&accounts[found].balance); // Pass address of balance
                break;
            case 3:
                withdrawMoney(&accounts[found].balance); // Pass address of balance
                break;
            case 4:
                printf("\n👋 Thank you for banking with us! Goodbye!\n");
                break;
            default:
                printf("\n❌ Invalid choice! Try again.\n");
        }
    } while (choice != 4); // Repeat menu until user chooses to exit

    return 0; // End program
}

// Function to check account balance
void checkBalance(float *balance) {
    printf("\n💰 Your current balance: $%.2f\n", *balance);
}

// Function to deposit money
void depositMoney(float *balance) {
    float deposit;
    printf("\n💵 Enter deposit amount: $");
    scanf("%f", &deposit);
    
    if (deposit > 0) { // Only accept positive deposit
        *balance += deposit; // Update balance
        printf("✅ Deposit successful! New balance: $%.2f\n", *balance);
    } else {
        printf("❌ Invalid amount. Deposit must be greater than $0.\n");
    }
}

// Function to withdraw money
void withdrawMoney(float *balance) {
    float withdraw;
    printf("\n🏧 Enter withdrawal amount: $");
    scanf("%f", &withdraw);

    if (withdraw > 0 && withdraw <= *balance) { // Check valid amount
        *balance -= withdraw; // Deduct from balance
        printf("✅ Withdrawal successful! New balance: $%.2f\n", *balance);
    } else if (withdraw > *balance) { // Not enough money
        printf("❌ Insufficient funds! Your balance is only $%.2f.\n", *balance);
    } else { // Invalid input
        printf("❌ Invalid amount. Withdrawal must be greater than $0.\n");
    }
}
