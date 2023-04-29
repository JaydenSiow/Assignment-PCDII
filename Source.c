#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "sales_declarations.h"
#include "Stock Declarations.h"
#pragma warning(disable:4996)
#define MAIN_MENU 0
#define MODIFIFICATION_MENU 1
#define FROM_SALES_FILE salesFile
typedef int Menu;
typedef char Sales;

void searchMenu() {
	rewind(stdin);
	printf("\n=========================================\n");
	printf("|              Search Menu              |\n");
	printf("========================================\n");
	printf("|    [1] Search By Name                 |\n");
	printf("|---------------------------------------|\n");
	printf("|    [2] Search By Date                 |\n");
	printf("|---------------------------------------|\n");
	printf("|    [3] Search By ID                   |\n");
	printf("|---------------------------------------|\n");
	printf("|    [4] Exit                           |\n");
	printf("=========================================\n\n");
}

void searchRecords(SalesRecord* salesRecords, int numberOfRecordsInFile, int* numberOfSearchedRecords, int indexOfSearchedRecords[]) {
	int option;
	int (*setConditionFunction[])() = { searchForProduct, searchForDate, searchByID };
	void (*obtainDataFunction[])() = { promptName, obtainDate, trigger };
	option = obtainOptionFor(3, 1, 4);
	if (--option != 3)
		searchByCondition(salesRecords, numberOfRecordsInFile, numberOfSearchedRecords, indexOfSearchedRecords, option, obtainDataFunction[option], setConditionFunction[option]);
	if (*numberOfSearchedRecords == 0 && option != 3)
		printf("\nNo Such Record!\n");
}


void searchByCondition(SalesRecord* salesRecords, int numberOfRecordsInFile, int* numberOfSearchedRecords, int indexOfSearchedRecords[], int whichSet, void(*obtainDataFunction)(), int (*setConditionFunction)()) {
	SalesRecord  salesRecord;
	SalesRecord recordsForDisplay[10];
	(whichSet == 0) ? (obtainDataFunction(salesRecord.itemName, "\nEnter the Product Name > ")) : (whichSet == 1) ? (obtainDataFunction(&salesRecord)) : (obtainDataFunction(promptForSalesID, salesRecord.salesID));
	for (int i = 0; i < numberOfRecordsInFile; i++) {
		if ((whichSet == 0) ? (setConditionFunction(salesRecord.itemName, salesRecords[i].itemName)) : (whichSet == 1) ? (setConditionFunction(&salesRecord, &salesRecords[i])) : (setConditionFunction(salesRecord.salesID, salesRecords[i].salesID))) {
			recordsForDisplay[*numberOfSearchedRecords] = salesRecords[i];
			indexOfSearchedRecords[(*numberOfSearchedRecords)++] = i;
		}

	}
	if (*numberOfSearchedRecords > 0)
		displayRecordsOrRecord(recordsForDisplay, *numberOfSearchedRecords);
}

int searchForProduct(char input[], char itemName[]) {
	return strcmp(input, itemName) == 0 ? 1 : 0;
}

int searchForDate(SalesRecord* inputDate, SalesRecord* salesRecord) {
	return (inputDate->salesDate.day == salesRecord->salesDate.day) && (inputDate->salesDate.month == salesRecord->salesDate.month) && (inputDate->salesDate.year == salesRecord->salesDate.year) == 1 ? 1 : 0;
}

int searchByID(char input[], char salesID[]) {
	return strcmp(input, salesID) == 0 ? 1 : 0;
}

void modifyARecord(SalesRecord* salesRecords, int numberOfRecordsInFile) {
	int numberOfSearchedRecords = 0;
	int indexOfSearchedRecords[10];
	searchRecords(salesRecords, numberOfRecordsInFile, &numberOfSearchedRecords, indexOfSearchedRecords);
	if (numberOfSearchedRecords == 0)
		return;
	searchSelection(salesRecords, indexOfSearchedRecords, numberOfSearchedRecords, dataModifyMenu, 0);
	//searchSelection(salesRecords, indexOfSearchedRecords, numberOfSearchedRecords);
	writeRecordsIntoFile(salesRecords, numberOfRecordsInFile);
}

