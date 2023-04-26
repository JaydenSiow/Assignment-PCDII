#pragma once
#define STOCK_FILENAME "StockFile.txt"
#define MAX_STOCK_SIZE 80
#define STRSIZE 200
#define PAUSE system("pause");
#define CLS system("cls");
#define ENTER printf("\n");
#define ID " product id"
#define NAME "product name"
#define DOUBLE "decimal number"
#define CHAR "single char"
#define DATE "date"
#define TIME "time"

typedef struct {
	int day, month, year;
} Date;

typedef struct {
	int hour, min;
} Time;

typedef struct {
	char prodID[5], prodName[31];
	double costPrice, sellPrice;
	int qtyInStock, minLvl;
	Date addedDate;
	Time addedTime;
}StockInfo;

//read and write file function
void readStockFile(StockInfo stock[], int* nStock);
void writeStockFile(StockInfo stock[], int* nStock);

//base function
void prompt(char input[], char question[]);
void capitalizeString(char input[]);
int checkFormatFor(const char type[], char input[]);
void cleanLeadingSpace(char input[]);
void cleanEndingSpace(char input[]);
int validateProductID(char input[]);
int promptYesNo(char question[]);
int checkYesNo(char input[]);
int promptInteger(char question[]);
int integerChecker(double input);
double promptDecimal(char question[]);
void promptID(char id[], char question[]);
void promptName(char name[], char question[]);
void promptDate(Date* date, char question[]);
int checkDate(Date date);
void promptTime(Time* time, char question[]);
int checkTime(Time time);
double promptPrice(char question[]);
int promptQty(char question[]);
double decimalConverter(char input[]);
Date dateConverter(char input[]);

//message
void noRecordMsg();
void invalidMsg();
void savedMsg();
void notSavedMsg();
void stockFullMsg();
void existedMsg();

//menu
void stockMainMenu();
void searchStockMenu();
void displayStockMenu();
void stockReportMenu();

//add stock function
void addStock(StockInfo stock[], int* size);
int checkExistedID(char id[], StockInfo stock[], int* size);
int checkExistedName(char name[], StockInfo stock[], int* size);
int comparePriceBetween(double costPrice, double sellPrice);
int compareStockBetween(int minlvl, int qtyInStock);
void saveCurrentDate(Date* date);
void saveCurrentTime(Time* time);

//search stock function
void searchStock(StockInfo stock[], int* size);

//display stock function
void displayStock(StockInfo stock[], int* size);
void displayAllStock(StockInfo stock[], int* size);
void displaySingleStock(StockInfo* stock);
void sortByID(StockInfo stock[], int* size);

//modify stock function
void modifyStock(StockInfo stock[], int* size);

//delete stock function
void deleteStock(StockInfo stock[], int* size);

//stock report function
void stockReport(StockInfo stock[], int* size);
void lowStockReport(StockInfo stock[], int* size);
void dataRangeReport(StockInfo stock[], int* size);
int compareDate(Date startDate, Date endDate);