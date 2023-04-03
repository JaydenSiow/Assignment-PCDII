#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define STAFF_FILE "staff.txt"
#define MAX_STAFF 80

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

//Validation
void checkStaffID(char[], int*, char(*)[]);
int checkStaffName(char[]);
int checkBirthDate(int, int, int);
int checkStaffGender(char);
void checkStaffPosition(char, int*, char*);
int checkPassword(char[]);
int checkRecovery(char[], char[]);
int checkNumber(char[]);
int checkYesNo(char);

//1. Add Staff Module
void StaffAdd();
void newStaffInf();
int checkDupStaff();
void saveStaff();

//2. Search Staff Module
void StaffSearch();
void searchByAttr(int);

//3. Modify Staff Module
void StaffModify();
void selectAttr();
void modifyStaffInf();

//4. Display Staff Module
void StaffDisplay();

//5. Delete Staff Module
void StaffDelete();
void deleteStaff();

//6. Login Module
void StaffLogin();
void login();
void verify();

//Functions used by multiple modules
void readStaffFile(Staff staff[], int*);            //used in all module except add module
void writeStaffFile(Staff staff[], int*);           //used in modify and delete module
void displayStaff(Staff staff[], int);              //used in search, modify and display module
void getStaffID();                                  //used in modify and delete module
void StaffMenu();                                   //used in all module

//Main function
void main() {
    //login();
    StaffMenu();
}

//--------------------------------------------Validation--------------------------------------------
void checkStaffID(char staffID[], int* validation, char(*validatedID)[]) {
    if (strlen(staffID) == 5) {
        if (isalpha(staffID[0]) == 0 || isalpha(staffID[1]) == 0 || isdigit(staffID[2]) == 0 || isdigit(staffID[3]) == 0 || isdigit(staffID[4]) == 0) {
            printf("Please enter the staff ID according to the format given\n");
            *validation = 1;
        }
        else if (isalpha(staffID[0]) == 2 || isalpha(staffID[1]) == 2) {
            staffID[0] = toupper(staffID[0]);
            staffID[1] = toupper(staffID[1]);
            strcpy(*validatedID, staffID);
            *validation = 0;
        }
        else {
            strcpy(*validatedID, staffID);
            *validation = 0;
        }
    }
    else {
        printf("Invalid staff ID\n");
        *validation = 1;
    }
}

int checkStaffName(char name[]) {
    for (int i = 0; i < strlen(name); i++) {
        if (isdigit(name[i]) || ispunct(name[i])) {
            printf("Invalid name!!! (The name inputted can only include characters)\n");
            return 1;
        }
    }
    return 0;
}

int checkBirthDate(int day, int month, int year) {
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900) {
        printf("Invalid date, try again\n");
        return 1;
    }
    else if (year > 2005 && year <= 2023) {
        printf("Too young to be a staff, try again\n");
        return 1;
    }
    else
        return 0;
}

int checkStaffGender(char gender) {
    switch (gender) {
    case 'M':
    case 'F':
        return 0;
    default:
        printf("Invalid gender!!! Please re-enter \n");
        return 1;
    }
}

void checkStaffPosition(char charPosition, int *validation, char *position) {
    if (charPosition == 'A') {
        strcpy(position, "ADMINISTRATOR");
        *validation = 0;
    }
    else if (charPosition == 'S') {
        strcpy(position, "STAFF");
        *validation = 0;
    }
    else {
        printf("Invalid postion!!!\n");
        *validation = 1;
    }
}

int checkPassword(char password[]) {
    if (strlen(password) < 6) {
        printf("Insufficient password length!!! Please input a new password\n");
        return 1;
    }
    else
        return 0;
}

int checkRecovery(char password[], char recovery[]) {
    if (strlen(recovery) >= 6) {
        if (strcmp(password, recovery) == 0) {
            printf("The password is same as the password recovery!!! Re-enter the password recovery\n");
            return 1;
        }
        else
            return 0;
    }
    else {
        printf("Insufficient password length!!! Please input a new password\n");
        return 1;
    }
}

int checkNumber(char input[]) {
    int choice;
    if (strlen(input) == 1 && isdigit(input[0])) {
        choice = input[0] - '0';
        return choice;
    }
    else
        return choice = 0;
}

