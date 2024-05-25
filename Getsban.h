#ifndef GETSBAN_H_ 
#define GETSBAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CUSTOMERS 100
#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 100

typedef struct {
    int id;
    char name[100];
    char address[150];
    int password;
} Client;

typedef struct {
    int account_number;
    int client_id;
    double balance;
} Account;

typedef struct {
    int transaction_id;
    int account_number;
    double amount;
    char type[10]; // "deposit" or "withdrawal"
} Transaction;

Client clients[MAX_CUSTOMERS];
Account accounts[MAX_ACCOUNTS];
Transaction transactions[MAX_TRANSACTIONS];

int number_of_clients = 0;
int number_of_accounts = 0;
int number_of_transactions = 0;

void create_Password(Client clients[], int number_of_clients) {
    int id;
    int password;
    int client_index = -1;

    printf("\n");

    while (1) {
        printf("Please enter your ID (to create your password) : ");
        scanf("%d", &id);

        // Find the client with the provided ID
        for (int i = 0; i < number_of_clients; i++) {
            if (clients[i].id == id) {
                client_index = i;
                break;
            }
        }

        if (client_index == -1) {
            printf("User ID not found. Please enter a valid ID or enter 0 to cancel.\n");
        } else {
            break; // Break out of the loop if a valid ID is entered
        }
    }

    // Loop to prompt for a 4-digit positive integer password
    do {
        printf("Create your 4-digit password : ");
        scanf("%4d", &password);

        if (password < 1000 || password > 9999 || password == 1234) {
            printf("Password must be a 4-digit positive integer. Please try again.\n");
        }
    } while (password < 1000 || password > 9999 || password == 1234);

    client_index = -1;
    for (int i = 0; i < number_of_clients; i++)
    {
        if(clients[i].password == password) {
            client_index = i;
            break;
        }
    }

    if(client_index != -1) {
        printf("The password has been used before. Please try a different password.\n");
        do {
            printf("Create your new 4-digit password : ");
            scanf("%4d", &password);

            if (password < 1000 || password > 9999 || password == 1234 || clients[client_index].password == password) {
                printf("Password must be a 4-digit positive integer and should not have been used before. Please try again.\n");
            }
        } while (password < 1000 || password > 9999 || password == 1234 || clients[client_index].password == password);
    }

        for (int i = 0; i < number_of_clients; i++) {
            if (clients[i].id == id) {
                // Update the password
                clients[i].password = password;
                printf("\n");
                printf("Password created successfully.\n");
                printf("\n\n");
                return;
            } 
        }
}

void add_Client() {
    if (number_of_clients >= MAX_CUSTOMERS) {
        printf("Maximum limit of clients reached.\n");
        return;
    }

    Client c;
    c.id = number_of_clients + 1;
    printf("Enter the client's name : ");
    scanf(" %[^\n]", c.name);
    printf("Enter the client's address : ");
    scanf(" %[^\n]", c.address);
    clients[number_of_clients++] = c;
    printf("Client added successfully with ID : %d\n", c.id);

    // Create password for the newly added client
    create_Password(clients, number_of_clients);
}

int verify_Password(Client clients[], int number_of_clients, int entered_password) {
    int id;
    int client_index = -1;

    while (1) {
        printf("please enter your ID (for verify the Password) : ");
        scanf("%d", &id);

        // Find the client with the provided ID
        for (int i = 0; i < number_of_clients; i++) {
            if (clients[i].id == id) {
                client_index = i;
                break;
            }
        }

        if (client_index == -1) {
            printf("User ID not found. Please enter a valid ID or enter 0 to cancel.\n");
            printf("\n");
        } else {
            break; // Break out of the loop if a valid ID is entered
        }
    }

    int max_attempts = 3; // Maximum number of password verification attempts

    // Find the client with the provided ID
    for (int i = 0; i < number_of_clients; i++) {
        if (clients[i].id == id) {
            int attempts = 0; // Counter for password verification attempts

            // Loop until the correct password is entered or max_attempts is reached
            while (attempts < max_attempts) {
                // Check if the entered password matches the stored password
                if (entered_password == clients[i].password) {
                    printf("Password verification successful.\n");
                    printf("\n");
                    return 1; // Return 1 for successful verification
                } else {
                    attempts++; // Increment attempts counter
                    printf("Incorrect password. %d attempts remaining.\n", max_attempts - attempts);
                    printf("\n");
                    printf("Enter your password : ");
                    scanf("%d", &entered_password);
                }
            }

            // If max_attempts is reached without successful verification
            printf("\n");
            printf("Max attempts reached. Access denied.\n");
            printf("\n\n");
            return 0; // Return 0 for failed verification
        }
    }
}