void searchSelection(SalesRecord* salesRecords, int indexOfSearchedRecords[], int numberOfSearchedRecords, void (*modifyOrDelete)(), int whichMenu) {
	int option;
	char deleteAll;
	searchSelectionMenu(salesRecords, indexOfSearchedRecords, numberOfSearchedRecords);
	option = obtainOptionFor(4, 1, numberOfSearchedRecords + 1);
	if (whichMenu && (option - 1) == numberOfSearchedRecords) {
		if (yesOrNoFunction("Confirm Deletion Of All Listed Records") == 'Y')
			modifyOrDelete(salesRecords, obtainSalesRecordsFromFile(salesRecords), indexOfSearchedRecords, numberOfSearchedRecords);
		return 0;
	}
	if (option != (numberOfSearchedRecords + 1))
		modifyOrDelete(&salesRecords[indexOfSearchedRecords[--option]], obtainSalesRecordsFromFile(salesRecords), &indexOfSearchedRecords[option], 1);
	//Display Delete All Option
}

void nothingMenu() {
	printf("");
}

void searchSelectionMenu(SalesRecord* salesRecords, int indexOfSearchedRecords[], int numberOfSearchedRecords) {
	if (numberOfSearchedRecords == 0)
		return 0;
	printf("\n Modify?\n");
	printf("===========\n\n");
	for (int i = 0; i < numberOfSearchedRecords; i++) {
		printf(" %d - %s\n", i + 1, salesRecords[indexOfSearchedRecords[i]].salesID);
	}
	printf(" %d - %s \n", numberOfSearchedRecords + 1, "EXIT");
	printf("\n");
}

void deleteSelectionMenu(SalesRecord* salesRecords, int indexOfSearchedRecords[], int numberOfSearchedRecords) {
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("| %17s %11s\n", "Delete?", "|");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (int i = 0; i < numberOfSearchedRecords; i++) {
		printf("%d | %s | %-14s |\n", i + 1, salesRecords[indexOfSearchedRecords[i]].salesID, salesRecords[indexOfSearchedRecords[i]].itemName);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	}
	printf("%d | %-25s |\n", numberOfSearchedRecords + 1, "EXIT");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");
}

void call(int whichMenu) {
	void (*functions[])() = { displayRecords, searchRecords, modifyARecord, addARecord, deleteARecord, salesPerformanceReport };
	menuOption(functions, whichMenu);
}

void menuOption(void (*functions[])(), int whichMenu) {
	SalesRecord salesRecords[10];
	Menu option;
	while ((option = obtainOptionFor(whichMenu, 1, 7)) != 7) {
		loopMainFunctions(functions, option);
	}
}

char loopMainFunctions(void (*functions[])(), int option) {
	SalesRecord salesRecords[10];
	char proceed = 'N';
	char loopFunctions[][40] = { {"Search Another Record"}, {"Modify Another Record"}, {"Add Another Record"}, {"Delete Another Record"} };
	do {
		int numberOfSearchedRecords = 0;
		int indexOfSearchedRecords[10];
		functions[option - 1](salesRecords, obtainSalesRecordsFromFile(salesRecords), &numberOfSearchedRecords, indexOfSearchedRecords);
		if (option != 1 && option != 6) {
			proceed = yesOrNoFunction(loopFunctions[option - 2]);
		}
	} while (proceed != 'N');
}










void displayRecords(SalesRecord* salesRecords, int numberOfRecordsInFile) {
	int option;
	void (*functions[])() = { displayByName, displayByDate, displayAllSalesRecordsFromFile , sortRecordsByName, sortRecordsByDate };
	while ((option = obtainOptionFor(2, 1, 6)) != 6) {
		functions[option - 1](salesRecords, numberOfRecordsInFile);
	}
}

void displayByName(SalesRecord salesRecords[], int numberOfRecordsInFile) {
	char buffer[50];
	SalesRecord recordsForDisplay[10];
	int j = 0;
	promptName(buffer, "Enter The Product Name > ");
	for (int i = 0; i < numberOfRecordsInFile; i++) {
		if (!strcmp(salesRecords[i].itemName, buffer))
			recordsForDisplay[j++] = salesRecords[i];
	}
	displayRecordsOrRecord(recordsForDisplay, j);
}

