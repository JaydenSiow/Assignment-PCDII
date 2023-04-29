#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<windows.h>
#include"stockDeclarations.h"
#pragma warning(disable:4996)

void stockmain() {
	StockInfo stock[MAX_STOCK_SIZE];
	int size = 0, opt;

	readStockFile(stock, &size);
	do {
		CLS;
		title("STOCK INFORMATION"); ENTER;
		stockLogo(); ENTER;
		line(); ENTER;
		makeMiddle("You would like to :", PAGE_WIDTH); ENTER; ENTER;
		line();
		stockMainMenu();
		do {
			switch (opt = promptInteger("\nEnter your selection (0-6) : ")) {
			case 1:
				addStock(stock, &size);	break;
			case 2:
				searchStock(stock, &size); break;
			case 3:
				modifyStock(stock, &size); break;
			case 4:
				displayStock(stock, &size); break;
			case 5:
				deleteStock(stock, &size); break;
			case 6:
				stockReport(stock, &size); break;
			case 0:
				return;
			default:
				errorM("Input! Please Enter Integer (0-6) Only");
			}
		} while (opt < 0 || opt>6);
	} while (opt != 7);
}

void stockMainMenu() {
	
	printf(
		"1. Add Stock\n"
		"2. Search Stock\n"
		"3. Modify Stock\n"
		"4. Display Stock\n"
		"5. Delete Stock\n"
		"6. Stock Report\n"
		"0. BACK\n"
	);
}
void searchStockMenu(char heading[]) {
	title(heading);
	printf(
		"1. Search By Product ID\n"
		"2. Search By Product Name\n"
		"0. BACK\n"
	);
}
void modifyStockMenu(StockInfo* modified) {
	title("MODIFY STOCK FUNCTION");
	displaySingleStock(modified);
	printf(
		"1. Product ID\n"
		"2. Product Name\n"
		"3. Cost Price\n"
		"4. Sell Price\n"
		"5. Minimum Level\n"
		"6. Quantity In Stock\n"
		"7. Added Date\n"
		"8. Added Time\n"
		"0. BACK\n"
	);
}
void stockReportMenu() {
	title("STOCK REPORT");
	printf(
		"1. Low Stock Report\n"
		"2. Date Range Report\n"
		"0. BACK\n"
	);
}

void noRecordMsg() {
	printf("\nNo Such Record Found...\n");
}
//void errorM() {
//	printf(RED"\aInvalid!\n\n"RESET);
//}
void savedMsg() {
	printf("\nRecord Saved Successfully...\n");
}
void notSavedMsg() {
	printf("\nRecord Will Not Be Saved...\n");
}
void stockFullMsg() {
	printf("\nStock Full...\n");
}
void existedMsg() {
	printf("Product Existed In File!\n\n");
}

void readStockFile(StockInfo stock[], int* nStock) {
	FILE* fp = fopen(STOCK_FILENAME, "r");
	if (fp == NULL) {
		printf("Unable to open %s file\n", STOCK_FILENAME);
		return;
	}
	while (fscanf(fp, "%[^,], %[^,], %lf, %lf, %d, %d, %d-%d-%d, %d:%d\n", stock[*nStock].prodID, stock[*nStock].prodName, &stock[*nStock].costPrice, &stock[*nStock].sellPrice, &stock[*nStock].qtyInStock, &stock[*nStock].minLvl, &stock[*nStock].addedDate.day, &stock[*nStock].addedDate.month, &stock[*nStock].addedDate.year, &stock[*nStock].addedTime.hour, &stock[*nStock].addedTime.min) != EOF) {
		*nStock += 1;
	}
	fclose(fp);
}
void writeStockFile(StockInfo stock[], int* nStock) {
	FILE* fp = fopen(STOCK_FILENAME, "w");
	if (fp == NULL) {
		printf("Unable to open %s file\n", STOCK_FILENAME);
		return;
	}
	sortIDInAscending(stock, nStock);
	for (int i = 0; i < *nStock; i++) {
		fprintf(fp, "%s, %s, %.2lf, %.2lf, %d, %d, %d-%d-%d, %d:%d\n", stock[i].prodID, stock[i].prodName, stock[i].costPrice, stock[i].sellPrice, stock[i].qtyInStock, stock[i].minLvl, stock[i].addedDate.day, stock[i].addedDate.month, stock[i].addedDate.year, stock[i].addedTime.hour, stock[i].addedTime.min);
	}
	fclose(fp);
}

