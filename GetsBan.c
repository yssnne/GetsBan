#include <stdio.h>
#include "Getsban.h"

int main() {
    int choice;
    system("CLS");
    load_Data();

    // Welcome message for customers
    printf("==============================================================================================================================================================================================================\n\n");
    printf("\n");

    printCentered("** Welcome to GestBan! **\n\n");
    printCentered("We are delighted to welcome you to GestBan. Thank you for your trust!\n");
    printf("\n\n");

    printf("==============================================================================================================================================================================================================\n\n");
    printf("\n\n");

    while (1) {
        printCentered("** Banking Management System **\n");

        printf("\n");
        printf("1. Add a client\n");
        printf("\n");
        printf("2. Create an account\n");
        printf("\n");
        printf("3. Perform a transaction\n");
        printf("\n");
        printf("4. Display client details\n");
        printf("\n");
        printf("5. Display account details\n");
        printf("\n");
        printf("6. Display transaction history\n");
        printf("\n");
        printf("7. Save data\n");
        printf("\n");
        printf("8. Load data\n");
        printf("\n");
        printf("9. Delete an account\n");
        printf("\n");
        printf("10. Delete a client\n");
        printf("\n");
        printf("11. Quit\n");
        printf("\n\n");

        printf("Enter your choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                system("CLS");
                add_Client();
                break;
            case 2:
                system("CLS");
                create_Account();
                break;
            case 3:
                system("CLS");
                perform_Transaction();
                break;
            case 4:
                system("CLS");
                display_Client_Details();
                break;
            case 5:
                system("CLS");
                display_Account_Details();
                break;

            case 6:
                system("CLS");
                printf("Enter the account number: ");
                int account_Number;
                scanf("%d", &account_Number);
                display_Transaction_History(account_Number);
                break;

            case 7:
                system("CLS");
                save_Data();
                break;
            case 8:
                system("CLS");
                load_Data();
                break;

            case 9:
                system("CLS");
                printf("Enter the account number to delete: ");
                int account_Num_To_Delete;
                scanf("%d", &account_Num_To_Delete);
                delete_Account(account_Num_To_Delete);
                break;

            case 10:
                system("CLS");
                printf("Enter the client ID to delete: ");
                int client_ID_To_Delete;
                scanf("%d", &client_ID_To_Delete);
                delete_Client(client_ID_To_Delete);
                break;

            case 11:
                system("CLS");
                save_Data();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
