#pragma once
/*------------------------------------------------------ shareable functions ------------------------------------------------------------------------------*/
void mainLogo();
void memberLogo();
void salesLogo();
void stockLogo();
void staffLogo();

/*------------------------------------------------------ stock module declarations ------------------------------------------------------------------------------*/
#define STOCK_FILENAME "StockFile.txt"
#define MAX_STOCK_SIZE 80
#define STRSIZE 200
#define INFINITE 999999
#define PAUSE system("pause")
#define CLS system("cls")
#define ENTER printf("\n")
#define PRODUCT_ID " id"
#define ITEM_NAME "name"
#define DOUBLE "decimal number"
#define CHAR "single char"
#define DATE "date"
#define TIME "time"
#define COST "cost"
#define SELL "sell"
#define QTY "qty"
#define MINLVL "min"
#define ALLSTOCK "id name cost sell qty min datetime"
#define MIN_PROD_YEAR 2015
#define RED "\033[0;31m"
#define RESET "\033[0m"
#define SAME_INPUT "Detected input same as previous value... Still use it(Y/N) > "

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
int checkDate(Date date);
void promptTime(Time* time, char question[]);
int checkTime(Time time);
double promptPrice(char question[]);
int promptQty(char question[]);
double decimalConverter(char input[]);
Date dateConverter(char input[]);
void promptDate(Date* date, char question[]);
Time timeConverter(char input[]);
int isBACK(char input[]);
int compareDates(Date* date1, Date* date2);
int compareTimes(Time* time1, Time* time2);

//message
void noRecordMsg();
//void errorM();
void savedMsg();
void notSavedMsg();
void stockFullMsg();
void existedMsg();

//menus
void stockMainMenu();
void searchStockMenu(char heading[]);
void modifyStockMenu(StockInfo* modified);
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
void searchedAction(StockInfo* stock, int index);
int findStock(char find[], StockInfo stock[], int* size, char heading[]);

//display stock function
void displayStock(StockInfo stock[], int* size);
void displaySingleStock(StockInfo* stock);
void sortIDInAscending(StockInfo stock[], int* size);
void numberOfRows(int rows);
void displayStockBy(char column[], StockInfo stock[], int* size);
void columnsHeading(char column[]);
void headingLine(char column[]);

//modify stock function
void modifyStock(StockInfo stock[], int* size);
void updateChangesToSales(char modified[], char newName[]);
int modifyStockData(StockInfo*, StockInfo stock[], int* size);

//delete stock function
void deleteStock(StockInfo stock[], int* size);

//stock report function
void stockReport(StockInfo stock[], int* size);
void lowStockReport(StockInfo stock[], int* size);
void dataRangeReport(StockInfo stock[], int* size);
int checkDatesRange(Date startDate, Date endDate);


/*------------------------------------------------------ sales module declarations ------------------------------------------------------------------------------*/
#pragma once
#define READING "rb"
#define WRITING "wb"
#define APPENDING "ab"
#define FILE_CLOSE fclose(salesFile)

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
FILE* openFileFor(const char* accessMode);

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