void prompt(char input[], char question[]) {
	printf("%s", question);
	rewind(stdin);
	fgets(input, STRSIZE, stdin);
}

int promptYesNo(char question[]) {
	char input[STRSIZE];
	int invalid;
	do {
		prompt(input, question);
		if (invalid = !checkYesNo(input)) 
			errorM("Input Please Enter Y/N only");
	} while (invalid);
	return (toupper(input[0]) == 'Y') ? 1 : 0;
}
int checkYesNo(char input[]) {
	if (checkFormatFor(CHAR, input)) 
		return (toupper(input[0]) == 'Y' || toupper(input[0]) == 'N') ? 1 : 0;
	else return 0;
}

double promptDecimal(char question[]) {
	char option[STRSIZE];
	int invalid;
	do {
		prompt(option, question);
		if (invalid = !checkFormatFor(DOUBLE, option))
			errorM("Input Please Enter Number Only");
	} while (invalid);
	return decimalConverter(option);
}
double decimalConverter(char input[]) {
	int dot = 0, length = strlen(input);
	double num = 0;
	//locate dot
	for (int i = 0; i < length; i++) {
		if (input[i] == '.') {
			dot = i;
			break;
		}
	}
	if (dot == 0)
		dot = length;

	if (input[0] == '-') { //negative
		for (int j = 1; j < length; j++) {
			if (input[j] == '.')
				continue;
			else if (j < dot)
				num += (int)(input[j] - 48) * pow(10, dot - j - 1);
			else if (input[j] != '\0')
				num += (int)(input[j] - 48) / pow(10, j - dot);
		}
		return -num;
	}
	else { // positive
		for (int j = 0; j < length; j++) {
			if (input[j] == '.')
				continue;
			else if (j < dot)
				num += (int)(input[j] - 48) * pow(10, dot - j - 1);
			else if (input[j] != '\0')
				num += (int)(input[j] - 48) / pow(10, j - dot);
		}
		return num;
	}
}

int promptInteger(char question[]) {
	int invalid;
	double num;
	do {
		num = promptDecimal(question);
		if (invalid = !integerChecker(num))
			errorM("Input Please Enter Integer Only");
	} while (invalid);
		return (int)num;
}
int integerChecker(double input) {
	return (ceil(input) - floor(input) == 0) ? 1 : 0;
}

void promptID(char id[], char question[]) {
	int invalid;
	do {
		prompt(id, question);
		(invalid = !validateProductID(id))? errorM("Input Please Enter Proper Product ID Format (EXP: P001)") : capitalizeString(id);
	} while (invalid);
}
int validateProductID(char input[]) {
	if (checkFormatFor(PRODUCT_ID, input))
		return (((input[1] - 48) * 100) + ((input[2] - 48) * 10) + (input[3] - 48)) == 0 ? 0 : 1;
	else return 0;
}

void promptName(char name[], char question[]) {
	int invalid;
	do {
		prompt(name, question);
		(invalid = !checkFormatFor(ITEM_NAME, name))? errorM("Input PLease Enter At Least One Alphabet") : capitalizeString(name);
	} while (invalid);
}
void capitalizeString(char input[]) {
	input = strlwr(input);
	input[0] = toupper(input[0]);
	for (int i = 0; i < strlen(input); i++) {
		if (input[i] == ' ')
			input[i + 1] = toupper(input[i + 1]);
	}
}