int checkYesNo(char yesNo) {
    if (yesNo == 'Y') {
        return 1;
    }
    else if (yesNo == 'N') {
        return 0;
    }
    else {
        printf("Invalid operation!!! Please re-enter a valid character\n\n");
        return 1;
    }
}


//---------------------------------------Functions used by multiple modules---------------------------------------
void readStaffFile(Staff staff[], int* staffCount) {
    FILE* fptr = fopen(STAFF_FILE, "r");
    if (fptr == NULL) {
        printf("File (%s) not found\n", STAFF_FILE);
        exit(-1);
    }

    int i = 0;
    while (fscanf(fptr, "%[^|]|%[^|]|%02d/%02d/%d|%[^|]|%[^|]|%[^|]%[^\n]\n", &staff[i].staffID, &staff[i].name, &staff[i].birthDate.day, &staff[i].birthDate.month,
        &staff[i].birthDate.year, &staff[i].gender, &staff[i].position, &staff[i].password, &staff[i].recovery) != EOF) {
        i++;
    }
    *staffCount = i;

    fclose(fptr);
}

void writeStaffFile(Staff staff[], int* staffCount) {
    FILE* fptr = fopen(STAFF_FILE, "w");



    fclose(fptr);
}

void displayStaff(Staff staff[], int staffCount) {
    printf("\n%s\n", "================================================================================");
    printf("%-3s|%-10s|%-25s|%-10s|%-8s|%-13s|", "|NO.", "STAFF ID", "STAFF NAME", "  BIRTH DATE  ", " GENDER ", "POSITION");
    printf("\n%s\n", "================================================================================");
    for (int i = 0; i < staffCount; i++) {
        printf("%s%-3d|%-10s|%-25s|%-2s%02d/%02d/%-4d%-2s|%-3s%c%-4s|%-13s|\n", "|", i + 1, staff[i].staffID, staff[i].name, " ", staff[i].birthDate.day, staff[i].birthDate.month,
            staff[i].birthDate.year, " ", " ", staff[i].gender, " ", staff[i].position);
    }
    printf("%s\n", "================================================================================");
    printf("\nThere are total %d staffs.\n", staffCount);
}

void getStaffID() {

}

//--------------------------------------------Add Staff--------------------------------------------
void StaffAdd() {
    char newStaffID[6];
    newStaffInf();
}

void newStaffInf() {
    FILE* fptr = fopen(STAFF_FILE, "a");
    Staff staff;
    char continueAdd;
    int validation;

    do {
        do {
            printf("\nEnter staff ID (Eg: AB123): ");
            rewind(stdin);
            scanf(" %s", staff.staffID);

            checkStaffID(staff.staffID, &validation, &staff.staffID);
            //validation = checkDupStaff(staff.staffID);
            //return strdup(staff.staffID);
        } while (validation);

        do {
            printf("\nEnter staff name: ");
            rewind(stdin);
            scanf(" %[^\n]", staff.name);

            for (int i = 0; i < strlen(staff.name); i++) {
                if (isalpha(staff.name[i]) == 2)
                    staff.name[i] = toupper(staff.name[i]);
            }
            validation = checkStaffName(staff.name);
        } while (validation);

        do {
            printf("\nEnter birth date (DD/MM/YYYY): ");
            scanf("%d/%d/%d", &staff.birthDate.day, &staff.birthDate.month, &staff.birthDate.year);

            validation = checkBirthDate(staff.birthDate.day, staff.birthDate.month, staff.birthDate.year);
        } while (validation);

        do {
            printf("\nEnter gender (M/F): ");
            rewind(stdin);
            scanf(" %c", &staff.gender);
            staff.gender = toupper(staff.gender);

            validation = checkStaffGender(staff.gender);
        } while (validation);

        char charPosition, position[15];
        do {
            printf("\nEnter position (A = Administrator / S = Staff): ");
            rewind(stdin);
            scanf(" %c", &charPosition);
            charPosition = toupper(charPosition);

            checkStaffPosition(charPosition, &validation, position);
            strcpy(staff.position, position);
        } while (validation);

        do {
            printf("\nEnter password (At least 6 numbers/characters): ");
            rewind(stdin);
            scanf(" %[^\n]", staff.password);

            validation = checkPassword(staff.password);
        } while (validation);

        do {
            printf("\nEnter password recovery (At least 6 numbers/characters): ");
            rewind(stdin);
            scanf(" %[^\n]", staff.recovery);

            validation = checkRecovery(staff.password, staff.recovery);
        } while (validation);

        printf("\nStaff added successfully!!!\n\n");

        fprintf(fptr, "%s|%s|%02d/%02d/%d|%c|%s|%s|%s\n",
            staff.staffID, staff.name, staff.birthDate.day, staff.birthDate.month, staff.birthDate.year,
            staff.gender, staff.position, staff.password, staff.recovery);

        printf("Continue add? (Y = Yes, N = No): ");
        rewind(stdin);
        scanf(" %c", &continueAdd);
        continueAdd = toupper(continueAdd);
        continueAdd = checkYesNo(continueAdd);
    } while (continueAdd);
}