//#define READING "rb"
//#define WRITING "wb"
//#define APPENDING "ab"
//#define FILE_CLOSE fclose(salesFile)
//
//typedef struct {
//	char salesID[10];
//	char itemName[30];
//	int itemQuantity;
//	char paymentMethod[30];
//	char creditCardDetails[30];
//	double salesTax;
//	double salesTotal;
//	Date salesDate;
//}SalesRecord;
//
//void deleteRecord(SalesRecord *salesRecords, int indexOfRecord, int numberOfRecordsInFile);
//char yesOrNoFunction(const char enquiry[]);
//void deleteARecord(SalesRecord* salesRecords, int numberOfRecordsInFile);
//void loopMainFunctions(void (*functions[])(), int option);
//void writeRecordsIntoFile(SalesRecord* salesRecords, int numberOfRecordsInFile);
//void promptsAndErrorMessages(int* loopCount, int errorMessage);
//
//
//void menuOption(void (*functions[])(), int whichMenu);
//void call(int whichMenu);
//
////Retrieve Records from File
//int numberOf(SalesRecord* row, FILE* salesFile);
//
////Format for File Opening
//FILE* openFileFor(const char* accessMode);
//
////Display Menu and Obtain Option
//int obtainOptionFor(int whichMenu, int lowerLimit, int upperLimit);
//
////Main Menu
//void mainMenuDesign();
//
////Auto-Generation of SalesID
//void generateSalesId(SalesRecord* salesRecord);
//
////Table of Displaying Sales Records
//void tableHeaderForDisplayingSalesRecords();
//void displayAllSalesRecordsFromFile(SalesRecord* salesRecords, int numberOfRecordsInFile);
//void displayRecordsOrRecord(SalesRecord line[], int loopCount);
//
////Obtain Sales Records from Binary File
//int obtainSalesRecordsFromFile(SalesRecord* salesRecords);
//
////Search For Specific Record In File
//int searchARecord(SalesRecord* salesRecords, int numberOfRecordsInFile);
//
////Add A Record Into the File
//void addARecord();
//
////Obtain Sales Data For Adding A Record or Modifying One
//void obtainDate(SalesRecord* salesRecord);
//void obtainQuantity(SalesRecord* salesRecord);
//void obtainPaymentMethod(SalesRecord* salesRecord);
//void obtainCreditCardDetails(SalesRecord* salesRecord);
//
////Modification Module
//void modifyARecord(SalesRecord* salesRecords, int numberOfRecordsInFile);
//void dataModifyMenu(SalesRecord* row);
//void dataModificationMenu();
//
////Validation Of the Sales Data Entered By User
//int validateIfIsValidDate(Date* dateOfSale);
//
////Lower Levels of Abstraction
//void trigger(void (*solicit)(), char* solicitedData);
//void promptForSalesID();
//int findRecordAndReturnIndex(char* searchedID, SalesRecord* line, int numberOfRecordsInFile);
//void recordNotFoundMessage();
//void modifyRecordData(SalesRecord* salesRecords, int indexOfRecordInFile, int numberOfRecordsInFile);
//void obtainDetailsOfNewRecord(SalesRecord* newRecord);
//void writeNewRecordIntoFile(SalesRecord* newRecord);
//
//#define LOWER_LIMIT 1
//#define UPPER_LIMIT 5


/*------------------------------------------------------ staff module declarations ------------------------------------------------------------------------------*/
#define STAFF_FILE "staff.txt"
#define MAX_STAFF 50
#define MAXCHAR_STAFF_ID 6
#define MAXCHAR_STAFF_NAME 25
#define MAXCHAR_STAFF_POSITION 15
#define MAXCHAR_PASSWORD 25

typedef struct {
	char staffID[MAXCHAR_STAFF_ID];
	char name[MAXCHAR_STAFF_NAME];
	Date birthDate;
	char gender;
	char position[MAXCHAR_STAFF_POSITION];
	char password[MAXCHAR_PASSWORD];
	char recovery[MAXCHAR_PASSWORD];
}Staff;

//Validations
void checkStaffID(char[], int*, char(*)[]);
int checkStaffName(char[]);
int checkBirthDate(int, int, int);
void checkStaffGender(int, char*, int*);
void checkStaffPosition(int, char(*), int*);
int checkPassword(char[]);
int checkNumber(char[]);
int checkDecision(char);

//1. Add Staff Module
void StaffAdd();
void saveStaff(Staff staff);

//2. Search Staff Module
void StaffSearch();
void searchByAttr(int);

//3. Modify Staff Module
void StaffModify();
int selectAttr();

//4. Display Staff Module
void StaffDisplay();

//5. Delete Staff Module
void StaffDelete();

//6. Login Module
void StaffLogin();
void staffLogout();

//Functions used by multiple modules
int checkStaffIDExist(char[]);
void readStaffFile(Staff staff[], int*);
void writeStaffFile(Staff staff[], int);
void displayAllStaff(Staff staff[], int);

//Function used to prompt data input
char* getStaffID(Staff* staff);
char* getStaffName(Staff* staff);
void getStaffBirth(Staff* staff, int* day, int* month, int* year);
int getGenderAndPosition();
char* getStaffPassword(Staff* staff);
char* getStaffRecovery(Staff* staff);

/*------------------------------------------------------ member module declarations ------------------------------------------------------------------------------*/
//#pragma once
#define MEMBER "member.bin"
#define MAX_MEMBER 50
#define MAX_STATUS 6
#define DEFAULT_ID "AAAAA"
#define PAGE_WIDTH 110
#define PAGE_LENGTH 18
#define EXIT "XXX"
#define M_MIN_OPT 0
#define MAX_CHAR_MEMBER_ID 5
#define MAX_CHAR_MEMBER_NAME 20
#define MAX_CHAR_MEMBER_IC 12
#define MAX_CHAR_MEMBER_EMAIL 30
#define MAX_CHAR_MEMBER_PHONE 10
#define MAX_SALES 100

