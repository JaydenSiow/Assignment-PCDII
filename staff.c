#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define STAFF_FILE "staff.txt"
#define MAX_STAFF 50

typedef struct{
    int day, month, year;
}Date;

typedef struct {
    char staffID[6];
    char name[25];
    Date birthDate;
    char gender;
    char position[15];
    char password[25];
    char recovery[25];
}Staff;

//Validation
void checkStaffID(char[], int*, char(*)[]);
int checkStaffName(char[]);
int checkBirthDate(int, int, int);
void checkStaffGender(int, char*, int*);
void checkStaffPosition(int, char*, int*);
int checkPassword(char[]);
int checkNumber(char[]);
int checkDecision(char);

//1. Add Staff Module
void StaffAdd();
void saveStaff(Staff staff);

//2. Search Staff Module
void StaffSearch();
void searchByAttr(int);

//3. Modify Staff Module
void StaffModify();
int selectAttr();

//4. Display Staff Module
void StaffDisplay();

//5. Delete Staff Module
void StaffDelete();

//6. Login Module
void StaffLogin();

//Functions used by multiple modules
int checkStaffIDExist(char[]);
void readStaffFile(Staff staff[], int*);           //used in all module except add module
void writeStaffFile(Staff staff[], int);           //used in modify and delete module
void displayAllStaff(Staff staff[], int);          //used in search, modify and display module

//Function used to prompt data input
char* getStaffID(Staff* staff);
char* getStaffName(Staff* staff);
void getStaffBirth(Staff* staff, int* day, int* month, int* year);
int getGenderAndPosition();
char* getStaffPassword(Staff* staff);
char* getStaffRecovery(Staff* staff);

//Menu function
void StaffMenu();

//Main function
void main() {
    //StaffLogin();
    StaffMenu();
}

//--------------------------------------------Main Menu--------------------------------------------
void StaffMenu() {
    int choice;
    char input[10];

    do {
        printf("\nOperation lists:\n");
        printf("1. Add Staff\n");
        printf("2. Search Staff\n");
        printf("3. Modify Staff Information by Staff ID\n");
        printf("4. Display All Staff\n");
        printf("5. Delete Staff\n");
        printf("6. Log Out\n");
        printf("7. Exit Program\n\n");

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
            StaffLogin();
            break;
        case 7:
            printf("\nProgram exited successfully!!!\n");
            exit(-1);
        default:
            printf("Invalid operation!!! Please try again\n");
        }
    } while (choice != 7);
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
    else if (strcmp(staffID, "E") == 0 || strcmp(staffID, "e") == 0) {
        StaffMenu();
    }
    else {
        printf("Please enter the staff ID according to the format given\n");
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
    if (day < 1 || day > 31) {
        printf("Invalid day, try again\n");
        return 1;
    }
    else if (month < 1 || month > 12) {
        printf("Invalid month, try again\n");
        return 1;
    }
    else if (year > 2005 && year <= 2023) {
        printf("Too young to be a staff, try again\n");
        return 1;
    }
    else if (year < 1900 || year > 2023) {
        printf("Invalid year, try again\n");
        return 1;
    }
    else
        return 0;
}

void checkStaffGender(int gender, char* staffGender, int* validation) {
    if (gender == 1) {
        *staffGender = 'M';
        *validation = 0;
    }
    else if (gender == 2) {
        *staffGender = 'F';
        *validation = 0;
    }
    else{
        printf("\nPlease enter a valid number (1-2)!\n");
        *validation = 1;
    }
}

void checkStaffPosition(int position, char* staffPosition, int* validation) {
    if (position == 1) {
        strcpy(staffPosition, "ADMINISTRATOR");
        *validation = 0;
    }
    else if (position == 2) {
        strcpy(staffPosition, "STAFF");
        *validation = 0;
    }
    else {
        printf("\nPlease enter a valid number (1-2)!\n");
        *validation = 1;
    }
}

