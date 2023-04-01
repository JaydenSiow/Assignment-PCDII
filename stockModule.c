#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<windows.h>
#pragma warning(disable:4996)

#define STOCK_FILENAME "stockInfo.txt"
#define ARCHIVE_FILENAME "archivedStock.txt"
#define MAX_STOCK 80

typedef struct {
	int day, month, year;
} Date;

typedef struct {
	int hour, min;
}Time;

typedef struct {
	char prodID[6], prodName[30];
	double costPrice, sellPrice;
	int qtyInStock, minLvl, reorderQty;
	char remarks[50];
	Date sysDate;
	Time sysTime;
} Stock;

//program function
void stockMenu();
void readTxtFile(Stock* stock, int* nStock, char filename[]);
void writeTxtFile(Stock stock[], int nStock, char filename[]);
void errorMsg(char name[], int type);
int getYesNo(char question[]);
int inputOpt(char* opt, int minOpt, int maxOpt);
//print 
void savedMsg();
void notSavedMsg();
void bye();
void noRecordMsg();

//validation function
int optValidation(char opt[], int minOpt, int maxOpt);
char yesNoValidation(char yesNo[]);
int checkID(char inputID[], Stock stock[], int nStock);
int checkName(char inputName[], Stock stock[], int nStock);
int comparePrice(double costPrice, double sellPrice);
int checkInteger(double* num);

// 1 Add Stock Function
void addStock(Stock* stock, int* nStock);
void inputID(char *id, Stock stock[], int nStock, int* index, char question[]);
void inputName(char* inputName, Stock stock[], int nStock, int *index, char question[]);
void inputCostPrice(double* inputCostPrice);
void inputSellPrice(double* inputSellPrice);
void inputQtyInStock(int* inputQty);
void inputMinLvl(int* inputMinLvl);
void inputReorderQty(int* inputQty);
void saveCurrentDateTime(Date* date, Time* time);

//date
void inputDate(Date* date, char question[]);
void displayByDates(Date startDate, Date endDate, Stock stock[], int nStock);
int compareDate(Date startDate, Date endDate); 
int checkDate(Date date);

void inputDate(Date* date, char question[]) {
	int check;
	do {
		printf("%s", question);
		rewind(stdin);
		if ((check = scanf("%d-%d-%d", &date->day, &date->month, &date->year) != 3) || (check = checkDate(*date) == -1))
			printf("Wrong Date Format!\n\n");
	} while (check);
}
void displayByDates(Date startDate, Date endDate, Stock stock[], int nStock) {
	for (int i = 0; i < nStock; i++) {
		if ((stock[i].sysDate.day >= startDate.day && stock[i].sysDate.day <= endDate.day) && (stock[i].sysDate.month >= startDate.month && stock[i].sysDate.month <= endDate.month) && (stock[i].sysDate.year >= startDate.year && stock[i].sysDate.year <= endDate.year)) {
			displaySingleStock(stock[i]);
		}
	}
}
int compareDate(Date startDate, Date endDate) {
	if (startDate.year > endDate.year)
		return -1;
	else if ((startDate.year == endDate.year) && (startDate.month > endDate.month)) 
		return -1;
	else if ((startDate.year == endDate.year) && (startDate.month == endDate.month) && (startDate.day > endDate.day))
		return -1;
	else
		return 1;
}
int checkDate(Date date) {
	SYSTEMTIME t;
	GetLocalTime(&t);
	if ((date.day < 1 || date.day>31) || (date.month < 1 || date.month>12) || (date.year < 2020 || date.year>t.wYear)) {
		return -1;
	}
	else {
		if ((date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12) && date.day <= 31)
			return 1;
		else if ((date.month == 2 || date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) && date.day <= 30) {
			if ((date.year % 4 == 0 && date.month == 2 && date.day > 29) || (date.year % 4 != 0 && date.month == 2 && date.day > 28))
				return -1;
			else
				return 1;
		}
		else
			return -1;
	}
}

// 2 Search Stock Function
void searchStock(Stock stock[], int nStock);
void searchByID(Stock stock[], int nStock);
void searchByName(Stock stock[], int nStock);
void searchByCostPrice(Stock stock[], int nStock);
void searchBySellPrice(Stock stock[], int nStock);
void searchByQtyInStock(Stock stock[], int nStock);
void searchByMinLvl(Stock stock[], int nStock);
void searchByReorderQty(Stock stock[], int nStock);
void searchByDate(Stock stock[], int nStock);