void promptDate(Date* date, char question[]) {
	int invalid;
	char temp[STRSIZE];
	do {
		prompt(temp, question);
		if (invalid = !checkFormatFor(DATE, temp))
			errorM("Input Please Enter Correct Date Format (DD/MM/YYYY)");
		else {
			*date = dateConverter(temp);
			if (invalid = !checkDate(*date))
				errorM("Input Please Enter A Valid Date Range");
		}
	} while (invalid);
	
}
Date dateConverter(char input[]) {
	Date temp = { 0 };
	int punct1 = 0, punct2 = 0, length = strlen(input);
	char day[STRSIZE], month[STRSIZE], year[STRSIZE];
	for (int i = 0; i < length; i++) {
		if (input[i] == '/' || input[i] == '-' || input[i] == ' ' || input[i] == '.') {
			if (punct1 > 0) {
				punct2 = i;
				break;
			}
			else if (punct1 == 0) 
				punct1 = i;
		}
	}
	for (int i = 0; i < punct1 + 1; i++) {
		if (isdigit(input[i]))
			day[i] = input[i];
		else {
			day[i] = '\0';
			break;
		}
	}
	for (int i = 0, j = punct1+1; i < punct2; i++,j++) {
		if (isdigit(input[j]))
			month[i] = input[j];
		else {
			month[i] = '\0';
			break;
		}
	}
	for (int i = 0, j = punct2+1; i < length; i++,j++) {
		if (isdigit(input[j]))
			year[i] = input[j];
		else {
			year[i] = '\0';
			break;
		}
	}
	temp.day = (int)decimalConverter(day);
	temp.month = (int)decimalConverter(month);
	temp.year = (int)decimalConverter(year);
	return temp;
}
int checkDate(Date date) {
	SYSTEMTIME t;
	GetLocalTime(&t);
	if ((date.day < 1 || date.day>31) || (date.month < 1 || date.month>12) || (date.year < MIN_PROD_YEAR || date.year>t.wYear)) 
		return 0;
	else if (date.year == t.wYear) {
		if (date.month > t.wMonth)
			return 0;
		else if (date.month == t.wMonth) {
			if (date.day > t.wDay)
				return 0;
			else return 1;
		}
		else return 1;
	}
	else {
		if ((date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12) && date.day <= 31)
			return 1;
		else if ((date.month == 2 || date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) && date.day <= 30) {
			if ((date.year % 4 == 0 && date.month == 2 && date.day > 29) || (date.year % 4 != 0 && date.month == 2 && date.day > 28))
				return 0;
			else
				return 1;
		}
		else
			return 0;
	}
}

void promptTime(Time* time, char question[]) {
	char input[STRSIZE];
	int invalid;
	do {
		prompt(input, question);
		if (invalid = !checkFormatFor(TIME, input))
			errorM("Input Please Enter Correct Time Format (HH:MM)");
		else {
			*time = timeConverter(input);
			if (invalid = !checkTime(*time))
				errorM("Input Please Enter Valid Time Dange");
		}
	} while (invalid);
}
int checkTime(Time time) {
	if (time.hour >= 0 && time.hour < 24) {
		return (time.min >= 0 && time.min < 60) ? 1 : 0;
	}
	else return 0;
}
Time timeConverter(char input[]) {
	Time temp;
	int punct = 0, length = strlen(input);
	char h[STRSIZE], m[STRSIZE];
	for (int i = 0; i < length; i++) {
		(input[i] == ':' || input[i] == '.') ? punct = i : i;
	}
	for (int i = 0; i < punct + 1; i++) {
		if (isdigit(input[i]))
			h[i] = input[i];
		else {
			h[i] = '\0';
			break;
		}
	}
	for (int i = 0; i < length; i++) {
		if (isdigit(input[punct + 1])) {
			m[i] = input[++punct];
		}
		else {
			m[i] = '\0'; break;
		}
	}
	temp.hour = (int)decimalConverter(h);
	temp.min = (int)decimalConverter(m);
	return temp;
}

void cleanLeadingSpace(char input[]) {
	int i = 0, j = 0;
	for (i; input[i] == ' '; i++); //locate the leading space 
	if (i > 0) {
		while (input[i] != '\0') 
			input[j++] = input[i++];
		input[j] = '\0';
	}
}
void cleanEndingSpace(char input[]) {
	int length = strlen(input);
	while (length > 0 && isspace(input[length - 1])) 
		input[--length] = '\0';
}