void displayByDate(SalesRecord* salesRecords, int numberOfRecordsInFile) {
	SalesRecord  salesRecord;
	SalesRecord recordsForDisplay[10];
	int j = 0;
	obtainDate(&salesRecord);
	for (int i = 0; i < numberOfRecordsInFile; i++) {
		if ((salesRecords[i].salesDate.day == salesRecord.salesDate.day) && (salesRecords[i].salesDate.month == salesRecord.salesDate.month) && (salesRecords[i].salesDate.year == salesRecord.salesDate.year))
			recordsForDisplay[j++] = salesRecords[i];
	}
	displayRecordsOrRecord(recordsForDisplay, j);
}

void displayMenu() {
	rewind(stdin);
	printf("\n=========================================\n");
	printf("|              Display Menu             |\n");
	printf("========================================\n");
	printf("|    [1] Display By Name                |\n");
	printf("|---------------------------------------|\n");
	printf("|    [2] Display By Date                |\n");
	printf("|---------------------------------------|\n");
	printf("|    [3] Display All                    |\n");
	printf("|---------------------------------------|\n");
	printf("|    [4] Sort By Name                   |\n");
	printf("|---------------------------------------|\n");
	printf("|    [5] Sort By Date                   |\n");
	printf("|---------------------------------------|\n");
	printf("|    [6] Exit                           |\n");
	printf("=========================================\n\n");
}

void main() {
	call(MAIN_MENU);
}

int obtainSalesRecordsFromFile(SalesRecord* salesRecords) {
	FILE* salesFile = openFileFor(READING);
	return numberOf(salesRecords, FROM_SALES_FILE);
}

void displayAllSalesRecordsFromFile(SalesRecord* salesRecords, int numberOfRecordsInFile) {
	displayRecordsOrRecord(salesRecords, numberOfRecordsInFile);
}


int searchARecord(SalesRecord* salesRecords, int numberOfRecordsInFile, int* numberOfSearchedRecords, int indexOfSearchedRecords[]) {
	Sales iD[5];
	int index;
	trigger(promptForSalesID, iD);
	index = findRecordAndReturnIndex(iD, salesRecords, numberOfRecordsInFile);
	if (index == -1)
		return 0;
	indexOfSearchedRecords[0] = index;
	*numberOfSearchedRecords = 1;
}

void addARecord() {
	SalesRecord newRecord;
	obtainDetailsOfNewRecord(&newRecord);
	writeNewRecordIntoFile(&newRecord);
}

void deleteARecord(SalesRecord* salesRecords, int numberOfRecordsInFile) {
	int numberOfSearchedRecords = 0;
	int indexOfSearchedRecords[10];
	searchRecords(salesRecords, numberOfRecordsInFile, &numberOfSearchedRecords, indexOfSearchedRecords);
	if (!numberOfSearchedRecords)
		return 0;
	searchSelection(salesRecords, indexOfSearchedRecords, numberOfSearchedRecords, deleteSearchedRecords, 1);
}

void deleteSearchedRecords(SalesRecord* salesRecords, int numberOfRecordsInFile, int indexOfSearchedRecords[], int numberOfSearchedRecords) {
	if (numberOfSearchedRecords) {
		if (yesOrNoFunction("Confirm Deletion") == 'N')
			return 0;
	}
	int num, size;
	num = size = 0;
	SalesRecord updatedRecords[10];
	StockInfo stock[MAX_STOCK_SIZE];
	readStockFile(stock, &size);
	for (int i = 0; i < numberOfRecordsInFile; i++) {
		int skipIndex = 0;
		for (int j = 0; j < numberOfSearchedRecords; j++) {
			if (indexOfSearchedRecords[j] == i) {
				int index = checkExistedName(salesRecords[i].itemName, stock, &size);
				skipIndex = 1;
				stock[index].qtyInStock += salesRecords[i].itemQuantity;
			}
		}
		if (!skipIndex)
			updatedRecords[num++] = salesRecords[i];
	}
	writeRecordsIntoFile(updatedRecords, num);
	writeStockFile(stock, &size);
}

