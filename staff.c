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
    char password[20];
    char recovery[20];
}Staff;

FILE* readFile();
void addStaff();
void searchStaff();
void modifyStaff();
void displayStaff();
void deleteStaff();
void login();
void menu();

void main() {
    menu();
}

FILE* readFile() {
    FILE* fptr = fopen(STAFFFILE, "r");
    if (fptr == NULL) {
        printf("File not found\n");
        exit(-1);
    }
    return fptr;
}

void addStaff() {
    FILE* fptr = fopen(STAFFFILE, "a");
    Staff staff;
    char continueAdd;
    
    do {
        printf("Enter staff ID: ");
        scanf(" %s", staff.staffID);

        printf("Enter staff name: ");
        scanf(" %[^\n]", staff.name);

        do {
            printf("Enter birth date (DD/MM/YYYY): ");
            scanf("%d/%d/%d", &staff.birthDate.day, &staff.birthDate.month, &staff.birthDate.year);
            if (staff.birthDate.day < 1 || staff.birthDate.day >= 31)
                printf("Invalid day\n");
            else if (staff.birthDate.month < 1 || staff.birthDate.month > 12)
                printf("Invalid month\n");
            else if (staff.birthDate.year > 2005 && staff.birthDate.year <= 2023)
                printf("Too young to be a staff\n");
            else if (staff.birthDate.year < 1900 || staff.birthDate.year > 2023)
                printf("Invalid year\n");
        } while (!(1 <= staff.birthDate.day && staff.birthDate.day <= 31 && 1 <= staff.birthDate.month &&
            staff.birthDate.month <= 12 && 1900 <= staff.birthDate.year && staff.birthDate.year <= 2005));
        
        do {
            printf("Enter gender (M/F): ");
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

        printf("Enter position (Administrator / Staff): ");
        scanf(" %s", staff.position);

        printf("Enter password: ");
        scanf(" %s", staff.password);

        printf("Enter password recovery: ");
        scanf(" %s", staff.recovery);

        fprintf(fptr, "%s|%s|%d/%d/%d|%c|%s|%s|%s\n",
            staff.staffID, staff.name, staff.birthDate.day, staff.birthDate.month, staff.birthDate.year,
            staff.gender, staff.position, staff.password, staff.recovery);

        printf("Continue add?: ");
        scanf(" %c", &continueAdd);
        continueAdd = tolower(continueAdd);
    } while (continueAdd == 'y');

    fclose(fptr);
}

void searchStaff() {

}

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
            printf("Attributes that can be modified: ");
            printf("1. Name\n");
            printf("2. Birth Date\n");
            printf("3. Gender\n");
            printf("4. Position\n");
            printf("5. Password\n");
            printf("6. Password Recovery\n");
            printf("7. All\n");
            printf("Select attribute to modify:");
            scanf("%d", &attribute);

            if (attribute == 1) {
                printf("Enter name: ");
                scanf("%[^\n]", staff[i].name);
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
                    scanf(" %s", newPassword);
                    strcpy(staff[i].password, newPassword);
                    printf("Password updated successfully!\n");
                }
                else
                    printf("\nIncorrect password!!!\n");
            }
            else if (attribute == 6) {
                char recovery[20];
                printf("Enter current password recovery: ");
                scanf(" %s", recovery);

                if (strcmp(staff[i].recovery, recovery) == 0) {
                    char newRecovery[20];
                    printf("Enter new password: ");
                    scanf(" %s", newRecovery);
                    strcpy(staff[i].recovery, newRecovery);
                    printf("Password recovery updated successfully!\n");
                }
                else
                    printf("\nIncorrect password recovery!!!\n");
            }
        }
        else
            printf("\nID does not exists!!!\n");
            break;
    }
    fclose(fptr);
}

void displayStaff() {
    FILE* fptr = readFile();
    Staff staff;

    int staffCount = 0;

    printf("\n%s\n", "==========================================================================");
    printf("%-10s|%-28s|%-12s|%-6s|%-18s", "Staff ID", "Staff Name", "Birth Date", "Gender", "Position");
    printf("\n%s\n", "==========================================================================");
    while (fscanf(fptr, "%[^|]|%[^|]|%02d/%02d/%d|%[^|]|%[^|]|%[^|]%[^\n]\n", staff.staffID, staff.name, &staff.birthDate.day, &staff.birthDate.month,
        &staff.birthDate.year, &staff.gender, staff.position, staff.password, staff.recovery) != EOF) {
        printf("%-10s|%-28s|%d/%d/%-6d|%-6c|%-18s\n", staff.staffID, staff.name, staff.birthDate.day, staff.birthDate.month,
            staff.birthDate.year, staff.gender, staff.position);
        staffCount++;
    }
    printf("%s\n", "==========================================================================");
    printf("\nThere are total %d staffs.\n", staffCount);
    fclose(fptr);
}

void deleteStaff() {

}

void login() {

}

void menu() {
    int choice;

    do {
        printf("\nOperation lists:\n");
        printf("1. Add Staff\n");
        printf("2. Search Staff\n");
        printf("3. Modify Staff Information\n");
        printf("4. Display Staffs\n");
        printf("5. Delete Staff\n");
        printf("6. Exit\n\n");
        printf("Select an operation: ");
        scanf("%d", &choice);

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
            exit(-1);
            break;
        default:
            printf("Invalid operation!!!\n");
        }
    } while (choice != 6);

}