// 3 Modify Stock Function
void modifyStock(Stock *stock, int *nStock);

// 4 Display Stock Function
void displayAllStock(Stock stock[], int nStock);
void displaySingleStock(Stock stock);

// 5 Archive Stock Function


// 6 Stock Report Function



// -------------------- Definition --------------------
// ---- Main ----
void main() {
	Stock stock[MAX_STOCK], archivedStock[20];
	int size = 0, checkedOpt, conti;
	char opt[100];

	readTxtFile(&stock, &size, STOCK_FILENAME);

	do {
		conti = 1;
		stockMenu();
		do {
			checkedOpt = inputOpt(opt, 1, 7);
			switch (checkedOpt) {
			//case 0:
			//	errorMsg("Positive Integer (1-7)", 1);
			//	break;
			case 1:
				addStock(&stock, &size);
				break;
			case 2:
				searchStock(stock, size);
				break;
			case 3:
				modifyStock(&stock, &size);
				break;
			case 4:
				displayAllStock(stock, size);
				break;
			case 7:
				conti = 0;
				break;
			}
		} while (checkedOpt == -1);
	} while (checkedOpt != 7);
}

// ---- program ----
void stockMenu() {
	printf(
		"==========================\n"
		" Stock Information Module\n"
		"==========================\n"
		"[1] Add New Stock\n"
		"[2] Search Stock\n"
		"[3] Modify Stock\n"
		"[4] Display Stock\n"
		"[5] Archive Stock\n"
		"[6] Stock Report\n"
		"[7] BACK\n"
	);
}

void readTxtFile(Stock* stock, int* nStock, char filename[]) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Unable to open %s file\n", filename);
		perror("Reason: ");
		exit(-1);
	}

	while (fscanf(fp, "%[^,], %[^,], %lf, %lf, %d, %d, %d, %[^,], %d-%d-%d, %d:%d\n", &stock->prodID, &stock->prodName, &stock->costPrice, &stock->sellPrice, &stock->qtyInStock, &stock->minLvl, &stock->reorderQty, &stock->remarks, &stock->sysDate.day, &stock->sysDate.month, &stock->sysDate.year, &stock->sysTime.hour, &stock->sysTime.min) != EOF) {
		stock++;
		*nStock += 1;
	}
	fclose(fp);
}

void writeTxtFile(Stock stock[], int nStock, char filename[]) {
	FILE* fp = fopen(filename, "w");

	for (int i = 0; i < nStock; i++) {
		fprintf(fp, "%s, %s, %.2lf, %.2lf, %d, %d, %d, %s, %d-%d-%d, %d:%d\n", stock[i].prodID, stock[i].prodName, stock[i].costPrice, stock[i].sellPrice, stock[i].qtyInStock, stock[i].minLvl, stock[i].reorderQty, stock[i].remarks, stock[i].sysDate.day, stock[i].sysDate.month, stock[i].sysDate.year, stock[i].sysTime.hour, stock[i].sysTime.min);
	}
	fclose(fp);
	
}

int getYesNo(char question[]) {
	char yesNo[100], check;

	do {
		printf("%s", question);
		rewind(stdin);
		gets(yesNo);
		check = yesNoValidation(yesNo);
		switch (check) {
		case 'Y':
			return 1;
		case 'N':
			return -1;
		}
	} while (check == 'X');
}

int inputOpt(char* opt, int minOpt, int maxOpt) {
	int check = -1;

	do {
		printf(" > ");
		rewind(stdin);
		gets(opt);

		check = optValidation(opt, minOpt, maxOpt);
	} while (check == -1);
	return check;
}

