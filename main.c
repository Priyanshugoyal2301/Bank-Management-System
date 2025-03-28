#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define FILE_NAME "bank_accounts.dat"

// Structure to store account details
typedef struct {
    int accountNumber;
    char name[MAX_NAME_LENGTH];
    float balance;
} Account;

// Function prototypes
void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
void viewAccounts();
void menu();

int main() {
    menu();
    return 0;
}

// Function to display menu
void menu() {
    int choice;
    while (1) {
        printf("\n--- Bank Management System ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. View All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: viewAccounts(); break;
            case 6: 
                printf("Exiting system... Thank you!\n");
                exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

// Function to create an account
void createAccount() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Account acc;
    printf("Enter Account Number: ");
    scanf("%d", &acc.accountNumber);
    printf("Enter Name: ");
    getchar(); // Clear input buffer
    fgets(acc.name, MAX_NAME_LENGTH, stdin);
    acc.name[strcspn(acc.name, "\n")] = 0; // Remove newline character
    acc.balance = 0.0; // Initial balance

    fwrite(&acc, sizeof(Account), 1, file);
    fclose(file);
    printf("Account created successfully!\n");
}

// Function to deposit money
void depositMoney() {
    int accNum;
    float amount;
    FILE *file = fopen(FILE_NAME, "rb+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    Account acc;
    int found = 0;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            found = 1;
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, file);
            printf("Amount deposited successfully! New Balance: %.2f\n", acc.balance);
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}

// Function to withdraw money
void withdrawMoney() {
    int accNum;
    float amount;
    FILE *file = fopen(FILE_NAME, "rb+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    Account acc;
    int found = 0;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            found = 1;
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);
            if (amount > acc.balance) {
                printf("Insufficient balance!\n");
            } else {
                acc.balance -= amount;
                fseek(file, -sizeof(Account), SEEK_CUR);
                fwrite(&acc, sizeof(Account), 1, file);
                printf("Amount withdrawn successfully! New Balance: %.2f\n", acc.balance);
            }
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}

// Function to check account balance
void checkBalance() {
    int accNum;
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    Account acc;
    int found = 0;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            found = 1;
            printf("Account Name: %s\n", acc.name);
            printf("Account Balance: %.2f\n", acc.balance);
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}

// Function to view all accounts
void viewAccounts() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n--- Account List ---\n");
    Account acc;
    while (fread(&acc, sizeof(Account), 1, file)) {
        printf("Account Number: %d\n", acc.accountNumber);
        printf("Name: %s\n", acc.name);
        printf("Balance: %.2f\n", acc.balance);
        printf("----------------------\n");
    }

    fclose(file);
}