int checkFormatFor(const char type[], char input[]) {

	cleanLeadingSpace(input);
	cleanEndingSpace(input);
	int i = 0, length = strlen(input);
	if (strcmp(type, PRODUCT_ID) == 0) {
		return ((isalpha(input[i]) && isdigit(input[i + 1]) && isdigit(input[i + 2]) && isdigit(input[i + 3]) && input[i + 4] == '\0') || (tolower(input[i]) == 'x' && input[i + 1] == '\0')) ? 1 : 0;
	}
	else if (strcmp(type, ITEM_NAME) == 0) {
		if (length > 30)
			return 0;
		int alp = 0;
		for (int j = 0; j < length; j++) {
			if (isalpha(input[j]))
				alp++;
		}
		return alp == 0 ? 0 : 1;
	}
	else if (strcmp(type, CHAR) == 0) {
		int c = 0;
		for (int j = 0; j < length; j++) {
			if (isdigit(input[j]) || ispunct(input[j]))
				return 0;
			else if (isalpha(input[j]))
				c++;
			if (c > 1)
				return 0;
		}
		return 1;
	}
	else if (strcmp(type, DOUBLE) == 0) {

		if (!isdigit(input[i]) && input[i] != '-')
			return 0;

		int dot = 0, negative, digit = 0;

		if (input[i] == '-') negative = 1;
		else negative = 0;

		for (int k = i + negative; k < length; k++) {
			if (isdigit(input[k]))
				digit++;
			else if (input[k] == '.' && dot == 0)
				dot++;
			else return 0;
		}
		if (digit > 0)
			return 1;
		else return 0;
	}
	else if (strcmp(type, DATE) == 0) {
		if (length < 8)
			return 0;
		int punct = 0, day = 0, month = 0, year = 0;
		for (i; i < length; i++) {
			if (isdigit(input[i])) {
				if (punct == 0)
					day++;
				else if (punct == 1)
					month++;
				else if (punct == 2)
					year++;
				else return 0;
			}
			else if (input[i] == '/' || input[i] == '-' || input[i] == ' ' || input[i] == '.')
				punct++;
			else return 0;
		}
		return (day > 0 && month > 0 && year >= 4 && punct == 2) ? 1 : 0;
	}
	else if (strcmp(type, TIME) == 0) {
		if (length < 3)
			return 0;
		int punct = 0, h = 0, m = 0;
		for (i; i < length; i++) {
			if (isdigit(input[i])) {
				if (punct == 0)
					h++;
				else if (punct == 1)
					m++;
				else return 0;
			}
			else if (input[i] == ':' || input[i] == '.')
				punct++;
			else return 0;
		}
		return(h > 0 && m > 0 && punct == 1) ? 1 : 0;
	}
	else return 0;
}

double promptPrice(char question[]) {
	double temp;
	do {
		temp = promptDecimal(question);
		if (temp <= 0)
			errorM("Input Price Less than or queal to 0");
	} while (temp <= 0);
	return temp;
}
int promptQty(char question[]) {
	int temp;
	do {
		temp = promptInteger(question);
		if (temp < 0)
			errorM("Input! Quantity Cannot less than 0");
	} while (temp <0);
	return temp;
}

void addStock(StockInfo stock[], int* size) {
	StockInfo temp;
	int index, invalidBuffer;
	do {
		CLS;
		if (*size < MAX_STOCK_SIZE) {
			do {
				title("STOCK INFORMATION"); ENTER;
				promptID(temp.prodID, "Enter Product ID (X to EXIT) > ");
				index = checkExistedID(temp.prodID, stock, size);
				if (strcmp(temp.prodID, "X") == 0)
					return;
				else if (index != -1)
					existedMsg();
			} while (index != -1);
			do {
				promptName(temp.prodName, "Enter Product Name > ");
				if (invalidBuffer = checkExistedName(temp.prodName, stock, size) != -1)
					existedMsg();
			} while (invalidBuffer);

			temp.costPrice = promptPrice("Enter Product Cost Price > ");
			do {
				temp.sellPrice = promptPrice("Enter Product Sell Price > ");
			} while (!comparePriceBetween(temp.costPrice, temp.sellPrice));

			temp.minLvl = promptQty("Enter Product Minimum Level > ");
			do {
				temp.qtyInStock = promptQty("Enter Product Quantity In Stock > ");
			} while (!compareStockBetween(temp.minLvl, temp.qtyInStock));
			saveCurrentDate(&temp.addedDate);
			saveCurrentTime(&temp.addedTime);
			switch (promptYesNo("Confirm to add this stock (Y - save into file / N - BACK) > ")) {
			case 1:
				stock[*size] = temp;
				*size += 1;
				writeStockFile(stock, size);
				savedMsg();
				break;
			case 0:
				notSavedMsg(); break;
			}
		}
		else {
			title("STOCK INFORMATION"); ENTER;
			stockFullMsg();
			PAUSE; return;
		}
	} while (promptYesNo("Continue to add (Y/N)? > "));
}

