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


//Include a Function for Write
//Include a Delete Function
//Search Function Look Again


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

int searchARecord(SalesRecord *salesRecords, int numberOfRecordsInFile) {
	Sales iD[5];
	trigger(promptForSalesID, iD);
	return findRecordAndReturnIndex(iD, salesRecords, numberOfRecordsInFile);
}

void modifyARecord(SalesRecord* salesRecords, int numberOfRecordsInFile) {
	int indexOfRecord = searchARecord(salesRecords, numberOfRecordsInFile);
	modifyRecordData(salesRecords, indexOfRecord, numberOfRecordsInFile);
}

void addARecord() {
	SalesRecord newRecord;
	obtainDetailsOfNewRecord(&newRecord);
	writeNewRecordIntoFile(&newRecord);
}

void deleteARecord(SalesRecord* salesRecords, int numberOfRecordsInFile) {
	int indexOfRecord = searchARecord(salesRecords, numberOfRecordsInFile);
	deleteRecord(salesRecords, indexOfRecord, numberOfRecordsInFile);
}

void deleteRecord(SalesRecord* salesRecords, int indexOfRecord, int numberOfRecordsInFile) {
	if (indexOfRecord == -1)
		return 0;
	if (yesOrNoFunction("Confirm Deletion") == 'N')
		return 0;
	else
		writeRecordsIntoFile(salesRecords, indexOfRecord, numberOfRecordsInFile);
	printf("\nRecord Successfully Deleted\n");
}

void mainMenuDesign() {
	printf("\n=========================================\n");
	printf("|        Sales Information Module       |\n");
	printf("========================================\n");
	printf("|    [1] Display All Sales Records      |\n");
	printf("|---------------------------------------|\n");
	printf("|    [2] Search A Record                |\n");
	printf("|---------------------------------------|\n");
	printf("|    [3] Modify A Record                |\n");
	printf("|---------------------------------------|\n");
	printf("|    [4] Add A Record                   |\n");
	printf("|---------------------------------------|\n");
	printf("|    [5] Exit	                        |\n");
	printf("=========================================\n\n");
}

void call(int whichMenu) {
	void (*functions[])() = { displayAllSalesRecordsFromFile, searchARecord, modifyARecord, addARecord, deleteARecord };
	menuOption(functions, whichMenu);
}

void menuOption(void (*functions[])(), int whichMenu) {
	SalesRecord salesRecords[10];
	Menu option;
	int limits[2] = { 1, 6 };
	while ((option = obtainOptionFor(whichMenu, limits[0], limits[1])) != limits[1]) {
		loopMainFunctions(functions, option);
	}
}

char loopMainFunctions(void (*functions[])(), int option) {
	SalesRecord salesRecords[10];
	char proceed = 'N';
	char loopFunctions[][40] = { {"Search Another Record"}, {"Modify Another Record"}, {"Add Another Record"}, {"Delete Another Record"} };
	do {
		functions[option - 1](salesRecords, obtainSalesRecordsFromFile(salesRecords));
		if (option != 1) {
			proceed = yesOrNoFunction(loopFunctions[option - 2]);
		}
	} while (proceed != 'N');
}

void dataModificationMenu() {

	rewind(stdin);
	printf("\n=========================================\n");
	printf("|        Record Modification Menu       |\n");
	printf("========================================\n");
	printf("|    [1] Modify Quantity                |\n");
	printf("|---------------------------------------|\n");
	printf("|    [2] Modify Date                    |\n");
	printf("|---------------------------------------|\n");
	printf("|    [3] Exit                           |\n");
	printf("=========================================\n\n");

}

void tableHeaderForDisplayingSalesRecords() {
	printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n");
	printf("%s%52s%41s", "|", "Sales Records", "|");
	printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}

int obtainOptionFor(int whichMenu, int lowerLimit, int upperLimit) {
	Menu option;
	void (*menuFunctions[])() = { mainMenuDesign, dataModificationMenu };
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
	while(fread(&row[i], sizeof(SalesRecord), 1, salesFile)) {
		i++;
	}
	FILE_CLOSE;
	return i;
}

