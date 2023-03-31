#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define STAFFFILE "staff.txt"

struct Date {
    int day, month, year;
};

typedef struct {
    char staffID[6];
    char name[25];
    struct Date birthDate;
    char gender;
    char position[15];
    char password[25];
    char recovery[25];
}Staff;

FILE* readFile();
void addStaff();
void searchStaff();
void modifyStaff();
void displayStaff();
void deleteStaff();
void login();
void staffMenu();

void main() {
    //login();
    staffMenu();
}

FILE* readFile() {
    FILE* fptr = fopen(STAFFFILE, "r");
    if (fptr == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    return fptr;
}

//Finished
void addStaff() {
    FILE* fptr = fopen(STAFFFILE, "a");
    Staff staff;
    char continueAdd;

    do {
        do {
            printf("\nEnter staff ID (at most 5 characters and numbers): "); 
            scanf(" %s", staff.staffID);

            if (strlen(staff.staffID) <= 5) {
                for (int i = 0; i < strlen(staff.staffID); i++) {
                    if (isalpha(staff.staffID[i]) == 2)
                        staff.staffID[i] = toupper(staff.staffID[i]);
                }
            }
            else
                printf("Invalid staff ID\n");
        } while (strlen(staff.staffID) > 5);

        int isValid = 1;
        do {
            printf("\nEnter staff name: ");
            scanf(" %[^\n]", staff.name);

            for (int i = 0; i < strlen(staff.name); i++) {
                if (isdigit(staff.name[i]) != 0 || ispunct(staff.name[i]) != 0) {
                    printf("Invalid name!!! (The name inputted can only include characters)\n");
                    isValid = 0;
                    break;
                }
                else
                    isValid = 1;
            }
        } while (isValid == 0);

        for (int i = 0; i < strlen(staff.name); i++) {
            if (isalpha(staff.name[i]) == 2)
                staff.name[i] = toupper(staff.name[i]);
        }

        do {
            printf("\nEnter birth date (DD/MM/YYYY): ");
            scanf("%d/%d/%d", &staff.birthDate.day, &staff.birthDate.month, &staff.birthDate.year);
            if (staff.birthDate.day < 1 || staff.birthDate.day > 31 || staff.birthDate.month < 1 || staff.birthDate.month > 12 || staff.birthDate.year < 1900)
                printf("Invalid date, try again\n");
            else if (staff.birthDate.year > 2005 && staff.birthDate.year <= 2023)
                printf("Too young to be a staff, try again\n");
        } while (!(1 <= staff.birthDate.day && staff.birthDate.day <= 31 && 1 <= staff.birthDate.month &&
            staff.birthDate.month <= 12 && 1900 <= staff.birthDate.year && staff.birthDate.year <= 2005));

        do {
            printf("\nEnter gender (M/F): ");
            scanf(" %c", &staff.gender);
            staff.gender = toupper(staff.gender);
            switch (staff.gender) {
            case 'M':
            case 'F':
                break;
            default:
                printf("Invalid gender!!!\n");
            }
        } while (staff.gender != 'M' && staff.gender != 'F');

        char position;
        do {
            printf("\nEnter position (A = Administrator / S = Staff): ");
            scanf(" %c", &position);
            position = toupper(position);
            if (position == 'A')
                strcpy(staff.position, "ADMINISTRATOR");
            else if (position == 'S')
                strcpy(staff.position, "STAFF");
            else
                printf("Invalid postion!!!\n");
        } while (position != 'A' && position != 'S');

        do {
            printf("\nEnter password (At least 6 numbers/characters): "); 
            scanf(" %[^\n]", staff.password);

            if (strlen(staff.password) < 6) 
                printf("Insufficient password length!!! Please input a new password\n");
        } while (strlen(staff.password) < 6);

        do{
            printf("\nEnter password recovery (At least 4 numbers/characters): ");
            scanf(" %[^\n]", staff.recovery);

            if (strlen(staff.recovery) < 4) 
                printf("\nInsufficient password recovery length!!! Please input a new password recovery\n");
        } while (strlen(staff.recovery) < 4);

        printf("\nStaff added successfully!!!\n");

        fprintf(fptr, "%s|%s|%02d/%02d/%d|%c|%s|%s|%s\n",
            staff.staffID, staff.name, staff.birthDate.day, staff.birthDate.month, staff.birthDate.year,
            staff.gender, staff.position, staff.password, staff.recovery);

        printf("Continue add?: ");
        scanf(" %c", &continueAdd);
        continueAdd = tolower(continueAdd);
    } while (continueAdd == 'y');

    fclose(fptr);
}

//Doing
void searchStaff() {
    FILE* fptr = readFile();
    Staff staff;
    int choice;
    char input[10];

    while (!feof(fptr)) {
        fscanf(fptr, "%[^|]|%[^|]|%02d/%02d/%d|%[^|]|%[^|]|%[^|]%[^\n]\n", staff.staffID, staff.name, &staff.birthDate.day, &staff.birthDate.month,
        &staff.birthDate.year, &staff.gender, staff.position, staff.password, staff.recovery);
    }

    printf("\nSearch by:\n");
    printf("1. Staff ID\n");
    printf("2. Name\n");
    printf("3. Birth Year\n");
    printf("4. Gender\n");
    printf("5. Position\n");
    printf("6. Return to staff menu\n\n");

    do{
        printf("Select attribute to search (1-5) or return to staff menu (6): ");
        rewind(stdin);
        scanf(" %s", input);

        if (strlen(input) == 1 && isdigit(input[0]))
            choice = input[0] - '0';
        else
            choice = 0;

        if (choice == 1) {

        }
        else if (choice == 2) {

        }
        else if (choice == 3) {

        }
        else if (choice == 4) {

        }
        else if (choice == 5) {

        }
        else if (choice == 6)
            staffMenu();
        else
            printf("Invalid input!!! Please try again\n\n");
    } while (choice < 1 || choice > 6);
}

//got problem
void modifyStaff() {
    FILE* fptr = readFile();
    Staff staff[50];
    int attribute, staffCount = 0;
    char ID[6];

    while (!feof(fptr)) {
        fscanf(fptr, "%[^|]|%[^|]|%02d/%02d/%d|%[^|]|%[^|]|%[^|]%[^\n]\n", staff[staffCount].staffID, staff[staffCount].name,
            &staff[staffCount].birthDate.day, &staff[staffCount].birthDate.month, &staff[staffCount].birthDate.year, &staff[staffCount].gender,
            staff[staffCount].position, staff[staffCount].password, staff[staffCount].recovery);
        staffCount++;
    }

    printf("Enter the staff ID to modify its information: ");
    scanf(" %s", ID);

    for (int i = 0; i < staffCount; i++) {
        if (strcmp(ID, staff[i].staffID) == 0) {
            printf("\nStaff ID: %s\n", staff[i].staffID);
            printf("Name: %s\n", staff[i].name);
            printf("Birth Date: %d/%d/%d\n", staff[i].birthDate.day, staff[i].birthDate.month, staff[i].birthDate.year);
            printf("Gender: %c\n", staff[i].gender);
            printf("Position: %s\n\n", staff[i].position);
            printf("Attributes that can be modified:\n");
            printf("1. Name\n");
            printf("2. Birth Date\n");
            printf("3. Gender\n");
            printf("4. Position\n");
            printf("5. Password\n");
            printf("6. Password Recovery\n");
            printf("7. All\n");
            printf("8. Return to staff menu\n");
            printf("Select attribute to modify: ");
            scanf("%d", &attribute);

            if (attribute == 1) {
                char name[25];
                printf("Enter name: ");
                scanf(" %[^\n]", name);
                strcpy(staff[i].name, name);
            }
            else if (attribute == 2) {
                printf("Enter year: ");
                scanf("%d", &staff[i].birthDate.year);
                printf("Enter month: ");
                scanf("%d", &staff[i].birthDate.month);
                printf("Enter month: ");
                scanf("%d", &staff[i].birthDate.month);
            }
            else if (attribute == 3) {
                do {
                    printf("Enter gender (M/F): ");
                    scanf(" %c", &staff[i].gender);
                    staff[i].gender = toupper(staff[i].gender);
                    switch (staff[i].gender) {
                    case 'M':
                    case 'F':
                        break;
                    default:
                        printf("Invalid gender!!!\n");
                    }
                } while (staff[i].gender != 'M' && staff[i].gender != 'F');
            }
            else if (attribute == 4) {
                printf("Enter position: ");
                scanf(" %s", &staff[i].position);
            }
            else if (attribute == 5) {
                char password[20];
                printf("Enter current password: ");
                scanf(" %s", password);

                if (strcmp(staff[i].password, password) == 0) {
                    char newPassword[20];
                    printf("Enter new password: ");
                    scanf(" %[^\n]", newPassword);
                    strcpy(staff[i].password, newPassword);
                    printf("Password updated successfully!\n");
                }
                else
                    printf("\nIncorrect password!!!\n");
            }
            else if (attribute == 6) {
                char recovery[20];
                printf("Enter current password recovery: ");
                scanf(" %[^\n]", recovery);

                if (strcmp(staff[i].recovery, recovery) == 0) {
                    char newRecovery[20];
                    printf("Enter new password: ");
                    scanf(" %[^\n]", newRecovery);
                    strcpy(staff[i].recovery, newRecovery);
                    printf("Password recovery updated successfully!\n");
                }
                else
                    printf("\nIncorrect password recovery!!!\n");
            }
            if (attribute == 8)
                staffMenu();
        }
        else
            printf("\nID does not exists!!!\n");
        break;
    }

    FILE* fptr1 = fopen(STAFFFILE, "w");
    for (int i = 0; i < staffCount; i++) {
        fprintf(fptr, "%[^|]|%[^|]|%02d/%02d/%d|%[^|]|%[^|]|%[^|]%[^\n]\n", staff[i].staffID, staff[i].name,
        staff[i].birthDate.day, staff[i].birthDate.month, staff[i].birthDate.year, staff[i].gender,
        staff[i].position, staff[i].password, staff[i].recovery);
    }
    fclose(fptr);
    fclose(fptr1);
}

//Finished
void displayStaff() {
    FILE* fptr = readFile();
    Staff staff;

    int staffCount = 0;

    printf("\n%s\n", "================================================================================");
    printf("%-3s|%-10s|%-25s|%-10s|%-8s|%-13s|", "|NO.", "STAFF ID", "STAFF NAME", "  BIRTH DATE  ", " GENDER ", "POSITION");
    printf("\n%s\n", "================================================================================");
    while (fscanf(fptr, "%[^|]|%[^|]|%02d/%02d/%d|%[^|]|%[^|]|%[^|]%[^\n]\n", staff.staffID, staff.name, &staff.birthDate.day, &staff.birthDate.month,
        &staff.birthDate.year, &staff.gender, staff.position, staff.password, staff.recovery) != EOF) {
        printf("%s%-3d|%-10s|%-25s|%-2s%02d/%02d/%-4d%-2s|%-3s%c%-4s|%-13s|\n", "|", staffCount + 1, staff.staffID, staff.name, " ", staff.birthDate.day, staff.birthDate.month,
            staff.birthDate.year, " ", " ",staff.gender, " ", staff.position);
        staffCount++;
    }
    printf("%s\n", "================================================================================");
    printf("\nThere are total %d staffs.\n", staffCount);

    fclose(fptr);
}

void deleteStaff() {

}

//Start lil bit only
void login() {
    FILE* fptr = readFile();
    Staff staff[50];
    int staffCount = 0, attempt = 0;
    char inputID[6], inputPassword[25], inputrecovery[25];

    while (fscanf(fptr, "%[^|]|%[^|]|%02d/%02d/%d|%[^|]|%[^|]|%[^|]%[^\n]\n", staff[staffCount].staffID, staff[staffCount].name,
        &staff[staffCount].birthDate.day, &staff[staffCount].birthDate.month, &staff[staffCount].birthDate.year, &staff[staffCount].gender,
        staff[staffCount].position, staff[staffCount].password, staff[staffCount].recovery) != EOF) {
        staffCount++;
    }

    printf("Enter staff ID: ");
    scanf(" %s", inputID);

    for (int i = 0; i < staffCount; i++) {
        if (inputID == staff[i].staffID) {
            printf("Enter password: ");
        }
    }

    fclose(fptr);
}

//Finished
void staffMenu() {
    int choice;
    char input[10];

    do {
        printf("\nOperation lists:\n");
        printf("1. Add Staff\n");
        printf("2. Search Staff\n");
        printf("3. Modify Staff Information\n");
        printf("4. Display Staffs\n");
        printf("5. Delete Staff\n");
        printf("6. Exit\n\n");

        printf("Select an operation (1-6): ");
        rewind(stdin);
        scanf(" %s", input);

        if (strlen(input) == 1 && isdigit(input[0]))
            choice = input[0] - '0';
        else
            choice = 0;

        switch (choice) {
        case 1:
            addStaff();
            break;
        case 2:
            searchStaff();
            break;
        case 3:
            modifyStaff();
            break;
        case 4:
            displayStaff();
            break;
        case 5:
            deleteStaff();
            break;
        case 6:
            printf("\nProgram exited successfully!!!\n");
            exit(-1);
        default:
            printf("Invalid operation!!! Please try again\n");
        }
    } while (choice != 6);
}