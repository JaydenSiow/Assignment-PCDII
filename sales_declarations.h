#pragma once
#define READING "rb"
#define WRITING "wb"
#define APPENDING "ab"
#define FILE_CLOSE fclose(salesFile)
#include "Stock Declarations.h"
#include "member_declarations.h"
#define MAX_SALES 10

/*A001, Vitalite Vitamin A, 51.50, 75.00, 120, 20, 24 - 4 - 2023, 16:10
A002, Vitalite Vitamin B, 45.00, 69.99, 120, 50, 24 - 4 - 2023, 16 : 11
A003, Vitalite Vitamin C, 59.50, 75.50, 200, 50, 24 - 4 - 2023, 16 : 11
C001, Calcium Magnesium Tablet, 65.50, 82.00, 100, 50, 24 - 4 - 2023, 16 : 13
B001, Baiyes Calcium, 20.99, 45.50, 200, 50, 25 - 4 - 2023, 12 : 0
*/

typedef struct {
	char salesID[10];
	char itemName[60];
	int itemQuantity;
	double salesTax;
	double salesTotal;
	Date salesDate;
	char memberId[6];
}SalesRecord;

//Main Functions
void searchRecords(SalesRecord* salesRecords, int numberOfRecordsInFile, int* numberOfSearchedRecords, int indexOfSearchedRecords[]);
void displayRecords(SalesRecord* salesRecords, int numberOfRecordsInFile);
void addARecord();
void modifyARecord(SalesRecord* salesRecords, int numberOfRecordsInFile);
void deleteARecord(SalesRecord* salesRecords, int numberOfRecordsInFile);
void salesPerformanceReport(SalesRecord* salesRecords, int numberOfSalesRecords);

//Modification Module
void dataModifyMenu(SalesRecord* salesRecord);
void dataModificationMenu();

//Select Records to Modify or Delete
void searchSelection(SalesRecord* salesRecords, int indexOfSearchedRecords[], int numberOfSearchedRecords, void (*modifyOrDelete)(), int whichMenu);

//Display Single Record
void displayRecord(SalesRecord* salesRecord);

void updateMemberStatus(Members* member);

//Record Deletion Function
void deleteSearchedRecords(SalesRecord* salesRecords, int numberOfRecordsInFile, int indexOfSearchedRecords[], int numberOfSearchedRecords);

//Condition Functions
int searchByID(char input[], char salesID[]);
int searchForDate(SalesRecord* inputDate, SalesRecord* salesRecord);
int searchForProduct(char input[], char itemName[]);
void searchByCondition(SalesRecord* salesRecords, int numberOfRecordsInFile, int* numberOfSearchedRecords, int indexOfSearchedRecords[], int whichSet, void(*obtainDataFunction)(), int (*setConditionFunction)());
void searchByMemberID(char inputMID[], char mIDInFile[]);

//Headers
void salesReportHeader();

//Menu Functions
void mainMenuDesign();
void nothingMenu();
void searchSelectionMenu(SalesRecord* salesRecords, int indexOfSearchedRecords[], int numberOfSearchedRecords, int whichMenu);
void searchMenu();
void displayMenu();
void menuOption(void (*functions[])(), int whichMenu);
void salesReportHeader();
char loopMainFunctions(void (*functions[])(), int option);
void menuOption(void (*functions[])(), int whichMenu);
void call(int whichMenu);

//Sort Functions
void sortRecordsByName(SalesRecord* salesRecords, int numberOfRecordsInFile);
void sortRecordsByDate(SalesRecord* salesRecords, int numberOfRecordsInFile);

//Obtain Data Functions
int obtainProductQuantity(SalesRecord* salesRecord, StockInfo* stock, int index, int size);
int obtainProductName(SalesRecord* salesRecord, StockInfo* stock, int size);
char yesOrNoFunction(const char enquiry[]);
void obtainDate(SalesRecord* salesRecord);
int obtainOptionFor(int whichMenu, int lowerLimit, int upperLimit);
void generateSalesId(SalesRecord* salesRecord);

//Obtain Data for New Record
void obtainDetailsOfNewRecord(SalesRecord* newRecord);

//Prompts and Displays of Error Messages
void promptsAndErrorMessages(int* loopCount, int errorMessage);
void trigger(void (*solicit)(), char* solicitedData);
void recordNotFoundMessage();
void promptMemberID(char inputMID[]);
void promptForSalesID();
int promptMemberIDForDataModify(SalesRecord* salesRecord, int* newIndex);


//Write Into File Functions
void writeRecordsIntoFile(SalesRecord* salesRecords, int numberOfRecordsInFile);
void writeNewRecordIntoFile(SalesRecord* newRecord);

//Retrieve Records from File
int numberOf(SalesRecord* row, FILE* salesFile);

//Format for File Opening
FILE* openFileFor(const char* accessMode);

//Table of Displaying Sales Records
void tableHeaderForDisplayingSalesRecords();
void sortBySalesID(SalesRecord* salesRecords, int numberOfRecordsInFile);
void displayRecordsOrRecord(SalesRecord line[], int loopCount);

//Obtain Sales Records from Binary File
int obtainSalesRecordsFromFile(SalesRecord* salesRecords);

//Validation Of Sales Data Entered By the User
int validateIfIsValidDate(Date* dateOfSale);


#define LOWER_LIMIT 1
#define UPPER_LIMIT 5
