/*--------------------------
ProjectBank.c

Banking System:
Prompt: Simulate a bank queue using a Linked List queue.
Each customer is represented by attributes Like TokenNumber, Name, and ServiceType.
Senior citizens should be given priority in the queue.
Write functions to:
a. Add a customer to the queue (senior citizens should get priority).
b. Serve the next customer based on their token and priority.
c. Display the current queue.

RISHAA
Jan 9th 2026
--------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define queue node
typedef struct Customer {
    int TokenNumber;
    char Name[50];
    int Age;
    char ServiceType[20];
    struct Customer* next;
} CUST;

CUST* front, *rear;

void InitQ();
void Enqueue(int token, char name[], char serviceType[], int Age);
void Dequeue();
void DisplayQueue();
int SeniorCitizen(int Age);
void ServeNextCustomer();

//Main function
int main() 
{
    InitQ(); //Initialize the queue

    int choice, Age, token;
    char name[50], serviceType[20];
    token = 1;

    while (1) {
        printf("\nBank Queue System\n");
        printf("1. Add Customer to Queue\n");
        printf("2. Serve Next Customer\n");
        printf("3. Display Current Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Customer Name: ");
                scanf("%s", name);
                printf("Enter Customer Age: ");
                scanf("%d", &Age);
                printf("Enter Service Type: ");
                scanf("%s", serviceType);
                Enqueue(token++, name, serviceType, Age);
                break;
            case 2:
                ServeNextCustomer();
                break;
            case 3:
                DisplayQueue();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

//Initialize the queue
void InitQ() 
{
    front = rear = NULL;
}

//insert customer into the queue
void Enqueue(int token, char name[], char serviceType[], int Age) 
{
    CUST* NewCust = (CUST*)malloc(sizeof(CUST));
    NewCust->TokenNumber = token;
    strcpy(NewCust->Name, name);
    strcpy(NewCust->ServiceType, serviceType);
    NewCust->Age = Age;
    NewCust->next = NULL;

    if (SeniorCitizen(Age)) { // for senior citizens 
        if (front == NULL) {
            front = rear = NewCust;
        } else if (!SeniorCitizen(front->Age)) {
            // No seniors yet, insert at front
            NewCust->next = front;
            front = NewCust;
        } else {
            // Find last senior in the queue
            CUST* curr = front;
            while (curr->next != NULL && SeniorCitizen(curr->next->Age)) {
                curr = curr->next;
            }
            // Insert after curr
            NewCust->next = curr->next;
            curr->next = NewCust;
            if (NewCust->next == NULL) { // inserted at the end
                rear = NewCust;
            }
        }
    } else {
        // for regular customers
        if (rear == NULL) {
            front = rear = NewCust;
        } else {
            rear->next = NewCust;
            rear = NewCust;
        }
    }
    printf("\nCustomer %s added to the queue with Token Number %d\n", name, token);
}

//Serve the next customer in the queue
void ServeNextCustomer()
{
    if (front == NULL) {
        printf("No customers in the queue.\n");
        return;
    }

    CUST* Curr = front;
    printf("Serving Customer: %s, Token Number: %d, Service Type: %s\n", front->Name, front->TokenNumber, front->ServiceType);
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    free(Curr);
}

//Display the current queue
void DisplayQueue()
{
    if (front == NULL) {
        printf("The queue is empty.\n");
        return;
    }

    CUST* Curr = front;
    printf("Current Queue:\n");
    printf("+-------+----------------------+-----+----------------------+\n");
    printf("| Token | Name                 | Age | Service Type         |\n");
    printf("+-------+----------------------+-----+----------------------+\n");
    while (Curr != NULL) {
        printf("| %-5d | %-20s | %-3d | %-20s |\n", Curr->TokenNumber, Curr->Name, Curr->Age, Curr->ServiceType);
        Curr = Curr->next;
    }
    printf("+-------+----------------------+-----+----------------------+\n");
}

//Check if the customer is a senior citizen
int SeniorCitizen(int Age)
{
    if(Age >= 70)
        return 1;
    return 0;
}
