#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<windows.h>
#pragma warning(disable:4996)

#define STOCK_FILENAME "stockFile.txt"
#define MAX_STOCK 80
#define MAX_ARCHIVED_STOCK 20

typedef struct {
	int day, month, year;
} Date;

typedef struct {
	int hour, min;
}Time;

typedef struct {
	char prodID[5], prodName[30];
	double costPrice, sellPrice;
	int qtyInStock, minLvl, reorderQty;
	char status[15];
	Date sysDate;
	Time sysTime;
} Stock;

//program function
void stockMenu();
void readStockFile(Stock*, int* nStock, Stock*, int* nArcStock);
void writeStockFile(Stock stock[], int nStock, Stock arcStock[], int arcSize);
void errorMsg(char reason[]);
int getYesNo(char question[]);
int inputOpt(char* opt, int minOpt, int maxOpt);
void stockHeading();

void savedMsg();
void notSavedMsg();
void bye();
void noRecordMsg();
void savedMsg() {
	SYSTEMTIME t;
	GetLocalTime(&t);
	printf("Record saved successfully...  [SYSTEM: %0d-%0d-%4d  %02d:%02d]\n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);
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

// validation
int optValidation(char opt[], int minOpt, int maxOpt);
char yesNoValidation(char yesNo[]);
int checkID(char inputID[], Stock stock[], int nStock);
int checkName(char inputName[], Stock stock[], int nStock);
int comparePrice(double costPrice, double sellPrice);
int checkInteger(double* num);
int checkDate(Date date);
int compareDate(Date startDate, Date endDate);
int checkTime(Time time);
int checkMinLvl(int minLvl, int qtyInStock);

// 1 Add Stock Function
void addStock(Stock* stock, int* nStock, Stock* archivedStock, int* nArcStock);
void inputID(char* id, Stock stock[], int nStock, int* index, char question[]);
void inputName(char* inputName, Stock stock[], int nStock, int* index, char question[]);
void inputCostPrice(double* inputCostPrice, char question[]);
void inputSellPrice(double* inputSellPrice, char question[]);
void inputQtyInStock(int* inputQty, char question[]);
void inputMinLvl(int* inputMinLvl, char question[]);
void inputReorderQty(int* inputQty, char question[]);
void saveCurrentDateTime(Date* date, Time* time);

// 2 Search Stock Function
void searchStock(Stock stock[], int nStock);
void searchStockMenu();

// 3 Modify Stock Function
void modifyStock(Stock* stock, int* nStock, Stock* archivedStock, int* nArcStock);
void modifyStockMenu();
void inputDate(Date* date, char question[]);
int inputTwoDates(Date* startDate, Date* endDate);
void displayByDates(Date startDate, Date endDate, Stock stock[], int nStock, Stock arcStock[], int nArcStock);
void inputTime(Time* time, char question[]);

// 4 Display
void displayStockMenu(Stock stock[], int size, Stock arcStock[], int nArcStock);
void displayAllStock(Stock stock[], int size); 
void displaySingleStock(Stock);
void sortByID(Stock stock[], int nStock);
void sortByCostPrice(Stock stock[], int nStock);
void sortBySellPrice(Stock stock[], int nStock);
void sortByQtyInStock(Stock stock[], int nStock);
void sortByDate(Stock stock[], int nStock);
void sortByTime(Stock stock[], int nStock);

// 5 Update stock status
void updateStockStatus(Stock* stock, int* nStock, Stock* archivedStock, int* nArcStock);

// 6 report
void stockReport(Stock stock[], int nStock, Stock arcStock[], int nArcStock);
void overviewReport(Stock stock[], int nStock, Stock arcStock[], int nArcStock);
void lowStockReport(Stock stock[], int nStock, Stock arcStock[], int nArcStock);
void trackDateReport(Stock stock[], int nStock, Stock arcStock[], int nArcStock);

/* ------------------------------ Definition ------------------------------ */
/* -------------------- Main -------------------- */
void main() {
	Stock stock[MAX_STOCK], archivedStock[MAX_ARCHIVED_STOCK];
	int size = 0, arcSize = 0, checkedOpt;
	char opt[100];

	readStockFile(stock, &size, archivedStock, &arcSize);

	//printf("%s\n\n", archivedStock[arcSize -1].prodID);

	do {
		stockMenu();
		do {
			checkedOpt = inputOpt(opt, 1, 7);
			switch (checkedOpt) {
			case 1:
				addStock(stock, &size, archivedStock, &arcSize);
				break;
			case 2:
				searchStock(stock, size);
				break;
			case 3:
				modifyStock(stock, &size, archivedStock, &arcSize);
				break;
			case 4:
				displayStockMenu(stock, size, archivedStock, arcSize);
				//displayAllStock(stock, size);
				break;
			case 5:
				updateStockStatus(stock, &size, archivedStock, &arcSize);
				break;
			case 6:
				stockReport(stock, size, archivedStock, arcSize);
				break;
			case 7:
				return;
			}
		} while (checkedOpt == -1);
	} while (checkedOpt != 7);
}

void stockMenu() {
	printf(
		"+============================+\n"
		"| Stock Information Module   |\n"
		"+===+========================+\n"
		"| 1 | Add New Stock          |\n"
		"| 2 | Search Active Stock    |\n"
		"| 3 | Modify Active Stock    |\n"
		"| 4 | Display Active Stock   |\n"
		"| 5 | Update Stock Status    |\n"
		"| 6 | Stock Report           |\n"
		"| 7 | BACK                   |\n"
		"+===+========================+\n"
	);
}

void readStockFile(Stock* stock, int* nStock, Stock* archivedStock, int* nArcStock) {
	Stock temp;
	FILE* fp = fopen(STOCK_FILENAME, "r");
	if (fp == NULL) {
		printf("Unable to open %s file\n", STOCK_FILENAME);
		return;
	}

	while (fscanf(fp, "%[^,], %[^,], %lf, %lf, %d, %d, %d, %[^,], %d-%d-%d, %d:%d\n", &temp.prodID, &temp.prodName, &temp.costPrice, &temp.sellPrice, &temp.qtyInStock, &temp.minLvl, &temp.reorderQty, &temp.status, &temp.sysDate.day, &temp.sysDate.month, &temp.sysDate.year, &temp.sysTime.hour, &temp.sysTime.min) != EOF) {
		if (strcmp(temp.status, "Active") == 0) {
			stock[*nStock] = temp;
			*nStock += 1;
		}
		else if (strcmp(temp.status, "Archived") == 0) {
			archivedStock[*nArcStock] = temp;
			*nArcStock += 1;
		}
	}
	fclose(fp);
}
void writeStockFile(Stock stock[], int nStock, Stock arcStock[], int arcSize) {
	FILE* fp = fopen(STOCK_FILENAME, "w");
	if (fp == NULL) {
		printf("Unable to write %s file\n", STOCK_FILENAME);
		return;
	}

	for (int i = 0; i < nStock; i++) {
		fprintf(fp, "%s, %s, %.2lf, %.2lf, %d, %d, %d, %s, %d-%d-%d, %d:%d\n", stock[i].prodID, stock[i].prodName, stock[i].costPrice, stock[i].sellPrice, stock[i].qtyInStock, stock[i].minLvl, stock[i].reorderQty, stock[i].status, stock[i].sysDate.day, stock[i].sysDate.month, stock[i].sysDate.year, stock[i].sysTime.hour, stock[i].sysTime.min);
	}
	for (int j = 0; j < arcSize; j++) {
		fprintf(fp, "%s, %s, %.2lf, %.2lf, %d, %d, %d, %s, %d-%d-%d, %d:%d\n", arcStock[j].prodID, arcStock[j].prodName, arcStock[j].costPrice, arcStock[j].sellPrice, arcStock[j].qtyInStock, arcStock[j].minLvl, arcStock[j].reorderQty, arcStock[j].status, arcStock[j].sysDate.day, arcStock[j].sysDate.month, arcStock[j].sysDate.year, arcStock[j].sysTime.hour, arcStock[j].sysTime.min);
	}
	fclose(fp);
}

void errorMsg(char reason[]) {
	printf("Invalid Input! Please Enter Again! [%s]\n\n", reason);
}
int getYesNo(char question[]) {
	char yesNo[100];
	char check;

	do {
		printf("%s", question);
		rewind(stdin);
		gets(yesNo);
		check = yesNoValidation(yesNo);
		switch (check) {
		case 'Y':
			return 1;
		case 'N':
			return 0;
		}
	} while (check == 'X');
}
int inputOpt(char *opt, int minOpt, int maxOpt) {
	int check = -1;

	do {
		printf(" > ");
		rewind(stdin);
		gets(opt);

		check = optValidation(opt, minOpt, maxOpt);
	} while (check == -1);
	return check;
}
void stockHeading() {
	printf(
		"+====+=======+===============================+=============+=============+=====================+================+===================+===================+\n"
		"|%3s | %-6s| %-30s| %-12s| %-12s| %-20s| %-15s| %-18s| %s |\n"
		"+====+=======+===============================+=============+=============+=====================+================+===================+===================+\n", "NO.", "ID", "PRODUCT NAME", "COST PRICE", "SELL PRICE", "QUANTITY IN STOCK", "MINIMUM LEVEL", "REORDER QUANTITY", "ADDED DATE & TIME"
	);
}

/* -------------------- validation -------------------- */ 
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
	int alphabet = 0, num = 0, alpIndex = 0;
	for (int j = 0; j < strlen(inputID); j++) {
		if (isalpha(inputID[j])) {
			alphabet++;
			alpIndex = j;
		}
		else if (isdigit(inputID[j]))
			num++;
	}
	if (alphabet == 1 && num == 3) {
		for (int i = 0; i < nStock; i++) {
			if (strcmp(inputID, stock[i].prodID) == 0) {
				return i;
			}
			
		}
		return -1;
	}
	//else if (alphabet == 1 && num == 0 && toupper(inputID[alpIndex]) == 'X')
	//	return 0;
	else {
		errorMsg("Reason: Wrong Product ID Format");
		return -2;
	}
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
		errorMsg("Reason: Sell Price <= Cost Price");
		return 0;
	}
	else
		return 1;
}