//Member Structures
typedef struct {
	char email[MAX_CHAR_MEMBER_EMAIL + 1];
	char phone[MAX_CHAR_MEMBER_PHONE + 1];
}Contacts;
typedef struct {
	char mID[MAX_CHAR_MEMBER_ID + 1];
	char mName[MAX_CHAR_MEMBER_NAME + 1];
	char mGender;
	char mIC[MAX_CHAR_MEMBER_IC + 1];
	Contacts mContact;
	char mStatus[10];
	char mUpID[MAX_CHAR_MEMBER_ID + 1];
	double mTotalSales;
}Members;
typedef struct {
	char upLineID[MAX_CHAR_MEMBER_ID + 1];
	int noRecruit;
}UpLines;
typedef struct {
	char memberStatus[10];
	int noMember;
}Levels;
typedef struct {
	char memberID[MAX_CHAR_MEMBER_ID + 1];
	double sPower;
}Power;

void main();

//main function
void addMember();
void searchMember();
void modifyMember();
void displayMember();
void deleteMember();
void reportMember();

//Menus
int memberMenu();
int mSearchMenu();
int mModifyMenu();
int mReportMenu();

//write,read,append data
void aData(Members mAdd);
void wData(Members* a, int i);
int rData(Members* a);

//Determine whether file is opened successfully or not
int chkFile(FILE* open);

//get member's details
//In Add
void mAddDetails(Members* a, int use, char action[]);

//In Search
void mSearchDetails(Members* a, int opt, char action[]);
//In Modify
void mModifyDetails(Members* a, int mLocation, int total, int opt, char action[]);
//In Report
void mReportDetails(int typeOption, char action[]);
void mBestUL(char action[]);
void mTotal(char action[]);
void mSellMost(char action[]);
//In Best UPLINE
void mFilterBest(UpLines* b, int noBest);
void emptyUArray(UpLines* b, int total);
int sortUArray(Members* a, UpLines* b, int total);
void sortUAsc(UpLines* b, int total);
void getUBest(UpLines* best, UpLines* all, int total);
//In Total MEMBER in each LEVEL
void mFilterStatus(Levels* c, Levels* most);
void sortSArray(Members* a, Levels* c, int total);
void mostS(Levels* most, Levels* c);
//In Highest Purchasing Power
void mFilterPower(Power* d, int total);
void collectPArray(Power* d, Members* a, int total);
void sortPAsc(Power* d, int total);
void getPBest(Power* strongest, Power* all, int total);

//sub function for sub modules
void mDisplay(Members* a, int total);
void mDetailedDisplay(Members* a, int total);
int mModify(Members* a, char action[]);
int mFind(char action[]);
int mDelete(Members* a, char action[], int total, int mPlace);
int mReport(char action[]);

//accept input
void acceptMemberID(Members* a, int use, char action[], char method[]);
void acceptMemberName(Members* a, int use, char action[], char method[]);
void acceptMemberGender(Members* a, int use, char action[], char method[]);
void acceptMemberIC(Members* a, int use, char action[], char method[]);
void acceptMemberEmail(Members* a, int use, char action[], char method[]);
void acceptMemberPhone(Members* a, int use, char action[], char method[]);
void acceptUplineID(Members* a, int use, char action[], char method[]);

//get valid input
void getMemberID(Members* a, int use, char action[], char method[]);
void getMemberName(Members* a, int use, char action[], char method[]);
void getMemberGender(Members* a, int use, char action[], char method[]);
void getMemberIC(Members* a, int use, char action[], char method[]);
void getMemberEmail(Members* a, int use, char action[], char method[]);
void getMemberPhone(Members* a, int use, char action[], char method[]);
void getMemberStatus(Members* a);
void getMemberTotalSales(Members* a);
void getMemberUpline(Members* a, int use, char action[], char method[]);

//update data
void updateUpline(Members* a, char mIDBefore[], int mLocation, int total);
void updateSalesMID(Members* a, char mIDBefore[]);

//clear data
void clearData(Members* a, int total);

//messages
void errorM(char what[]);
void existM(char what[]);
void inexistM();
void successM();
void addM();
void declineM();
void backM();
void mMethod(char action[], char method[]);