int checkDupStaff(char staffID[]) {
    Staff staff[MAX_STAFF];
    int staffCount = 0;

    readStaffFile(staff, &staffCount);

    for (int i = 0; i < staffCount; i++) {
        if (strcmp(staffID, staff[i].staffID) == 0) {
            printf("Duplicate Staff ID!!! Re-enter a new staff ID\n");
            return 1;
        }
    }
    return 0;
}

void saveStaff() {

}


//--------------------------------------------Search Staff--------------------------------------------
void StaffSearch() {
    Staff staff[MAX_STAFF];
    int choice, staffCount = 0;
    char input[10];
    readStaffFile(staff, &staffCount);

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
        
        choice = checkNumber(input);
        searchByAttr(choice);

    } while (choice < 1 || choice > 6);
}


void searchByAttr(int choice){
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
        StaffMenu();
    else
        printf("Invalid input!!! Please try again\n\n");
}

//--------------------------------------------Modify Staff--------------------------------------------
void StaffModify() {
    Staff staff[MAX_STAFF];
    int attribute, staffCount = 0;
    char ID[6];
    readStaffFile(&staff, &staffCount);

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
                StaffMenu();
        }
        else
            printf("\nID does not exists!!!\n");
        break;
    }

    FILE* fptr1 = fopen(STAFF_FILE, "w");
    for (int i = 0; i < staffCount; i++) {
        fprintf(fptr1, "%[^|]|%[^|]|%02d/%02d/%d|%[^|]|%[^|]|%[^|]%[^\n]\n", staff[i].staffID, staff[i].name,
        staff[i].birthDate.day, staff[i].birthDate.month, staff[i].birthDate.year, staff[i].gender,
        staff[i].position, staff[i].password, staff[i].recovery);
    }
    fclose(fptr1);
}


void selectAttr() {

}

void modifyStaffInf() {

}

//--------------------------------------------Display Staff--------------------------------------------
//Finished
void StaffDisplay() {
    Staff staff[MAX_STAFF];
    int staffCount = 0;

    readStaffFile(staff, &staffCount);
    displayStaff(staff, staffCount);
}

//--------------------------------------------Delete Staff--------------------------------------------
void StaffDelete() {

}

void deleteStaff() {

}

//--------------------------------------------Login--------------------------------------------
void StaffLogin() {
    Staff staff[MAX_STAFF];
    int staffCount = 0, attempt = 0;
    char inputID[6], inputPassword[25], inputrecovery[25];
    readStaffFile(&staff, &staffCount);

    printf("Enter staff ID: ");
    scanf(" %s", inputID);

    for (int i = 0; i < staffCount; i++) {
        if (inputID == staff[i].staffID) {
            printf("Enter password: ");
        }
    }
}

void login() {

}

void verify() {

}

//--------------------------------------------Main Menu--------------------------------------------
//Finished
void StaffMenu() {
    int choice, staffCount;
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

        choice = checkNumber(input);

        switch (choice) {
        case 1:
            StaffAdd();
            break;
        case 2:
            StaffSearch();
            break;
        case 3:
            StaffModify();
            break;
        case 4:
            StaffDisplay();
            break;
        case 5:
            StaffDelete();
            break;
        case 6:
            printf("\nProgram exited successfully!!!\n");
            exit(-1);
        default:
            printf("Invalid operation!!! Please try again\n");
        }
    } while (choice != 6);
}