int checkPassword(char password[]) {
    if (strlen(password) < 6) {
        printf("Insufficient length!!! Please re-enter \n");
        return 1;
    }
    else
        return 0;
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

int checkDecision(char yesNo) {
    if (yesNo == 'Y' || yesNo == 'N')
        return 0;
    else if (yesNo == 'E') {
        printf("\nProgram exited successfully!!!\n");
        exit(-1);
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
        printf("File (%s) not found!\n", STAFF_FILE);
        exit(-1);
    }

    int i = 0;
    while (fscanf(fptr, "%[^|]|%[^|]|%02d/%02d/%d|%[^|]|%[^|]|%[^|]|%[^\n]\n", staff[i].staffID, staff[i].name, &staff[i].birthDate.day, &staff[i].birthDate.month,
        &staff[i].birthDate.year, &staff[i].gender, staff[i].position, staff[i].password, staff[i].recovery) != EOF) {
        i++;
    }
    *staffCount = i;

    fclose(fptr);
}

void writeStaffFile(Staff staff[], int staffCount) {
    FILE* fptr = fopen(STAFF_FILE, "w");
    for (int i = 0; i < staffCount; i++) {
        fprintf(fptr, "%s|%s|%02d/%02d/%d|%c|%s|%s|%s\n", staff[i].staffID, staff[i].name, staff[i].birthDate.day, staff[i].birthDate.month,
            staff[i].birthDate.year, staff[i].gender, staff[i].position, staff[i].password, staff[i].recovery);
    }
    fclose(fptr);
}

void displayAllStaff(Staff staff[], int staffCount) {
    printf("\n\nStaff Information:");
    printf("\n%s\n", "================================================================================");
    printf("%-3s|%-10s|%-25s|%-10s|%-8s|%-13s|", "|NO.", "STAFF ID", "STAFF NAME", "  BIRTH DATE  ", " GENDER ", "POSITION");
    printf("\n%s\n", "================================================================================");
    for (int i = 0; i < staffCount; i++) {
        printf("%s%-3d|%-10s|%-25s|%-2s%02d/%02d/%-4d%-2s|%-3s%c%-4s|%-13s|\n", "|", i + 1, staff[i].staffID, staff[i].name, " ", staff[i].birthDate.day, staff[i].birthDate.month,
            staff[i].birthDate.year, " ", " ", staff[i].gender, " ", staff[i].position);
    }
    printf("%s\n", "================================================================================");
    printf("\nThere are total %d staffs.\n\n", staffCount);
}

void displayCertainStaff(Staff staff[], int staffCount, char staffID[], char staffName[], int day, int month, int year, char gender, char position[]) {
    int no = 1;
    printf("\n\nStaff Information:");
    printf("\n%s\n", "================================================================================");
    printf("%-3s|%-10s|%-25s|%-10s|%-8s|%-13s|", "|NO.", "STAFF ID", "STAFF NAME", "  BIRTH DATE  ", " GENDER ", "POSITION");
    printf("\n%s\n", "================================================================================");
    for (int i = 0; i < staffCount; i++) {
        if (strcmp(staffID, staff[i].staffID) == 0 || strcmp(staffName, staff[i].name) == 0 || day == staff[i].birthDate.day || month == staff[i].birthDate.month || year == staff[i].birthDate.year ||
            gender == staff[i].gender || strcmp(position, staff[i].position) == 0) {
            printf("%s%-3d|%-10s|%-25s|%-2s%02d/%02d/%-4d%-2s|%-3s%c%-4s|%-13s|\n", "|", no, staff[i].staffID, staff[i].name, " ", staff[i].birthDate.day, staff[i].birthDate.month,
            staff[i].birthDate.year, " ", " ", staff[i].gender, " ", staff[i].position);
            no++;
        }
    }
    printf("%s\n", "================================================================================");
    printf("\nThere are total %d staff(s) listed.\n\n", no - 1);
}

int checkStaffIDExist(char staffID[]) {
    Staff staff[MAX_STAFF];
    int staffCount = 0;

    readStaffFile(staff, &staffCount);

    for (int i = 0; i < staffCount; i++) {
        if (strcmp(staffID, staff[i].staffID) == 0) {
            return 1;
        }
    }
    return 0;
}

//---------------------------------------Prompt staff information---------------------------------------
char* getStaffID(Staff* staff) {
    rewind(stdin);
    scanf(" %s", staff->staffID);
    return staff->staffID;
}

char* getStaffName(Staff* staff) {
    printf("\nEnter staff name: ");
    rewind(stdin);
    scanf(" %[^\n]", staff->name);

    for (int i = 0; i < strlen(staff->name); i++) {
        if (isalpha(staff->name[i]) == 2)
            staff->name[i] = toupper(staff->name[i]);
    }
    return staff->name;
}

void getStaffBirth(Staff* staff, int* day, int* month, int* year) {
    char input[12];
    int validFormat = 0;

    do {
        printf("\nEnter birth date (DD/MM/YYYY): ");
        scanf(" %s", input);

        if (sscanf(input, "%2d/%2d/%4d", day, month, year) == 3)
            validFormat = 1;
        else
            printf("Invalid format! Please re-enter date in the format DD/MM/YYYY\n");
    } while (validFormat == 0);

    staff->birthDate.day = *day;
    staff->birthDate.month = *month;
    staff->birthDate.year = *year;
}

int getGenderAndPosition() {
    char input[15], attribute;
    rewind(stdin);
    scanf(" %s", input);
    attribute = checkNumber(input);
    return attribute;
}

char* getStaffPassword(Staff* staff) {
    printf("\nEnter new password (At least 6 numbers/characters): ");
    rewind(stdin);
    scanf(" %[^\n]", staff->password);
    return staff->password;
}

char* getStaffRecovery(Staff* staff) {
    printf("\nEnter new password recovery (At least 6 numbers/characters): ");
    rewind(stdin);
    scanf(" %[^\n]", staff->recovery);
    return staff->recovery;
}

char getDecision() {
    char continueAdd;
    printf("\nContinue? (Y = Yes, N = Exit to Main Program, E = Exit Whole Program): ");
    rewind(stdin);
    scanf(" %c", &continueAdd);
    return continueAdd;
}

//----------------------------------------------Add Staff----------------------------------------------
void StaffAdd() {
    Staff staff;
    char continueAdd, input[10];
    int validation, duplicateID;

    do {
        system("cls");
        do {
            printf("\nEnter staff ID of new staff (Eg: AB123, E = Exit to Staff Menu): ");
            getStaffID(&staff);
            checkStaffID(staff.staffID, &validation, &staff.staffID);
            duplicateID = checkStaffIDExist(staff.staffID);
            if (duplicateID)
                printf("Staff ID already exist!!! Enter a new staff ID\n");
        } while (validation || duplicateID);

        do {
            getStaffName(&staff);
            validation = checkStaffName(staff.name);
        } while (validation);

        do {
            getStaffBirth(&staff, &staff.birthDate.day, &staff.birthDate.month, &staff.birthDate.year);
            validation = checkBirthDate(staff.birthDate.day, staff.birthDate.month, staff.birthDate.year);
        } while (validation);

        do {
            int gender;
            char staffGender;

            printf("\nEnter gender by number (1. Male / 2. Female): ");
            gender = getGenderAndPosition();
            checkStaffGender(gender, &staffGender, &validation);
            staff.gender = staffGender;
        } while (validation);

        do {
            int position;
            char staffPosition[15];

            printf("\nEnter staff position by number (1. Administrator / 2. Staff): ");
            position = getGenderAndPosition();
            checkStaffPosition(position, &staffPosition, &validation);
            strcpy(staff.position, staffPosition);
        } while (validation);

        do {
            getStaffPassword(&staff);
            validation = checkPassword(staff.password);
        } while (validation);

        do {
            getStaffRecovery(&staff);
            validation = checkPassword(staff.recovery);
        } while (validation);

        printf("\nStaff added successfully!!!\n");

        saveStaff(staff);

        do {
            continueAdd = getDecision();
            continueAdd = toupper(continueAdd);
            validation = checkDecision(continueAdd);
        } while (validation);
    } while (continueAdd == 'Y');
}

void saveStaff(Staff staff) {
    FILE* fptr = fopen(STAFF_FILE, "a");

    fprintf(fptr, "%s|%s|%02d/%02d/%d|%c|%s|%s|%s\n",
        staff.staffID, staff.name, staff.birthDate.day, staff.birthDate.month, staff.birthDate.year,
        staff.gender, staff.position, staff.password, staff.recovery);

    fclose(fptr);
}

//--------------------------------------------Search Staff--------------------------------------------
void StaffSearch() {
    int choice, validation;
    char input[10], continueSearch;

    do {
        system("cls");
        printf("\nSearch by:\n");
        printf("1. Staff ID\n");
        printf("2. Name\n");
        printf("3. Birth Date\n");
        printf("4. Gender\n");
        printf("5. Position\n");
        printf("6. Return to staff menu\n\n");

        do {
            printf("Select attribute to search (1-5) or return to staff menu (6): ");
            rewind(stdin);
            scanf(" %s", input);

            choice = checkNumber(input);

            if (choice < 1 || choice > 6) {
                printf("Invalid input. Please try again.\n\n");
            }
            else {
                searchByAttr(choice);
                do {
                    continueSearch = getDecision();
                    continueSearch = toupper(continueSearch);
                    validation = checkDecision(continueSearch);
                } while (validation);
            }
        } while (choice < 1 || choice > 6);
    } while (continueSearch == 'Y');
}

void searchByAttr(int choice){
    Staff staff[MAX_STAFF];
    Staff getAttr;
    int validation, staffCount;
    readStaffFile(staff, &staffCount);

    if (choice == 1) {
        do{
            printf("\nEnter staff ID to search (Eg: AB123, E = Exit to Staff Menu): ");
            getStaffID(&getAttr);
            checkStaffID(getAttr.staffID, &validation, &getAttr.staffID);
        } while (validation);
        if (checkStaffIDExist(getAttr.staffID)) {
            displayCertainStaff(staff, staffCount, getAttr.staffID, "void", 0, 0, 0, 'X', "void");
        }
        else {
            printf("Staff with ID %s not found.\n", getAttr.staffID);
        }
    }
    else if (choice == 2) {
        do {
            getStaffName(&getAttr);
            validation = checkStaffName(getAttr.name);
        } while (validation);
        int found = 0;
        for (int i = 0; i < staffCount; i++) {
            if (strcmp(getAttr.name, staff[i].name) == 0) {
                displayCertainStaff(staff, staffCount, "void", getAttr.name, 0, 0, 0, 'X', "void");
                found = 1;
            }
        }
        if (found == 0) {
            printf("\nStaff not found\n");
        }
    }
    else if (choice == 3) {
        char input[10];
        int date;
        printf("\nSearch by:\n");
        printf("1. Day\n");
        printf("2. Month\n");
        printf("3. Year\n");

        do {
            printf("\nSelect day, month or year to search: ");
            rewind(stdin);
            scanf(" %s", input);

            date = checkNumber(input);

            if (date != 1 && date != 2 && date != 3)
                printf("\nPlease enter a valid number (1-3) to search!\n");
        } while (date != 1 && date != 2 && date != 3);

        if (date == 1) {
            do {
                printf("\nEnter day to search: ");
                scanf("%d", &getAttr.birthDate.day);
                if (getAttr.birthDate.day < 1 || getAttr.birthDate.day > 31)
                    printf("Invalid day, please re-enter\n");
            } while (getAttr.birthDate.day < 1 || getAttr.birthDate.day > 31);
            displayCertainStaff(staff, staffCount, "void", "void", getAttr.birthDate.day, 0, 0, 'X', "void");
        }
        else if (date == 2) {
            do {
                printf("\nEnter month to search: ");
                scanf("%d", &getAttr.birthDate.month);
                if (getAttr.birthDate.month < 1 || getAttr.birthDate.month > 12)
                    printf("Invalid month, please re-enter\n");
            } while (getAttr.birthDate.month < 1 || getAttr.birthDate.month > 12);
            displayCertainStaff(staff, staffCount, "void", "void", 0, getAttr.birthDate.month, 0, 'X', "void");
        }
        else if (date == 3) {
            do {
                printf("\nEnter year to search: ");
                scanf("%d", &getAttr.birthDate.year);
                if (getAttr.birthDate.year < 1900 || getAttr.birthDate.year > 2005)
                    printf("Invalid year, please re-enter\n");
            } while (getAttr.birthDate.year < 1900 || getAttr.birthDate.year > 2005);
            displayCertainStaff(staff, staffCount, "void", "void", 0, 0, getAttr.birthDate.year, 'X', "void");
        }
    }
    else if (choice == 4) {
        int gender;
        char staffGender;

        do {
            printf("\nSearch gender by number (1. Male / 2. Female): ");
            gender = getGenderAndPosition();
            checkStaffGender(gender, &staffGender, &validation);
            getAttr.gender = staffGender;
        } while (validation);

        displayCertainStaff(staff, staffCount, "void", "void", 0, 0, 0, getAttr.gender, "void");
    }
    else if (choice == 5) {
        int position;
        char staffPosition[15];

        do {
            printf("\nSearch staff position by number (1. Administrator / 2. Staff): ");
            position = getGenderAndPosition();
            checkStaffPosition(position, &staffPosition, &validation);
            strcpy(getAttr.position, staffPosition);
        } while (validation);

        displayCertainStaff(staff, staffCount, "void", "void", 0, 0, 0, 'X', getAttr.position);
    }
    else if (choice == 6)
        StaffMenu();
    else
        printf("Invalid input!!! Please try again\n\n");
}

//--------------------------------------------Modify Staff--------------------------------------------
void StaffModify() {
    Staff staff[MAX_STAFF];
    Staff modifyAttr;
    int attribute, staffCount, validation, duplicateID;
    char continueModify;
    readStaffFile(staff, &staffCount);

    do {
        system("cls");
        do {
            printf("\nEnter staff ID to modify (Eg: AB123, E = Exit to Staff Menu): ");
            getStaffID(&modifyAttr);
            checkStaffID(modifyAttr.staffID, &validation, &modifyAttr.staffID);
        } while (validation);

        if (checkStaffIDExist(modifyAttr.staffID)) {
            displayCertainStaff(staff, staffCount, modifyAttr.staffID, "void", 0, 0, 0, 'X', "void");
            attribute = selectAttr();

            for (int i = 0; i < staffCount; i++) {
                if (strcmp(staff[i].staffID, modifyAttr.staffID) == 0) {
                    if (attribute == 1) {
                        do {
                            printf("\nEnter new Staff ID (Eg: AB123, E = Exit to Staff Menu): ");
                            getStaffID(&modifyAttr);
                            checkStaffID(modifyAttr.staffID, &validation, &modifyAttr.staffID);
                            duplicateID = checkStaffIDExist(modifyAttr.staffID);
                            if (strcmp(staff[i].staffID, modifyAttr.staffID) == 0)
                                printf("Staff ID before and after modifying are the same! Try enter a new Staff ID\n");
                            else if (duplicateID)
                                printf("Staff ID already exist!!! Re-enter a new staff ID\n");
                        } while (validation || duplicateID);
                        strcpy(staff[i].staffID, modifyAttr.staffID);
                    }
                    else if (attribute == 2) {
                        do {
                            getStaffName(&modifyAttr);
                            validation = checkStaffName(modifyAttr.name);
                            if (strcmp(staff[i].name, modifyAttr.name) == 0) {
                                printf("Name of staff before and after modifying are the same! Please enter a new name\n");
                                validation = 1;
                            }
                        } while (validation);
                        strcpy(staff[i].name, modifyAttr.name);
                    }
                    else if (attribute == 3) {
                        do {
                            getStaffBirth(&modifyAttr, &modifyAttr.birthDate.day, &modifyAttr.birthDate.month, &modifyAttr.birthDate.year);
                            validation = checkBirthDate(modifyAttr.birthDate.day, modifyAttr.birthDate.month, modifyAttr.birthDate.year);
                            if (staff[i].birthDate.day == modifyAttr.birthDate.day && staff[i].birthDate.month == modifyAttr.birthDate.month && staff[i].birthDate.year == modifyAttr.birthDate.year) {
                                printf("The birth date before and after modifying are the same! Please enter a new birth date value\n");
                                validation = 1;
                            }
                        } while (validation);
                        staff[i].birthDate.day = modifyAttr.birthDate.day;
                        staff[i].birthDate.month = modifyAttr.birthDate.month;
                        staff[i].birthDate.year = modifyAttr.birthDate.year;
                    }
                    else if (attribute == 4) {
                        char changeGender[10];
                        if (staff[i].gender == 'M') {
                            strcpy(changeGender, "FEMALE");
                            modifyAttr.gender = 'F';
                        }
                        else if (staff[i].gender == 'F') {
                            strcpy(changeGender, "MALE");
                            modifyAttr.gender = 'M';
                        }
                        printf("Staff gender has changed to %s!\n", changeGender);
                        staff[i].gender = modifyAttr.gender;
                    }
                    else if (attribute == 5) {
                        if (strcmp(staff[i].position, "ADMINISTRATOR") == 0) {
                            strcpy(modifyAttr.position, "STAFF");
                        }
                        else if (strcmp(staff[i].position, "STAFF") == 0) {
                            strcpy(modifyAttr.position, "ADMINISTRATOR");
                        }
                        printf("Staff position has changed to %s!\n", modifyAttr.position);
                        strcpy(staff[i].position, modifyAttr.position);
                    }
                    else if (attribute == 6) {
                        do {
                            printf("\nEnter current password: (Input -1 to exit staff menu): ");
                            rewind(stdin);
                            scanf(" %[^\n]", modifyAttr.password);
                            if (strcmp(staff[i].password, modifyAttr.password) == 0) {
                                do {
                                    getStaffPassword(&modifyAttr);
                                    validation = checkPassword(modifyAttr.password);
                                } while (validation);
                                strcpy(staff[i].password, modifyAttr.password);
                            }
                            else if (strcmp(modifyAttr.password, "-1") == 0)
                                StaffMenu();
                            else {
                                printf("Incorrect password!\n");
                                validation = 1;
                            }
                        } while (validation);
                    }
                    else if (attribute == 7) {
                        do {
                            printf("\nEnter current password recovery: (Input -1 to exit staff menu): ");
                            rewind(stdin);
                            scanf(" %[^\n]", modifyAttr.recovery);
                            if (strcmp(staff[i].recovery, modifyAttr.recovery) == 0) {
                                do {
                                    getStaffRecovery(&modifyAttr);
                                    validation = checkPassword(modifyAttr.recovery);
                                } while (validation);
                                strcpy(staff[i].recovery, modifyAttr.recovery);
                            }
                            else if (strcmp(modifyAttr.recovery, "-1") == 0)
                                StaffMenu();
                            else {
                                printf("Incorrect password recovery!\n");
                                validation = 1;
                            }
                        } while (validation);
                    }
                    else if (attribute == 8)
                        StaffMenu();
                    printf("\nStaff details modified successfully!\n");
                    break;
                }
            }
        }
        else {
            printf("Staff with ID %s not found.\n", modifyAttr.staffID);
        }
        writeStaffFile(staff, staffCount);
        do {
            continueModify = getDecision();
            continueModify = toupper(continueModify);
            validation = checkDecision(continueModify);
        } while (validation);
    } while (continueModify == 'Y');
}

int selectAttr() {
    char input[10];
    int attribute;
    printf("Attributes that can be modified:\n");
    printf("1. Staff ID\n");
    printf("2. Name\n");
    printf("3. Birth Date\n");
    printf("4. Gender\n");
    printf("5. Position\n");
    printf("6. Password\n");
    printf("7. Password Recovery\n");
    printf("8. Return to Staff Menu\n");
    printf("\nSelect attribute to be modified: ");
    scanf(" %s", &input);

    attribute = checkNumber(input);
    return attribute;
}

//--------------------------------------------Display Staff--------------------------------------------
void StaffDisplay() {
    Staff staff[MAX_STAFF];
    int staffCount = 0;

    readStaffFile(staff, &staffCount);
    displayAllStaff(staff, staffCount);
}

//--------------------------------------------Delete Staff--------------------------------------------
void StaffDelete() {
    Staff staff[MAX_STAFF];
    Staff staffToDelete;
    int validation, staffCount, index = 0;
    char continueDelete, yesNo;
    readStaffFile(staff, &staffCount);

    do {
        system("cls");
        do {
            printf("\nEnter Staff ID to delete the staff information (Eg: AB123, E = Exit to Staff Menu): ");
            getStaffID(&staffToDelete);
            checkStaffID(staffToDelete.staffID, &validation, &staffToDelete.staffID);
        } while (validation);

        if (checkStaffIDExist(staffToDelete.staffID)) {
            displayCertainStaff(staff, staffCount, staffToDelete.staffID, "void", 0, 0, 0, 'X', "void");
            do {
                printf("Do you want to delete this staff? (Y = Yes / N = No): ");
                rewind(stdin);
                scanf(" %c", &yesNo);
                yesNo = toupper(yesNo);
                validation = checkDecision(yesNo);
            } while (validation);

            if (yesNo == 'Y' || yesNo == 'y') {
                for (int i = 0; i < staffCount; i++) {
                    if (strcmp(staff[i].staffID, staffToDelete.staffID) == 0) {
                        index = i;
                        break;
                    }
                }
                for (int i = index; i < staffCount; i++) {
                    staff[i] = staff[i + 1];
                }
                staffCount--;
                writeStaffFile(staff, staffCount);
                printf("Staff with ID %s deleted successfully.\n", staffToDelete.staffID);
            }
        }
        else {
            printf("Staff with ID %s not found.\n", staffToDelete.staffID);
        }
        do {
            continueDelete = getDecision();
            continueDelete = toupper(continueDelete);
            validation = checkDecision(continueDelete);
        } while (validation);
    } while (continueDelete == 'Y');
}

//------------------------------------------------Login------------------------------------------------
void StaffLogin() {
    Staff login;
    Staff staff[MAX_STAFF];
    int staffCount, existence, validation, loginSuccess = 1, changeID = 0;
    readStaffFile(staff, &staffCount);

    do {
        system("cls");
        printf("MLM Company Staff Login Portal\n");

        do {
            printf("\nEnter Staff ID (Eg: AB123): ");
            getStaffID(&login);
            checkStaffID(login.staffID, &validation, &login.staffID);
            existence = checkStaffIDExist(login.staffID);
            if (existence == 0 && validation == 0)
                printf("Staff with Staff ID %s does not exist\n", login.staffID);
        } while (existence == 0 || validation);

        do {
            printf("\nEnter password (Input -1 to login by password recovery, input -2 to change Staff ID): ");
            rewind(stdin);
            scanf(" %[^\n]", login.password);

            if (strcmp(login.password, "-2") == 0) {
                changeID = 1;
                loginSuccess = 0;
                system("cls");
            }
            else if (strcmp(login.password, "-1") != 0) {
                for (int i = 0; i < staffCount; i++) {
                    if (strcmp(login.password, staff[i].password) == 0) {
                        printf("\nLogin successfully!!!\n");
                        loginSuccess = 0;
                        changeID = 0;
                        break;
                    }
                    else
                        loginSuccess = 1;
                }
                if (loginSuccess == 1)
                    printf("Invalid password! Please try again\n");
            }
            else {
                printf("\nEnter password recovery: ");
                rewind(stdin);
                scanf(" %[^\n]", login.recovery);
                for (int i = 0; i < staffCount; i++) {
                    if (strcmp(login.recovery, staff[i].recovery) == 0) {
                        printf("\nLogin successfully!!!\n");
                        loginSuccess = 0;
                        changeID = 0;
                        break;
                    }
                    else
                        loginSuccess = 1;
                }
                if (loginSuccess == 1)
                    printf("Invalid password recovery! Please try again\n");
            }
        } while (loginSuccess);
    } while (changeID);
}