int checkExistedID(char id[], StockInfo stock[], int* size) {
	for (int i = 0; i < *size; i++) {
		if (strcmp(stock[i].prodID, id) == 0)
			return i;
	}
	return -1;
}
int checkExistedName(char name[], StockInfo stock[], int* size) {
	for (int i = 0; i < *size; i++) {
		if (strcmp(stock[i].prodName, name) == 0)
			return i;
	}
	return -1;
}
int comparePriceBetween(double costPrice, double sellPrice) {
	if (sellPrice > costPrice)
		return 1;
	else {
		errorM("Input! Cost Price Cannot Greater Than Sell Price");
		return 0;
	}
}
int compareStockBetween(int minlvl, int qtyInStock) {
	if (minlvl <= qtyInStock)
		return 1;
	else {
		errorM("Quantity");
		return 0;
	}
}
void saveCurrentDate(Date* date) {
	SYSTEMTIME t;
	GetLocalTime(&t);
	date->day = t.wDay;
	date->month = t.wMonth;
	date->year = t.wYear;
}
void saveCurrentTime(Time* time) {
	SYSTEMTIME t;
	GetLocalTime(&t);
	time->hour = t.wHour;
	time->min = t.wMinute;
}

void searchStock(StockInfo stock[], int* size) {
	char buffer[STRSIZE];
	int index;
	do {
		CLS;
		title("STOCK INFORMATION"); ENTER;
		if ((index = findStock(buffer, stock, size, "SEARCH FUNCTION")) == -2)
			return;
		else
			searchedAction(&stock[index], index);
		PAUSE;
	} while (promptYesNo("Continue to search (Y/N)? > "));
}

int findStock(char find[], StockInfo stock[], int* size, char heading[]) {
	int opt;
	searchStockMenu(heading);
	do {
		switch (opt = promptInteger("\nEnter your selection (0-2) : ")) {
		case 1:
			CLS;
			title("STOCK INFORMATION"); ENTER;
			promptID(find, "Enter Product ID (X - BACK) > ");
			return isBACK(find) ? -2 : checkExistedID(find, stock, size);
			break;
		case 2:
			CLS;
			title("STOCK INFORMATION"); ENTER;
			promptName(find, "Enter Product Name (X - BACK) > ");
			return isBACK(find) ? -2 : checkExistedName(find, stock, size);
			break;
		case 0:
			return -2;
		default:
			errorM("Input Please Enter Integer (0-2) Only");
		}
	} while (opt < 0 || opt>2);
}

void searchedAction(StockInfo* stock, int index) {
	(index == -1) ? noRecordMsg() : displaySingleStock(stock);
}

int isBACK(char input[]) {
	return(strcmp(input, "X") == 0) ? 1 : 0;
}

void displayStock(StockInfo stock[], int* size) {
	CLS;
	title("STOCK INFORMATION"); ENTER;
	displayStockBy(PRODUCT_ID ITEM_NAME COST QTY MINLVL DATE TIME, stock, size);
	if (promptYesNo("Display details? (Y/N) > ")) {
		for (int i = 0; i < *size; i++) {
			displaySingleStock(&stock[i]);
		}
	}
	PAUSE;
}