//get option
int getOption(int maxOpt);
int confirm(char action[]);
int anymore(char action[]);
//validation
int optValidation(char opt[], int minOpt, int maxOpt);
int validDigit(char text[], int length, char data[]);
int validString(char text[], int length, char mustInclude, char data[]);
int validGender(char gender, char data[]);
int validName(char text[], char data[]);
int validMemberID(char text[], int length, char data[]);
//others
//formating
void space();
void gap(int number);
void line();
void spacing();
//formating words position
void makeMiddle(char text[], int length);
void makeIntFit(int num, char text[], int length);
void makeDbFit(double num, char text[], int length);
//check existance
int mChkRedundancy(Members* a);
int mChkRedundancyTimes(Members* a);
int chkUplineMember(char uplineID[]);
//title
void title(char action[]);
void mainTitle(char action[]);
//profile picture
void male();
void female();
//cancel
void cancel(char action[]);
//table format
void tableLine(int length, int number);
void tableHead(int number);
//report layout format
void rptLine(int width);
int rptTitle(char title[], int width);
void rptTitleLine(int width);
void rptTitleContent(char title[], int width);
void rptLeft();
void rptRight();
void rptBlank(int row, int width);
int rptContentHead(char a[], char b[], int width);
void rptContentTitle(char a[], char b[], int width);
void rptContentLine(int leftLine, int rightLine, int width);
//report content formating
int rptUContent(UpLines* b, int total, int width, char intTitle[]);
int rptSContent(Levels* c, int width, char intTitle[]);
int rptDbContent(Power* b, int total, int width, char intTitle[]);
void rptIntContentFoot(char who[], char text[], int total, int width);
void rptDbContentFoot(char who[], char text[], double total, int width);