void create_Account() {
    if (number_of_accounts >= MAX_ACCOUNTS) {
        printf("Maximum limit of accounts reached.\n");
        return;
    }

    int id;
    int client_index = -1;

   // Loop until a valid ID is entered
    while (1) {
        printf("Enter your ID to create an account (or enter 0 to cancel) : ");
        scanf("%d", &id);

        // Check if the user entered 0 to cancel
        if (id == 0) {
            printf("Account creation cancelled.\n");
            return;
        }

        // Find the client with the provided ID
        for (int i = 0; i < number_of_clients; i++) {
            if (clients[i].id == id) {
                client_index = i;
                break;
            }
        }

        if (client_index == -1) {
            printf("User ID not found. Please enter a valid ID or enter 0 to cancel.\n");
        } else {
            break; // Break out of the loop if a valid ID is entered
        }
    }

    // Prompt for password verification
    int entered_password;
    printf("\n");
    printf("Enter your password to proceed : ");
    scanf("%d", &entered_password);

    // Verify the entered password
    if (!verify_Password(clients, number_of_clients, entered_password)) {
        printf("Password verification failed. Access denied.\n");
        printf("\n");
        return;
    }

    // Now you can proceed with creating the account using the provided client's information
    Account a;
    a.client_id = clients[client_index].id;
    a.account_number = number_of_accounts + 1;
    a.balance = 0.0;
    accounts[number_of_accounts++] = a;
    printf("Account created successfully with the account number : %d\n", a.account_number);
    printf("\n\n");
}

void perform_Transaction() {
    if (number_of_transactions >= MAX_TRANSACTIONS) {
        printf("Maximum limit of transactions reached.\n");
        return;
    }

    int id;
    int client_index = -1;

    // Loop until a valid ID is entered
    while (1) {
        printf("Enter your ID to perform Transaction (or enter 0 to cancel) : ");
        scanf("%d", &id);

        // Check if the user entered 0 to cancel
        if (id == 0) {
            printf("Transaction cancelled.\n");
            return;
        }

        // Find the client with the provided ID
        for (int i = 0; i < number_of_clients; i++) {
            if (clients[i].id == id) {
                client_index = i;
                break;
            }
        }

        if (client_index == -1) {
            printf("User ID not found. Please enter a valid ID or enter 0 to cancel.\n");
            printf("\n");
        } else {
            break; // Break out of the loop if a valid ID is entered
        }
    }

    // Prompt for password verification
    int entered_password;
    printf("\n");
    printf("Enter your password to proceed: ");
    scanf("%d", &entered_password);

    // Verify the entered password
    if (!verify_Password(clients, number_of_clients, entered_password)) {
        printf("Password verification failed. Access denied.\n");
        printf("\n");
        return;
    }

    Transaction t;
    printf("\n");
    printf("Enter the account number: ");
    scanf("%d", &t.account_number);
    printf("Enter the transaction type (deposit/withdrawal) : ");
    scanf("%s", t.type);
    printf("Enter the amount: ");
    scanf("%lf", &t.amount);
    t.transaction_id = number_of_transactions + 1;

    int account_found = 0;
    for (int i = 0; i < number_of_accounts; i++) {
        if (accounts[i].account_number == t.account_number) {
            account_found = 1;
            if (strcmp(t.type, "deposit") == 0) {
                accounts[i].balance += t.amount;
            } else if (strcmp(t.type, "withdrawal") == 0) {
                if (accounts[i].balance >= t.amount) {
                    accounts[i].balance -= t.amount;
                } else {
                    printf("Insufficient balance.\n");
                    return;
                }
            } else {
                printf("Invalid transaction type.\n");
                return;
            }
            break;
        }
    }

    if (!account_found) {
        printf("Account not found.\n");
        return;
    }

    transactions[number_of_transactions++] = t;
    printf("\n");
    printf("Transaction successfully completed with transaction ID : %d\n", t.transaction_id);
    printf("\n\n");
}

void display_Client_Details() {
    int id;
    int client_index = -1;

    // Loop until a valid ID is entered
    while (1) {
        printf("Enter your ID to display your Details (or enter 0 to cancel)  : ");
        scanf("%d", &id);

        // Check if the user entered 0 to cancel
        if (id == 0) {
            printf("display Details cancelled.\n");
            return;
        }

        // Find the client with the provided ID
        for (int i = 0; i < number_of_clients; i++) {
            if (clients[i].id == id) {
                client_index = i;
                break;
            }
        }

        if (client_index == -1) {
            printf("User ID not found. Please enter a valid ID or enter 0 to cancel.\n");
            printf("\n");
        } else {
            break; // Break out of the loop if a valid ID is entered
        }
    }

    // Prompt for password verification
    int entered_password;
    printf("\n");
    printf("Enter your password to proceed : ");
    scanf("%d", &entered_password);

    // Verify the entered password
    if (!verify_Password(clients, number_of_clients, entered_password)) {
        printf("Password verification failed. Access denied.\n");
        printf("\n");
        return;
    }

    for (int i = 0; i < number_of_clients; i++) {
        if (clients[i].id == id) {
            printf("\n");
            printf("Client ID : %d\n", clients[i].id);
            printf("Name : %s\n", clients[i].name);
            printf("Address : %s\n", clients[i].address);
            printf("\n\n");
            return;
        }
    }
}