void displayStockBy(char column[], StockInfo stock[], int* size) {
	int i;
	headingLine(column);
	columnsHeading(column);
	headingLine(column);
	for (i = 0; i < *size; i++) {
		printf("|%3d.|", i + 1);
		if (strstr(column, PRODUCT_ID)) 
			printf(" %-6s|", stock[i].prodID);
		if (strstr(column, ITEM_NAME))
			printf(" %-30s|", stock[i].prodName);
		if (strstr(column, COST)) 
			printf(" %-15.2lf|", stock[i].costPrice);
		if (strstr(column, SELL)) 
			printf(" %-15.2lf|", stock[i].sellPrice);
		if (strstr(column, QTY)) 
			printf(" %-20d|", stock[i].qtyInStock);
		if (strstr(column, MINLVL)) 
			printf(" %-15d|", stock[i].minLvl);
		if (strstr(column, DATE TIME)) 
			printf(" %02d-%02d-%d  %02d:%02d |", stock[i].addedDate.day, stock[i].addedDate.month, stock[i].addedDate.year, stock[i].addedTime.hour, stock[i].addedTime.min);
		ENTER;
	}
	headingLine(column);
	numberOfRows(i);
}
void columnsHeading(char column[]) {	
	printf("| %-3s|", "NO.");
	if (strstr(column, PRODUCT_ID)) 
		printf(" %-6s|", "ID");
	if (strstr(column, ITEM_NAME)) 
		printf(" %-30s|", "PRODUCT NAME");
	if (strstr(column, COST)) 
		printf(" %-15s|", "COST PRICE(RM)");
	if (strstr(column, SELL)) 
		printf(" %-15s|", "SELL PRICE(RM)");
	if (strstr(column, QTY)) 
		printf(" %-20s|", "QUANTITY IN STOCK");
	if (strstr(column, MINLVL)) 
		printf(" %-15s|", "MINIMUM LEVEL");
	if (strstr(column, DATE TIME)) 
		printf(" %-18s|", "ADDED DATE & TIME");
	ENTER;
}
void headingLine(char column[]) {
	printf("+====");
	if (strstr(column, PRODUCT_ID)) 
		printf("+=======");
	if (strstr(column, ITEM_NAME)) 
		printf("+===============================");
	if (strstr(column, COST)) 
		printf("+================");
	if (strstr(column, SELL)) 
		printf("+================");
	if (strstr(column, QTY)) 
		printf("+=====================");
	if (strstr(column, MINLVL)) 
		printf("+================");
	if (strstr(column, DATE TIME)) 
		printf("+===================");
	printf("+\n");
}
void numberOfRows(int rows) {
	printf(" < %d Record(s) Found >\n\n", rows);
}

void displaySingleStock(StockInfo* stock) {
	printf(
		"\n%-20s: %s\n"
		"%-20s: %s\n"
		"%-20s: %.2lf\n"
		"%-20s: %.2lf\n"
		"%-20s: %d\n"
		"%-20s: %d\n"
		"%-20s: %02d-%02d-%4d\n"
		"%-20s: %02d:%02d\n\n", "Product ID", stock->prodID, "Product Name", stock->prodName, "Cost Price", stock->costPrice, "Sell Price", stock->sellPrice, "Minimum Level", stock->minLvl, "Quantity In Stock", stock->qtyInStock, "Added Date", stock->addedDate.day, stock->addedDate.month, stock->addedDate.year, "Added Time", stock->addedTime.hour, stock->addedTime.min
	);
}
void sortIDInAscending(StockInfo stock[], int *size) {
	StockInfo temp;
	for (int i = 0; i < *size - 1; i++) {
		for (int j = i + 1; j < *size; j++) {
			if (strcmp(stock[i].prodID, stock[j].prodID) > 0) {
				temp = stock[j];
				stock[j] = stock[i];
				stock[i] = temp;
			}
		}
	}
}

void modifyStock(StockInfo stock[], int* size) {
	int index, newIndex;
	char buffer[STRSIZE];
	StockInfo temp;
	char str[STRSIZE], attributes[STRSIZE] = {" "};
	int invalid;
	do {
		CLS;
		if ((index = findStock(buffer, stock, size, "CHOOSE A METHOD TO SEARCH A STOCK TO MODIFY")) == -2)
			return;
		else
			searchedAction(&stock[index], index);

		if (index >= 0) {
			if (promptYesNo("Want to modify (Y/N)? > ")) {
				if (!modifyStockData(&stock[index], stock, size))
					return;
				else {
					printf("Modified Product will like this:\n");
					displaySingleStock(&stock[index]);
					writeStockFile(stock, size);
				}
			}
		}
		PAUSE;
	} while (promptYesNo("Continue to modify? (Y/N) > "));
}

