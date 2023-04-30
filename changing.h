#pragma once
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
#define RED "\033[0;31m"
#define RESET "\033[0m"
#define ENTER printf("\n")
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
void updateDownline(Members* a, char mIDBefore[], int total);

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