void display_Account_Details() {
    int account_number;
    int id;
    int client_index = -1;

    // Loop until a valid ID is entered
    while (1) {
        printf("Enter your ID to display your Account Details (or enter 0 to cancel) : ");
        scanf("%d", &id);

        // Check if the user entered 0 to cancel
        if (id == 0) {
            printf("Display cancelled.\n");
            return;
        }

        // Find the client with the provided ID
        for (int i = 0; i < number_of_clients; i++) {
            if (clients[i].id == id) {
                client_index = i;
                break;
            }
        }

        if (client_index == -1) {
            printf("User ID not found. Please enter a valid ID or enter 0 to cancel.\n");
            printf("\n");
        } else {
            break; // Break out of the loop if a valid ID is entered
        }
    }

    // Prompt for password verification
    int entered_password;
    printf("\n");
    printf("Enter your password to proceed : ");
    scanf("%d", &entered_password);

    // Verify the entered password
    if (!verify_Password(clients, number_of_clients, entered_password)) {
        printf("Password verification failed. Access denied.\n");
        printf("\n");
        return;
    }

    printf("Enter the account number : ");
    scanf("%d", &account_number);
    for (int i = 0; i < number_of_accounts; i++) {
        if (accounts[i].account_number == account_number) {
            printf("\n");
            printf("Account Number : %d\n", accounts[i].account_number);
            printf("Client ID : %d\n", accounts[i].client_id);
            printf("Balance : %.2f DH\n", accounts[i].balance);
            printf("\n\n");
            return;
        }
    }
    printf("Account not found.\n");
}