int modifyStockData(StockInfo* modified, StockInfo stock[], int* size) {
	int existed, tempQty;
	char tempStr[STRSIZE];
	double tempPrice;
	Date tempDate;
	Time tempTime;
	int opt;
	modifyStockMenu(modified);
	do {
		switch (opt = promptInteger("Option: ")) {
		case 1:
			do {
				promptID(tempStr, "Enter Product ID > ");
				if (!strcmp(tempStr, modified->prodID))
					(promptYesNo("Same Product ID Input... Still use it? (Y/N) > ")) ? (existed = 0) : (existed = 1);
				else if (!strcmp(tempStr, "X")) {
					errorM("Input Please Proper Product ID Format (EXP: P001)");
					existed = 1;
				}
				else if (checkExistedID(tempStr, stock, size) >= 0) {
					existedMsg();
					existed = 1;
				}
				else existed = 0;
			} while (existed);
			strcpy(modified->prodID, tempStr);
			break;
		case 2:
			do {
				promptName(tempStr, "Enter Product Name > ");
				if (!strcmp(tempStr, modified->prodName))
					(promptYesNo("Same Product Name Input... Still use it? (Y/N) > ")) ? (existed = 0) : (existed = 1);
				else if (checkExistedName(tempStr, stock, size) >= 0) {
					existedMsg();
					existed = 1;
				}
				else existed = 0;
			} while (existed);
			updateChangesToSales(modified->prodName, tempStr);
			strcpy(modified->prodName, tempStr);
			break;
		case 3:
			do {
				tempPrice = 0;
				tempPrice = promptPrice("Enter Cost Price > ");
				if (tempPrice == modified->costPrice)
					(promptYesNo("Same Cost Price Input... Still use it? (Y/N) > ")) ? (existed = 0) : (existed = 1);
				else if (!comparePriceBetween(tempPrice, modified->sellPrice))
					existed = 1;
				else
					existed = 0;
			} while (existed);
			modified->costPrice = tempPrice;
			break;
		case 4:
			do {
				tempPrice = 0;
				tempPrice = promptPrice("Enter Sell Price > ");
				if (tempPrice == modified->sellPrice)
					(promptYesNo("Same Sell Price Input... Still use it? (Y/N) > ")) ? (existed = 0) : (existed = 1);
				else if (!comparePriceBetween(modified->costPrice, tempPrice))
					existed = 1;
				else
					existed = 0;
			} while (existed);
			modified->sellPrice = tempPrice;
			break;
		case 5:
			do {
				tempQty = 0;
				tempQty = promptQty("Enter Minimum Level > ");
				if (tempQty == modified->minLvl)
					(promptYesNo("Same Minimum Level Input... Still use it? (Y/N) > ")) ? (existed = 0) : (existed = 1);
				else if (!compareStockBetween(tempQty, modified->qtyInStock))
					existed = 1;
				else
					existed = 0;
			} while (existed);
			modified->minLvl = tempQty;
			break;
		case 6:
			do {
				tempQty = 0;
				tempQty = promptQty("Enter Quantity In Stock > ");
				if (tempQty == modified->qtyInStock)
					(promptYesNo("Same Quantity In Stock Input... Still use it? (Y/N) > ")) ? (existed = 0) : (existed = 1);
				else if (!compareStockBetween(modified->minLvl, tempQty))
					existed = 1;
				else
					existed = 0;
			} while (existed);
			modified->qtyInStock = tempQty;
			break;
		case 7:
			do {
				promptDate(&tempDate, "Enter Added Date > ");
				if (compareDates(&tempDate, &modified->addedDate))
					(promptYesNo("Same Input... Still use it? (Y/N) > ")) ? (existed = 0) : (existed = 1);
				else
					existed = 0;
			} while (existed);
			modified->addedDate = tempDate;
			break;
		case 8:
			do {
				promptTime(&tempTime, "Enter Added Time > ");
				if (compareTimes(&tempTime, &modified->addedTime))
					(promptYesNo("Same Input... Still use it? (Y/N) > ")) ? (existed = 0) : (existed = 1);
				else
					existed = 0;
			} while (existed);
			modified->addedTime = tempTime;
			break;
		case 0:
			return 0;
		default:
			errorM("Input Please Enter Integer (0-8) Only");
		}
	} while (opt < 0 || opt>8);
	return 1;
}

int compareDates(Date* date1, Date* date2) {
	return ((date1->day == date2->day) && (date1->month == date2->month) && (date1->year == date2->year)) ? 1 : 0;
}
int compareTimes(Time* time1, Time* time2) {
	return ((time1->hour == time2->hour) && (time1->min == time2->min)) ? 1 : 0;
}

