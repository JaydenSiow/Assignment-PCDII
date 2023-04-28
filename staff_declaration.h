#pragma once
#define STAFF_FILE "staff.txt"
#define MAX_STAFF 50
#define MAXCHAR_STAFF_ID 6
#define MAXCHAR_STAFF_NAME 25
#define MAXCHAR_STAFF_POSITION 15
#define MAXCHAR_PASSWORD 25

typedef struct {
    int day, month, year;
}Date;

typedef struct {
    char staffID[MAXCHAR_STAFF_ID];
    char name[MAXCHAR_STAFF_NAME];
    Date birthDate;
    char gender;
    char position[MAXCHAR_STAFF_POSITION];
    char password[MAXCHAR_PASSWORD];
    char recovery[MAXCHAR_PASSWORD];
}Staff;

//Validation
void checkStaffID(char[], int*, char(*)[]);
int checkStaffName(char[]);
int checkBirthDate(int, int, int);
void checkStaffGender(int, char*, int*);
void checkStaffPosition(int, char(*), int*);
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