char yesNoValidation(char yesNo[]) {
	int length = 0, idxLoc = 0, isYN = 0;
	for (int i = 0; i < strlen(yesNo); i++) {
		if ((isYN = toupper(yesNo[i]) == 'Y') || (isYN = toupper(yesNo[i]) == 'N')) {
			length++;
			idxLoc = i;
		}
		else if (!isspace(yesNo[i])) {
			length++;
		}
	}
	if (length == 1 && isYN)
		return toupper(yesNo[idxLoc]);
	else {
		errorMsg("Enter Y/N Only");
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

int compareDate(Date startDate, Date endDate) {
	if (startDate.year > endDate.year)
		return 0;
	else if ((startDate.year == endDate.year) && (startDate.month > endDate.month))
		return 0;
	else if ((startDate.year == endDate.year) && (startDate.month == endDate.month) && (startDate.day > endDate.day))
		return 0;
	else
		return 1;
}
int checkDate(Date date) {
	SYSTEMTIME t;
	GetLocalTime(&t);
	if ((date.day < 1 || date.day>31) || (date.month < 1 || date.month>12) || (date.year < 2018 || date.year>t.wYear)) {
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

int checkTime(Time time) {
	if (time.hour >= 0 && time.hour < 24) {
		if (time.min >= 0 && time.min < 60)
			return 1;
		else
			return -1;
	}
	else
		return -1;
}

int checkMinLvl(int minLvl, int qtyInStock) {
	if (qtyInStock < minLvl) {
		errorMsg("Reason: Quantity In Stock Cannot Lower Than Minimum Level");
		return 0;
	}
	else
		return 1;
}

/* -------------------- 1 Add -------------------- */
void addStock(Stock* stock, int* nStock, Stock* archivedStock, int* nArcStock) {
	Stock temp;
	int check = 0, saveFile = 0;

	if (*nStock < MAX_STOCK) {
		do {
			do {
				inputID(temp.prodID, stock, *nStock, &check, "Enter Product ID you wish to add (EXP: P001) > "); // &check will return index number if same as input
				if (check == -1)
					check = checkID(temp.prodID, archivedStock, *nArcStock);
				if (check >= 0)
					errorMsg("Reason: Duplicated Product ID");
			} while (check != -1); // -1 = correct format and no duplicated, -2 = wrong format, >=0 index number from stock
			do {
				inputName(temp.prodName, stock, *nStock, &check, "Enter Name you wish to add > ");
				if (check != -1)
					errorMsg("Reason: Duplicated Product Name");
			} while (check != -1);
			inputCostPrice(&temp.costPrice, "Enter Product Cost Price (RM) > ");
			do {
				inputSellPrice(&temp.sellPrice, "Enter Product Sell Price (RM) > ");
			} while (!comparePrice(temp.costPrice, temp.sellPrice));
			inputMinLvl(&temp.minLvl, "Enter Product Minimum Level > ");
			do { 
				inputQtyInStock(&temp.qtyInStock, "Enter Product Quantity In Stock > ");
			} while (!checkMinLvl(temp.minLvl, temp.qtyInStock));
			
			inputReorderQty(&temp.reorderQty, "Enter Product Reorder Quantity > ");
			saveCurrentDateTime(&temp.sysDate, &temp.sysTime);
			saveFile = getYesNo("Do you want to save latest records into file (Y/N) ? > ");
			switch (saveFile) {
			case 1:
				strcpy(temp.status, "Active");
				stock[*nStock] = temp;
				*nStock += 1;
				writeStockFile(stock, *nStock, archivedStock, *nArcStock);
				savedMsg();
				break;
			case 0:
				notSavedMsg();
				break;
			}
			//check = getYesNo("Continue to add (Y/N) ? > ");
		} while (getYesNo("Continue to add (Y/N) ? > "));
	}
	else {
		printf("Stock FULL! T.T \n\n");
	}
}

void inputID(char* inputID, Stock stock[], int nStock, int* index, char question[]) {

	printf("%s", question);
	rewind(stdin);
	gets(inputID);
	*index = checkID(inputID, stock, nStock); //matched, will return particular index number 
	
}
void inputName(char* inputName, Stock stock[], int nStock, int* index, char question[]) {

	printf("%s", question);
	rewind(stdin);
	gets(inputName);
	*index = checkName(inputName, stock, nStock);
}
void inputCostPrice(double* inputCostPrice, char question[]) {
	int check;
	do {
		printf("%s", question);
		rewind(stdin);
		scanf("%lf", inputCostPrice);
		if (check = *inputCostPrice <= 0) {
			errorMsg("Reason: Not a Decimal Number");
			//printf("Invalid Input [Reason: Not a Decimal Number]! Please Enter Again!!\n\n");
		}
		else
			check = 0;
	} while (check);
}
void inputSellPrice(double* inputSellPrice, char question[]) {
	int check;
	do {
		printf("%s", question);
		rewind(stdin);
		scanf("%lf", inputSellPrice);
		if (check = *inputSellPrice <= 0) {
			errorMsg("Reason: Not a Decimal Number");
		}
		//else if (comparePrice(costPrice, *inputSellPrice) <= 0)
		//	check = 0;
		else
			check = 0;
	} while (check);
}
void inputQtyInStock(int* inputQty, char question[]) {
	int check;
	double input;
	do {
		printf("%s", question);
		rewind(stdin);
		scanf("%lf", &input);
		if (check = checkInteger(&input) <= 0) {
			errorMsg("Reason: Not an Integer Number");
		}
		else {
			*inputQty = (int)input;
			check = 0;
		}
		//(check = scanf("%lf", &input) <= 0) || 
	} while (check);
}
void inputMinLvl(int* inputMinLvl, char question[]) {
	int check;
	double input;
	do {
		printf("%s", question);
		rewind(stdin);
		scanf("%lf", &input);
		if (check = checkInteger(&input) <= 0) {
			errorMsg("Reason: Not an Integer Number");
		}
		else {
			*inputMinLvl = (int)input;
			check = 0;
		}
	} while (check);
}
void inputReorderQty(int* inputQty, char question[]) {
	int check;
	double input;
	do {
		printf("%s", question);
		rewind(stdin);
		scanf("%lf", &input);
		if (check = checkInteger(&input) <= 0) {
			errorMsg("Reason: Not an Integer Number");
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

/* -------------------- 2 Search -------------------- */
void searchStockMenu() {
	printf(
		"===============================\n"
		" Search Method\n"
		"===============================\n"
		"[1] Search By ID\n"
		"[2] Search By Name\n"
		"[3] Search By Cost Price\n"
		"[4] Search By Sell Price\n"
		"[5] Search By Quantity In Stock\n"
		"[6] Search By Minimum Level\n"
		"[7] Search By Reorder Quantity\n"
		"[8] Search By Added In Date\n"
		"[9] Search By Added In Time\n"
		"[0] BACK\n"
	);
}
void searchStock(Stock stock[], int nStock) {
	char opt[100];
	int checkedOpt = 0, conti, check;
	Stock display[MAX_STOCK], temp;
	do {
		do {
			searchStockMenu();
			checkedOpt = inputOpt(opt, 0, 9);
		} while (checkedOpt < 0);

		switch (checkedOpt) {
		case 0:
			return;
		case 1:  
			//searchByID
			check = -1;
			inputID(temp.prodID, stock, nStock, &check, "Enter Product ID you wish to search > ");

			if (check == -1) {
				noRecordMsg();
			}
			else
				displaySingleStock(stock[check]);
			break;
		case 2:
			//searchByName
			check = -1;
			inputName(temp.prodName, stock, nStock, &check, "Enter Product Name you wish to search > ");

			if (check == -1) {
				noRecordMsg();
			}
			else
				displaySingleStock(stock[check]);
			break;
		case 3:
			//searchByCostPrice
			check = 0;

			inputCostPrice(&temp.costPrice, "Enter Product Cost Price (RM) You Wish to Search > ");
			for (int i = 0; i < nStock; i++) {
				if (temp.costPrice == stock[i].costPrice) {
					display[check] = stock[i];
					check++;
				}
			}
			if (check == 0) {
				noRecordMsg();
			}
			else
				sortByID(display, check);
			break;
		case 4:
			//searchBySellPrice
			check = 0;

			inputSellPrice(&temp.sellPrice, "Enter Product Sell Price (RM) You Wish to Search > ");
			for (int i = 0; i < nStock; i++) {
				if (temp.sellPrice == stock[i].sellPrice) {
					display[check] = stock[i];
					check++;
				}
			}
			if (check == 0) {
				noRecordMsg();
			}
			else
				sortByID(display, check);
			break;
		case 5:
			//searchByQtyInStock
			check = 0;

			inputQtyInStock(&temp.qtyInStock, "Enter Product Quantity In Stock You Wish to Search > ");
			for (int i = 0; i < nStock; i++) {
				if (temp.qtyInStock == stock[i].qtyInStock) {
					display[check] = stock[i];
					check++;
				}
			}
			if (check == 0) {
				noRecordMsg();
			}
			else
				sortByID(display, check);
			break;
		case 6:
			//searchByMinLvl
			check = 0;

			inputMinLvl(&temp.minLvl, "Enter Product Minimum Level You Wish to Search > ");
			for (int i = 0; i < nStock; i++) {
				if (temp.minLvl == stock[i].minLvl) {
					display[check] = stock[i];
					check++;
				}
			}
			if (check == 0) {
				noRecordMsg();
			}
			else
				sortByID(display, check);
			break;
		case 7:
			//searchByReorderQty
			check = 0;

			inputReorderQty(&temp.reorderQty, "Enter Product Reorder Quantity You Wish to Search > ");
			for (int i = 0; i < nStock; i++) {
				if (temp.reorderQty == stock[i].reorderQty) {
					display[check] = stock[i];
					check++;
				}
			}
			if (check == 0) {
				noRecordMsg();
			}
			else
				sortByID(display, check);
			break;
		case 8:
			//searchByDate
			check = 0;
			inputDate(&temp.sysDate, "Enter Date (DD-MM-YYYY) > ");
			for (int i = 0; i < nStock; i++) {
				if ((temp.sysDate.day == stock[i].sysDate.day) && (temp.sysDate.month == stock[i].sysDate.month) && (temp.sysDate.year == stock[i].sysDate.year)) {
					display[check] = stock[i];
					check++;
				}
			}
			if (check == 0) {
				noRecordMsg();
			}
			else
				sortByID(display, check);
			break;
		case 9:
			check = 0;
			inputTime(&temp.sysTime, "Enter Time (HH:MM) > ");
			for (int i = 0; i < nStock; i++) {
				if ((temp.sysTime.hour == stock[i].sysTime.hour) && (temp.sysTime.min == stock[i].sysTime.min)) {
					display[check] = stock[i];
					check++;
				}
			}
			if (check == 0) {
				noRecordMsg();
			}
			else
				sortByID(display, check);
			break;
		}
		//conti = getYesNo("Continue to search (Y/N) ? > ");
	} while (getYesNo("Continue to search (Y/N) ? > "));
}

/* -------------------- 3 Modify -------------------- */
void modifyStockMenu() {
	printf(
		"=====================\n"
		" Modify Part\n"
		"=====================\n"
		"[1] ALL\n"
		"[2] Product ID\n"
		"[3] Product Name\n"
		"[4] Cost Price\n"
		"[5] Sell Price\n"
		"[6] Quantity In Stock\n"
		"[7] Minimum Level\n"
		"[8] Reorder Quantity\n"
		"[9] Added Date & Time\n"
		"[0] BACK\n"
	);
}
void modifyStock(Stock* stock, int* nStock, Stock* archivedStock, int* nArcStock) {
	char modifyID[6], opt[100];
	int location = -1, check = 0, checkedOpt, saveFile, sameInput;
	Stock temp;

	do {
		do {
			inputID(modifyID, stock, *nStock, &location, "Enter Product ID you wish to modify > ");
			if (location == -1)
				errorMsg("Reason: No Such Product ID");
			else if(location != -2)
				displaySingleStock(stock[location]);
		} while (location <= -1);

		modifyStockMenu();
		checkedOpt = inputOpt(opt, 0, 9);
		switch (checkedOpt) {
		case 1:
			do {
				inputID(temp.prodID, stock, *nStock, &check, "Enter New Product ID > "); // check will return index number
				if (check == -1)
					check = checkID(temp.prodID, archivedStock, *nArcStock);

				if (check == location) { // means it is the same id
					sameInput = getYesNo("Same ID Input... Still use it (Y/N)? ") != 1;
				}
				else if (check >= 0) { // same id with other product, reject
					errorMsg("Reason: Duplicated Product ID");
					sameInput = 1;
				}
				else if (check == -2)
					sameInput = 1;
				else // id that not same with all product
					sameInput = 0;
			} while (sameInput);
			do {
				inputName(temp.prodName, stock, *nStock, &check, "Enter New Product Name > ");
				if (check == location) {
					sameInput = getYesNo("Same Product Name Input... Still use it (Y/N)? ") != 1;
				}
				else if (check != -1) {
					errorMsg("Reason: Duplicated Product Name");
					sameInput = 1;
				}
				else
					sameInput = 0;
			} while (sameInput);
			inputCostPrice(&temp.costPrice, "Enter New Cost Price (RM) > ");
			do {
				inputSellPrice(&temp.sellPrice, "Enter New Sell Price (RM) > ");
			} while (!comparePrice(temp.costPrice, temp.sellPrice));
			inputMinLvl(&temp.minLvl, "Enter New Minimum Level for Product > ");
			do {
				inputQtyInStock(&temp.qtyInStock, "Enter New Quantity In Stock for Product > ");
			} while (!checkMinLvl(temp.minLvl, temp.qtyInStock));
			
			inputReorderQty(&temp.reorderQty, "Enter Reorder Quantity for Product > ");
			inputDate(&temp.sysDate, "Enter New Date (DD/MM/YYYY) > ");
			inputTime(&temp.sysTime, "Enter New Time (HH:MM) > ");
			break;
		case 2:
			do {
				inputID(temp.prodID, stock, *nStock, &check, "Enter New Product ID > "); // check will return index number
				if (check == -1)
					check = checkID(temp.prodID, archivedStock, *nArcStock);
				if (check == location) { // means it is the same id
					sameInput = getYesNo("Same ID Input... Still use it (Y/N)? ") != 1;
				}
				else if (check >= 0) { // same id with other product, reject
					errorMsg("Reason: Duplicated Product ID");
					sameInput = 1;
				}
				else if (check == -2)
					sameInput = 1;
				else // id that not same with all product
					sameInput = 0;
			} while (sameInput);
			break;
		case 3:
			do {
				inputName(temp.prodName, stock, *nStock, &check, "Enter New Product Name > ");
				if (check == location) {
					sameInput = getYesNo("Same Product Name Input... Still use it (Y/N)? ") != 1;
				}
				else if (check != -1) {
					errorMsg("Reason: Duplicated Product Name");
					sameInput = 1;
				}
				else
					sameInput = 0;
			} while (sameInput);
			break;
		case 4:
			do {
				inputCostPrice(&temp.costPrice, "Enter New Cost Price (RM) > ");
			} while (!comparePrice(temp.costPrice, stock[location].sellPrice));
			break;
		case 5:
			do {
				inputSellPrice(&temp.sellPrice, "Enter New Sell Price (RM) > ");
			} while (!comparePrice(stock[location].costPrice, temp.sellPrice));
			break;
		case 6:
			do { 
				inputQtyInStock(&temp.qtyInStock, "Enter New Quantity In Stock for Product > ");
			} while (!checkMinLvl(stock[location].minLvl, temp.qtyInStock));
			break;
		case 7:
			do {
				inputMinLvl(&temp.minLvl, "Enter New Minimum Level for Product > ");
			} while (!checkMinLvl(temp.minLvl, stock[location].qtyInStock));
			break;
		case 8:
			inputReorderQty(&temp.reorderQty, "Enter Reorder Quantity for Product > ");
			break;
		case 9:
			inputDate(&temp.sysDate, "Enter New Date (DD/MM/YYYY) > ");
			inputTime(&temp.sysTime, "Enter New Time (HH:MM) > ");
			break;
		case 0:
			return;
		}
		saveFile = getYesNo("Do you want to save latest records into file (Y/N) ? > ");
		switch (saveFile) {
		case 1:
			//save each record after confirmed
			switch (checkedOpt) {
			case 1:
				strcpy(temp.status, stock[location].status);
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
			case 9:
				stock[location].sysDate = temp.sysDate;
				stock[location].sysTime = temp.sysTime;
				break;
			}
			//saveCurrentDateTime(&stock[location].sysDate, &stock[location].sysTime);
			writeStockFile(stock, *nStock, archivedStock, *nArcStock);
			savedMsg();
			break;
		case 0:
			notSavedMsg();
			break;
		}
		//check = getYesNo("Continue to modify (Y/N) ? > ");
	} while (getYesNo("Continue to modify (Y/N) ? > "));
}

void inputDate(Date* date, char question[]) {
	int check;
	char c1, c2;
	do {
		check = 0;
		printf("%s", question);
		rewind(stdin);
		if ((scanf("%d%c%d%c%d", &date->day, &c1, &date->month, &c2, &date->year) != 5) || (checkDate(*date) == -1) || ((c1 != '-' && c1 != '/' && c1 != ' ') || (c2 != '-' && c2 != '/' & c2 != ' '))){
			errorMsg("Reason: Wrong Date Format");
			check = 1;
		}
	} while (check);
}
int inputTwoDates(Date* startDate, Date* endDate) {
	int checkDates;
	inputDate(startDate, "Enter start date (DD-MM-YYYY) > ");
	inputDate(endDate, "Enter end date (DD-MM-YYYY) > ");
	//checkDates = compareDate(*startDate, *endDate);
	//return checkDates;

	return compareDate(*startDate, *endDate);
}

void inputTime(Time* time, char question[]) {
	int wrong;
	char c;
	do {
		wrong = 0;
		printf("%s", question);
		rewind(stdin);
		if (((scanf("%d%c%d", &time->hour, &c, &time->min) != 3) || (checkTime(*time) == -1)) || (c != ':' && c != '.' && c != ' ')) {
			errorMsg("Reason: Wrong Time Format");
			wrong = 1;
		}
	} while (wrong);
}

/* -------------------- 4 Display -------------------- */
void displayStockMenu(Stock stock[], int size, Stock arcStock[], int nArcStock) {
	char opt[100], conti;
	int checkedOpt;
	do {
		printf(
			"=============================\n"
			" Display Stock\n"
			"=============================\n"
			"[1] Unsorted Stock\n"
			"[2] Sort By Product ID\n"
			"[3] Sort By Cost Price\n"
			"[4] Sort By Sell Price\n"
			"[5] Sort By Quantity In Stock\n"
			"[6] Sort By Added Date\n"
			"[7] Sort By Added Time\n"
			"[8] Archived Stock\n"
			"[0] BACK\n"
		);
		checkedOpt = inputOpt(opt, 0, 8);
		switch (checkedOpt) {
		case 1:
			displayAllStock(stock, size); break;
		case 2:
			sortByID(stock, size); break;
		case 3:
			sortByCostPrice(stock, size); break;
		case 4:
			sortBySellPrice(stock, size); break;
		case 5:
			sortByQtyInStock(stock, size); break;
		case 6:
			sortByDate(stock, size); break;
		case 7:
			sortByTime(stock, size); break;
		case 8:
			sortByID(arcStock, nArcStock);
			break;
		case 0:
			return;
		}
		//conti = getYesNo("Continue to Display? (Y - Back to Search Menu / N - Back to Stock Menu) > ");
	} while (getYesNo("Continue to Display? (Y - Back to Search Menu / N - Back to Stock Menu) > "));
}

void displayAllStock(Stock stock[], int size) {
	int i;
	stockHeading();
	for (i = 0; i < size; i++) {
		printf("|%3d.| %-6s| %-30s| %-12.2lf| %-12.2lf| %-20d| %-15d| %-18d| %02d-%02d-%d  %02d:%02d |\n", i + 1, stock[i].prodID, stock[i].prodName, stock[i].costPrice, stock[i].sellPrice, stock[i].qtyInStock, stock[i].minLvl, stock[i].reorderQty, stock[i].sysDate.day, stock[i].sysDate.month, stock[i].sysDate.year, stock[i].sysTime.hour, stock[i].sysTime.min);
	}
	printf("+====+=======+===============================+=============+=============+=====================+================+===================+===================+\n");
	printf(" < %d Row(s) Created >\n\n", i);
	
}

void displaySingleStock(Stock stock) {
	stockHeading();
	printf("| 1. | %-6s| %-30s| %-12.2lf| %-12.2lf| %-20d| %-15d| %-18d| %02d-%02d-%d  %02d:%02d |\n", stock.prodID, stock.prodName, stock.costPrice, stock.sellPrice, stock.qtyInStock, stock.minLvl, stock.reorderQty, stock.sysDate.day, stock.sysDate.month, stock.sysDate.year, stock.sysTime.hour, stock.sysTime.min);
	printf("+====+=======+===============================+=============+=============+=====================+================+===================+===================+\n\n");
}

void sortByID(Stock stock[], int nStock) {
	Stock copy[MAX_STOCK], temp;
	int a;
	for (a = 0; a < nStock; a++) {
		copy[a] = stock[a];
	}
	if (a == 0) {
		noRecordMsg();
		return;
	}
	//displayAllStock(stock, nStock); printf("\n");
	for (int i = 0; i < nStock - 1; i++) {
		for (int j = i + 1; j < nStock; j++) { //find smallest ID in each row
			if (strcmp(copy[i].prodID, copy[j].prodID) > 0) { //second string smaller than first string, will return +ve
				temp = copy[j];
				copy[j] = copy[i]; //when j smaller than i, j will interchange with i.
				copy[i] = temp;
			}
			//displaySingleStock(stock[j]); printf("\n");
		}
		//displayAllStock(stock, nStock); printf("\n");
	}
	displayAllStock(copy, nStock);
}
void sortByCostPrice(Stock stock[], int nStock) {
	Stock copy[MAX_STOCK], temp;
	for (int a = 0; a < nStock; a++) {
		copy[a] = stock[a];
	}
	for (int i = 0; i < nStock - 1; i++) {
		for (int j = i + 1; j < nStock; j++) {
			if (copy[i].costPrice > copy[j].costPrice) {
				temp = copy[j];
				copy[j] = copy[i];
				copy[i] = temp;
			}
		}
	}
	displayAllStock(copy, nStock);
}
void sortBySellPrice(Stock stock[], int nStock) {
	Stock copy[MAX_STOCK], temp;
	for (int a = 0; a < nStock; a++) {
		copy[a] = stock[a];
	}
	for (int i = 0; i < nStock - 1; i++) {
		for (int j = i + 1; j < nStock; j++) {
			if (copy[i].sellPrice > copy[j].sellPrice) {
				temp = copy[j];
				copy[j] = copy[i];
				copy[i] = temp;
			}
		}
	}
	displayAllStock(copy, nStock);
}
void sortByQtyInStock(Stock stock[], int nStock) {
	Stock copy[MAX_STOCK], temp;
	for (int a = 0; a < nStock; a++) {
		copy[a] = stock[a];
	}
	for (int i = 0; i < nStock - 1; i++) {
		for (int j = i + 1; j < nStock; j++) {
			if (copy[i].qtyInStock > copy[j].qtyInStock) {
				temp = copy[j];
				copy[j] = copy[i];
				copy[i] = temp;
			}
		}
	}
	displayAllStock(copy, nStock);
}
void sortByDate(Stock stock[], int nStock) {
	Stock copy[MAX_STOCK], temp;
	for (int a = 0; a < nStock; a++) {
		copy[a] = stock[a];
	}
	for (int i = 0; i < nStock - 1; i++) {
		for (int j = i + 1; j < nStock; j++) {
			if ((copy[i].sysDate.year > copy[j].sysDate.year)) {
				temp = copy[j];
				copy[j] = copy[i];
				copy[i] = temp;
			}
		}
		for (int k = i + 1; k < nStock; k++) {
			if ((copy[i].sysDate.month > copy[k].sysDate.month) && (copy[i].sysDate.year == copy[k].sysDate.year)) {
				temp = copy[k];
				copy[k] = copy[i];
				copy[i] = temp;
			}
		}
		for (int l = i + 1; l < nStock; l++) {
			if ((copy[i].sysDate.day > copy[l].sysDate.day) && (copy[i].sysDate.month == copy[l].sysDate.month) && (copy[i].sysDate.year == copy[l].sysDate.year)) {
				temp = copy[l];
				copy[l] = copy[i];
				copy[i] = temp;
			}
		}
	}
	displayAllStock(copy, nStock);
}
void sortByTime(Stock stock[], int nStock) {
	Stock copy[MAX_STOCK], temp;
	for (int a = 0; a < nStock; a++) {
		copy[a] = stock[a];
	}

	for (int i = 0; i < nStock - 1; i++) {
		for (int j = i + 1; j < nStock; j++) {
			if (copy[i].sysTime.hour > copy[j].sysTime.hour) {
				temp = copy[j];
				copy[j] = copy[i];
				copy[i] = temp;
			}
		}
		for (int k = i + 1; k < nStock; k++) {
			if ((copy[i].sysTime.min > copy[k].sysTime.min) && (copy[i].sysTime.hour == copy[k].sysTime.hour)) {
				temp = copy[k];
				copy[k] = copy[i];
				copy[i] = temp;
			}
		}
	}

	displayAllStock(copy, nStock);
}

/* -------------------- 5 Update -------------------- */
void updateStockStatus(Stock* stock, int* nStock, Stock* archivedStock, int* nArcStock) {
	char opt[50], tempID[6];
	int location, yesNo, checkedOpt, conti;

	do {
		printf(
			"=======================\n"
			" Update Stock Status\n"
			"=======================\n"
			"[1] From Active Stock\n"
			"[2] From Archived Stock\n"
			"[0] BACK\n"
		);
		checkedOpt = inputOpt(opt, 0, 2);

		switch (checkedOpt) {
		case 0:
			return;
		case 1:
			if (*nArcStock < MAX_ARCHIVED_STOCK) {
				do {
					inputID(tempID, stock, *nStock, &location, "Enter Product ID you wish to archive > ");
					if (location == -1) {
						errorMsg("Reason: No Such Product ID");
					}
					else
						displaySingleStock(stock[location]);
				} while (location == -1);

				yesNo = getYesNo("Do you want to archive it from active stock? (Y/N) > ");
				switch (yesNo) {
				case 1:
					strcpy(stock[location].status, "Archived");
					archivedStock[*nArcStock] = stock[location];
					*nArcStock += 1;
					*nStock -= 1;
					for (int i = 0; i < *nStock; i++) {
						stock[location + i] = stock[location + i + 1];
					}
					writeStockFile(stock, *nStock, archivedStock, *nArcStock);
					break;
				case 0:
					notSavedMsg();
					break;
				}
			}
			else {
				printf("Number of Archived Stock FULL T.T\n\n");
			}
			break;
		case 2:
			if (*nStock < MAX_STOCK) {
				do {
					inputID(tempID, archivedStock, *nArcStock, &location, "Enter Product ID you wish to active > ");
					if (location == -1) {
						errorMsg("Reason: No Such Product ID");
					}
					else
						displaySingleStock(archivedStock[location]);
				} while (location == -1);

				yesNo = getYesNo("Do you want to active it from archive stock? (Y/N) > ");
				switch (yesNo) {
				case 1:
					strcpy(archivedStock[location].status, "Active");
					stock[*nStock] = archivedStock[location];
					*nStock += 1;
					*nArcStock -= 1;
					for (int i = 0; i < *nArcStock; i++) {
						archivedStock[location + i] = archivedStock[location + i + 1];
					}
					writeStockFile(stock, *nStock, archivedStock, *nArcStock); 
					break;
				case 0:
					notSavedMsg();
					break;
				}
			}
			else {
				printf("Number of Active Stock FULL T.T\n\n");
			}
			break;
		}
		//conti = getYesNo("Continue to Update Stock Status? (Y/N) > ");
	} while (getYesNo("Continue to Update Stock Status? (Y/N) > "));
}

/* -------------------- 6 Report -------------------- */
void stockReport(Stock stock[], int nStock, Stock arcStock[], int nArcStock) {
	char opt[50];
	int checkedOpt;
	do {
		printf(
			"===========================\n"
			" GENERATE STOCK REPORT\n"
			"===========================\n"
			"[1] Overview Report\n"
			"[2] Low Stock Report\n"
			"[3] Products Added In Specific Period of Dates Report\n"
			"[0] BACK\n"
		);
		do {
			checkedOpt = inputOpt(opt, 0, 3);
		} while (checkedOpt == -1);
		switch (checkedOpt) {
		case 1:
			overviewReport(stock, nStock, arcStock, nArcStock);
			break;
		case 2:
			lowStockReport(stock, nStock, arcStock, nArcStock);

			break;
		case 3:
			trackDateReport(stock, nStock, arcStock, nArcStock);
			break;
		case 0:
			return;
		}
	} while (getYesNo("Continue to generate stock report? (Y - Back to Stock Report Menu / N - Back to Stock Module) > "));
}

void overviewReport(Stock stock[], int nStock, Stock arcStock[], int nArcStock) {
	printf(
		"+====+=======+===============================+===========+=====================+\n"
		"|%3s | %-6s| %-30s| %-10s| %-20s|\n"
		"+====+=======+===============================+===========+=====================+\n", "NO.", "ID", "PRODUCT NAME", "Status", "QUANTITY IN STOCK"
	);
	int i, sumStock = 0, sumArcStock = 0;
	for (i = 0; i < nStock; i++) {
		printf("|%3d.| %-6s| %-30s| %-10s|%20d |\n", i + 1, stock[i].prodID, stock[i].prodName, stock[i].status, stock[i].qtyInStock);
		sumStock += stock[i].qtyInStock;
	}
	for (int j = 0; j < nArcStock; j++) {
		printf("|%3d.| %-6s| %-30s| %-10s|%20d |\n", i + 1, arcStock[j].prodID, arcStock[j].prodName, arcStock[j].status, stock[j].qtyInStock);
		i++;
		sumArcStock = arcStock[j].qtyInStock;
	}
	printf(
		"+====+=======+===============================+===========+=====================+\n"
		"| %-55s|%20d |\n"
		"| %-55s|%20d |\n"
		"| %-55s|%20d |\n"
		"+========================================================+=====================+\n"
		" < %d Row(s) Created >\n\n", "QUANTITY IN STOCK FROM ACTIVE STOCK", sumStock, "QUANTITY IN STOCK FROM ARCHIVED STOCK", sumArcStock, "TOTAL QUANTITY IN STOCK", sumStock + sumArcStock, i);
}

void lowStockReport(Stock stock[], int nStock, Stock arcStock[], int nArcStock) {
	int t1 = 0, t2 = 0;
	Stock tempStock[MAX_STOCK], tempArcStock[MAX_ARCHIVED_STOCK];
	printf(
		"+=======================================================================================================================================================+\n"
		"| %150s|\n"
		"| %-150s|\n"
		"| %150s|\n"
		"+=======================================================================================================================================================+\n", " ", "PRODUCT(S) THAT HITTED OR NEAR TO MINIMUM LEVEL", " "
	);
	printf("FROM ACTIVE STOCK\n");
	for (int i = 0; i < nStock; i++) {
		if ((stock[i].qtyInStock == stock[i].minLvl) || (stock[i].qtyInStock - stock[i].minLvl <= 20)) {
			tempStock[t1] = stock[i];
			t1++;
		}
	}
	if (t1 > 0)
		sortByQtyInStock(tempStock, t1);
	else
		noRecordMsg();

	printf("FROM ARCHIVED STOCK\n");
	for (int i = 0; i < nArcStock; i++) {
		if ((arcStock[i].qtyInStock == arcStock[i].minLvl)|| (arcStock[i].qtyInStock - arcStock[i].minLvl <= 20)) {
			tempArcStock[t2] = arcStock[i];
			t2++;
		}
	}
	if (t2 > 0)
		sortByQtyInStock(tempArcStock, t2);
	else
		noRecordMsg();
}

void trackDateReport(Stock stock[], int nStock, Stock arcStock[], int nArcStock) {
	Date startDate, endDate;
	int checkedDate;
	do {
		checkedDate = inputTwoDates(&startDate, &endDate);
		switch (checkedDate) {
		case 0:
			errorMsg("Reason: End Date early than Start Date");
			break;
		case 1:
			displayByDates(startDate, endDate, stock, nStock, arcStock, nArcStock);
			break;
		}
	} while (checkedDate == -1);
}

void displayByDates(Date startDate, Date endDate, Stock stock[], int nStock, Stock arcStock[], int nArcStock) {
	int count = 0, sumQty = 0;
	Stock temp[MAX_STOCK + MAX_ARCHIVED_STOCK];
	for (int i = 0; i < nStock; i++) {
		if (compareDate(startDate, stock[i].sysDate) == 1 && compareDate(stock[i].sysDate, endDate) == 1) {
			temp[count] = stock[i];
			count++;
		}
	}
	for (int k = 0; k < nArcStock; k++) {
		if (compareDate(startDate, arcStock[k].sysDate) == 1 && compareDate(arcStock[k].sysDate, endDate) == 1) {
			temp[count] = arcStock[k];
			count++;
		}
	}
	if (count == 0) {
		noRecordMsg();
	}
	else {
		printf(
			"+====+=======+===============================+===================+===========+\n"
			"|%3s | %-6s| %-30s| %-17s | %-10s|\n"
			"+====+=======+===============================+===================+===========+\n", "NO.", "ID", "PRODUCT NAME", "ADDED DATE & TIME", "Status"
		);
		int j;
		for (j = 0; j < count; j++) {
			printf("|%3d.| %-6s| %-30s| %02d-%02d-%d  %02d:%02d | %-10s|\n", j + 1, temp[j].prodID, temp[j].prodName, temp[j].sysDate.day, temp[j].sysDate.month, temp[j].sysDate.year, temp[j].sysTime.hour, temp[j].sysTime.min, temp[j].status);
		}
		printf("+====+=======+===============================+===================+===========+\n");
		printf(" < %d Row(s) Created >\n\n", j);
	}
}