void updateChangesToSales(char modified[], char newName[]) {
	SalesRecord salesRecords[MAX_STOCK_SIZE];
	int numberOfSalesRecordsInFile;
	numberOfSalesRecordsInFile = obtainSalesRecordsFromFile(salesRecords);
	for (int i = 0; i < numberOfSalesRecordsInFile; i++) {
		if (strcmp(modified, salesRecords[i].itemName) == 0) {
			strcpy(salesRecords[i].itemName, newName);
		}
	}
	FILE* salesFile = openFileFor(WRITING);
	fwrite(&salesRecords, sizeof(SalesRecord), numberOfSalesRecordsInFile, salesFile);
	FILE_CLOSE;
}

void deleteStock(StockInfo stock[], int* size) {
	char buffer[STRSIZE];
	int index;
	do {
		CLS;
		title("STOCK INFORMATION"); ENTER;
		if ((index = findStock(buffer, stock, size, "CHOOSE A METHOD TO SEARCH A STOCK TO DELETE")) == -2)
			return;
		else
			searchedAction(&stock[index], index);
		if (index >= 0) {
			switch (promptYesNo("Want to delete (Y/N)? > ")) {
			case 1:
				*size -= 1;
				for (index; index < *size; index++) {
					stock[index] = stock[index + 1];
				}
				writeStockFile(stock, size);
				savedMsg();
				break;
			case 0:
				notSavedMsg();
				break;
			}
		} PAUSE;
	} while (promptYesNo("Continue to delete (Y/N)? > "));
}

void stockReport(StockInfo stock[], int* size) {
	int opt;
	do {
		CLS;
		stockReportMenu();
		do {
			switch (opt = promptInteger("\nEnter your selection (0-2) : ")) {
			case 1:
				CLS;
				lowStockReport(stock, size); 
				break;
			case 2:
				CLS;
				title("STOCK REPORT"); ENTER;
				dataRangeReport(stock, size); 
				break;
			case 0:
				return;
			default:
				errorM("Input Please Enter Integer (0-2) Only");
			}
		} while (opt < 0 || opt>2);
		PAUSE;
	} while (promptYesNo("Continue to generate report (Y/N)? > "));
}

void lowStockReport(StockInfo stock[], int* size) {
	int count = 0;
	StockInfo temp[MAX_STOCK_SIZE];

	for (int i = 0; i < *size; i++) {
		if ((stock[i].qtyInStock == stock[i].minLvl) || (stock[i].qtyInStock - stock[i].minLvl <= 20)) 
			temp[count++] = stock[i];
	}
	if (count > 0) {
		CLS;
		title("PRODUCT(S) THAT HITTED OR NEAR TO MINIMUM LEVEL"); ENTER; 
		displayStockBy(PRODUCT_ID ITEM_NAME QTY MINLVL, temp, &count);
	}
	else
		noRecordMsg();
}

void dataRangeReport(StockInfo stock[], int* size) {
	Date start, end;
	StockInfo temp[MAX_STOCK_SIZE];
	char reportTitle[STRSIZE] = "PRODUCT(S) ADDED FROM ";
	char dateString[STRSIZE];
	int count = 0;
	do {
		promptDate(&start, "Enter Start Date (DD/MM/YYYY) > ");
		promptDate(&end, "Enter End Date (DD/MM/YYYY) > ");
	} while (!checkDatesRange(start, end));

	for (int i = 0; i < *size; i++) {
		if (checkDatesRange(start, stock[i].addedDate) && checkDatesRange(stock[i].addedDate, end)) 
			temp[count++] = stock[i];
	}
	if (count == 0)
		noRecordMsg();
	else {
		CLS;
		sprintf(dateString, "%02d-%02d-%4d TO %02d-%02d-%4d", start.day, start.month, start.year, end.day, end.month, end.year);
		strcat(reportTitle, dateString);
		
		title(reportTitle); ENTER; 
		displayStockBy(PRODUCT_ID ITEM_NAME DATE TIME, temp, &count);
	}
}

int checkDatesRange(Date startDate, Date endDate) {
	if (startDate.year > endDate.year)
		return 0;
	else if ((startDate.year == endDate.year) && (startDate.month > endDate.month))
		return 0;
	else if ((startDate.year == endDate.year) && (startDate.month == endDate.month) && (startDate.day > endDate.day))
		return 0;
	else
		return 1;
}