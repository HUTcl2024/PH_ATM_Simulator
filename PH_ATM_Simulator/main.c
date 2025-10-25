//
//  main.c
//  PH_ATM_Simulator
//
//  Created by Rong Liao on 2025-10-11.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BALANCE_FILE "balance.txt"
#define TRANSACTION_FILE "transactions.txt"

// Function prototypes
void displayMenu();
void viewBalance();
void deposit();
void withdraw();
void viewTransactions();
double getBalance();
void updateBalance(double newBalance);
void logTransaction(const char* type, double amount, double balanceAfter);
void clearInputBuffer();

int main(int argc, const char * argv[]) {
    int choice;
    
    printf("========================================\n");
    printf("   Welcome to PH ATM Simulator\n");
    printf("========================================\n\n");
    
    // Initialize balance file if it doesn't exist
    FILE *balanceFile = fopen(BALANCE_FILE, "r");
    if (balanceFile == NULL) {
        balanceFile = fopen(BALANCE_FILE, "w");
        fprintf(balanceFile, "0.00");
        fclose(balanceFile);
        printf("Account initialized with balance: $0.00\n\n");
    } else {
        fclose(balanceFile);
    }
    
    // Main menu loop
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\nInvalid input! Please enter a number.\n\n");
            continue;
        }
        clearInputBuffer();
        
        printf("\n");
        
        switch (choice) {
            case 1:
                viewBalance();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                viewTransactions();
                break;
            case 5:
                printf("Thank you for using PH ATM Simulator!\n");
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please select 1-5.\n\n");
        }
    }
    
    return 0;
}

void displayMenu() {
    printf("========================================\n");
    printf("              MAIN MENU\n");
    printf("========================================\n");
    printf("1. View Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. View Transactions\n");
    printf("5. Exit\n");
    printf("========================================\n");
}

void viewBalance() {
    double balance = getBalance();
    printf("========================================\n");
    printf("         CURRENT BALANCE\n");
    printf("========================================\n");
    printf("Your current balance: $%.2f\n", balance);
    printf("========================================\n\n");
}

void deposit() {
    double amount;
    double currentBalance = getBalance();
    
    printf("========================================\n");
    printf("              DEPOSIT\n");
    printf("========================================\n");
    printf("Current balance: $%.2f\n", currentBalance);
    printf("Enter amount to deposit: $");
    
    if (scanf("%lf", &amount) != 1) {
        clearInputBuffer();
        printf("Invalid input! Deposit cancelled.\n\n");
        return;
    }
    clearInputBuffer();
    
    if (amount <= 0) {
        printf("Invalid amount! Amount must be positive.\n\n");
        return;
    }
    
    double newBalance = currentBalance + amount;
    updateBalance(newBalance);
    logTransaction("DEPOSIT", amount, newBalance);
    
    printf("\nDeposit successful!\n");
    printf("Amount deposited: $%.2f\n", amount);
    printf("New balance: $%.2f\n", newBalance);
    printf("========================================\n\n");
}

void withdraw() {
    double amount;
    double currentBalance = getBalance();
    
    printf("========================================\n");
    printf("             WITHDRAWAL\n");
    printf("========================================\n");
    printf("Current balance: $%.2f\n", currentBalance);
    printf("Enter amount to withdraw: $");
    
    if (scanf("%lf", &amount) != 1) {
        clearInputBuffer();
        printf("Invalid input! Withdrawal cancelled.\n\n");
        return;
    }
    clearInputBuffer();
    
    if (amount <= 0) {
        printf("Invalid amount! Amount must be positive.\n\n");
        return;
    }
    
    if (amount > currentBalance) {
        printf("Insufficient funds! Withdrawal cancelled.\n");
        printf("Your current balance is: $%.2f\n\n", currentBalance);
        return;
    }
    
    double newBalance = currentBalance - amount;
    updateBalance(newBalance);
    logTransaction("WITHDRAW", amount, newBalance);
    
    printf("\nWithdrawal successful!\n");
    printf("Amount withdrawn: $%.2f\n", amount);
    printf("New balance: $%.2f\n", newBalance);
    printf("========================================\n\n");
}

void viewTransactions() {
    printf("========================================\n");
    printf("        TRANSACTION HISTORY\n");
    printf("========================================\n");
    
    FILE *transFile = fopen(TRANSACTION_FILE, "r");
    if (transFile == NULL) {
        printf("No transactions found.\n");
        printf("========================================\n\n");
        return;
    }
    
    char line[256];
    int count = 0;
    
    while (fgets(line, sizeof(line), transFile)) {
        printf("%s", line);
        count++;
    }
    
    fclose(transFile);
    
    if (count == 0) {
        printf("No transactions found.\n");
    }
    
    printf("========================================\n\n");
}

double getBalance() {
    FILE *balanceFile = fopen(BALANCE_FILE, "r");
    if (balanceFile == NULL) {
        return 0.0;
    }
    
    double balance;
    fscanf(balanceFile, "%lf", &balance);
    fclose(balanceFile);
    
    return balance;
}

void updateBalance(double newBalance) {
    FILE *balanceFile = fopen(BALANCE_FILE, "w");
    if (balanceFile == NULL) {
        printf("Error updating balance!\n");
        return;
    }
    
    fprintf(balanceFile, "%.2f", newBalance);
    fclose(balanceFile);
}

void logTransaction(const char* type, double amount, double balanceAfter) {
    FILE *transFile = fopen(TRANSACTION_FILE, "a");
    if (transFile == NULL) {
        printf("Error logging transaction!\n");
        return;
    }
    
    // Get current date and time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    fprintf(transFile, "%04d-%02d-%02d %02d:%02d:%02d | %-10s | $%10.2f | Balance: $%.2f\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec,
            type, amount, balanceAfter);
    
    fclose(transFile);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
