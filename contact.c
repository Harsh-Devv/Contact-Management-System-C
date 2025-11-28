# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX 100                    // constant to change memory easily
# define FILENAME "contacts.dat"    // constant to save spelling mistake of filename

struct Contact
{
    char name[100];
    char phone[20];
    char email[100];
};

struct Contact contacts[MAX];      // array of struct contacts of size 100
int contactCount = 0;

void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addContact(){
    // Checking if space is avaliable
    if (contactCount >= MAX){
        printf("Error: Failed to Add Contact. Contact List is Full!\n");
        return;
    }

    struct Contact newContact;    // Temporary form to fill the details

    printf("Enter Name: ");
    fgets(newContact.name, 100, stdin);
    newContact.name[strcspn(newContact.name, "\n")] = 0; // to replace the enter key with null

    printf("Enter Phone: ");
    fgets(newContact.phone, 20, stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = 0;

    printf("Enter Email: ");
    fgets(newContact.email, 100, stdin);
    newContact.email[strcspn(newContact.email, "\n")] = 0;

    contacts[contactCount] = newContact;  // copying the data in temporary to main array
    contactCount++;            
    printf("\n");
    printf("\nContact Added Successfully\n");
    printf("\n");
}

void displayContact(){
    if (contactCount == 0){
        printf("No Contacts to Display yet. \n");
        return;
    }

    for (int i = 0; i < contactCount; ++i){
        printf("\n--- Contact %d ---\n", i + 1);
        printf(" Name : %s\n", contacts[i].name);
        printf(" Phone: %s\n", contacts[i].phone);
        printf(" Email: %s\n", contacts[i].email);
        printf("\n");
    }
}

void searchContact(){
    char search[100];
    printf("Enter the name to search: ");
    fgets(search, 100, stdin);
    search[strcspn(search, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < contactCount; ++i){
        if (strcmp(contacts[i].name, search) == 0){
            printf("---Contact Found!---\n");
            printf(" Name : %s\n", contacts[i].name);
            printf(" Phone: %s\n", contacts[i].phone);
            printf(" Email: %s\n", contacts[i].email);
            printf("\n");
            found = 1;
            break;
        }
    }
    if (!found){
        printf("Contact Not Found!\n");
    }
}

void deleteContact(){
    char search[100];
    printf("Enter the Name to Delete: ");
    fgets(search, 100, stdin);
    search[strcspn(search,"\n")] = 0;

    int foundIndex = -1;
    for (int i = 0; i < contactCount;++i){
        if (strcmp(contacts[i].name, search) ==0){
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1){
        printf("No such Contact to Delete");
    } else{
        for (int i = foundIndex; i < contactCount -1; ++i){
            contacts[i] = contacts[i + 1];
        }
        contactCount--;
        printf("\n");
        printf("Contact Deleted Successfully!\n");
        printf("\n");
    }
}

void saveContacts(){
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL){
        printf("Error: Could not open the file for wrtiting");
        return;
    }
    fwrite(contacts,sizeof(struct Contact), contactCount, file);
    fclose(file);
    printf("Contacts Saved Successfully to %s\n", FILENAME);
}

void loadContacts(){
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL){
        printf("Error: Could not open the file for reading");
        return;
    }
    contactCount = fread(contacts, sizeof(struct Contact), MAX, file);
    fclose(file);
    printf("Loaded %d contacts from %s.\n", contactCount, FILENAME);
}

int main(){
    loadContacts();
    int choice;

    while(1){
        printf("\n---Contact Management System---\n");
        printf("1. Add Contact\n");
        printf("2. Display All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Save & Exit\n");

        if (scanf("%d", &choice) != 1){
            printf("Invalid input. Enter a number");
            clearInputBuffer();            
            continue;
        }
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            addContact();
            break;
        case 2:
            displayContact();
            break;
        case 3:
            searchContact();
            break;
        case 4:
            deleteContact();
            break;
        case 5:
            saveContacts();
            exit(0);
        default:
            printf("Invalid Choice. Please try again.\n");     
        }
    }

    return 0;
}