void deleteRecord(SalesRecord* salesRecord, int indexOfRecord) {
	SalesRecord salesRecords[10];
	int numberOfRecordsInFile = obtainSalesRecordsFromFile(salesRecords);
	if (yesOrNoFunction("Confirm Deletion") == 'N')
		return 0;
	int size = 0;
	SalesRecord indexOfSearchedRecords[10];
	StockInfo stock[MAX_STOCK_SIZE];
	readStockFile(stock, &size);
	int index = checkExistedName(salesRecord->itemName, stock, &size);
	stock[index].qtyInStock += salesRecord->itemQuantity;
	writeStockFile(stock, &size);
	FILE* salesFile = openFileFor(WRITING);
	for (int i = 0; i < numberOfRecordsInFile; i++) {
		if (i != indexOfRecord)
			fwrite(&salesRecords[i], sizeof(SalesRecord), 1, salesFile);
	}
	FILE_CLOSE;
	printf("\nRecord Successfully Deleted\n");
}


void mainMenuDesign() {
	printf("\n=========================================\n");
	printf("|        Sales Information Module       |\n");
	printf("========================================\n");
	printf("|    [1] Display Records                |\n");
	printf("|---------------------------------------|\n");
	printf("|    [2] Search A Record                |\n");
	printf("|---------------------------------------|\n");
	printf("|    [3] Modify A Record                |\n");
	printf("|---------------------------------------|\n");
	printf("|    [4] Add A Record                   |\n");
	printf("|---------------------------------------|\n");
	printf("|    [5] Delete A Record                |\n");
	printf("|---------------------------------------|\n");
	printf("|    [6] Sales Performance Report       |\n");
	printf("|---------------------------------------|\n");
	printf("|    [7] Exit	                        |\n");
	printf("=========================================\n\n");
}


void dataModificationMenu() {
	rewind(stdin);
	printf("\n=========================================\n");
	printf("|        Record Modification Menu       |\n");
	printf("========================================\n");
	printf("|    [1] Modify Product Name            |\n");
	printf("|---------------------------------------|\n");
	printf("|    [2] Modify Quantity                |\n");
	printf("|---------------------------------------|\n");
	printf("|    [3] Modify Date                    |\n");
	printf("|---------------------------------------|\n");
	printf("|    [4] Exit                           |\n");
	printf("=========================================\n\n");

}

void tableHeaderForDisplayingSalesRecords() {
	printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n");
	printf("%s%45s%36s", "|", "Sales Records", "|");
	printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}

int obtainOptionFor(int whichMenu, int lowerLimit, int upperLimit) {
	Menu option;
	void (*menuFunctions[])() = { mainMenuDesign, dataModificationMenu, displayMenu, searchMenu, nothingMenu };
	menuFunctions[whichMenu]();
	do {
		printf("Enter your selection (%d-%d) > ", lowerLimit, upperLimit);
	} while (!scanf("%d", &option) || (option < lowerLimit || option > upperLimit));
	rewind(stdin);
	return option;
}

char yesOrNoFunction(const char enquiry[]) {
	char yesNo;
	printf("\n%s (Y-Yes N-No)? > ", enquiry);
	while ((yesNo = toupper(getchar())) != 'N' && yesNo != 'Y') {
		rewind(stdin);
		printf("\nInvalid Input! Enter Y Or N Only > ");
	};
	rewind(stdin);
	return yesNo;
}

int openFileFor(const char* accessMode) {
	FILE* salesFile = fopen("sales.bin", accessMode);
	if (salesFile == NULL) {
		printf("Error Opening File");
		exit(-1);
	}
	return salesFile;
}

int numberOf(SalesRecord* row, FILE* salesFile) {
	int i = 0;
	while (fread(&row[i], sizeof(SalesRecord), 1, salesFile)) {
		i++;
	}
	FILE_CLOSE;
	return i;
}