// ---- print ----
void errorMsg(char name[], int type) {

	switch (type) {
	case 1:
		printf("Invalid Input!! Please Enter %s Only!!\n\n", name);
		break;
	case 2:
		printf("%s Input!! Please Enter Again!!\n\n", name);
		break;
	}
}
void savedMsg() {
	SYSTEMTIME t;
	GetLocalTime(&t);
	printf("Record saved successfully...  [SYSTEM: %0d-%0d-%4d  %0d:%0d]\n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);
}
void notSavedMsg() {
	printf("Record will not be saved...\n\n");
}
void bye() {
	printf("Bye Bye...\n\n");
}
void noRecordMsg() {
	printf("No record found T.T\n\n");
}

// ---- 1 ----
void addStock(Stock *stock, int *nStock) {
	Stock temp;
	int check = 0, saveFile = 0;
	
	if (*nStock < MAX_STOCK) {
		do {
			do {
				inputID(&temp.prodID, stock, *nStock, &check, "you wish to add "); // &check will return index number if same as input
				if (check != -1)
					errorMsg("Duplicated Product ID", 2);
			} while (check != -1);
			do { 
				inputName(&temp.prodName, stock, *nStock, &check, "you wish to add ");
				if (check != -1)
					errorMsg("Duplicated Product Name", 2);
			} while (check != -1);
			inputCostPrice(&temp.costPrice);
			do {
				inputSellPrice(&temp.sellPrice);
			} while (!comparePrice(temp.costPrice, temp.sellPrice));
			inputQtyInStock(&temp.qtyInStock);
			inputMinLvl(&temp.minLvl);
			inputReorderQty(&temp.reorderQty);
			saveCurrentDateTime(&temp.sysDate, &temp.sysTime);
			saveFile = getYesNo("Do you want to save latest records into file (Y/N) ? > ");
			switch (saveFile) {
			case 1:
				stock[*nStock] = temp;
				*nStock += 1;
				writeTxtFile(stock, *nStock, STOCK_FILENAME);
				savedMsg();
				break;
			case -1:
				notSavedMsg();
				break;
			}
			check = getYesNo("Continue to add (Y/N) ? > ");
		} while (check == 1);

	}
	else {
		printf("Stock FULL! T.T \n\n");
	}
}

void inputID(char* inputID, Stock stock[], int nStock, int* index, char question[]) {

	printf("Enter Product ID %s> ", question);
	rewind(stdin);
	gets(inputID);
	*index = checkID(inputID, stock, nStock); //matched, will return particular index number 
}
void inputName(char* inputName, Stock stock[], int nStock, int* index, char question[]) {
	
	printf("Enter Name %s> ", question);
	rewind(stdin);
	gets(inputName);
	*index = checkName(inputName, stock, nStock);
}
void inputCostPrice(double* inputCostPrice) {
	int check;
	do {
		printf("Enter Product Cost Price > ");
		rewind(stdin);
		scanf("%lf", inputCostPrice);
		if (check = *inputCostPrice <= 0) {
			errorMsg("Positive Number", 1);
		}
		else
			check = 0;
	} while (check);
}
void inputSellPrice(double* inputSellPrice) {
	int check;
	do {
		printf("Enter Product Sell Price > ");
		rewind(stdin);
		scanf("%lf", inputSellPrice);
		if (check = *inputSellPrice <= 0) {
			errorMsg("Positive Number", 1);
		}
		//else if (comparePrice(costPrice, *inputSellPrice) <= 0)
		//	check = 0;
		else
			check = 0;
	} while (check);
}
void inputQtyInStock(int* inputQty) {
	int check;
	double input;
	do {
		printf("Enter Quantity In Stock > ");
		rewind(stdin);
		scanf("%lf", &input);
		if (check = checkInteger(&input) <= 0) {
			errorMsg("Positive Integer", 1);
		}
		else {
			*inputQty = (int)input;
			check = 0;
		}
		//(check = scanf("%lf", &input) <= 0) || 
	} while (check);
}
void inputMinLvl(int* inputMinLvl) {
	int check;
	double input;
	do {
		printf("Enter Minimum Level > ");
		rewind(stdin);
		scanf("%lf", &input);
		if (check = checkInteger(&input) <= 0) {
			errorMsg("Positive Integer", 1);
		}
		else {
			*inputMinLvl = (int)input;
			check = 0;
		}
	} while (check);
}
void inputReorderQty(int* inputQty) {
	int check;
	double input;
	do {
		printf("Enter Reorder Quantity > ");
		rewind(stdin);
		scanf("%lf", &input);
		if (check = checkInteger(&input) <= 0) {
			errorMsg("Positive Integer", 1);
		}
		else {
			*inputQty = (int)input;
			check = 0;
		}
	} while (check);
}
void saveCurrentDateTime(Date* date, Time* time) {
	SYSTEMTIME t;
	GetLocalTime(&t);
	date->day = t.wDay;
	date->month = t.wMonth;
	date->year = t.wYear;
	time->min = t.wMinute;
	time->hour = t.wHour;
}

// ---- 2 ----
void searchStock(Stock stock[], int nStock) {
	char opt[100];
	int checkedOpt = 0, conti;
	do {
		do {
			printf(
				"Search Method\n"
				"-------------------------------\n"
				"1. Search By ID\n"
				"2. Search By Name\n"
				"3. Search By Cost Price\n"
				"4. Search By Sell Price\n"
				"5. Search By Quantity In Stock\n"
				"6. Search By Minimum Level\n"
				"7. Search By Reorder Quantity\n"
				"8. Search By Added In Date\n"
				"9. Search By Added In Time\n"
				"0. BACK\n"
			);
			checkedOpt = inputOpt(opt, 0, 9);
		} while (checkedOpt < 0);

		switch (checkedOpt) {
		case 0:
			return;
		case 1:
			searchByID(stock, nStock);
			break;
		case 2:
			searchByName(stock, nStock);
			break;
		case 3:
			searchByCostPrice(stock, nStock);
			break;
		case 4:
			searchBySellPrice(stock, nStock);
			break;
		case 5:
			searchByQtyInStock(stock, nStock);
			break;
		case 6:
			searchByMinLvl(stock, nStock);
			break;
		case 7:
			searchByReorderQty(stock, nStock);
			break;
		case 8:
			searchByDate(stock, nStock);
			break;
		}
		conti = getYesNo("Continue to search (Y/N) ? > ");
	} while (conti == 1);
}

void searchByID(Stock stock[], int nStock) {
	char searchID[6];
	int check = -1;

	inputID(searchID, stock, nStock, &check, "you wish to search ");

	if (check == -1) {
		noRecordMsg();
	}
	else
		displaySingleStock(stock[check]);
}

void searchByName(Stock stock[], int nStock) {
	char searchName[30];
	int check = -1;

	inputName(searchName, stock, nStock, &check, "you wish to search ");

	if (check == -1) {
		noRecordMsg();
	}
	else
		displaySingleStock(stock[check]);
}

void searchByCostPrice(Stock stock[], int nStock) {
	double searchPrice;
	int check = 0;

	inputCostPrice(&searchPrice);
	for (int i = 0; i < nStock; i++) {
		if (searchPrice == stock[i].costPrice) {
			displaySingleStock(stock[i]);
			check++;
		}
	}
	if (check == 0) {
		noRecordMsg();
	}
}

void searchBySellPrice(Stock stock[], int nStock) {
	double searchPrice;
	int check = 0;

	inputSellPrice(&searchPrice);
	for (int i = 0; i < nStock; i++) {
		if (searchPrice == stock[i].sellPrice) {
			displaySingleStock(stock[i]);
			check++;
		}
	}
	if (check == 0) {
		noRecordMsg();
	}
}

void searchByQtyInStock(Stock stock[], int nStock) {
	int check = 0, searchPrice;

	inputQtyInStock(&searchPrice);
	for (int i = 0; i < nStock; i++) {
		if (searchPrice == stock[i].qtyInStock) {
			displaySingleStock(stock[i]);
			check++;
		}
	}
	if (check == 0) {
		noRecordMsg();
	}
}

void searchByMinLvl(Stock stock[], int nStock) {
	int check = 0, searchPrice;

	inputMinLvl(&searchPrice);
	for (int i = 0; i < nStock; i++) {
		if (searchPrice == stock[i].minLvl) {
			displaySingleStock(stock[i]);
			check++;
		}
	}
	if (check == 0) {
		noRecordMsg();
	}
}

void searchByReorderQty(Stock stock[], int nStock) {
	int check = 0, searchPrice;

	inputReorderQty(&searchPrice);
	for (int i = 0; i < nStock; i++) {
		if (searchPrice == stock[i].reorderQty) {
			displaySingleStock(stock[i]);
			check++;
		}
	}
	if (check == 0) {
		noRecordMsg();
	}
}

void searchByDate(Stock stock[], int nStock) {
	Date date;
	int check = 0;
	inputDate(&date);
	for (int i = 0; i < nStock; i++) {
		if ((date.day == stock[i].sysDate.day) && (date.month == stock[i].sysDate.month) && (date.year == stock[i].sysDate.year)) {
			displaySingleStock(stock[i]);
			check++;
		}
	}
	if (check == 0) {
		noRecordMsg();
	}
}
 
// ---- 3 ----
void modifyStock(Stock *stock, int *nStock) {
	char modifyID[6], opt[100];
	int location = -1, check = 0, checkedOpt, saveFile, sameInput;
	Stock temp;

	do {
		do {
			inputID(&modifyID, stock, *nStock, &location, "you wish to modify ");
			if (location == -1)
				errorMsg("Correct ID Name", 1);
		} while (location == -1);
		displaySingleStock(stock[location]);

		printf(
			"Modify Part\n"
			"1. ALL\n"
			"2. Product ID\n"
			"3. Product Name\n"
			"4. Cost Price\n"
			"5. Sell Price\n"
			"6. Quantity In Stock\n"
			"7. Minimum Level\n"
			"8. Reorder Quantity\n"
			"9. EXIT\n"
		);
		checkedOpt = inputOpt(opt, 1, 9);
		switch (checkedOpt) {
		case 1:
			do {
				inputID(&temp.prodID, stock, *nStock, &check, ""); // check will return index number

				if (check == location) { // means it is the same id
					sameInput = getYesNo("Same ID Input... Still use it (Y/N)? ") != 1;
				}
				else if (check != -1) { // same id with other product, reject
					errorMsg("Duplicated Product ID", 2);
					sameInput = 1;
				}
				else // id that not same with all product
					sameInput = 0;
			} while (sameInput);
			do {
				inputName(temp.prodName, stock, *nStock, &check, "");
				if (check == location) {
					sameInput = getYesNo("Same Product Name Input... Still use it (Y/N)? ") != 1;
				}
				else if (check != -1) {
					errorMsg("Duplicated Product Name", 2);
					sameInput = 1;
				}
				else
					sameInput = 0;
			} while (sameInput);
			inputCostPrice(&temp.costPrice);
			do {
				inputSellPrice(&temp.sellPrice);
			} while (!comparePrice(temp.costPrice, temp.sellPrice));
			inputQtyInStock(&temp.qtyInStock);
			inputMinLvl(&temp.minLvl);
			inputReorderQty(&temp.reorderQty);
			break;
		case 2:
			do {
				inputID(&temp.prodID, stock, *nStock, &check, ""); // check will return index number

				if (check == location) { // means it is the same id
					sameInput = getYesNo("Same ID Input... Still use it (Y/N)? ") != 1;
				}
				else if (check != -1) { // same id with other product, reject
					errorMsg("Duplicated Product ID", 2);
					sameInput = 1;
				}
				else // id that not same with all product
					sameInput = 0;
			} while (sameInput);
			//do {
			//	inputID(&temp.prodID, stock, *nStock, &check, ""); // check will return index number

			//	if (check == location) {
			//		sameInput = getYesNo("Same ID Input... Still use it (Y/N)? ");
			//		check = sameInput - 2;
			//	}
			//	else if (check != -1)
			//		errorMsg("Duplicated Product ID", 2);
			//} while (check != -1);
			break;
		case 3:
			do {
				inputName(temp.prodName, stock, *nStock, &check, "");
				if (check == location) {
					sameInput = getYesNo("Same Product Name Input... Still use it (Y/N)? ") != 1;
				}
				else if (check != -1) {
					errorMsg("Duplicated Product Name", 2);
					sameInput = 1;
				}
				else
					sameInput = 0;
			} while (sameInput);
			//do {
			//	inputName(temp.prodName, stock, *nStock, &check, "");
			//	if (check == location) {
			//		sameInput = getYesNo("Same Product Name Input... Still use it (Y/N)? ");
			//		check = sameInput - 2;
			//	}
			//	else if (check != -1)
			//		errorMsg("Duplicated Product Name", 2);
			//} while (check != -1);
			break;
		case 4:
			do {
				inputCostPrice(&temp.costPrice);
			} while (!comparePrice(temp.costPrice, stock[location].sellPrice));
			break;
		case 5:
			do {
				inputSellPrice(&temp.sellPrice);
			} while (!comparePrice(stock[location].costPrice, temp.sellPrice));
			break;
		case 6:
			inputQtyInStock(&temp.qtyInStock);
			break;
		case 7:
			inputMinLvl(&temp.minLvl);
			break;
		case 8:
			inputReorderQty(&temp.reorderQty);
			break;
		case 9:
			return;
		}
		saveFile = getYesNo("Do you want to save latest records into file (Y/N) ? > ");
		switch (saveFile) {
		case 1:
			//save each record after confirmed
			switch (checkedOpt) {
			case 1:
				stock[location] = temp; break;
			case 2:
				strcpy(stock[location].prodID, temp.prodID); break;
			case 3:
				strcpy(stock[location].prodName, temp.prodName); break;
			case 4:
				stock[location].costPrice = temp.costPrice; break;
			case 5:
				stock[location].sellPrice = temp.sellPrice; break;
			case 6:
				stock[location].qtyInStock = temp.qtyInStock; break;
			case 7:
				stock[location].minLvl = temp.minLvl; break;
			case 8:
				stock[location].reorderQty = temp.reorderQty; break;
			}
			saveCurrentDateTime(&stock[location].sysDate, &stock[location].sysTime);
			writeTxtFile(stock, *nStock, STOCK_FILENAME);
			savedMsg();
			break;
		case -1:
			notSavedMsg();
			break;
		}
		check = getYesNo("Continue to modify (Y/N) ? > ");
	} while (check == 1);
}

// ---- 4 ----
void displayAllStock(Stock stock[], int nStock) {

	printf("%-6s %-30s %-12s %-12s %-20s %-15s %-18s %s\n", "ID", "Product Name", "Cost Price", "Sell Price", "Quantity In Stock", "Minimum Level", "Reorder Quantity", "Added Date & Time");
	for (int i = 0; i < 140; i++) {
		printf("-");
		if (i == 139)
			printf("\n");
	}
	for (int i = 0; i < nStock; i++) {
		printf("%-6s %-30s %-12.2lf %-12.2lf %-20d %-15d %-18d %02d-%02d-%d   %02d:%02d\n", stock[i].prodID, stock[i].prodName, stock[i].costPrice, stock[i].sellPrice, stock[i].qtyInStock, stock[i].minLvl, stock[i].reorderQty, stock[i].sysDate.day, stock[i].sysDate.month, stock[i].sysDate.year, stock[i].sysTime.hour, stock[i].sysTime.min);
	}
}

void displaySingleStock(Stock stock) {

	printf("%-6s %-30s %-12.2lf %-12.2lf %-20d %-15d %-18d %02d-%02d-%d   %02d:%02d\n", stock.prodID, stock.prodName, stock.costPrice, stock.sellPrice, stock.qtyInStock, stock.minLvl, stock.reorderQty, stock.sysDate.day, stock.sysDate.month, stock.sysDate.year, stock.sysTime.hour, stock.sysTime.min);
}

// ---- 5 ----


// ---- 6 ----


// ---- validation ----
int optValidation(char opt[], int minOpt, int maxOpt) {
	int count = 0, idxLoc = 0;
	for (int i = 0; i < strlen(opt); i++) {
		if (isdigit(opt[i])) {
			count++;
			idxLoc = i;
		}
		else if (!isspace(opt[i]))
			count++;
	}
	if (count == 1) {
		for (int i = 0; i <= 9; i++) {
			if ((opt[idxLoc] < minOpt + 48) || (opt[idxLoc] > maxOpt + 48)) {
				printf("Invalid Input!! Please Enter Integer (%d-%d) Only!!\n\n", minOpt, maxOpt);
				return -1;
			}
			else if (opt[idxLoc] == i + 48)
				return i;	
		}
	}
	else {
		printf("Invalid Input!! Please Enter Integer (%d-%d) Only!!\n\n", minOpt, maxOpt);
		return -1;
	}
}

int checkID(char inputID[], Stock stock[], int nStock) {
	for (int i = 0; i < nStock; i++) {
		if (strcmp(inputID, stock[i].prodID) == 0) {
			return i; 
		}
	}
	return -1;
}

int checkName(char inputName[], Stock stock[], int nStock) {
	for (int i = 0; i < nStock; i++) {
		if (strcmp(inputName, stock[i].prodName) == 0) {
			return i;
		}
	}
	return -1;
}

int comparePrice(double costPrice, double sellPrice) {
	if (sellPrice <= costPrice) {
		errorMsg("Price Violation", 2);
		return 0;
	}
	else
		return 1;
}

char yesNoValidation(char yesNo[]) {
	int count = 0, idxLoc = 0;
	for (int i = 0; i < strlen(yesNo); i++) {
		if (toupper(yesNo[i]) == 'Y' || toupper(yesNo[i]) == 'N') {
			count++;
			idxLoc = i;
		}
		else if (!isspace(yesNo[i])) {
			count++;
		}
	}
	if (count == 1)
		return toupper(yesNo[idxLoc]);
	else {
		errorMsg("Y or N", 1);
		return 'X'; // to identify is a wrong input
	}
}

int checkInteger(double* num) {
	if (((ceil(*num) - floor(*num)) != 0) || *num <= 0) {
		return -1;
	}
	else
		return 1;

}