void display_Transaction_History(int account_number) {
    int id;
    int client_index = -1;
    // Loop until a valid ID is entered

    while (1) {
        printf("Enter your ID to view your transaction history (or enter 0 to cancel) : ");
        scanf("%d", &id);

        // Check if the user entered 0 to cancel
        if (id == 0) {
            printf("Transaction history view cancelled.\n");
            return;
        }

        // Find the client with the provided ID
        for (int i = 0; i < number_of_clients; i++) {
            if (clients[i].id == id) {
                client_index = i;
                break;
            }
        }

        if (client_index == -1) {
            printf("User ID not found. Please enter a valid ID or enter 0 to cancel.\n");
            printf("\n");
        } else {
            break; // Break out of the loop if a valid ID is entered
        }
    }

    // Prompt for password verification
    int entered_password;
    printf("\n");
    printf("Enter your password to proceed : ");
    scanf("%d", &entered_password);

    // Verify the entered password
    if (!verify_Password(clients, number_of_clients, entered_password)) {
        printf("Password verification failed. Access denied.\n");
        printf("\n");
        return;
    }

    printf("Transaction history for account number: %d\n", account_number);
    printf("------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < number_of_transactions; i++) {
        if (transactions[i].account_number == account_number) {
            printf("Transaction ID : %d, Type : %s, Amount : %.2f DH\n", transactions[i].transaction_id, transactions[i].type, transactions[i].amount);
            printf("\n\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No transactions found for this account.\n");
    }
}

void delete_Account(int account_number) {
    int index = -1;
    int id;
    int client_index = -1;

    // Loop until a valid ID is entered
    while (1) {
        printf("Enter your ID to delete your account (or enter 0 to cancel): ");
        scanf("%d", &id);

        // Check if the user entered 0 to cancel
        if (id == 0) {
            printf("Account deletion cancelled.\n");
            return;
        }

        // Find the client with the provided ID
        for (int i = 0; i < number_of_clients; i++) {
            if (clients[i].id == id) {
                client_index = i;
                break;
            }
        }

        if (client_index == -1) {
            printf("User ID not found. Please enter a valid ID or enter 0 to cancel.\n");
        } else {
            break; // Break out of the loop if a valid ID is entered
        }
    }

    // Prompt for password verification
    int entered_password;
    printf("Enter your password to proceed: ");
    scanf("%d", &entered_password);

    // Verify the entered password
    if (!verify_Password(clients, number_of_clients, entered_password)) {
        printf("Password verification failed. Access denied.\n");
        return;
    }

    printf("Enter the account number : ");
    scanf("%d", &account_number);
    for (int i = 0; i < number_of_accounts; i++) {
        if (accounts[i].account_number == account_number) {
            index = i;
            break;
        }
    }

    if (index != -1) {

        // Delete transactions associated with this account
        for (int i = 0; i < number_of_transactions; i++) {
            if (transactions[i].account_number == account_number) {
                for (int j = i; j < number_of_transactions - 1; j++) {
                    transactions[j] = transactions[j + 1];
                }
                number_of_transactions--;
                i--; // to revisit the deleted transaction in the loop
            }
        }

        // Delete the found account
        for (int i = index; i < number_of_accounts - 1; i++) {
            accounts[i] = accounts[i + 1];
        }
        number_of_accounts--;
        printf("Account number %d deleted successfully, along with its transaction history.\n", account_number);

    } else {
        printf("Account not found.\n");
    }
}

void delete_Client(int client_id) {
    int index = -1;
    int id;
    int client_index = -1;

    // Loop until a valid ID is entered
    while (1) {
        printf("Enter your ID to delete you from clients (or enter 0 to cancel): ");
        scanf("%d", &id);

        // Check if the user entered 0 to cancel
        if (id == 0) {
            printf("Client deletion cancelled.\n");
            return;
        }

        // Find the client with the provided ID
        for (int i = 0; i < number_of_clients; i++) {
            if (clients[i].id == id) {
                client_index = i;
                break;
            }
        }

        if (client_index == -1) {
            printf("User ID not found. Please enter a valid ID or enter 0 to cancel.\n");
        } else {
            break; // Break out of the loop if a valid ID is entered
        }
    }

    // Prompt for password verification
    int entered_password;
    printf("Enter your password to proceed: ");
    scanf("%d", &entered_password);

    // Verify the entered password
    if (!verify_Password(clients, number_of_clients, entered_password)) {
        printf("Password verification failed. Access denied.\n");
        return;
    }

    for (int i = 0; i < number_of_clients; i++) {
        if (clients[i].id == id) {
            index = i;
            break;
        }
    }

    if (index != -1) {

        // Delete the found client
        for (int i = index; i < number_of_clients - 1; i++) {
            clients[i] = clients[i + 1];
        }
        number_of_clients--;

        // Delete all accounts associated with the client
        for (int i = 0; i < number_of_accounts; i++) {
            if (accounts[i].client_id == client_id) {
                delete_Account(accounts[i].account_number);
            }
        }
        printf("Client with ID %d and all associated accounts have been deleted successfully.\n", id);

    } else {
        printf("Client not found.\n");
    }
}

void save_Data() {
    FILE *file = fopen("bank_data.bin", "wb");
    if (!file) {
        printf("Error while opening file for saving data.\n");
        return;
    }
    if (fwrite(&number_of_clients, sizeof(int), 1, file) != 1 ||
        fwrite(clients, sizeof(Client), number_of_clients, file) != number_of_clients ||
        fwrite(&number_of_accounts, sizeof(int), 1, file) != 1 ||
        fwrite(accounts, sizeof(Account), number_of_accounts, file) != number_of_accounts ||
        fwrite(&number_of_transactions, sizeof(int), 1, file) != 1 ||
        fwrite(transactions, sizeof(Transaction), number_of_transactions, file) != number_of_transactions) {
        printf("Error while writing data to file.\n");
        fclose(file);
        return;
    }
    if (fclose(file) != 0) {
        printf("Error while closing file after saving data.\n");
        return;
    }
    printf("Data saved successfully.\n");
}

void load_Data() {
    FILE *file = fopen("bank_data.bin", "rb");
    if (!file) {
        printf("Error while opening file for loading data.\n");
        return;
    }
    if (fread(&number_of_clients, sizeof(int), 1, file) != 1 ||
        fread(clients, sizeof(Client), number_of_clients, file) != number_of_clients ||
        fread(&number_of_accounts, sizeof(int), 1, file) != 1 ||
        fread(accounts, sizeof(Account), number_of_accounts, file) != number_of_accounts ||
        fread(&number_of_transactions, sizeof(int), 1, file) != 1 ||
        fread(transactions, sizeof(Transaction), number_of_transactions, file) != number_of_transactions) {
        printf("Error while reading data from file.\n");
        fclose(file);
        return;
    }
    if (fclose(file) != 0) {
        printf("Error while closing file after loading data.\n");
        return;
    }
    printf("Data loaded successfully.\n");
}


void printCentered(const char *text) {
    int width = 200;
    int length = strlen(text);
    int pad = (width - length) / 2;
    printf("%*s%s%*s\n", pad, "", text, pad, "");
}

#endif
