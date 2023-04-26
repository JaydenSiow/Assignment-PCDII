#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<windows.h>
#include"stockDeclarations.h"
#pragma warning(disable:4996)

void main() {
	StockInfo stock[MAX_STOCK_SIZE];
	int size = 0, opt;

	readStockFile(stock, &size);

	char temp[STRSIZE];
	Date date;
	while (1) {
		prompt(temp, "Enter date: ");
		if (checkFormatFor(DATE, temp)) {
			date = dateConverter(temp);
			printf("%02d-%02d-%04d\n\n", date.day, date.month, date.year);
		}
		else printf("Invalid\n\n");
	}

	do {
		CLS;
		stockMainMenu();
		opt = promptInteger("Option: ");
		switch (opt) {
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
		case 7:
			return;
		default:
			invalidMsg();
		}
	} while (opt != 7);
}

void stockMainMenu() {
	printf(
		"STOCK INFORMATION MODULE\n"
		"1. Add Stock\n"
		"2. Search Stock\n"
		"3. Modify Stock\n"
		"4. Display Stock\n"
		"5. Delete Stock\n"
		"6. Stock Report\n"
		"7. BACK\n"
	);
}
void searchStockMenu() {
	printf(
		"SEARCH FUNCTION\n"
		"1. Search By Product ID\n"
		"2. Search By Product Name\n"
		"3. BACK\n"
	);
}
void displayStockMenu() {
	printf(
		"STOCK DISPLAY FUNCTION\n"
		"1. Unsorted\n"
		"2. Sorted By Product ID\n"
		"3. BACK\n"
	);
}
void stockReportMenu() {
	printf(
		"STOCK REPORT\n"
		"1. Low Stock Report\n"
		"2. Date Range Report\n"
		"3. BACK\n"
	);
}

void noRecordMsg() {
	printf("\nNo Record Found...\n");
}
void invalidMsg() {
	printf("Invalid!\n\n");
}
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
			invalidMsg();
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
			invalidMsg();
		else
			return decimalConverter(option);
	} while (invalid);
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
			invalidMsg();
		else return (int)num;
	} while (invalid);

}
int integerChecker(double input) {
	return (ceil(input) - floor(input) == 0) ? 1 : 0;
}

void promptID(char id[], char question[]) {
	int invalid;
	do {
		prompt(id, question);
		if (invalid = !validateProductID(id))
			invalidMsg();
	} while (invalid);
	capitalizeString(id);
}
int validateProductID(char input[]) {
	if (checkFormatFor(ID, input))
		return (((input[1] - 48) * 100) + ((input[2] - 48) * 10) + (input[3] - 48)) == 0 ? 0 : 1;
	else return 0;
}

void promptName(char name[], char question[]) {
	int invalid;
	do {
		prompt(name, question);
		if (invalid = !checkFormatFor(NAME, name))
			invalidMsg();
	} while (invalid);
	capitalizeString(name);
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
	int wrong;
	char c1, c2;
	do {
		wrong = 0;
		printf("%s", question);
		rewind(stdin);
		if ((scanf("%d%c%d%c%d", &date->day, &c1, &date->month, &c2, &date->year) != 5) || !checkDate(*date) || ((c1 != '-' && c1 != '/' && c1 != ' ' && c1!= '.') || (c2 != '-' && c2 != '/' & c2 != ' ' && c1 != '.'))) {
			invalidMsg();
			wrong = 1;
		}
	} while (wrong);
}