//#define MEMBER "member.bin"
//
//#define MAX_MEMBER 50
//
//#define MAX_STATUS 6
//
//#define DEFAULT_ID "AAAAA"
//
//#define PAGE_WIDTH 110
//
//#define EXIT "XXX"
//
//#define M_MIN_OPT 0
//
//#define MAX_CHAR_MEMBER_ID 5
//
//#define MAX_CHAR_MEMBER_NAME 20
//
//#define MAX_CHAR_MEMBER_IC 12
//
//#define MAX_CHAR_MEMBER_EMAIL 30
//
//#define MAX_CHAR_MEMBER_PHONE 10
//
////Member Structures
//
//typedef struct {
//
//	char email[MAX_CHAR_MEMBER_EMAIL + 1];
//
//	char phone[MAX_CHAR_MEMBER_PHONE + 1];
//
//}Contacts;
//
//typedef struct {
//
//	char mID[MAX_CHAR_MEMBER_ID + 1];
//
//	char mName[MAX_CHAR_MEMBER_NAME + 1];
//
//	char mGender;
//
//	char mIC[MAX_CHAR_MEMBER_IC + 1];
//
//	Contacts mContact;
//
//	char mStatus[10];
//
//	char mUpID[MAX_CHAR_MEMBER_ID + 1];
//
//}Members;
//
//typedef struct {
//
//	char upLineID[MAX_CHAR_MEMBER_ID + 1];
//
//	int noRecruit;
//
//}UpLines;
//
//typedef struct {
//
//	char memberStatus[10];
//
//	int noMember;
//
//}Levels;
//
//typedef struct {
//
//	char memberID[MAX_CHAR_MEMBER_ID + 1];
//
//	double sPower;
//
//}Power;
//
//typedef struct {
//
//	char mSID[MAX_CHAR_MEMBER_ID + 1];
//
//	double amount;
//
//}Sales;
//
//
//
//
//
//
//
////main function
//
//void addMember();
//
//void searchMember();
//
//void modifyMember();
//
//void displayMember();
//
//void deleteMember();
//
//void reportMember();
//
//
//
//
////Menus
//
//int memberMenu();
//
//int mSearchMenu();
//
//int mModifyMenu();
//
//int mReportMenu();
//
//
//
//
////write,read,append data
//
//void aData(Members mAdd);
//
//void wData(Members* a, int i);
//
//int rData(Members* a);
//
//int rSData(Sales* a);
//
////Determine whether file is opened successfully or not
//
//int chkFile(FILE* open);
//
//
//
//
////get member's details
//
////In Add
//
//void mAddDetails(Members* a, int use, char action[]);
//
//
//
//
////In Search
//
//void mSearchDetails(Members* a, int opt, char action[]);
//
////In Modify
//
//void mModifyDetails(Members* a, int mLocation, int total, int opt, char action[]);
//
////In Report
//
//void mReportDetails(int typeOption, char action[]);
//
//void mBestUL(char action[]);
//
//void mTotal(char action[]);
//
//void mBuyMost(char action[]);
//
////In Best UPLINE
//
//void mFilterBest(UpLines* b, int noBest);
//
//void emptyUArray(UpLines* b, int total);
//
//int sortUArray(Members* a, UpLines* b, int total);
//
//void sortUAsc(UpLines* b, int total);
//
//void getUBest(UpLines* best, UpLines* all, int total);
//
////In Total MEMBER in each LEVEL
//
//int rptSContent(Levels* c, int width, char intTitle[]);
//
//void mFilterStatus(Levels* c, Levels* most);
//
//void sortSArray(Members* a, Levels* c, int total);
//
//void mostS(Levels* most, Levels* c);
//
////In Highest Purchasing Power
//
//void mFilterPower(Power* d, int total);
//
//void emptyPArray(Power* b, Members* a, int total);
//
//void sortPArray(Power* d, int total);
//
//void sortPAsc(Power* b, int total);
//
//void getPBest(Power* strongest, Power* all, int total);
//
//
//
//
////sub function for sub modules
//
//void mDisplay(Members* a, int total);
//
//void mDetailedDisplay(Members* a, int total);
//
//int mModify(Members* a, char action[]);
//
//int mFind(char action[]);
//
//int mDelete(Members* a, char action[], int total, int mPlace);
//
//int mReport(char action[]);
//
//
//
//
////accept input
//
//void acceptMemberID(Members* a, int use, char action[], char method[]);
//
//void acceptMemberName(Members* a, int use, char action[], char method[]);
//
//void acceptMemberGender(Members* a, int use, char action[], char method[]);
//
//void acceptMemberIC(Members* a, int use, char action[], char method[]);
//
//void acceptMemberEmail(Members* a, int use, char action[], char method[]);
//
//void acceptMemberPhone(Members* a, int use, char action[], char method[]);
//
//void acceptUplineID(Members* a, int use, char action[], char method[]);
//
//
//
//
////get valid input
//
//void getMemberID(Members* a, int use, char action[], char method[]);
//
//void getMemberName(Members* a, int use, char action[], char method[]);
//
//void getMemberGender(Members* a, int use, char action[], char method[]);
//
//void getMemberIC(Members* a, int use, char action[], char method[]);
//
//void getMemberEmail(Members* a, int use, char action[], char method[]);
//
//void getMemberPhone(Members* a, int use, char action[], char method[]);
//
//void getMemberStatus(Members* a);
//
//void getMemberUpline(Members* a, int use, char action[], char method[]);
//
//
//
//
////update data
//
//void updateUpline(Members* a, char uplineBefore[], int mLocation, int total);
//
//
//
//
////clear data
//
//void clearData(Members* a, int total);
//
//
//
//
////messages
//
//void errorM(char what[]);
//
//void existM(char what[]);
//
//void inexistM();
//
//void successM();
//
//void addM();
//
//void declineM();
//
//void backM();
//
//void mMethod(char action[], char method[]);
//
//
//
//
////get option
//
//int getOption(int maxOpt);
//
//int confirm(char action[]);
//
//int anymore(char action[]);
//
////validation
//
//int optValidation(char opt[], int minOpt, int maxOpt);
//
//int validDigit(char text[], int length, char data[]);
//
//int validString(char text[], int length, char mustInclude, char data[]);
//
//int validGender(char gender, char data[]);
//
//int validName(char text[], char data[]);
//
//int validMemberID(char text[], int length, char data[]);
//
////others
//
////formating
//
//void space();
//
//void gap();
//
//void line();
//
//void spacing();
//
////formating words position
//
//void makeMiddle(char text[], int length);
//
//void makeIntFit(int num, char text[], int length);
//
//void makeDbFit(double num, char text[], int length);
//
////check existance
//
//int mChkRedundancy(Members* a);
//
//int mChkRedundancyTimes(Members* a);
//
//int chkUplineMember(char uplineID[]);
//
////title
//
//void title(char action[]);
//
////profile picture
//
//void male();
//
//void female();
//
////cancel
//
//void cancel(char action[]);
//
////table format
//
//void tableLine(int length);
//
//void tableHead();
//
////report layout format
//
//void rptLine(int width);
//
//int rptTitle(char title[], int width);
//
//void rptTitleLine(int width);
//
//void rptTitleContent(char title[], int width);
//
//void rptLeft();
//
//void rptRight();
//
//void rptBlank(int row, int width);
//
//void rptContentHead(char a[], char b[], int width);
//
//void rptContentTitle(char a[], char b[], int width);
//
//void rptContentLine(int leftLine, int rightLine, int width);
//
////report content formating
//
//int rptUContent(UpLines* b, int total, int width, char intTitle[]);
//
//int rptDbContent(Power* b, int total, int width, char intTitle[]);
//
//void rptIntContentFoot(char who[], char text[], int total, int width);
//
//void rptDbContentFoot(char who[], char text[], double total, int width);