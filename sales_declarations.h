#pragma once
#define READING "rb"
#define WRITING "wb"
#define APPENDING "ab"
#define FILE_CLOSE fclose(salesFile)
#include "Stock Declarations.h"

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
	char memberId[5];
}SalesRecord;

void deleteSearchedRecords(SalesRecord* salesRecords, int numberOfRecordsInFile, int indexOfSearchedRecords[], int numberOfSearchedRecords);
int searchByID(char input[], char salesID[]);
int searchForDate(SalesRecord* inputDate, SalesRecord* salesRecord);
int searchForProduct(char input[], char itemName[]);
void searchByCondition(SalesRecord* salesRecords, int numberOfRecordsInFile, int* numberOfSearchedRecords, int indexOfSearchedRecords[], int whichSet, void(*obtainDataFunction)(), int (*setConditionFunction)());

int searchARecord(SalesRecord* salesRecords, int numberOfRecordsInFile, int* numberOfSearchedRecords, int indexOfSearchedRecords[]);
void nothingMenu();
void searchSelectionMenu(SalesRecord* salesRecords, int indexOfSearchedRecords[], int numberOfSearchedRecords);
void searchSelection(SalesRecord* salesRecords, int indexOfSearchedRecords[], int numberOfSearchedRecords, void (*modifyOrDelete)(), int whichMenu);
void searchRecords(SalesRecord* salesRecords, int numberOfRecordsInFile, int* numberOfSearchedRecords, int indexOfSearchedRecords[]);
void searchMenu();
void deleteSelectionMenu(SalesRecord* salesRecords, int indexOfSearchedRecords[], int numberOfSearchedRecords);
void sortRecordsByName(SalesRecord* salesRecords, int numberOfRecordsInFile);
void sortRecordsByDate(SalesRecord* salesRecords, int numberOfRecordsInFile);

void displayRecords(SalesRecord* salesRecords, int numberOfRecordsInFile);
void displayByName(SalesRecord salesRecords[], int numberOfRecordsInFile);
void displayByDate(SalesRecord* salesRecords, int numberOfRecordsInFile);
void displayMenu();




void salesPerformanceReport(SalesRecord* salesRecords, int numberOfSalesRecords);
int obtainProductQuantity(SalesRecord* salesRecord, StockInfo* stock, int index, int size);
int obtainProductName(SalesRecord* salesRecord, StockInfo* stock, int size);
void deleteRecord(SalesRecord* salesRecords, int indexOfRecord);
char yesOrNoFunction(const char enquiry[]);
void deleteARecord(SalesRecord* salesRecords, int numberOfRecordsInFile);
char loopMainFunctions(void (*functions[])(), int option);
void writeRecordsIntoFile(SalesRecord* salesRecords, int numberOfRecordsInFile);
void promptsAndErrorMessages(int* loopCount, int errorMessage);


void menuOption(void (*functions[])(), int whichMenu);
void call(int whichMenu);

//Retrieve Records from File
int numberOf(SalesRecord* row, FILE* salesFile);

//Format for File Opening
int openFileFor(const char* accessMode);

//Display Menu and Obtain Option
int obtainOptionFor(int whichMenu, int lowerLimit, int upperLimit);

//Main Menu
void mainMenuDesign();

//Auto-Generation of SalesID
void generateSalesId(SalesRecord* salesRecord);

//Table of Displaying Sales Records
void tableHeaderForDisplayingSalesRecords();
void displayAllSalesRecordsFromFile(SalesRecord* salesRecords, int numberOfRecordsInFile);
void displayRecordsOrRecord(SalesRecord line[], int loopCount);

//Obtain Sales Records from Binary File
int obtainSalesRecordsFromFile(SalesRecord* salesRecords);

//Search For Specific Record In File

//Add A Record Into the File
void addARecord();

//Obtain Sales Data For Adding A Record or Modifying One
void obtainDate(SalesRecord* salesRecord);


//Modification Module
void dataModifyMenu(SalesRecord* salesRecord);
void dataModificationMenu();

//Validation Of the Sales Data Entered By User
int validateIfIsValidDate(Date* dateOfSale);

//Lower Levels of Abstraction
void trigger(void (*solicit)(), char* solicitedData);
void promptForSalesID();
int findRecordAndReturnIndex(char* searchedID, SalesRecord* line, int numberOfRecordsInFile);
void recordNotFoundMessage();
void obtainDetailsOfNewRecord(SalesRecord* newRecord);
void writeNewRecordIntoFile(SalesRecord* newRecord);

#define LOWER_LIMIT 1
#define UPPER_LIMIT 5
