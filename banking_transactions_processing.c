//Importing Libraries
#include <stdio.h>

//Main Function
int main() {
    //Initializting Variables
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    int length = sizeof(transactions) / sizeof(transactions[0]);
    int tobeprocessed[length];
    int initial_balance = 100;
    int tobeprocessedIndex = 0;

    //Printing Initial Status
    printf("*Welcome to CSCI291 Banking*\n\n");
    printf("Your Initial Balance is: %d\n",initial_balance);
    printf("Transactions to be Done: ");
    for (int i = 0; i < length; i++) {
        printf("%d ",transactions[i]);
    }
    printf("\n\n");

    //Iterating Through To Transactions Array
    for (int i = 0; i < length; i++) {
        printf("Current Transaction Processing: %d\n",transactions[i]);
        //If Transactions More Than Balance
        if (transactions[i] < 0 && initial_balance + transactions[i] < 0) {
            printf("Invalid transaction: %d\n", transactions[i]);
            printf("Current Balance: %d\n",initial_balance);
            tobeprocessed[tobeprocessedIndex] = transactions[i];
            tobeprocessedIndex++;
        } 
        //If Transactions are Valid
        else {
            initial_balance += transactions[i];
            printf("Transaction Complete\n");
            printf("Current Balance: %d\n",initial_balance);
            if (initial_balance == 0) {
                printf("Current balance is zero. No further transactions will be processed.\n");
                for (int j = i + 1; j < length; j++) {
                    tobeprocessed[tobeprocessedIndex] = transactions[j];
                    tobeprocessedIndex++;
                }
                break;
            }
        }
        printf("\n");
    }

    //Printing Final Status
    printf("Final balance: %d AED\n", initial_balance);
    printf("Unprocessed transactions: ");
    for (int i = 0; i < tobeprocessedIndex; i++) {
        printf("%d ", tobeprocessed[i]);
    }
    printf("\n");

    return 0;
}