void displayRecordsOrRecord(SalesRecord line[], int loopCount) {
	StockInfo stock[MAX_STOCK_SIZE], temp;
	int size = 0;
	int index;
	char buffer[50];
	readStockFile(stock, &size);
	tableHeaderForDisplayingSalesRecords();
	for (int i = 0; i < loopCount; i++) {
		printf("\n| %s | %-4s %-30s | %d | %-12s | %-20s | $%.2f | $%-6.2f | %02d/%02d/%04d |\n", line[i].salesID, (checkExistedName(buffer, stock, &size)) < 0 ? ("(Item Deleted)") : "", line[i].itemName, line[i].itemQuantity, line[i].paymentMethod, line[i].creditCardDetails, line[i].salesTax, line[i].salesTotal, line[i].salesDate.day, line[i].salesDate.month, line[i].salesDate.year);
		printf("%s", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}
	printf("\n\n");
	system("pause");
}

void trigger(void (*solicit)(), char* solicitedData) {
	solicit();
	scanf("%[^\n]", solicitedData);
	rewind(stdin);
}

int findRecordAndReturnIndex(char* searchedID, SalesRecord* line, int numberOfRecordsInFile) {
	//int indexOfSearchedRecords[50] = { NULL };
	//int index = 0;
	for (int i = 0; i < numberOfRecordsInFile; i++) {
		if (!strcmp(searchedID, line[i].salesID)) {
			displayRecordsOrRecord(&line[i], 1);
			//indexOfSearchedRecords[index++];
			return i;
		}
	}
	//return indexOfSearchedRecords;
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

void modifyRecordData(SalesRecord* salesRecords, int indexOfRecordInFile, int numberOfRecordsInFile) {
	if (indexOfRecordInFile == -1)
		return 0;
	dataModifyMenu(&salesRecords[indexOfRecordInFile]);
	writeRecordsIntoFile(salesRecords, -1, numberOfRecordsInFile);
}

void writeRecordsIntoFile(SalesRecord * salesRecords, int numberOfRecordsInFile) {
	FILE* salesFile = openFileFor(WRITING);
	for(int i = 0; i < numberOfRecordsInFile; i++){
			fwrite(salesRecords, sizeof(SalesRecord), 1, salesFile);
	}	
	FILE_CLOSE;
}            

void dataModifyMenu(SalesRecord *row) {
	Menu option;
	void (*modifyFunctions[5])(SalesRecord *) = { obtainQuantity, obtainDate};
	while ((option = obtainOptionFor(1, 1, 3)) != 3) {
		modifyFunctions[--option](row);
	}
}

void obtainDetailsOfNewRecord(SalesRecord  *newRecord) {
	StockInfo stock[MAX_STOCK_SIZE], temp;
	int size = 0;
	int index;
	char buffer[50];
    readStockFile(stock, &size);
	//obtainProductName(stock, size);
	//obtainQuantity(stock);
	generateSalesId(newRecord);
	obtainPaymentMethod(newRecord);
	obtainCreditCardDetails(newRecord);
	obtainDate(newRecord);
	
}

/*void obtainQuantity(StockInfo* stock) {
	int tempQty;
	do {
		tempQty = promptQty("Enter Product Quantity In Stock > ");
	} while (!compareStockBetween(stock[index].minLvl, stock[index].qtyInStock - tempQty));
}

void obtainProductName(StockInfo *stock, int size) {
	char buffer[50];
	int index;
	do {
		promptName(buffer, "Enter Product Name > ");
	} while ((index = checkExistedName(buffer, stock, &size)) < 0);
	return index;
}
*/
void generateSalesId(SalesRecord *salesRecord) {
	SalesRecord recordsInFile[10];
	int newSequenceNumber = 0;
	for (int i = 0, highestSequenceNumber = 0; i < obtainSalesRecordsFromFile(recordsInFile); i++) {
		sscanf(recordsInFile[i].salesID, "S%d", &highestSequenceNumber);
		if (highestSequenceNumber > newSequenceNumber)
			newSequenceNumber = highestSequenceNumber;
	}
	sprintf(salesRecord->salesID, "S%03d", ++newSequenceNumber);
}

void obtainQuantity(SalesRecord* salesRecord) {
	int loopCount = NULL; //Equals Zero
	do {
		promptsAndErrorMessages(&loopCount, 1);// Loop Count = 1
	} while (!scanf("%d", &salesRecord->itemQuantity) || (salesRecord->itemQuantity < 1 || salesRecord->itemQuantity > 100));
}

void obtainDate(SalesRecord * salesRecord) {
	int loopCount = 2;
	do {
		promptsAndErrorMessages(&loopCount, 3);
	} while (scanf("%d/%d/%d", &salesRecord->salesDate.day, &salesRecord->salesDate.month, &salesRecord->salesDate.year) != 3 || validateIfIsValidDate(&salesRecord->salesDate));
	rewind(stdin);
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

void obtainPaymentMethod(SalesRecord * salesRecord) {
	int loopCount = 4;
	do {
		promptsAndErrorMessages(&loopCount, 5);
		scanf("%[^\n]", salesRecord->paymentMethod);
	} while (strcmp(salesRecord->paymentMethod, "Credit Card") && strcmp(salesRecord->paymentMethod, "Cash"));
}

void obtainCreditCardDetails(SalesRecord * salesRecord) {
	int a, b, c, d;
	int loopCount = 6;
	if (!strcmp(salesRecord->paymentMethod, "Credit Card")) {
		do {
			promptsAndErrorMessages(&loopCount, 7);
		} while ((scanf("%d-%d-%d-%d", &a, &b, &c, &d) != 4 || (a < 1000 || a > 9999) || (b < 1000 || b > 9999) || (c < 1000 || c > 9999) || (d < 1000 || d > 9999)));
		sprintf(salesRecord->creditCardDetails, "%d-%d-%d-%d", a, b, c, d);
	}
	//string = strupr(string);
	else
		strcpy(salesRecord->creditCardDetails, "-");
}

void writeNewRecordIntoFile(SalesRecord* newRecord) {
	if (yesOrNoFunction("Confirm Addition") == 'N')
		return 0;
	FILE* salesFile = openFileFor(APPENDING);
	fwrite(newRecord, sizeof(SalesRecord), 1, salesFile);
	FILE_CLOSE;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          

/*void salesPerformanceReport(SalesRecord *salesRecords, int numberOfSalesRecords) {
	StockInfo stock[MAX_STOCK_SIZE];
	int size = 0;
	readStockFile(stock, &size);
	int quantitySold[MAX_STOCK_SIZE] = { NULL };
	int i = 0;
	while (i++ < size) {
		int j = NULL;
		int highestInIteration = NULL;
		while (j++ < numberOfSalesRecords){
			if (!strcmp(stock[i].prodName, salesRecords[j].itemName))
				quantitySold[i] += salesRecords[j].itemQuantity;
		}
	}

	i = 0;

	while (i++ < size) {
		int j = NULL;
		int highestInIteration = NULL;
		while (j++ < size) {
			if (quantitySold[j] > highestInIteration)
				highestInIteration = j;
		}
		printf("Top %d : %s With %d Sales", i + 1, stock[highestInIteration].prodName, quantitySold[highestInIteration]);
		quantitySold[highestInIteration] = 0;
	}

}
*/


/*void main() {
	FILE* file = fopen("sales.bin", "wb");
	SalesRecord row[] = { {"S001","Ramen",3,"Credit Card","3289-3289-1020-2132",0.23,20.53,2,2018,21},{"S002","Crack",2,"Cash","-",0.43,10.32,5,2011,23},{"S003","Onions",6,"Cash","-",0.12,2.31,6,2011,1},{"S004","Americano",6,"Credit Card","6489-9302-1390-8929",1.93,30.87,1,2015,12},{"S005","Bento",5,"Credit Card", "1134-2189-8329-2891",4.59,56.78,3,2020,1}};
	//SalesRecord row[5];
	fwrite(row, sizeof(row), 1, file);
	//for(int i = 0; i < 5; i++){
		//printf("\n%s | %-10s | %d | %-12s | %-20s | %.2f | %-6.2f | %02d/%02d/%04d |", row[i].salesID, row[i].itemName, row[i].itemQuantity, row[i].paymentMethod, row[i].creditCardDetails, row[i].salesTax, row[i].salesTotal, row[i].salesDate.day, row[i].salesDate.month, row[i].salesDate.year);
		//printf("\n%s", "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	//}
	fclose(file);
}*/