Date dateConverter(char input[]) {
	Date temp = { 0 };
	int punct1 = 0, punct2 = 0;
	char day[3], month[3], year[5];
	int i, length = strlen(input);
	for (i = 0; i < length; i++) {
		if (input[i] == '/' || input[i] == '-' || input[i] == ' ' || input[i] == '.') {
			if (punct1 > 0) {
				punct2 = i;
				break;
			}
			else if (punct1 == 0) {
				punct1 = i;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (isdigit(input[i]))
			day[i] = input[i];
		else 
			day[i] = '\0';
	}
	for (int i = 0, j = punct2 - punct1; i < 3; i++,j++) {
		if (isdigit(input[j]))
			month[i] = input[j];
		else month[i] ='\0';
	}
	for (int i = 0, j = length - punct2-1; i < 5; i++,j++) {
		if (isdigit(input[j]))
			year[i] = input[j];
		else year[i]='\0';
	}
	temp.day = (int)decimalConverter(day);
	temp.month = (int)decimalConverter(month);
	temp.year = (int)decimalConverter(year);

	return temp;
}

int checkDate(Date date) {
	SYSTEMTIME t;
	GetLocalTime(&t);
	if ((date.day < 1 || date.day>31) || (date.month < 1 || date.month>12) || (date.year < 2015 || date.year>t.wYear)) 
		return 0;
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
	int wrong;
	char c;
	do {
		wrong = 0;
		printf("%s", question);
		rewind(stdin);
		if (((scanf("%d%c%d", &time->hour, &c, &time->min) != 3) || (checkTime(*time) == -1)) || (c != ':' && c != '.' && c != ' ')) {
			invalidMsg();
			wrong = 1;
		}
	} while (wrong);
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

void cleanLeadingSpace(char input[]) {
	int i = 0, j = 0;
	for (i; input[i] == ' '; i++); //locate the leading space 
	if (i > 0) {
		while (input[i] != '\0') {
			input[j++] = input[i++];
		}
		input[j] = '\0';
	}
}
void cleanEndingSpace(char input[]) {
	int length = strlen(input);
	while (length > 0 && isspace(input[length - 1])) {
		input[--length] = '\0';
	}
}

int checkFormatFor(const char type[], char input[]) {

	cleanLeadingSpace(input);
	cleanEndingSpace(input);

	int i = 0, length = strlen(input);

	if (strcmp(type, ID) == 0) {
		if ((isalpha(input[i]) && isdigit(input[i + 1]) && isdigit(input[i + 2]) && isdigit(input[i + 3]) && input[i + 4] == '\0') || (tolower(input[i]) == 'x' && input[i + 1] == '\0'))
			return 1;
		else {
			return 0;
		}
	}
	else if (strcmp(type, NAME) == 0) {
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

		int dot = 0, negative;

		if (input[i] == '-') negative = 1;
		else negative = 0;

		for (int k = i + negative; k < length; k++) {
			if (isdigit(input[k]))
				continue;
			else if (input[k] == '.' && dot == 0)
				dot++;
			else return 0;
		}
		return 1;
	}
	else if (strcmp(type, DATE) == 0) {
		if (length < 8 || length > 10)
			return 0;
		int punct = 0;
		do {
			if (isdigit(input[i])) {
				i++;
				if (isdigit(input[i])) {
					i++;
					if (input[i] == '/' || input[i] == '-' || input[i] == ' ' || input[i] == '.') {
						i++;
						punct++;
					}
					else return 0;
				}
				else if (input[i] == '/' || input[i] == '-' || input[i] == ' ' || input[i] == '.') {
					i++;
					punct++;
				}
				else return 0;
			}
			else return 0;
			if (i > 6 && punct < 2)
				return 0;
		} while (punct < 2);
		if (isdigit(input[i]) && isdigit(input[i + 1]) && isdigit(input[i + 2]) && isdigit(input[i + 3]))
			return 1;
		else return 0;
	}
	else return 0;
}

double promptPrice(char question[]) {
	double temp;
	do {
		temp = promptDecimal(question);
		if (temp <= 0)
			invalidMsg();
	} while (temp <= 0);
	return temp;
}
int promptQty(char question[]) {
	int temp;
	do {
		temp = promptInteger(question);
		if (temp < 0)
			invalidMsg();
	} while (temp <0);
	return temp;
}

void addStock(StockInfo stock[], int* size) {
	StockInfo temp;
	int index, invalidBuffer;
	do { CLS
		if (*size < MAX_STOCK_SIZE) {
			do {
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
			stockFullMsg();
			PAUSE return;
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
		invalidMsg();
		return 0;
	}
}
int compareStockBetween(int minlvl, int qtyInStock) {
	if (minlvl <= qtyInStock)
		return 1;
	else {
		invalidMsg();
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
	int index, opt;
	do { CLS
		searchStockMenu();
		do {
			opt = promptInteger("Option: ");
			switch (opt) {
			case 1:
				CLS
				promptID(buffer, "Enter Product ID (X - BACK) > ");
				index = checkExistedID(buffer, stock, size);
				if (strcmp(buffer, "X") == 0)
					return;
				else if (index == -1)
					noRecordMsg();
				else 
					displaySingleStock(&stock[index]);
				break;
			case 2:
				CLS
				promptName(buffer, "Enter Product Name (X - BACK) > ");
				index = checkExistedName(buffer, stock, size);
				if (strcmp(buffer, "X") == 0)
					return;
				else if (index == -1)
					noRecordMsg();
				else 
					displaySingleStock(&stock[index]);
				break;
			case 3:
				return;
			default:
				invalidMsg();
			}
		} while (opt < 1 || opt>3);
		PAUSE
	} while (promptYesNo("Continue to search (Y/N)? > "));
}

void displayStock(StockInfo stock[], int* size) {
	int opt;
	do { CLS
		displayStockMenu();
		do {
			opt = promptInteger("Option: ");
			switch (opt) {
			case 1:
				CLS
				displayAllStock(stock, size); 
				break;
			case 2:
				CLS
				sortByID(stock, size); 
				break;
			case 3:
				return;
			default:
				invalidMsg();
			}
		} while (opt < 1 || opt>3);
	} while (promptYesNo("Continue to display (Y/N)? > "));
}

void displayAllStock(StockInfo stock[], int* size) {
	printf(
		"+====+=======+===============================+================+================+=====================+================+===================+\n"
		"| %-3s| %-6s| %-30s| %-15s| %-15s| %-20s| %-15s| %-18s|\n"
		"+====+=======+===============================+================+================+=====================+================+===================+\n", "NO.", "ID", "PRODUCT NAME", "COST PRICE(RM)", "SELL PRICE(RM)", "QUANTITY IN STOCK", "MINIMUM LEVEL", "ADDED DATE & TIME"
	);
	int i;
	for (i = 0; i < *size; i++) {
		printf("|%3d.| %-6s| %-30s| %-15.2lf| %-15.2lf| %-20d| %-15d| %02d-%02d-%d  %02d:%02d |\n", i + 1, stock[i].prodID, stock[i].prodName, stock[i].costPrice, stock[i].sellPrice, stock[i].qtyInStock, stock[i].minLvl, stock[i].addedDate.day, stock[i].addedDate.month, stock[i].addedDate.year, stock[i].addedTime.hour, stock[i].addedTime.min);
	}
	printf("+====+=======+===============================+================+================+=====================+================+===================+\n");
	printf(" < %d Record(s) Found >\n\n", i);
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
		"%-20s: %02d:%02d\n\n", "Product ID", stock->prodID, "Product Name", stock->prodName, "Cost Price", stock->costPrice, "Sell Price", stock->sellPrice, "Quantity In Stock", stock->qtyInStock, "Minimum Level", stock->minLvl, "Added Date", stock->addedDate.day, stock->addedDate.month, stock->addedDate.year, "Added Time", stock->addedTime.hour, stock->addedTime.min
	);
}
void sortByID(StockInfo stock[], int *size) {
	StockInfo copy[MAX_STOCK_SIZE], temp;
	int a;
	for (a = 0; a < *size; a++) {
		copy[a] = stock[a];
	}
	if (a == 0) {
		noRecordMsg();
		PAUSE
		return;
	}
	for (int i = 0; i < *size - 1; i++) {
		for (int j = i + 1; j < *size; j++) {
			if (strcmp(copy[i].prodID, copy[j].prodID) > 0) { 
				temp = copy[j];
				copy[j] = copy[i];
				copy[i] = temp;
			}
		}
	}
	displayAllStock(copy, size);
}

void modifyStock(StockInfo stock[], int* size) {
	int index, newIndex;
	char buffer[STRSIZE];
	StockInfo temp;
	do { CLS
		promptID(buffer, "Enter Product ID (X - BACK) > ");
		index = checkExistedID(buffer, stock, size);
		if (strcmp(buffer, "X") == 0)
			return;
		if (index == -1) {
			noRecordMsg(); 
			PAUSE continue;
		}
		else {
			displaySingleStock(&stock[index]); PAUSE
		}
		switch (promptYesNo("Want to modify (Y/N)? > ")) {
		case 1:
			do {
				ENTER
				promptID(temp.prodID, "Enter New Product ID > ");
				if (strcmp(temp.prodID, "X") == 0)
					newIndex = 0;
				newIndex = checkExistedID(temp.prodID, stock, size);
				if (newIndex == index) {
					switch (promptYesNo("Same Product ID Input... Still use it (Y/N) ? > ")) {
					case 1:
						newIndex = -1;
						break;
					case 0:
						break; 
					}
				}
				else if (newIndex >= 0) {
					existedMsg();
				}
			} while (newIndex != -1);

			do {
				promptName(temp.prodName, "Enter New Product Name > ");
				newIndex = checkExistedName(temp.prodName, stock, size);
				if (newIndex == index) {
					switch (promptYesNo("Same Product Name Input... Still use it (Y/N) ? > ")) {
					case 1:
						newIndex = -1;
						break;
					case 0:
						break; 
					}
				}
				else if (newIndex >= 0) {
					existedMsg();
				}
			} while (newIndex != -1);
			
			temp.costPrice = promptPrice("Enter Product Cost Price (RM) > ");
			do {
				temp.sellPrice = promptPrice("Enter Product Sell Price (RM) > ");
			} while (!comparePriceBetween(temp.costPrice, temp.sellPrice));
			temp.minLvl = promptQty("Enter Product Minimum Level > ");
			do {
				temp.qtyInStock = promptQty("Enter Product Quantity In Stock > ");
			} while (!compareStockBetween(temp.minLvl, temp.qtyInStock));

			promptDate(&temp.addedDate, "Enter New Added Date (DD/MM/YYYY) > ");
			promptTime(&temp.addedTime, "Enter New Added Time (HH:MM) > ");

			switch (promptYesNo("Confirm changes (Y/N)? > ")) {
			case 1:
				stock[index] = temp;
				writeStockFile(stock, size);
				savedMsg();
				break;
			case 0:
				notSavedMsg(); break;
			}
			PAUSE
			break;
		case 0:
			return;
		default:
			invalidMsg();
		}
	} while (promptYesNo("Continue to modify? (Y/N) > "));
}

void deleteStock(StockInfo stock[], int* size) {
	char buffer[STRSIZE];
	int index;
	do { CLS
		promptID(buffer, "Enter Product ID to Delete (X - BACK) > ");
		index = checkExistedID(buffer, stock, size);
		if (strcmp(buffer, "X") == 0)
			return;
		else if (index == -1) {
			noRecordMsg();  
		}
		else {
			displaySingleStock(&stock[index]); PAUSE
			switch (promptYesNo("Want to delete (Y/N)? > ")) {
			case 1:
				*size -= 1;
				for (index; index < *size; index++) {
					stock[index] = stock[index + 1];
				}
				savedMsg();
				break;
			case 0:
				notSavedMsg();
				break;
			}
		} PAUSE
	} while (promptYesNo("Continue to delete (Y/N)? > "));
}

void stockReport(StockInfo stock[], int* size) {
	int opt;
	do { CLS
		stockReportMenu();
		do {
			opt = promptInteger("Option: ");
			switch (opt) {
			case 1:
				CLS;
				lowStockReport(stock, size); 
				break;
			case 2:
				CLS;
				dataRangeReport(stock, size); 
				break;
			case 3:
				return;
			default:
				invalidMsg();
			}
		} while (opt < 0 || opt>2);
		PAUSE;
	} while (promptYesNo("Continue to generate report (Y/N)? > "));
}

void lowStockReport(StockInfo stock[], int* size) {
	int count = 0;
	StockInfo temp[MAX_STOCK_SIZE];

	for (int i = 0; i < *size; i++) {
		if ((stock[i].qtyInStock == stock[i].minLvl) || (stock[i].qtyInStock - stock[i].minLvl <= 20)) {
			temp[count] = stock[i];
			count++;
		}
	}
	if (count > 0) {
		CLS
		printf(
			"+=========================================================================================================================================+\n"
			"| %136s|\n"
			"|                                             PRODUCT(S) THAT HITTED OR NEAR TO MINIMUM LEVEL                                             |\n"
			"| %136s|\n"
			"+=========================================================================================================================================+\n\n", " ", " "
		);
		sortByID(temp, &count);
	}
	else
		noRecordMsg();
}

void dataRangeReport(StockInfo stock[], int* size) {
	Date start, end;
	StockInfo temp[MAX_STOCK_SIZE];
	int count = 0;
	do {
		promptDate(&start, "Enter Start Date (DD/MM/YYYY) > ");
		promptDate(&end, "Enter End Date (DD/MM/YYYY) > ");
	} while (!compareDate(start, end));

	for (int i = 0; i < *size; i++) {
		if (compareDate(start, stock[i].addedDate) == 1 && compareDate(stock[i].addedDate, end) == 1) {
			temp[count++] = stock[i];
		}
	}
	if (count == 0)
		noRecordMsg();
	else {
		CLS
		printf(
			"+=========================================================================================================================================+\n"
			"| %136s|\n"
			"|                                              PRODUCT(S) ADDED FROM %02d-%02d-%4d TO %02d-%02d-%4d                                             |\n"
			"| %136s|\n"
			"+=========================================================================================================================================+\n\n", " ", start.day, start.month, start.year, end.day, end.month, end.year, " "
		);
		sortByID(temp, &count);
	}
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