void displayRecordsOrRecord(SalesRecord line[], int loopCount) {
	tableHeaderForDisplayingSalesRecords();
	for (int i = 0; i < loopCount; i++) {
		printf("\n| %s | %-30s | %-2d | $%-7.2f | $%-6.2f | %02d/%02d/%-6d |\n", line[i].salesID, line[i].itemName, line[i].itemQuantity, line[i].salesTax, line[i].salesTotal, line[i].salesDate.day, line[i].salesDate.month, line[i].salesDate.year);
		printf("%s", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}
	printf("\n\n");
}

void trigger(void (*solicit)(), char* solicitedData) {
	solicit();
	scanf("%[^\n]", solicitedData);
	rewind(stdin);
}

int findRecordAndReturnIndex(char* searchedID, SalesRecord* line, int numberOfRecordsInFile) {
	for (int i = 0; i < numberOfRecordsInFile; i++) {
		if (!strcmp(searchedID, line[i].salesID)) {
			displayRecordsOrRecord(&line[i], 1);
			return i;
		}
	}
	recordNotFoundMessage();
	return -1;
}


void promptForSalesID() {
	printf("\nEnter The Sales ID > ");
}

void promptsAndErrorMessages(int* loopCount, int errorMessage) {
	char dataRequest[][100] = { {"\nEnter Quantity (1-99) > "}, {"\nInvalid! Re-enter Quantity (1-99) > "} //0,1
	, {"\nEnter Date by (DD/MM/YYYY) > "},{"\nInvalid Date. Re-enter Date (DD/MM/YYYY) > "} //2,3
	, {"\nEnter Your Payment Method (Credit Card Or Cash) > "}, {"\nInvalid Payment Method! Re-Enter Payment Method (Credit Card Or Cash) > "} //3,4
	, {"\nEnter Your Credit Card Details (AAAA-BBBB-CCCC-DDDD) > "}, {"\nInvalid Credit Card Number! Re-Enter Your Credit Card Details(AAAA-BBBB-CCCC-DDDD) > "} };//8
	printf(dataRequest[*loopCount = (*loopCount >= (errorMessage) ? errorMessage : *loopCount)]);
	(*loopCount)++;
	rewind(stdin);
}

void recordNotFoundMessage() {
	printf("\nNo Such Record Was Found!\n");
}

/*void modifyRecordData(SalesRecord* salesRecords, int indexOfRecordInFile, int numberOfRecordsInFile) {
	if (indexOfRecordInFile == -1)
		return 0;
	dataModifyMenu(&salesRecords[indexOfRecordInFile]);
	writeRecordsIntoFile(salesRecords, numberOfRecordsInFile);
}
*/

void dataModifyMenu(SalesRecord* salesRecord) {
	StockInfo stock[MAX_STOCK_SIZE];
	int size = 0;
	readStockFile(stock, &size);
	int index = checkExistedName(salesRecord->itemName, stock, &size);//Obtain Index of Name In Stock File
	int newIndex = index;//Assign Index to New Index 
	Menu option;
	int (*modifyFunctions[5])(SalesRecord*) = { obtainProductName, obtainProductQuantity, obtainDate };
	while ((option = obtainOptionFor(1, 1, 4)) != 4) {
		(--option) == 0 ? (newIndex = modifyFunctions[option](salesRecord, stock, size)) : (modifyFunctions[option](salesRecord, stock, index, size));//Update New Index Every Iteration
		if (newIndex != index) {//If the New Name is not Equal to the Old Name 
			stock[newIndex].qtyInStock -= salesRecord->itemQuantity;// Minus the Quantity of the New Name In Stock
			stock[index].qtyInStock += salesRecord->itemQuantity;// Plus the Quantity of the Old Name In Stock
			index = newIndex;//Assign the New Index as the Old Index
			if (!compareStockBetween(stock[index].minLvl, (stock[index].qtyInStock))) {// If the Quantity in Stock is Below Min Lvl
				modifyFunctions[1](salesRecord, stock, index, size);//Enter the New Quantity
			};
		}
		writeStockFile(stock, &size);
	}
}

int obtainProductQuantity(SalesRecord* salesRecord, StockInfo* stock, int index, int size) {
	int tempQty;
	do {
		tempQty = promptQty("Enter Product Quantity  > ");
	} while (!compareStockBetween(stock[index].minLvl, (stock[index].qtyInStock - (tempQty - salesRecord->itemQuantity))));
	stock[index].qtyInStock -= (tempQty - salesRecord->itemQuantity);//110
	salesRecord->itemQuantity = tempQty;//10
}

int obtainProductName(SalesRecord* salesRecord, StockInfo* stock, int size) {
	char buffer[50];
	int index;
	do {
		promptName(buffer, "Enter Product Name > ");
	} while ((index = checkExistedName(buffer, stock, &size)) < 0);
	strcpy(salesRecord->itemName, stock[index].prodName);
	return index;
}

void writeRecordsIntoFile(SalesRecord* salesRecords, int numberOfRecordsInFile) {
	FILE* salesFile = openFileFor(WRITING);
	fwrite(salesRecords, sizeof(SalesRecord), numberOfRecordsInFile, salesFile);
	FILE_CLOSE;
}


void generateSalesId(SalesRecord* salesRecord) {
	SalesRecord recordsInFile[10];
	int newSequenceNumber = 0;
	for (int i = 0, highestSequenceNumber = 0; i < obtainSalesRecordsFromFile(recordsInFile); i++) {
		sscanf(recordsInFile[i].salesID, "S%d", &highestSequenceNumber);
		if (highestSequenceNumber > newSequenceNumber)
			newSequenceNumber = highestSequenceNumber;
	}
	sprintf(salesRecord->salesID, "S%03d", ++newSequenceNumber);
}

int validateIfIsValidDate(Date* dateOfSale) {

	if (dateOfSale->day < 32 || dateOfSale->day > 0 || dateOfSale->month < 13 || dateOfSale->month > 0 || dateOfSale->year < 2023 || dateOfSale->year > 0) {
		if (dateOfSale->month != 1 && dateOfSale->month != 3 && dateOfSale->month != 5 && dateOfSale->month != 7 && dateOfSale->month != 8 && dateOfSale->month != 11 && dateOfSale->month != 12 && dateOfSale->day > 30)
			return 1;
		if (dateOfSale->month == 2 && dateOfSale->day > 28) {
			if ((dateOfSale->year % 4) != 0)
				return 1;
			else if (dateOfSale->day > 29)
				return 1;
		}
		return 0;
	}
	else
		return 1;
}

void writeNewRecordIntoFile(SalesRecord* newRecord) {
	if (yesOrNoFunction("Confirm Addition") == 'N')
		return 0;
	FILE* salesFile = openFileFor(APPENDING);
	fwrite(newRecord, sizeof(SalesRecord), 1, salesFile);
	FILE_CLOSE;
}

void obtainDate(SalesRecord* salesRecord) {
	int loopCount = 2;
	do {
		promptsAndErrorMessages(&loopCount, 3);
	} while (scanf("%d/%d/%d", &salesRecord->salesDate.day, &salesRecord->salesDate.month, &salesRecord->salesDate.year) != 3 || validateIfIsValidDate(&salesRecord->salesDate));
	rewind(stdin);
}

void obtainDetailsOfNewRecord(SalesRecord* newRecord) {
	//numberOfRecordsInFile = rData(members);
	StockInfo stock[MAX_STOCK_SIZE];
	int size = 0;
	newRecord->itemQuantity = NULL;
	readStockFile(stock, &size);
	generateSalesId(newRecord);
	int index = obtainProductName(newRecord, stock, size);
	obtainProductQuantity(newRecord, stock, index, size);
	//PromptMemberID 
	//Declare Member Structure
	//index = mCheckRedundancy(&member); //Return 0 If Not Existent 
	newRecord->salesTax = stock[index].sellPrice * newRecord->itemQuantity * 0.066;
	newRecord->salesTotal = stock[index].sellPrice * newRecord->itemQuantity + newRecord->salesTax;
	//members[index].mTotalSales += salesTotal;
	//if members[index].mTotalSales reaches a certain limit Update Member Status Example : (Iron to Platinum)
	obtainDate(newRecord);
	writeStockFile(stock, &size);
	//wData(members, numberOfRecordsInFile);
}

void salesPerformanceReport(SalesRecord* salesRecords, int numberOfSalesRecords) {
	StockInfo stock[MAX_STOCK_SIZE];
	int size = 0;
	readStockFile(stock, &size);
	int quantitySold[MAX_STOCK_SIZE] = { NULL };
	int i = 0;
	while (i < size) {
		int j = NULL;
		while (j < numberOfSalesRecords) {
			if (!strcmp(stock[i].prodName, salesRecords[j].itemName))
				quantitySold[i] += salesRecords[j].itemQuantity;
			j++;
		}
		i++;
	}
	i = 0;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("|%35s%18s\n", "Sales Performance", "|");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	while (i < size) {
		int j = NULL;
		int highestInIteration = NULL;
		int number = NULL;
		while (j < size) {
			if (quantitySold[j] > number) {
				highestInIteration = j;
				number = quantitySold[j];
			}
			j++;
		}
		//printf("")
		printf("| %d | %-25s | %d Sales | $%-7.2f |\n", i + 1, stock[highestInIteration].prodName, quantitySold[highestInIteration], quantitySold[highestInIteration] * (stock[highestInIteration].sellPrice - stock[highestInIteration].costPrice));;
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		quantitySold[highestInIteration] = 0;
		i++;
	}
}



/*void main() {
	FILE* file = fopen("sales.bin", "wb");
	SalesRecord row[] = { {"S001","Vitalite Vitamin A",3,0.23,20.53,2,6,2018},{"S002","Vitalite Vitamin B",2,0.43,10.32,5,9,2011},{"S003","Vitalite Vitamin C",6,0.12,2.31,6,1,2011},{"S004","Calcium Magnesium Tablet",6,1.93,30.87,1,12,2015},{"S005","Baiyes Calcium",5,4.59,56.78,3,5,2020},{"S006","Vitalite Vitamin A",5,0.23,20.53,5,12,2017},};
	//SalesRecord row[5];
	fwrite(row, sizeof(row), 1, file);
	//for(int i = 0; i < 5; i++){
		//printf("\n%s | %-10s | %d | %-12s | %-20s | %.2f | %-6.2f | %02d/%02d/%04d |", row[i].salesID, row[i].itemName, row[i].itemQuantity, row[i].paymentMethod, row[i].creditCardDetails, row[i].salesTax, row[i].salesTotal, row[i].salesDate.day, row[i].salesDate.month, row[i].salesDate.year);
		//printf("\n%s", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	//}
	fclose(file);
}*/


void sortRecordsByName(SalesRecord* line, int numberOfRecordsInFile) {
	tableHeaderForDisplayingSalesRecords();
	for (int i = 65; i < 90; i++) {
		for (int j = 0; j < numberOfRecordsInFile; j++) {
			if ((int)(line[j].itemName[0]) == i) {
				printf("\n| %s | %-30s | %-2d | $%-7.2f | $%-6.2f | %02d/%02d/%-6d |\n", line[j].salesID, line[j].itemName, line[j].itemQuantity, line[j].salesTax, line[j].salesTotal, line[j].salesDate.day, line[j].salesDate.month, line[j].salesDate.year);
				printf("%s", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			}
		}
	}
}

void sortRecordsByDate(SalesRecord* salesRecords, int numberOfRecordsInFile) {
	for (int i = 2022; i > 2000; i--) {
		for (int j = 12; j > 0; j--) {
			for (int k = 31; k > 0; k--) {
				for (int z = 0; z < numberOfRecordsInFile; z++) {
					if (salesRecords[z].salesDate.year == i && salesRecords[z].salesDate.month == j && salesRecords[z].salesDate.day == k)
						displayRecordsOrRecord(&salesRecords[z], 1);
				}
			}
		}
	}
}

/*void main() {
	FILE* file = fopen("sales.bin", "wb");
	SalesRecord row[] = { {"S001","Vitalite Vitamin A",3,0.23,20.53,2,6,2018},{"S002","Vitalite Vitamin B",2,0.43,10.32,5,9,2011},{"S003","Vitalite Vitamin C",6,0.12,2.31,6,1,2011},{"S004","Calcium Magnesium Tablet",6,1.93,30.87,1,12,2015},{"S005","Baiyes Calcium",5,4.59,56.78,3,5,2020},{"S006","Vitalite Vitamin A",5,0.23,20.53,5,12,2017},};
	//SalesRecord row[5];
	fwrite(row, sizeof(row), 1, file);
	//for(int i = 0; i < 5; i++){
		//printf("\n%s | %-10s | %d | %-12s | %-20s | %.2f | %-6.2f | %02d/%02d/%04d |", row[i].salesID, row[i].itemName, row[i].itemQuantity, row[i].paymentMethod, row[i].creditCardDetails, row[i].salesTax, row[i].salesTotal, row[i].salesDate.day, row[i].salesDate.month, row[i].salesDate.year);
		//printf("\n%s", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	//}
	fclose(file);
}*/



