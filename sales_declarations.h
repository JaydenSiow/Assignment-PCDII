#pragma once
#define READING "rb"
#define WRITING "wb"
#define APPENDING "ab"
#define FILE_CLOSE fclose(salesFile)
#include "Stock Declarations.h"

typedef struct {
	char salesID[10];
	char itemName[15];
	int itemQuantity;
	char paymentMethod[30];
	char creditCardDetails[30];
	double salesTax;
	double salesTotal;
	Date salesDate;
}SalesRecord;

void deleteRecord(SalesRecord* salesRecords, int indexOfRecord, int numberOfRecordsInFile);
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
void generateSalesId(SalesRecord *salesRecord);

//Table of Displaying Sales Records
void tableHeaderForDisplayingSalesRecords();
void displayAllSalesRecordsFromFile(SalesRecord* salesRecords, int numberOfRecordsInFile);
void displayRecordsOrRecord(SalesRecord line[], int loopCount);

//Obtain Sales Records from Binary File
int obtainSalesRecordsFromFile(SalesRecord* salesRecords);

//Search For Specific Record In File
int searchARecord(SalesRecord* salesRecords, int numberOfRecordsInFile);

//Add A Record Into the File
void addARecord();

//Obtain Sales Data For Adding A Record or Modifying One
void obtainDate(SalesRecord* salesRecord);
void obtainQuantity(SalesRecord* salesRecord);
void obtainPaymentMethod(SalesRecord* salesRecord);
void obtainCreditCardDetails(SalesRecord* salesRecord);

//Modification Module
void modifyARecord(SalesRecord* salesRecords, int numberOfRecordsInFile);
void dataModifyMenu(SalesRecord* row);
void dataModificationMenu();

//Validation Of the Sales Data Entered By User
int validateIfIsValidDate(Date *dateOfSale);

//Lower Levels of Abstraction
void trigger(void (*solicit)(), char* solicitedData);
void promptForSalesID();
int findRecordAndReturnIndex(char* searchedID, SalesRecord* line, int numberOfRecordsInFile);
void recordNotFoundMessage();
void modifyRecordData(SalesRecord* salesRecords, int indexOfRecordInFile, int numberOfRecordsInFile);
void obtainDetailsOfNewRecord(SalesRecord* newRecord);
void writeNewRecordIntoFile(SalesRecord* newRecord);

#define LOWER_LIMIT 1
#define UPPER_LIMIT 5
