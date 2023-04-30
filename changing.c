#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"changing.h"
#pragma warning(disable:4996)
void memberLogo() {
	ENTER; ENTER; ENTER;
	makeMiddle("                         .^7??7^.                         ", PAGE_WIDTH); printf("\n");
	makeMiddle("                        ?#&GPPG##Y.                       ", PAGE_WIDTH); printf("\n");
	makeMiddle("         .:^:.         P@P:    .J@B:         :^:.         ", PAGE_WIDTH); printf("\n");
	makeMiddle("       ~P##B##P~      ~@#.       5@Y      :5##B##G7       ", PAGE_WIDTH); printf("\n");
	makeMiddle("      7@#!...!#@?     ?@G        ?@G     ~&@7:..~G@5      ", PAGE_WIDTH); printf("\n");
	makeMiddle("     .#@~     ^@&:    ^@&:       P@J     P@J     .#@~     ", PAGE_WIDTH); printf("\n");
	makeMiddle("     .&@^     :@@:     J@B~.   :5@G.     G@7      B@!     ", PAGE_WIDTH); printf("\n");
	makeMiddle("      Y@G:   .5@5       ~#@#GGB@@J       7@#^    ?@B.     ", PAGE_WIDTH); printf("\n");
	makeMiddle("       ?@&GPP&@Y.   .:~?P&B7~!~5&BY!^.    !&@BPP#@P.      ", PAGE_WIDTH); printf("\n");
	makeMiddle("   :~7YB&G7?75&P..JGB#BPJ~      :75B##BP~ ?&B?77Y##P?~^.  ", PAGE_WIDTH); printf("\n");
	makeMiddle(" ~B&BG57:     :^ G@5^:              .:!&@~.^     .~JPB##Y ", PAGE_WIDTH); printf("\n");
	makeMiddle(".&@!            ~@#                    J@P            .B@7", PAGE_WIDTH); printf("\n");
	makeMiddle("^@@J??????????! !@&???????????????????7P@G ~??????????7B@Y", PAGE_WIDTH); printf("\n");
	makeMiddle(".JY55555555555J .JY5555555555555555555555! !555555555555Y~", PAGE_WIDTH); printf("\n");
	ENTER; ENTER;
}
void main() {
	int option, totalOpt;
	char action[] = "MEMBER INFORMATION";

	do {
		title(action); ENTER;
		memberLogo(); ENTER;
		totalOpt = memberMenu();

		option = getOption(totalOpt);

		switch (option) {
		case M_MIN_OPT:
			break;
		case 1:
			addMember();
			break;
		case 2:
			searchMember();
			break;
		case 3:
			modifyMember();
			break;
		case 4:
			displayMember();
			break;
		case 5:
			deleteMember();
			break;
		case 6:
			reportMember();
			break;
		default:
			system("pause");
		}
	} while (option != M_MIN_OPT);
}

//main function
void addMember() {
	char action[] = "ADDING MEMBERS";
	int use = 1;
	Members mAdd;

	do {
		title(action);
		mAddDetails(&mAdd, use, action);
		if (!strcmp(mAdd.mID, EXIT)) {
			backM();
			return;
		}
		if (confirm(action)) {
			title(action);
			aData(mAdd);
			clearData(&mAdd, 1);
			addM();
		}
		else
			cancel(action);
	} while (anymore(action));
}
void searchMember() {
	char action[] = "SEARCHING MEMBERS";
	int mPlace;
	Members mArray[MAX_MEMBER];
	rData(mArray);

	do {
		mPlace = mFind(action);
		if (mPlace > 0) {
			title(action);
			mDisplay(&mArray[mPlace - 1], 1);
			if (confirm("Display in detailed")) {
				title(action);
				mDetailedDisplay(&mArray[mPlace - 1], 1);
				system("pause");
			}
		}
		else if (mPlace == -1) {
			backM();
			break;
		}
		else
		{
			errorM("INPUT");
			inexistM();
			system("pause");
		}
		title(action);
	} while (anymore(action));
}
void modifyMember() {
	char action[] = "MODIFYING MEMBERS";
	int option = 0, mPlace, count;
	Members mArray[MAX_MEMBER];
	count = rData(mArray);

	do {
		//Searching
		mPlace = mFind("SEARCHING MEMBERS FOR MODIFICATIONS");
		if (mPlace > 0) {
			title(action);
			//Show the selected Member
			mDetailedDisplay(&mArray[mPlace - 1], 1);
			if (confirm(action)) {
				do {
					//Modifying
					option = mModify(&mArray[mPlace - 1], action);
					if (option > 0)
						mModifyDetails(&mArray[mPlace - 1], mPlace - 1, count, option, action);
					else if (option == -1) {
						backM();
						break;
					}
				} while (anymore("MODIFYING CURRENT MEMBER"));
			}
		}
		else if (mPlace == -1) {
			backM();
			break;
		}
		else
		{
			errorM("INPUT");
			inexistM();
			system("pause");
		}
		title(action);
	} while (anymore(action));
	wData(mArray, count);
}
void displayMember() {
	char action[] = "DISPLAYING MEMBERS";
	int total;
	Members display[MAX_MEMBER];
	total = rData(display);
	title(action);
	mDisplay(display, total);
	space();
	printf("%d record(s) found.\n", total);
	if (confirm("Display in detailed")) {
		title(action);
		mDetailedDisplay(display, total);
		printf("%d record(s) found.\n", total);
		system("pause");
	}
}
void deleteMember() {
	char action[] = "DELETING MEMBERS";
	int mPlace, count;
	Members mArray[MAX_MEMBER];
	count = rData(mArray);

	do {
		title(action);
		mPlace = mFind("SEARCHING MEMBERS FOR DELETATION");
		if (mPlace > 0) {
			title(action);
			mDetailedDisplay(&mArray[mPlace - 1], 1);
			if (confirm(action)) {
				count = mDelete(mArray, action, count, mPlace);

			}
		}
		else if (mPlace == -1) {
			backM();
			break;
		}
		else
		{
			errorM("INPUT");
			inexistM();
			system("pause");
		}
		title(action);
	} while (anymore(action));
	wData(mArray, count);
}
void reportMember() {
	char action[] = "GENERATING MEMBER REPORTS";
	int option;

	do {
		option = mReport(action);
		if (option == -1) {
			backM();
			break;
		}
		else
			system("pause");
	} while (anymore(action));
}

//Menus
int memberMenu() {
	int num = -1;
	line(); ENTER;
	space(); makeMiddle("You would like to :", PAGE_WIDTH); ENTER; ENTER;
	line();
	space(); printf("%d. %s\n", ++num, "BACK");
	space(); printf("%d. %s\n", ++num, "ADD MEMBER(S)");
	space(); printf("%d. %s\n", ++num, "SEARCH MEMBER(S)");
	space(); printf("%d. %s\n", ++num, "MODIFY MEMBER(S)");
	space(); printf("%d. %s\n", ++num, "DISPLAY MEMBER(S)");
	space(); printf("%d. %s\n", ++num, "DELETE MEMBER(S)");
	space(); printf("%d. %s\n", ++num, "GENERATE MEMBER REPORT(S)");
	return num;

}
int mSearchMenu() {
	int num = -1;
	space(); printf("You would like to SEARCH the MEMBER by :\n");
	space(); printf("%d. %s\n", ++num, "BACK");
	space(); printf("%d. %s\n", ++num, "Member ID");
	space(); printf("%d. %s\n", ++num, "Member IC");
	space(); printf("%d. %s\n", ++num, "Email");
	space(); printf("%d. %s\n", ++num, "Phone Number");
	return num;
}
int mModifyMenu() {
	int num = -1;
	space(); printf("You would like to MODIFY the MEMBER by :\n");
	space(); printf("%d. %s\n", ++num, "BACK");
	space(); printf("%d. %s\n", ++num, "Member ID");
	space(); printf("%d. %s\n", ++num, "Member Name");
	space(); printf("%d. %s\n", ++num, "Member Gender");
	space(); printf("%d. %s\n", ++num, "Member IC");
	space(); printf("%d. %s\n", ++num, "Email");
	space(); printf("%d. %s\n", ++num, "Phone Number");
	space(); printf("%d. %s\n", ++num, "Up Line ID");
	return num;
}
int mReportMenu() {
	int num = -1;
	space(); printf("You would like to GENERATE MEMBER REPORT of :\n");
	space(); printf("%d. %s\n", ++num, "BACK");
	space(); printf("%d. %s\n", ++num, "Top 3 Members who recruit others the most.");
	space(); printf("%d. %s\n", ++num, "Total number of member from each level");
	space(); printf("%d. %s\n", ++num, "Top 5 Members with the highest purchasing power");
	return num;
}

//write,read,append data
void aData(Members mAdd) {
	FILE* insert = fopen(MEMBER, "ab");
	if (chkFile(insert))
		return;
	fwrite(&mAdd, sizeof(Members), 1, insert);
	fclose(insert);
}
void wData(Members* a, int i) {
	FILE* write = fopen(MEMBER, "wb");
	if (chkFile(write))
		return;

	for (int j = 0; j < i; j++) {
		fwrite(a++, sizeof(Members), 1, write);
	}

	fclose(write);
}
int rData(Members* a) {
	int count = 0;
	FILE* read = fopen(MEMBER, "rb");
	if (chkFile(read))
		return 0;

	while (fread(a++, sizeof(Members), 1, read)) {
		count++;
	}

	fclose(read);
	return count;
}

//Determine whether file is opened successfully or not
int chkFile(FILE* open) {
	if (open == NULL) {
		space(); printf("Failed to open the file.\n");
		return 1;
	}
	else
		return 0;
}

//get member's details
//In Add
void mAddDetails(Members* a, int use, char action[]) {
	//get New MEMBER Details
	//MEMBER ID
	getMemberID(a, use, action, "MEMBER ID");
	//back when user input sentinel
	if (!strcmp(a->mID, EXIT))
		return;
	//MEMBER NAME
	getMemberName(a, use, action, "MEMBER NAME");
	//GENDER
	getMemberGender(a, use, action, "GENDER");
	//IC
	getMemberIC(a, use, action, "MEMBER IC");
	//EMAIL
	getMemberEmail(a, use, action, "MEMBER EMAIL");
	//PHONE NUMBER
	getMemberPhone(a, use, action, "PHONE NUMBER");
	//STATUS
	getMemberStatus(a);
	//TOTAL SALES
	getMemberTotalSales(a);
	//UPLINE ID
	getMemberUpline(a, use, action, "Upline ID");
}

//In Search
void mSearchDetails(Members* a, int opt, char action[]) {
	int use = 2;
	title(action);
	switch (opt) {
	case 1:
		getMemberID(a, use, action, "MEMBER ID");
		break;
	case 2:
		getMemberIC(a, use, action, "MEMBER IC");
		break;
	case 3:
		getMemberEmail(a, use, action, "MEMBER EMAIL");
		break;
	default:
		getMemberPhone(a, use, action, "MEMBER PHONE NUMBER");
	}
}
//In Modify
void mModifyDetails(Members* a, int mLocation, int total, int opt, char action[]) {
	int use = 3;
	char mIDBefore[MAX_CHAR_MEMBER_ID + 1] = " ";
	title(action);
	mDetailedDisplay(a, 1);
	switch (opt) {
	case 1:
		strcpy(mIDBefore, a->mID);
		getMemberID(a, use, action, "MEMBER ID");
		updateUpline(a, mIDBefore, mLocation, total);
		updateSalesMID(a, mIDBefore);
		break;
	case 2:
		getMemberName(a, use, action, "MEMBER NAME");
		break;
	case 3:
		getMemberGender(a, use, action, "MEMBER GENDER");
		break;
	case 4:
		getMemberIC(a, use, action, "MEMBER IC");
		break;
	case 5:
		getMemberEmail(a, use, action, "MEMBER EMAIL");
		break;
	case 6:
		getMemberPhone(a, use, action, "MEMBER PHONE NUMBER");
		break;
	default:
		getMemberUpline(a, use, action, "UPLINE ID");
	}
}
//In Report
void mReportDetails(int typeOption, char action[]) {
	switch (typeOption) {
	case 1:
		mBestUL(action);
		break;
	case 2:
		mTotal(action);
		break;
	case 3:
		mSellMost(action);
	}
}
void mBestUL(char action[]) {
	int rptLength = PAGE_LENGTH - 2, rptWidth = PAGE_WIDTH - 4, minusH = 0;
	int noBest = 3;
	UpLines best[3];

	mFilterBest(best, noBest);

	title(action);
	printf("\n");
	rptLine(rptWidth);
	minusH += rptTitle("Top 3 Members who recruit others the most", rptWidth);
	minusH += rptContentHead("MEMBER ID", "No. OF RECRUITMENT", rptWidth);
	minusH += rptUContent(best, noBest, rptWidth, "No. OF RECRUITMENT");
	rptBlank(1, rptWidth); minusH++;
	rptIntContentFoot(best[0].upLineID, "recruits the most :", best[0].noRecruit, rptWidth); minusH++;
	rptBlank(rptLength - minusH, rptWidth);
	rptLine(rptWidth);

}
void mTotal(char action[]) {
	int rptLength = PAGE_LENGTH - 2, rptWidth = PAGE_WIDTH - 4, minusH = 0;
	Levels noStatus[MAX_STATUS] = {
		{"IRON",0},
		{"BRONZE",0},//>5000
		{"SILVER",0},//>15000
		{"GOLD",0},//>35000
		{"PLATINUM",0},//>75000
		{"DIAMOND",0}//155000
	};
	Levels mostStatus = { " ",-1 };

	mFilterStatus(noStatus, &mostStatus);

	title(action);
	printf("\n");
	rptLine(rptWidth);
	minusH += rptTitle("Total number of member from each level", rptWidth);
	minusH += rptContentHead("STATUS", "NO. OF MEMBERS", rptWidth);
	minusH += rptSContent(noStatus, rptWidth, "NO. OF MEMBERS");
	rptBlank(1, rptWidth); minusH++;
	rptIntContentFoot(mostStatus.memberStatus, "having the most MEMBER(S) :", mostStatus.noMember, rptWidth); minusH++;
	rptBlank(rptLength - minusH, rptWidth);
	rptLine(rptWidth);
}
void mSellMost(char action[]) {
	int rptLength = PAGE_LENGTH - 2, rptWidth = PAGE_WIDTH - 4, minusH = 0;
	//number of records
	int noPower = 5;
	Power strong[5];

	mFilterPower(strong, noPower);

	title(action);
	printf("\n");
	rptLine(rptWidth);
	minusH += rptTitle("Top 5 Members with the highest selling power", rptWidth);
	minusH += rptContentHead("MEMBER ID", "SELLING POWER", rptWidth);
	minusH += rptDbContent(strong, noPower, rptWidth, "SELLING POWER");
	rptBlank(1, rptWidth); minusH++;
	rptDbContentFoot(strong[0].memberID, "having the highest selling power : $", strong[0].sPower, rptWidth); minusH++;
	rptBlank(rptLength - minusH, rptWidth);
	rptLine(rptWidth);
}
//In Best UPLINE
void mFilterBest(UpLines* b, int noBest) {
	int total, totalU;
	Members mArray[MAX_MEMBER];
	UpLines uArray[MAX_MEMBER];
	total = rData(mArray);

	emptyUArray(uArray, total);
	totalU = sortUArray(mArray, uArray, total);
	sortUAsc(uArray, totalU);
	getUBest(b, uArray, noBest);
}
void emptyUArray(UpLines* b, int total) {
	UpLines* test;
	for (int i = 0; i < total; i++) {
		test = b + i;
		test->noRecruit = 0;
		strcpy(test->upLineID, DEFAULT_ID);
	}
}
int sortUArray(Members* a, UpLines* b, int total) {
	Members* testM;
	UpLines* testU;
	int count = 0;
	for (int i = 0; i < total; i++) {
		testM = a + i;
		//only perform this function if the upline id is existing member
		if (strcmp(testM->mUpID, DEFAULT_ID)) {
			for (int j = 0; j < total; j++) {
				testU = b + j;
				//if it is the same upline ID, increase number of recruit by 1
				if (!strcmp(testU->upLineID, testM->mUpID)) {
					testU->noRecruit++;
					break;
				}//if it is not recorded yet, record the name and increase number of recruit by 1
				else if (!strcmp(testU->upLineID, DEFAULT_ID)) {
					strcpy(testU->upLineID, testM->mUpID);
					testU->noRecruit++;
					count++;
					break;
				}

			}
		}
	}
	return count;
}
void sortUAsc(UpLines* b, int total) {
	UpLines* currentU, * afterU;
	UpLines middleMan;
	int test = 1;

	//get ascending order
	while (test != 0) {
		test = 0;
		for (int i = 0; i < total - 1; i++) {
			currentU = b + i;
			afterU = currentU + 1;
			if (currentU->noRecruit < afterU->noRecruit) {
				//store current data
				middleMan.noRecruit = currentU->noRecruit;
				strcpy(middleMan.upLineID, currentU->upLineID);
				//interchange the data
				currentU->noRecruit = afterU->noRecruit;
				strcpy(currentU->upLineID, afterU->upLineID);
				afterU->noRecruit = middleMan.noRecruit;
				strcpy(afterU->upLineID, middleMan.upLineID);
				//to tell the system the array not yet in ascending order
				test = 1;
			}
		}
	}

}
void getUBest(UpLines* best, UpLines* all, int total) {
	UpLines* placeU;
	for (int i = 0; i < total; i++) {
		placeU = all + i;
		best->noRecruit = placeU->noRecruit;
		strcpy(best->upLineID, placeU->upLineID);
		best++;
	}
}
//In Total MEMBER in each LEVEL
void mFilterStatus(Levels* c, Levels* most) {
	int count;
	Members mArray[MAX_MEMBER];
	count = rData(mArray);
	sortSArray(mArray, c, count);
	mostS(most, c);

}
void sortSArray(Members* a, Levels* c, int total) {
	Members* testA;
	Levels* testC;
	for (int i = 0; i < MAX_STATUS; i++) {
		testC = c + i;
		for (int j = 0; j < total; j++) {
			testA = a + j;
			if (!strcmp(testC->memberStatus, testA->mStatus))
				testC->noMember++;
		}
	}
}
void mostS(Levels* most, Levels* c) {
	for (int i = 0; i < MAX_STATUS; i++) {
		if (most->noMember < c->noMember) {
			most->noMember = c->noMember;
			strcpy(most->memberStatus, c->memberStatus);
		}
		c++;
	}
}
//In Highest Purchasing Power
void mFilterPower(Power* d, int total) {
	int count;
	Members mArray[MAX_MEMBER];
	Power pArray[MAX_MEMBER];
	count = rData(mArray);

	collectPArray(pArray, mArray, count);
	sortPAsc(pArray, count);
	getPBest(d, pArray, total);

}
void collectPArray(Power* d, Members* a, int total) {
	Power* test;
	for (int i = 0; i < total; i++) {
		test = d + i;
		test->sPower = a->mTotalSales;
		strcpy(test->memberID, a->mID);
		a++;
	}
}
void sortPAsc(Power* d, int total) {
	Power* currentP, * afterP;
	Power middleMan;
	int test = 1;

	//get ascending order
	while (test != 0) {
		test = 0;
		for (int i = 0; i < total - 1; i++) {
			currentP = d + i;
			afterP = currentP + 1;
			if (currentP->sPower < afterP->sPower) {
				//store current data
				middleMan.sPower = currentP->sPower;
				strcpy(middleMan.memberID, currentP->memberID);
				//interchange the data
				currentP->sPower = afterP->sPower;
				strcpy(currentP->memberID, afterP->memberID);
				afterP->sPower = middleMan.sPower;
				strcpy(afterP->memberID, middleMan.memberID);

				//to tell the system the array not yet in ascending order
				test = 1;
			}
		}
	}

}
void getPBest(Power* strongest, Power* all, int total) {
	Power* placeP;
	for (int i = 0; i < total; i++) {
		placeP = all + i;
		strongest->sPower = placeP->sPower;
		strcpy(strongest->memberID, placeP->memberID);
		strongest++;
	}
}

//sub function for sub modules
void mDisplay(Members* a, int total) {
	int number = 7;
	tableHead(number);
	for (int i = 0; i < total; i++) {
		space();
		printf("%-9s", a->mID);
		gap(number);
		printf("%-20s", a->mName);
		gap(number);
		printf("%-12s", a->mIC);
		gap(number);
		printf("%-30s", a->mContact.email);
		gap(number);
		printf("%-10s", a->mContact.phone);
		printf("\n");
		a++;
	}
	line();
}
void mDetailedDisplay(Members* a, int total) {
	int width = PAGE_WIDTH;
	for (int i = 0; i < total; i++) {
		if (a->mGender == 'F')
			female();
		else
			male();
		space(); makeMiddle(a->mName, width);
		printf("\n\n");
		space(); spacing(); printf("%45s : %s\n", "MEMBER ID", a->mID);
		space(); spacing(); printf("%45s : %s\n", "IC NUMBER", a->mIC);
		space(); spacing(); printf("%45s : %s\n", "EMAIL", a->mContact.email);
		space(); spacing(); printf("%45s : %s\n", "PHONE NUMBER", a->mContact.phone);
		space(); spacing(); printf("%45s : %s\n", "STATUS", a->mStatus);
		space(); spacing(); printf("%45s : $ %.2f\n", "Total Sales", a->mTotalSales);
		if (!strcmp(a->mUpID, DEFAULT_ID))
		{
			space(); spacing(); printf("%45s : %s\n", "UPLINE ID", " N/A ");
		}
		else
		{
			space(); spacing(); printf("%45s : %s\n", "UPLINE ID", a->mUpID);
		}
		printf("\n");
		line();
		printf("\n");
		a++;
	}
}
int mModify(Members* a, char action[]) {
	int opt, totalOpt;
	do {
		title(action);
		mDetailedDisplay(a, 1);
		totalOpt = mModifyMenu();
		opt = getOption(totalOpt);
		if (opt > 0)
			return opt;
		else if (opt == 0)
			return -1;
		else
			system("pause");
	} while (opt < 0);
}
int mFind(char action[]) {
	Members find;
	int opt, totalOpt;
	do {
		title(action);
		totalOpt = mSearchMenu();
		opt = getOption(totalOpt);
		if (opt > 0) {
			mSearchDetails(&find, opt, action);
			return mChkRedundancy(&find);
		}
		else if (opt == 0)
			return -1;
		else
			system("pause");
	} while (opt < 0);
}
int mDelete(Members* a, char action[], int total, int mPlace) {
	Members* current;
	Members* after;
	Members* deletedMember;
	char mIDBefore[MAX_CHAR_MEMBER_ID+1];
	
	//get old member ID
	deletedMember = a + mPlace - 1;
	strcpy(mIDBefore, deletedMember->mID);

	for (int i = mPlace - 1; i < total; i++) {
		current = a + i;
		after = current + 1;
		strcpy(current->mID, after->mID);
		strcpy(current->mName, after->mName);
		current->mGender = after->mGender;
		strcpy(current->mIC, after->mIC);
		strcpy(current->mContact.email, after->mContact.email);
		strcpy(current->mContact.phone, after->mContact.phone);
		current->mTotalSales = after->mTotalSales;
		strcpy(current->mStatus, after->mStatus);
		strcpy(current->mUpID, after->mUpID);
	}
	updateDownline(a, mIDBefore, total-1);
	return total - 1;
}
int mReport(char action[]) {
	int opt, totalOpt;
	do {
		title(action);
		totalOpt = mReportMenu();
		opt = getOption(totalOpt);
		if (opt > 0) {
			mReportDetails(opt, action);
			return 1;
		}
		else if (opt == 0)
			return -1;
		else
			system("pause");
	} while (opt < 0);
}

//accept input
void acceptMemberID(Members* a, int use, char action[], char method[]) {
	char inputString[100] = " ";
	//if "use" value =
	//1 : add function
	//2 : search function
	//3 : modify function
	switch (use) {
	case 1:
		space(); printf("%s : ", "Member ID (\"XXX\" to EXIT)");
		break;
	case 2:
	case 3:
		//PROMPT USER
		mMethod(action, method);
	}
	gets(inputString);
	rewind(stdin);
	strncpy(a->mID, inputString, MAX_CHAR_MEMBER_ID);
	a->mID[MAX_CHAR_MEMBER_ID] = '\0';
	for (int i = 0; i < MAX_CHAR_MEMBER_ID; i++) {
		a->mID[i] = toupper(a->mID[i]);
	}
}
void acceptMemberName(Members* a, int use, char action[], char method[]) {
	char inputString[100];
	//if "use" value =
	//1 : add function
	//2 : search function
	//3 : modify function
	switch (use) {
	case 1:
		space(); printf("%s : ", "Member Name");
		break;
	case 2:
	case 3:
		//PROMPT USER
		mMethod(action, method);
	}
	gets(inputString);
	rewind(stdin);
	strncpy(a->mName, inputString, MAX_CHAR_MEMBER_NAME);
	a->mName[MAX_CHAR_MEMBER_NAME] = '\0';
}
void acceptMemberGender(Members* a, int use, char action[], char method[]) {
	//if "use" value =
	//1 : add function
	//2 : search function
	//3 : modify function
	switch (use) {
	case 1:
		space(); printf("%s : ", "Gender (F = Female / M = Male)");
		break;
	case 2:
	case 3:
		//PROMPT USER
		mMethod(action, method);
	}
	a->mGender = getchar();
	rewind(stdin);
	a->mGender = toupper(a->mGender);
}
void acceptMemberIC(Members* a, int use, char action[], char method[]) {
	char inputString[100];
	//if "use" value =
	//1 : add function
	//2 : search function
	//3 : modify function
	switch (use) {
	case 1:
		space(); printf("%s : ", "Member IC");
		break;
	case 2:
	case 3:
		//PROMPT USER
		mMethod(action, method);
	}
	gets(inputString);
	rewind(stdin);
	strncpy(a->mIC, inputString, MAX_CHAR_MEMBER_IC);
	a->mIC[MAX_CHAR_MEMBER_IC] = '\0';
}
void acceptMemberEmail(Members* a, int use, char action[], char method[]) {
	char inputString[100];
	//if "use" value =
	//1 : add function
	//2 : search function
	//3 : modify function
	switch (use) {
	case 1:
		space(); printf("%s : ", "Email (E.g XXX@sample.com)");
		break;
	case 2:
	case 3:
		//PROMPT USER
		mMethod(action, method);
	}
	gets(inputString);
	rewind(stdin);
	strncpy(a->mContact.email, inputString, MAX_CHAR_MEMBER_EMAIL);
	a->mContact.email[MAX_CHAR_MEMBER_EMAIL] = '\0';
}
void acceptMemberPhone(Members* a, int use, char action[], char method[]) {
	char inputString[100];
	//if "use" value =
	//1 : add function
	//2 : search function
	//3 : modify function
	switch (use) {
	case 1:
		space(); printf("%s : ", "Phone Number");
		break;
	case 2:
	case 3:
		//PROMPT USER
		mMethod(action, method);
	}

	gets(inputString);
	rewind(stdin);
	strncpy(a->mContact.phone, inputString, MAX_CHAR_MEMBER_PHONE);
	a->mContact.phone[MAX_CHAR_MEMBER_PHONE] = '\0';
}
void acceptUplineID(Members* a, int use, char action[], char method[]) {
	char inputString[100];
	//if "use" value =
	//1 : add function
	//2 : search function
	//3 : modify function
	switch (use) {
	case 1:
		space(); printf("%s : ", "Up Line ID (Only existing MEMBER ID will be saved)");
		break;
	case 2:
	case 3:
		//PROMPT USER
		space(); printf("%s\n", "*Only existing MEMBER ID will be saved*");
		mMethod(action, method);
	}

	gets(inputString);
	rewind(stdin);
	strncpy(a->mUpID, inputString, MAX_CHAR_MEMBER_ID);
	a->mUpID[MAX_CHAR_MEMBER_ID] = '\0';
}

//get valid input
void getMemberID(Members* a, int use, char action[], char method[]) {
	int chkValid, repeatTimes;
	do {
		chkValid = 1;
		acceptMemberID(a, use, action, method);
		switch (use) {
		case 1://add function
			if (!strcmp(a->mID, EXIT))
				return;
			if (mChkRedundancy(a)) {
				chkValid = 0;
				existM(method);
			}
			break;
		case 2://search function
			break;
		case 3://modify function
			repeatTimes = mChkRedundancyTimes(a);
			if (repeatTimes > 1) {
				existM(method);
				chkValid = 0;
			}
		}
		//check if valid ID entered
		if (chkValid == 1)
			chkValid = validMemberID(a->mID, MAX_CHAR_MEMBER_ID, method);
	} while (chkValid == 0);
}
void getMemberName(Members* a, int use, char action[], char method[]) {
	int chkValid;
	do {
		chkValid = 1;
		acceptMemberName(a, use, action, method);
		switch (use) {//future use
		case 1://add function
		case 2://search function
		case 3://modify function
			break;
		}
		//check if valid NAME entered
		if (chkValid == 1)
			chkValid = validName(a->mName, method);
	} while (chkValid == 0);
}
void getMemberGender(Members* a, int use, char action[], char method[]) {
	int chkValid;
	do {
		chkValid = 1;
		acceptMemberGender(a, use, action, method);
		switch (use) {//future use
		case 1://add function
		case 2://search function
		case 3://modify function
			break;
		}
		//check if valid GENDER entered
		if (chkValid == 1)
			chkValid = validGender(a->mGender, method);
	} while (chkValid == 0);
}
void getMemberIC(Members* a, int use, char action[], char method[]) {
	int chkValid, repeatTimes;
	do {
		chkValid = 1;
		acceptMemberIC(a, use, action, method);
		switch (use) {
		case 1://add function
			if (mChkRedundancy(a)) {
				chkValid = 0;
				existM(method);
			}
			break;
		case 2://search function
			break;
		case 3://modify function
			repeatTimes = mChkRedundancyTimes(a);
			if (repeatTimes > 1) {
				existM(method);
				chkValid = 0;
			}
		}
		//check if valid ID entered
		if (chkValid == 1)
			chkValid = validDigit(a->mIC, MAX_CHAR_MEMBER_IC, method);
	} while (chkValid == 0);
}
void getMemberEmail(Members* a, int use, char action[], char method[]) {
	int chkValid, repeatTimes;
	do {
		chkValid = 1;
		acceptMemberEmail(a, use, action, method);
		switch (use) {
		case 1://add function
			if (mChkRedundancy(a)) {
				chkValid = 0;
				existM(method);
			}
			break;
		case 2://search function
			break;
		case 3://modify function
			repeatTimes = mChkRedundancyTimes(a);
			if (repeatTimes > 1) {
				existM(method);
				chkValid = 0;
			}
		}
		//check if valid ID entered
		if (chkValid == 1)
			chkValid = validString(a->mContact.email, strlen(a->mContact.email), '@', "EMAIL FORMAT");
	} while (chkValid == 0);
}
void getMemberPhone(Members* a, int use, char action[], char method[]) {
	int chkValid, repeatTimes;
	do {
		chkValid = 1;
		acceptMemberPhone(a, use, action, method);
		switch (use) {
		case 1://add function
			if (mChkRedundancy(a)) {
				chkValid = 0;
				existM(method);
			}
			break;
		case 2://search function
			break;
		case 3://modify function
			repeatTimes = mChkRedundancyTimes(a);
			if (repeatTimes > 1) {
				existM(method);
				chkValid = 0;
			}
		}
		//check if valid ID entered
		if (chkValid == 1)
			chkValid = validDigit(a->mContact.phone, MAX_CHAR_MEMBER_PHONE, "PHONE NUMBER");
	} while (chkValid == 0);
}
void getMemberStatus(Members* a) {
	strcpy(a->mStatus, "IRON");
}
void getMemberTotalSales(Members* a) {
	a->mTotalSales = 0;
}
void getMemberUpline(Members* a, int use, char action[], char method[]) {
	acceptUplineID(a, use, action, method);
	if (!chkUplineMember(a->mUpID))
		strcpy(a->mUpID, DEFAULT_ID);
}

//update data
void updateUpline(Members* a, char mIDBefore[], int mLocation, int total) {
	Members* starting;
	starting = a - mLocation;
	for (int i = 0; i < total; i++) {
		if (!strcmp(starting->mUpID, mIDBefore)) {
			strcpy(starting->mUpID, a->mID);
		}
		starting++;
	}
}
void updateSalesMID(Members* a, char mIDBefore[]) {
	int countOfSales;
	SalesRecord sales[MAX_SALES];

	countOfSales = obtainSalesRecordsFromFile(sales);

	for (int j = 0; j < countOfSales; j++) {
		//check if which member ID is old
		if (!strcmp(sales[j].memberId, mIDBefore)) {
			//update member ID
			strcpy(sales[j].memberId, a->mID);
		}
	}
	writeRecordsIntoFile(sales, countOfSales);
}
void updateDownline(Members* a, char mIDBefore[], int total) {
	Members* starting;
	for (int i = 0; i < total; i++) {
		starting = a + i;
		if (!strcmp(starting->mUpID, mIDBefore)) {
			strcpy(starting->mUpID, DEFAULT_ID);
		}
	}
}
//clear data
void clearData(Members* a, int total) {
	char emptyString[100] = "\0";
	for (int i = 0; i < total; i++) {
		strncpy(a->mID, emptyString, MAX_CHAR_MEMBER_ID);
		strncpy(a->mName, emptyString, MAX_CHAR_MEMBER_NAME);
		strncpy(a->mIC, emptyString, MAX_CHAR_MEMBER_IC);
		strncpy(a->mContact.email, emptyString, MAX_CHAR_MEMBER_EMAIL);
		strncpy(a->mContact.phone, emptyString, MAX_CHAR_MEMBER_PHONE);
		strncpy(a->mUpID, emptyString, MAX_CHAR_MEMBER_ID);
		a->mGender = '\0';
		a->mTotalSales = 0;
		a++;
	}
}

//messages
void errorM(char what[]) {
	space(); printf(RED "\a%s\n", "!!! ERROR !!!" RESET);
	space(); printf("*Invalid %s*\n\n", what);
}
void existM(char what[]) {
	space(); printf("This %s exists.\n", what);
}
void inexistM() {
	space(); printf("%s\n", "No Such Record Found...");
}
void successM() {
	space(); printf("%s\n", "OK.");
}
void addM() {
	space(); printf("%s\n", "The MEMBER data has successfully added.");
}
void declineM() {
	space(); printf("%s\n", "~~ DECLINED ~~");
}
void backM() {
	printf("\n");
	printf("%s\n", "Okay, let's back to MENU.");
	system("pause");
}
void mMethod(char action[], char method[]) {
	space(); printf("You have chosen METHOD : %s By %s.\n", action, method);
	space(); printf("Please enter %s.\n", method);
	space(); printf("> ");
}

//get option
int getOption(int maxOpt) {
	char opt[100] = " ";
	printf("\n");
	space();
	printf("Enter your selection (0-%d) : ", maxOpt);

	gets(opt);
	rewind(stdin);

	return optValidation(opt, M_MIN_OPT, maxOpt);
}
int confirm(char action[]) {
	char chkConfirm, yesNo[100] = " ";
	printf("\n");
	space();
	printf("%s %s%s\n", "Confirm", action, "? (y / Y = YES, any other input = NO)");
	space();
	printf("> ");
	gets(yesNo);
	rewind(stdin);
	yesNo[0] = toupper(yesNo[0]);
	if (!strcmp(yesNo, "Y")) {
		chkConfirm = 'Y';
	}
	else {
		chkConfirm = 'N';
	}
	if (toupper(chkConfirm) == 'Y') {
		printf("\n");
		successM();
		system("pause");
		return 1;
	}
	else {
		printf("\n");
		declineM();
		system("pause");
		return 0;
	}
}
int anymore(char action[]) {
	char chkMore, yesNo[999] = " ";
	printf("\n");
	space();
	printf("%s %s%s\n", "Continue", action, "? (y / Y = YES, any other input = NO)");
	space();
	printf("> ");

	gets(yesNo);
	rewind(stdin);
	yesNo[0] = toupper(yesNo[0]);
	if (!strcmp(yesNo, "Y")) {
		chkMore = 'Y';
	}
	else {
		chkMore = 'N';
	}
	if (toupper(chkMore) == 'Y') {
		printf("\n");
		space();
		printf("%s %s%s\n", "Okay, Continue", action, ".");
		system("pause");
		system("cls");
		return 1;
	}
	else {
		printf("\n");
		printf("%s\n", "Okay, let's back to MENU.");
		system("pause");
		system("cls");
		return 0;
	}
}
//validation
int optValidation(char opt[], int minOpt, int maxOpt) {
	int length = 0, index = 0, wordLength;
	wordLength = strlen(opt);
	for (int i = 0; i < wordLength; i++) {
		if (isdigit(opt[i])) {
			length++;
			index = i;
		}
		else if (!isspace(opt[i]))
			length++;
	}
	if (length == 1) {
		for (int i = 0; i <= 9; i++) {
			if ((opt[index] < minOpt + 48) || (opt[index] > maxOpt + 48)) {
				printf("Invalid Input!! Please Enter Integer (%d-%d) Only!!\n\n", minOpt, maxOpt);
				return -1;
			}
			else if (opt[index] == i + 48)
				return i;
		}
	}
	else {
		printf("Invalid Input!! Please Enter Integer (%d-%d) Only!!\n\n", minOpt, maxOpt);
		return -1;
	}
}
int validDigit(char text[], int length, char data[]) {
	for (int i = 0; i < length; i++) {
		if (!isdigit(text[i])) {
			if (data != NULL) {
				errorM(data);
			}
			return 0;
		}
	}
	return 1;
}
int validString(char text[], int length, char mustInclude, char data[]) {
	for (int i = 0; i < length; i++) {
		if (text[i] == mustInclude) {
			return 1;
		}
	}
	if (data != NULL) {
		errorM(data);
	}
	return 0;
}
int validGender(char gender, char data[]) {
	if (gender != 'F' && gender != 'M') {
		if (data != NULL) {
			errorM(data);
		}
		return 0;
	}
	else
		return 1;
}
int validName(char text[], char data[]) {
	int length = strlen(text);
	for (int i = 0; i < length; i++) {
		if (isdigit(text[i])) {
			if (data != NULL) {
				errorM(data);
			}
			return 0;
		}
	}
	return 1;
}
int validMemberID(char text[], int length, char data[]) {
	for (int i = 0; i < length; i++) {
		if (isspace(text[i]) || text[i] == '\0') {
			if (data != NULL) {
				errorM(data);
			}
			return 0;
		}
	}
	return 1;
}
//others
//formating
void space() {
	//printf("%30s", " ");
}
void gap(int number) {
	for (int i = 0; i < number; i++) {
		printf(" ");
	}
}
void line() {
	space();
	for (int i = 0; i < PAGE_WIDTH; i++) {
		printf(":");
	}
	printf("\n");
}
void spacing() {
	for (int i = 0; i < 8; i++)
		printf(" ");
}
//formating words position
void makeMiddle(char text[], int length) {
	int right, left, sLength = strlen(text), odd, extraSpace;
	odd = sLength % 2;
	extraSpace = length % 2;
	right = (length - (sLength - odd)) / 2;
	left = right - odd + extraSpace;


	for (int i = 0; i < left; i++) {
		printf(" ");
	}
	printf("%s", text);
	for (int i = 0; i < right; i++) {
		printf(" ");
	}

}
void makeIntFit(int num, char text[], int length) {
	int left, right, sLength = strlen(text), odd, digit, count = 1, extraSpace;
	odd = sLength % 2;
	extraSpace = length % 2;
	right = (length - (sLength - odd)) / 2;
	left = right - odd + extraSpace;

	digit = num;
	do {
		digit /= 10;
		if (digit != 0)
			count++;
	} while (digit != 0);

	for (int i = 0; i < left + sLength; i++) {
		printf(" ");
	}
	for (int i = 0; i < count; i++)
		printf("\b");
	printf("%d", num);
	for (int i = 0; i < right; i++) {
		printf(" ");
	}
}
void makeDbFit(double num, char text[], int length) {
	int left, right, sLength = strlen(text), odd, digit, count = 4, extraSpace;
	odd = sLength % 2;
	extraSpace = length % 2;
	right = (length - (sLength - odd)) / 2;
	left = right - odd + extraSpace;
	//remove fractional part
	digit = num;

	do {
		digit /= 10;
		if (digit != 0)
			count++;
	} while (digit != 0);

	for (int i = 0; i < left + sLength; i++) {
		printf(" ");
	}
	for (int i = 0; i < count; i++)
		printf("\b");
	printf("%.2f", num);
	for (int i = 0; i < right; i++) {
		printf(" ");
	}
}
//check existance
int mChkRedundancy(Members* a) {
	int count;
	Members checking[MAX_MEMBER];
	count = rData(checking);
	for (int i = 0; i < count; i++) {
		if (!strcmp(checking[i].mID, a->mID))
			return ++i;
		else if (!strcmp(checking[i].mIC, a->mIC))
			return ++i;
		else if (!strcmp(checking[i].mContact.email, a->mContact.email))
			return ++i;
		else if (!strcmp(checking[i].mContact.phone, a->mContact.phone))
			return ++i;
	}
	return 0;
}
int mChkRedundancyTimes(Members* a) {
	int count, redundancyTimes = 0;
	Members checking[MAX_MEMBER];
	count = rData(checking);
	for (int i = 0; i < count; i++) {
		if (!strcmp(checking[i].mID, a->mID))
			redundancyTimes++;
		else if (!strcmp(checking[i].mIC, a->mIC))
			redundancyTimes++;
		else if (!strcmp(checking[i].mContact.email, a->mContact.email))
			redundancyTimes++;
		else if (!strcmp(checking[i].mContact.phone, a->mContact.phone))
			redundancyTimes++;
	}
	return redundancyTimes;
}
int chkUplineMember(char uplineID[]) {
	int count;
	Members checking[MAX_MEMBER];
	count = rData(checking);
	for (int i = 0; i < count; i++) {
		if (!strcmp(checking[i].mID, uplineID))
			return 1;
	}
	return 0;
}
//title
void title(char action[]) {
	system("cls");

	line();
	printf("::"); for (int i = 0; i < PAGE_WIDTH - 4; i++) { printf(" "); }printf("::"); printf("\n");
	printf("::"); space(); makeMiddle(action, PAGE_WIDTH - 4); printf("::"); printf("\n");
	printf("::"); for (int i = 0; i < PAGE_WIDTH - 4; i++) { printf(" "); }printf("::"); printf("\n");
	line();
}
//title without clear screen
void mainTitle(char action[]) {

	line();
	printf("::"); for (int i = 0; i < PAGE_WIDTH - 4; i++) { printf(" "); }printf("::"); printf("\n");
	printf("::"); space(); makeMiddle(action, PAGE_WIDTH - 4); printf("::"); printf("\n");
	printf("::"); for (int i = 0; i < PAGE_WIDTH - 4; i++) { printf(" "); }printf("::"); printf("\n");
	line();
}
//profile picture
void male() {
	space(); makeMiddle("                                   ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("                                   ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("            ----------             ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("          /            \\           ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("         /   =      =   \\          ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("        |    O  ||  O    |         ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("        |                |         ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("         \\      \\/      /          ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("         \\            /          ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("          ------------           ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("         /            \\          ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("        /              \\         ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("       /                \\        ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("      /                  \\       ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("     /                    \\      ", PAGE_WIDTH); spacing(); printf("\n");
}
void female() {
	space(); makeMiddle("                                   ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("           ..::::::::..            ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("        .::::::::::::::::.         ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("       .::::::::/\\::::::::.        ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("      :::::/ _      _ \\:::::       ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("     :::::/  U  ||  U  \\:::::      ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("    .::::|      ||      |::::.     ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("    :::::|              |:::::     ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("    ::::::\\     VV     /::::::     ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("    :::::::\\__________/:::::::     ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("    :::::::/          \\:::::::     ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("    ::::::/            \\::::::     ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("         /              \\          ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("        /                \\         ", PAGE_WIDTH); spacing(); printf("\n");
	space(); makeMiddle("       /                  \\        ", PAGE_WIDTH); spacing(); printf("\n");
}
//cancel
void cancel(char action[]) {
	printf("\n");
	space(); printf("%s %s.\n", "Cancel", action);
}
//table format
void tableLine(int length, int number) {
	for (int i = 0; i < length; i++) {
		printf("=");
	}
	gap(number);
}
void tableHead(int number) {
	int num[] = { 9,20,12,30,10 }, count = 0;
	line();
	space();
	printf("%-9s", "MEMBER ID"); count++;
	gap(number);
	printf("%-20s", "MEMBER NAME"); count++;
	gap(number);
	printf("%-12s", "MEMBER IC"); count++;
	gap(number);
	printf("%-30s", "EMAIL"); count++;
	gap(number);
	printf("%-10s", "PHONE NO"); count++;
	space();
	printf("\n");
	for (int i = 0; i < count; i++) {
		tableLine(num[i], number);
	}
	printf("\n");
}
//report layout format
void rptLine(int width) {
	rptLeft();
	for (int i = 0; i < width; i++) {
		printf(":");
	}
	rptRight();
}
int rptTitle(char title[], int width) {
	int row = 0;
	rptBlank(1, width); row++;
	rptTitleLine(width); row++;
	rptTitleContent(title, width); row++;
	rptTitleLine(width); row++;
	rptBlank(1, width); row++;
	return row;
}
void rptTitleLine(int width) {
	rptLeft();
	spacing();
	for (int i = 0; i < width - 16; i++) {
		printf("=");
	}
	spacing();
	rptRight();
}
void rptTitleContent(char title[], int width) {
	rptLeft();
	spacing();
	makeMiddle(title, width - 16);
	spacing();
	rptRight();
}
void rptLeft() {
	space();
	printf("::");
}
void rptRight() {
	printf("::");
	printf("\n");
}
void rptBlank(int row, int width) {
	for (int i = 0; i < row; i++) {
		rptLeft();
		for (int j = 0; j < width; j++) {
			printf(" ");
		}

		rptRight();
	}
}
int rptContentHead(char a[], char b[], int width) {
	int row = 0;
	rptContentTitle(a, b, width / 2); row++;
	rptContentLine(strlen(a), strlen(b), width / 2); row++;
	return row;
}
void rptContentTitle(char a[], char b[], int width) {
	rptLeft();
	makeMiddle(a, width);
	makeMiddle(b, width);
	rptRight();
}
void rptContentLine(int leftLine, int rightLine, int width) {
	char left[21] = " ";
	char right[21] = " ";

	for (int i = 0; i < leftLine; i++) {
		left[i] = '=';
	}
	for (int i = 0; i < rightLine; i++) {
		right[i] = '=';
	}

	rptLeft();
	makeMiddle(left, width);
	makeMiddle(right, width);
	rptRight();
}
//report content formating
int rptUContent(UpLines* b, int total, int width, char intTitle[]) {
	UpLines* test;
	int count = 0;

	for (int i = 0; i < total; i++) {
		rptLeft();
		test = b + i;
		makeMiddle(test->upLineID, width / 2);
		makeIntFit(test->noRecruit, intTitle, width / 2);
		rptRight();
		count++;
	}

	return count;
}
int rptSContent(Levels* c, int width, char intTitle[]) {
	Levels* test;
	int count = 0;

	for (int i = 0; i < MAX_STATUS; i++) {
		rptLeft();
		test = c + i;
		makeMiddle(test->memberStatus, width / 2);
		makeIntFit(test->noMember, intTitle, width / 2);
		rptRight();
		count++;
	}

	return count;
}
int rptDbContent(Power* b, int total, int width, char intTitle[]) {
	Power* test;
	int count = 0;

	for (int i = 0; i < total; i++) {
		rptLeft();
		test = b + i;
		makeMiddle(test->memberID, width / 2);
		makeDbFit(test->sPower, intTitle, width / 2);
		rptRight();
		count++;
	}

	return count;
}
void rptIntContentFoot(char who[], char text[], int total, int width) {
	int spaceAfterWords, count = 1, digit;
	digit = total;
	while (digit != 0) {
		digit /= 10;
		if (digit != 0)
			count++;
	}
	spaceAfterWords = width - strlen(who) - strlen(text) - count - 3 - 8;
	rptLeft();
	spacing();
	printf("%s %s %d.", who, text, total);
	for (int i = 0; i < spaceAfterWords; i++) {
		printf(" ");
	}
	rptRight();
}
void rptDbContentFoot(char who[], char text[], double total, int width) {
	int spaceAfterWords, count = 1;
	int digit;
	digit = total;
	while (digit != 0) {
		digit /= 10;
		if (digit != 0)
			count++;
	}
	spaceAfterWords = width - strlen(who) - strlen(text) - count - 3 - 8 - 3;
	rptLeft();
	spacing();
	printf("%s %s %.2f.", who, text, total);
	for (int i = 0; i < spaceAfterWords; i++) {
		printf(" ");
	}
	rptRight();
}




//#include<stdio.h>
//#include<stdlib.h>
//#include<ctype.h>
//#include<string.h>
////#include "member_declarations.h"
//#include"stockDeclarations.h"
//
//#pragma warning(disable:4996)
//
//void membermain() {
//	int option, totalOpt;
//
//	do {
//		system("cls");
//		totalOpt = memberMenu();
//
//		option = getOption(totalOpt);
//
//		switch (option) {
//		case M_MIN_OPT:
//			break;
//		case 1:
//			addMember();
//			break;
//		case 2:
//			searchMember();
//			break;
//		case 3:
//			modifyMember();
//			break;
//		case 4:
//			displayMember();
//			break;
//		case 5:
//			deleteMember();
//			break;
//		case 6:
//			reportMember();
//			break;
//		default:
//			system("pause");
//		}
//	} while (option != M_MIN_OPT);
//}
//
////main function
//void addMember() {
//	char action[] = "ADDING MEMBERS";
//	int use = 1;
//	Members mAdd;
//
//	do {
//		title(action);
//		mAddDetails(&mAdd, use, action);
//		if (!strcmp(mAdd.mID, EXIT)) {
//			backM();
//			return;
//		}
//		if (confirm(action)) {
//			title(action);
//			aData(mAdd);
//			clearData(&mAdd, 1);
//			addM();
//		}
//		else
//			cancel(action);
//	} while (anymore(action));
//}
//void searchMember() {
//	char action[] = "SEARCHING MEMBERS";
//	int mPlace;
//	Members mArray[MAX_MEMBER];
//	rData(mArray);
//
//	do {
//		mPlace = mFind(action);
//		if (mPlace > 0) {
//			title(action);
//			mDisplay(&mArray[mPlace - 1], 1);
//			if (confirm("Display in detailed")) {
//				title(action);
//				mDetailedDisplay(&mArray[mPlace - 1], 1);
//				system("pause");
//			}
//		}
//		else if (mPlace == -1) {
//			backM();
//			break;
//		}
//		else
//		{
//			errorM("INPUT");
//			inexistM();
//			system("pause");
//		}
//		title(action);
//	} while (anymore(action));
//}
//void modifyMember() {
//	char action[] = "MODIFYING MEMBERS";
//	int option = 0, mPlace, count;
//	Members mArray[MAX_MEMBER];
//	count = rData(mArray);
//
//	do {
//		//Searching
//		mPlace = mFind("SEARCHING MEMBERS FOR MODIFICATIONS");
//		if (mPlace > 0) {
//			title(action);
//			//Show the selected Member
//			mDetailedDisplay(&mArray[mPlace - 1], 1);
//			if (confirm(action)) {
//				do {
//					//Modifying
//					option = mModify(&mArray[mPlace - 1], action);
//					if (option > 0)
//						mModifyDetails(&mArray[mPlace - 1], mPlace - 1, count, option, action);
//					else if (option == -1) {
//						backM();
//						break;
//					}
//				} while (anymore("MODIFYING CURRENT MEMBER"));
//			}
//		}
//		else if (mPlace == -1) {
//			backM();
//			break;
//		}
//		else
//		{
//			errorM("INPUT");
//			inexistM();
//			system("pause");
//		}
//		title(action);
//	} while (anymore(action));
//	wData(mArray, count);
//}
//void displayMember() {
//	char action[] = "DISPLAYING MEMBERS";
//	int total;
//	Members display[MAX_MEMBER];
//	total = rData(display);
//	title(action);
//	mDisplay(display, total);
//	space();
//	printf("%d record(s) found.\n", total);
//	if (confirm("Display in detailed")) {
//		title(action);
//		mDetailedDisplay(display, total);
//		printf("%d record(s) found.\n", total);
//	}
//	system("pause");
//}
//void deleteMember() {
//	char action[] = "DELETING MEMBERS";
//	int mPlace, count;
//	Members mArray[MAX_MEMBER];
//	count = rData(mArray);
//
//	do {
//		title(action);
//		mPlace = mFind("SEARCHING MEMBERS");
//		if (mPlace > 0) {
//			title(action);
//			mDetailedDisplay(&mArray[mPlace - 1], 1);
//			if (confirm(action)) {
//				title(action);
//				mDetailedDisplay(&mArray[mPlace - 1], 1);
//				count = mDelete(&mArray[mPlace - 1], action, count, mPlace);
//
//			}
//		}
//		else if (mPlace == -1) {
//			backM();
//			break;
//		}
//		else
//		{
//			errorM("INPUT");
//			inexistM();
//			system("pause");
//		}
//		title(action);
//	} while (anymore(action));
//	wData(mArray, count);
//}
//void reportMember() {
//	char action[] = "GENERATING MEMBER REPORTS";
//	int option;
//
//	do {
//		option = mReport(action);
//		if (option == -1)
//			break;
//		else
//			system("pause");
//	} while (anymore(action));
//}
//
////Menus
//int memberMenu() {
//	int num = -1;
//	space(); printf("You would like to :\n");
//	space(); printf("%d. %s\n", ++num, "BACK");
//	space(); printf("%d. %s\n", ++num, "ADD MEMBER(S)");
//	space(); printf("%d. %s\n", ++num, "SEARCH MEMBER(S)");
//	space(); printf("%d. %s\n", ++num, "MODIFY MEMBER(S)");
//	space(); printf("%d. %s\n", ++num, "DISPLAY MEMBER(S)");
//	space(); printf("%d. %s\n", ++num, "DELETE MEMBER(S)");
//	space(); printf("%d. %s\n", ++num, "GENERATE MEMBER REPORT(S)");
//	return num;
//
//}
//int mSearchMenu() {
//	int num = -1;
//	space(); printf("You would like to SEARCH the MEMBER by :\n");
//	space(); printf("%d. %s\n", ++num, "BACK");
//	space(); printf("%d. %s\n", ++num, "Member ID");
//	space(); printf("%d. %s\n", ++num, "Member IC");
//	space(); printf("%d. %s\n", ++num, "Email");
//	space(); printf("%d. %s\n", ++num, "Phone Number");
//	return num;
//}
//int mModifyMenu() {
//	int num = -1;
//	space(); printf("You would like to MODIFY the MEMBER by :\n");
//	space(); printf("%d. %s\n", ++num, "BACK");
//	space(); printf("%d. %s\n", ++num, "Member ID");
//	space(); printf("%d. %s\n", ++num, "Member Name");
//	space(); printf("%d. %s\n", ++num, "Member Gender");
//	space(); printf("%d. %s\n", ++num, "Member IC");
//	space(); printf("%d. %s\n", ++num, "Email");
//	space(); printf("%d. %s\n", ++num, "Phone Number");
//	space(); printf("%d. %s\n", ++num, "Up Line ID");
//	return num;
//}
//int mReportMenu() {
//	int num = -1;
//	space(); printf("You would like to GENERATE MEMBER REPORT of :\n");
//	space(); printf("%d. %s\n", ++num, "BACK");
//	space(); printf("%d. %s\n", ++num, "Top 3 Members who recruit others the most.");
//	space(); printf("%d. %s\n", ++num, "Total number of member from each level");
//	space(); printf("%d. %s\n", ++num, "Top 5 Members with the highest purchasing power");
//	return num;
//}
//
////write,read,append data
//void aData(Members mAdd) {
//	FILE* insert = fopen(MEMBER, "ab");
//	if (chkFile(insert))
//		return;
//	fwrite(&mAdd, sizeof(Members), 1, insert);
//	fclose(insert);
//}
//void wData(Members* a, int i) {
//	FILE* write = fopen(MEMBER, "wb");
//	if (chkFile(write))
//		return;
//
//	for (int j = 0; j < i; j++) {
//		fwrite(a++, sizeof(Members), 1, write);
//	}
//
//	fclose(write);
//}
//int rData(Members* a) {
//	int count = 0;
//	FILE* read = fopen(MEMBER, "rb");
//	if (chkFile(read))
//		return 0;
//
//	while (fread(a++, sizeof(Members), 1, read)) {
//		count++;
//	}
//
//	fclose(read);
//	return count;
//}
//int rSData(Sales* a) {
//	int count = 0;
//	FILE* read = fopen("sales.txt", "r");
//	if (chkFile(read))
//		return 0;
//
//	while (fscanf(read, "%[^|]|%lf\n", a->mSID, &a->amount) != EOF) {
//		count++;
//		a++;
//	}
//
//	fclose(read);
//	return count;
//}
////Determine whether file is opened successfully or not
//int chkFile(FILE* open) {
//	if (open == NULL) {
//		space(); printf("Failed to open the file.\n");
//		return 1;
//	}
//	else
//		return 0;
//}
//
////get member's details
////In Add
//void mAddDetails(Members* a, int use, char action[]) {
//	//get New MEMBER Details
//	//MEMBER ID
//	getMemberID(a, use, action, "MEMBER ID");
//	//back when user input sentinel
//	if (!strcmp(a->mID, EXIT))
//		return;
//	//MEMBER NAME
//	getMemberName(a, use, action, "MEMBER NAME");
//	//GENDER
//	getMemberGender(a, use, action, "GENDER");
//	//IC
//	getMemberIC(a, use, action, "MEMBER IC");
//	//EMAIL
//	getMemberEmail(a, use, action, "MEMBER EMAIL");
//	//PHONE NUMBER
//	getMemberPhone(a, use, action, "PHONE NUMBER");
//	//STATUS
//	getMemberStatus(a);
//	//UPLINE ID
//	getMemberUpline(a, use, action, "Upline ID");
//}
//
////In Search
//void mSearchDetails(Members* a, int opt, char action[]) {
//	int use = 2;
//	title(action);
//	switch (opt) {
//	case 1:
//		getMemberID(a, use, action, "MEMBER ID");
//		break;
//	case 2:
//		getMemberIC(a, use, action, "MEMBER IC");
//		break;
//	case 3:
//		getMemberEmail(a, use, action, "MEMBER EMAIL");
//		break;
//	default:
//		getMemberPhone(a, use, action, "MEMBER PHONE NUMBER");
//	}
//}
////In Modify
//void mModifyDetails(Members* a, int mLocation, int total, int opt, char action[]) {
//	int use = 3;
//	char uplineBefore[MAX_CHAR_MEMBER_ID + 1] = " ";
//	title(action);
//	mDetailedDisplay(a, 1);
//	switch (opt) {
//	case 1:
//		strcpy(uplineBefore, a->mID);
//		getMemberID(a, use, action, "MEMBER ID");
//		updateUpline(a, uplineBefore, mLocation, total);
//		break;
//	case 2:
//		getMemberName(a, use, action, "MEMBER NAME");
//		break;
//	case 3:
//		getMemberGender(a, use, action, "MEMBER GENDER");
//		break;
//	case 4:
//		getMemberIC(a, use, action, "MEMBER IC");
//		break;
//	case 5:
//		getMemberEmail(a, use, action, "MEMBER EMAIL");
//		break;
//	case 6:
//		getMemberPhone(a, use, action, "MEMBER PHONE NUMBER");
//		break;
//	default:
//		getMemberUpline(a, use, action, "UPLINE ID");
//	}
//}
////In Report
//void mReportDetails(int typeOption, char action[]) {
//	switch (typeOption) {
//	case 1:
//		mBestUL(action);
//		break;
//	case 2:
//		mTotal(action);
//		break;
//	case 3:
//		mBuyMost(action);
//	}
//}
//void mBestUL(char action[]) {
//	int rptLength = 30, rptWidth = PAGE_WIDTH - 4;
//	int minusH = 7;
//	int noBest = 3;
//	UpLines best[3];
//
//	mFilterBest(best, noBest);
//
//	title(action);
//	printf("\n");
//	rptLine(rptWidth);
//	minusH += rptTitle("Top 3 Members who recruit others the most", rptWidth);
//	rptContentHead("MEMBER ID", "No. OF RECRUITMENT", rptWidth);
//	minusH += rptUContent(best, noBest, rptWidth, "No. OF RECRUITMENT");
//	rptIntContentFoot(best[0].upLineID, "recruits the most :", best[0].noRecruit, rptWidth);
//	rptBlank(rptLength - minusH, rptWidth);
//	rptLine(rptWidth);
//
//}
//void mTotal(char action[]) {
//	int rptLength = 30, rptWidth = PAGE_WIDTH - 4, minusH = 7;
//	Levels noStatus[MAX_STATUS] = {
//		{"IRON",0},
//		{"BRONZE",0},
//		{"SILVER",0},
//		{"GOLD",0},
//		{"PLATINUM",0},
//		{"DIAMOND",0}
//	};
//	Levels mostStatus = { " ",-1 };
//
//	mFilterStatus(noStatus, &mostStatus);
//
//	title(action);
//	printf("\n");
//	rptLine(rptWidth);
//	minusH += rptTitle("Total number of member from each level", rptWidth);
//	rptContentHead("STATUS", "NO. OF MEMBERS", rptWidth);
//	minusH += rptSContent(noStatus, rptWidth, "NO. OF MEMBERS");
//	rptIntContentFoot(mostStatus.memberStatus, "having the most MEMBER(S) :", mostStatus.noMember, rptWidth);
//	rptBlank(rptLength - minusH, rptWidth);
//	rptLine(rptWidth);
//}
//void mBuyMost(char action[]) {
//	int rptLength = 30, rptWidth = PAGE_WIDTH - 4;
//	int minusH = 7;
//	int noPower = 5;
//	Power strong[5];
//
//	mFilterPower(strong, noPower);
//
//	title(action);
//	printf("\n");
//	rptLine(rptWidth);
//	minusH += rptTitle("Top 5 Members with the highest purchasing power", rptWidth);
//	rptContentHead("MEMBER ID", "PURCHASING POWER", rptWidth);
//	minusH += rptDbContent(strong, noPower, rptWidth, "PURCHASING POWER");
//	rptDbContentFoot(strong[0].memberID, "having the highest purchasing power : RM", strong[0].sPower, rptWidth);
//	rptBlank(rptLength - minusH, rptWidth);
//	rptLine(rptWidth);
//}
////In Best UPLINE
//void mFilterBest(UpLines* b, int noBest) {
//	int total, totalU;
//	Members mArray[MAX_MEMBER];
//	UpLines uArray[MAX_MEMBER];
//	total = rData(mArray);
//
//	emptyUArray(uArray, total);
//	totalU = sortUArray(mArray, uArray, total);
//	sortUAsc(uArray, totalU);
//	getUBest(b, uArray, noBest);
//}
//void emptyUArray(UpLines* b, int total) {
//	UpLines* test;
//	for (int i = 0; i < total; i++) {
//		test = b + i;
//		test->noRecruit = 0;
//		strcpy(test->upLineID, DEFAULT_ID);
//	}
//}
//int sortUArray(Members* a, UpLines* b, int total) {
//	Members* testM;
//	UpLines* testU;
//	int count = 0;
//	for (int i = 0; i < total; i++) {
//		testM = a + i;
//		for (int j = 0; j < total; j++) {
//			testU = b + j;
//			if (!strcmp(testU->upLineID, DEFAULT_ID)) {
//				strcpy(testU->upLineID, testM->mUpID);
//				testU->noRecruit++;
//				count++;
//				break;
//			}
//			else if (!strcmp(testU->upLineID, testM->mUpID))
//				testU->noRecruit++;
//		}
//	}
//	return count;
//}
//void sortUAsc(UpLines* b, int total) {
//	UpLines* placeU;
//	UpLines change[MAX_MEMBER];
//	int order[MAX_MEMBER][2] = { 0 }, test = 0, middleMan;
//	//assign order number for each no of recruit of each UPLINE
//	for (int i = 0; i < total; i++) {
//		placeU = b + i;
//		order[i][0] = i;
//
//		order[i][1] = placeU->noRecruit;
//	}
//
//	//get ascending order
//	while (test == 0) {
//		test = 0;
//		for (int i = 0; i < total; i++) {
//			if (order[order[i][0]][1] < order[order[i + 1][0]][1]) {
//				middleMan = order[i][0];
//				order[i][0] = order[i + 1][0];
//				order[i + 1][0] = middleMan;
//
//				test = 1;
//			}
//		}
//	}
//
//	//sort the data by ascending order
//	for (int i = 0; i < total; i++) {
//		placeU = b + order[i][0];
//		change[i].noRecruit = placeU->noRecruit;
//		strcpy(change[i].upLineID, placeU->upLineID);
//	}
//	//cpy and paste the data to array
//	for (int i = 0; i < total; i++) {
//		placeU = b + i;
//		placeU->noRecruit = change[i].noRecruit;
//		strcpy(placeU->upLineID, change[i].upLineID);
//	}
//}
//void getUBest(UpLines* best, UpLines* all, int total) {
//	UpLines* placeU;
//	for (int i = 0; i < total; i++) {
//		placeU = all + i;
//		best->noRecruit = placeU->noRecruit;
//		strcpy(best->upLineID, placeU->upLineID);
//		best++;
//	}
//}
////In Total MEMBER in each LEVEL
//int rptSContent(Levels* c, int width, char intTitle[]) {
//	Levels* test;
//	int count = 0;
//
//	for (int i = 0; i < MAX_STATUS; i++) {
//		rptLeft();
//		test = c + i;
//		makeMiddle(test->memberStatus, width / 2);
//		makeIntFit(test->noMember, intTitle, width / 2);
//		rptRight();
//		count++;
//	}
//
//	return count;
//}
//void mFilterStatus(Levels* c, Levels* most) {
//	int count;
//	Members mArray[MAX_MEMBER];
//	count = rData(mArray);
//	sortSArray(mArray, c, count);
//	mostS(most, c);
//
//}
//void sortSArray(Members* a, Levels* c, int total) {
//	Members* testA;
//	Levels* testC;
//	for (int i = 0; i < MAX_STATUS; i++) {
//		testC = c + i;
//		for (int j = 0; j < total; j++) {
//			testA = a + j;
//			if (!strcmp(testC->memberStatus, testA->mStatus))
//				testC->noMember++;
//		}
//	}
//}
//void mostS(Levels* most, Levels* c) {
//	for (int i = 0; i < MAX_STATUS; i++) {
//		if (most->noMember < c->noMember) {
//			most->noMember = c->noMember;
//			strcpy(most->memberStatus, c->memberStatus);
//		}
//		c++;
//	}
//}
////In Highest Purchasing Power
//void mFilterPower(Power* d, int total) {
//	int count;
//	Members mArray[MAX_MEMBER];
//	Power pArray[MAX_MEMBER];
//	count = rData(mArray);
//
//	emptyPArray(pArray, mArray, count);
//	sortPArray(pArray, count);
//	sortPAsc(pArray, count);
//	getPBest(d, pArray, total);
//
//}
//void emptyPArray(Power* b, Members* a, int total) {
//	Power* test;
//	for (int i = 0; i < total; i++) {
//		test = b + i;
//		test->sPower = 0;
//		strcpy(test->memberID, a->mID);
//	}
//}
//void sortPArray(Power* d, int total) {
//	Sales mSales[999];
//	Power* testP;
//	int count;
//	count = rSData(mSales);
//
//	for (int i = 0; i < total; i++) {
//		testP = d + i;
//		for (int j = 0; j < count; j++) {
//			if (!strcmp(testP->memberID, mSales[i].mSID))
//				testP->sPower += mSales[i].amount;
//		}
//	}
//}
//void sortPAsc(Power* b, int total) {
//	Power* placeP;
//	Power change[MAX_MEMBER];
//	int order[MAX_MEMBER], test = 0, middleMan;
//	double moneyAmt[MAX_MEMBER] = { 0.00 };
//	//assign order number for each no of recruit of each UPLINE
//	for (int i = 0; i < total; i++) {
//		placeP = b + i;
//		order[i] = i;
//		moneyAmt[i] = placeP->sPower;
//	}
//
//	//get ascending order
//	while (test == 0) {
//		test = 0;
//		for (int i = 0; i < total; i++) {
//			if (moneyAmt[order[i]] < moneyAmt[order[i] + 1]) {
//				middleMan = order[i];
//				order[i] = order[i + 1];
//				order[i + 1] = middleMan;
//
//				test = 1;
//			}
//		}
//	}
//
//	//sort the data by ascending order
//	for (int i = 0; i < total; i++) {
//		placeP = b + order[i];
//		change[i].sPower = placeP->sPower;
//		strcpy(change[i].memberID, placeP->memberID);
//	}
//	//cpy and paste the data to array
//	for (int i = 0; i < total; i++) {
//		placeP = b + i;
//		placeP->sPower = change[i].sPower;
//		strcpy(placeP->memberID, change[i].memberID);
//	}
//}
//void getPBest(Power* strongest, Power* all, int total) {
//	Power* placeP;
//	for (int i = 0; i < total; i++) {
//		placeP = all + i;
//		strongest->sPower = placeP->sPower;
//		strcpy(strongest->memberID, placeP->memberID);
//		strongest++;
//	}
//}
//
////sub function for sub modules
//void mDisplay(Members* a, int total) {
//	tableHead();
//	for (int i = 0; i < total; i++) {
//		space();
//		printf("%-9s", a->mID);
//		gap();
//		printf("%-20s", a->mName);
//		gap();
//		printf("%-12s", a->mIC);
//		gap();
//		printf("%-30s", a->mContact.email);
//		gap();
//		printf("%-10s", a->mContact.phone);
//		printf("\n");
//		a++;
//	}
//	line();
//}
//void mDetailedDisplay(Members* a, int total) {
//	int width = PAGE_WIDTH;
//	for (int i = 0; i < total; i++) {
//		if (a->mGender == 'F')
//			female();
//		else
//			male();
//		space(); makeMiddle(a->mName, width);
//		printf("\n\n");
//		space(); spacing(); printf("%45s : %s\n", "MEMBER ID", a->mID);
//		space(); spacing(); printf("%45s : %s\n", "IC NUMBER", a->mIC);
//		space(); spacing(); printf("%45s : %s\n", "EMAIL", a->mContact.email);
//		space(); spacing(); printf("%45s : %s\n", "PHONE NUMBER", a->mContact.phone);
//		space(); spacing(); printf("%45s : %s\n", "STATUS", a->mStatus);
//		if (!strcmp(a->mUpID, DEFAULT_ID))
//		{
//			space(); spacing(); printf("%45s : %s\n", "UPLINE ID", " N/A ");
//		}
//		else
//		{
//			space(); spacing(); printf("%45s : %s\n", "UPLINE ID", a->mUpID);
//		}
//		printf("\n");
//		line();
//		printf("\n");
//		a++;
//	}
//}
//int mModify(Members* a, char action[]) {
//	int opt, totalOpt;
//	do {
//		title(action);
//		mDetailedDisplay(a, 1);
//		totalOpt = mModifyMenu();
//		opt = getOption(totalOpt);
//		if (opt > 0)
//			return opt;
//		else if (opt == 0)
//			return -1;
//		else
//			system("pause");
//	} while (opt < 0);
//}
//int mFind(char action[]) {
//	Members find;
//	int opt, totalOpt;
//	do {
//		title(action);
//		totalOpt = mSearchMenu();
//		opt = getOption(totalOpt);
//		if (opt > 0) {
//			mSearchDetails(&find, opt, action);
//			return mChkRedundancy(&find);
//		}
//		else if (opt == 0)
//			return -1;
//		else
//			system("pause");
//	} while (opt < 0);
//}
//int mDelete(Members* a, char action[], int total, int mPlace) {
//	Members* current;
//	Members* after;
//	for (int i = mPlace - 1; i < total; i++) {
//		current = a + i;
//		after = current + 1;
//		strcpy(current->mID, after->mID);
//		strcpy(current->mName, after->mName);
//		current->mGender = after->mGender;
//		strcpy(current->mIC, after->mIC);
//		strcpy(current->mContact.email, after->mContact.email);
//		strcpy(current->mContact.phone, after->mContact.phone);
//		strcpy(current->mStatus, after->mStatus);
//		strcpy(current->mUpID, after->mUpID);
//	}
//	return total - 1;
//}
//int mReport(char action[]) {
//	int opt, totalOpt;
//	do {
//		title(action);
//		totalOpt = mReportMenu();
//		opt = getOption(totalOpt);
//		if (opt > 0) {
//			mReportDetails(opt, action);
//			return 1;
//		}
//		else if (opt == 0)
//			return -1;
//		else
//			system("pause");
//	} while (opt < 0);
//}
//
////accept input
//void acceptMemberID(Members* a, int use, char action[], char method[]) {
//	char inputString[100] = " ";
//	//if "use" value =
//	//1 : add function
//	//2 : search function
//	//3 : modify function
//	switch (use) {
//	case 1:
//		space(); printf("%s : ", "Member ID (\"XXX\" to EXIT)");
//		break;
//	case 2:
//	case 3:
//		//PROMPT USER
//		mMethod(action, method);
//	}
//	gets(inputString);
//	rewind(stdin);
//	strncpy(a->mID, inputString, MAX_CHAR_MEMBER_ID);
//	a->mID[MAX_CHAR_MEMBER_ID] = '\0';
//}
//void acceptMemberName(Members* a, int use, char action[], char method[]) {
//	char inputString[100];
//	//if "use" value =
//	//1 : add function
//	//2 : search function
//	//3 : modify function
//	switch (use) {
//	case 1:
//		space(); printf("%s : ", "Member Name");
//		break;
//	case 2:
//	case 3:
//		//PROMPT USER
//		mMethod(action, method);
//	}
//	gets(inputString);
//	rewind(stdin);
//	strncpy(a->mName, inputString, MAX_CHAR_MEMBER_NAME);
//	a->mName[MAX_CHAR_MEMBER_NAME] = '\0';
//}
//void acceptMemberGender(Members* a, int use, char action[], char method[]) {
//	//if "use" value =
//	//1 : add function
//	//2 : search function
//	//3 : modify function
//	switch (use) {
//	case 1:
//		space(); printf("%s : ", "Gender (F = Female / M = Male)");
//		break;
//	case 2:
//	case 3:
//		//PROMPT USER
//		mMethod(action, method);
//	}
//
//	a->mGender = getchar();
//	rewind(stdin);
//}
//void acceptMemberIC(Members* a, int use, char action[], char method[]) {
//	char inputString[100];
//	//if "use" value =
//	//1 : add function
//	//2 : search function
//	//3 : modify function
//	switch (use) {
//	case 1:
//		space(); printf("%s : ", "Member IC");
//		break;
//	case 2:
//	case 3:
//		//PROMPT USER
//		mMethod(action, method);
//	}
//	gets(inputString);
//	rewind(stdin);
//	strncpy(a->mIC, inputString, MAX_CHAR_MEMBER_IC);
//	a->mIC[MAX_CHAR_MEMBER_IC] = '\0';
//}
//void acceptMemberEmail(Members* a, int use, char action[], char method[]) {
//	char inputString[100];
//	//if "use" value =
//	//1 : add function
//	//2 : search function
//	//3 : modify function
//	switch (use) {
//	case 1:
//		space(); printf("%s : ", "Email (E.g XXX@sample.com)");
//		break;
//	case 2:
//	case 3:
//		//PROMPT USER
//		mMethod(action, method);
//	}
//	gets(inputString);
//	rewind(stdin);
//	strncpy(a->mContact.email, inputString, MAX_CHAR_MEMBER_EMAIL);
//	a->mContact.email[MAX_CHAR_MEMBER_EMAIL] = '\0';
//}
//void acceptMemberPhone(Members* a, int use, char action[], char method[]) {
//	char inputString[100];
//	//if "use" value =
//	//1 : add function
//	//2 : search function
//	//3 : modify function
//	switch (use) {
//	case 1:
//		space(); printf("%s : ", "Phone Number");
//		break;
//	case 2:
//	case 3:
//		//PROMPT USER
//		mMethod(action, method);
//	}
//
//	gets(inputString);
//	rewind(stdin);
//	strncpy(a->mContact.phone, inputString, MAX_CHAR_MEMBER_PHONE);
//	a->mContact.phone[MAX_CHAR_MEMBER_PHONE] = '\0';
//}
//void acceptUplineID(Members* a, int use, char action[], char method[]) {
//	char inputString[100];
//	//if "use" value =
//	//1 : add function
//	//2 : search function
//	//3 : modify function
//	switch (use) {
//	case 1:
//		space(); printf("%s : ", "Up Line ID (Only existing MEMBER ID will be saved)");
//		break;
//	case 2:
//	case 3:
//		//PROMPT USER
//		space(); printf("%s\n", "*Only existing MEMBER ID will be saved*");
//		mMethod(action, method);
//	}
//
//	gets(inputString);
//	rewind(stdin);
//	strncpy(a->mUpID, inputString, MAX_CHAR_MEMBER_ID);
//	a->mUpID[MAX_CHAR_MEMBER_ID] = '\0';
//}
//
////get valid input
//void getMemberID(Members* a, int use, char action[], char method[]) {
//	int chkValid, repeatTimes;
//	do {
//		chkValid = 1;
//		acceptMemberID(a, use, action, method);
//		switch (use) {
//		case 1://add function
//			if (!strcmp(a->mID, EXIT))
//				return;
//			if (mChkRedundancy(a)) {
//				chkValid = 0;
//				existM(method);
//			}
//			break;
//		case 2://search function
//			break;
//		case 3://modify function
//			repeatTimes = mChkRedundancyTimes(a);
//			if (repeatTimes > 1) {
//				existM(method);
//				chkValid = 0;
//			}
//		}
//		//check if valid ID entered
//		if (chkValid == 1)
//			chkValid = validMemberID(a->mID, MAX_CHAR_MEMBER_ID, method);
//	} while (chkValid == 0);
//}
//void getMemberName(Members* a, int use, char action[], char method[]) {
//	int chkValid;
//	do {
//		chkValid = 1;
//		acceptMemberName(a, use, action, method);
//		switch (use) {//future use
//		case 1://add function
//		case 2://search function
//		case 3://modify function
//			break;
//		}
//		//check if valid NAME entered
//		if (chkValid == 1)
//			chkValid = validName(a->mName, method);
//	} while (chkValid == 0);
//}
//void getMemberGender(Members* a, int use, char action[], char method[]) {
//	int chkValid;
//	do {
//		chkValid = 1;
//		acceptMemberGender(a, use, action, method);
//		a->mGender = toupper(a->mGender);
//		switch (use) {//future use
//		case 1://add function
//		case 2://search function
//		case 3://modify function
//			break;
//		}
//		//check if valid GENDER entered
//		if (chkValid == 1)
//			chkValid = validGender(a->mGender, method);
//	} while (chkValid == 0);
//}
//void getMemberIC(Members* a, int use, char action[], char method[]) {
//	int chkValid, repeatTimes;
//	do {
//		chkValid = 1;
//		acceptMemberIC(a, use, action, method);
//		switch (use) {
//		case 1://add function
//			if (mChkRedundancy(a)) {
//				chkValid = 0;
//				existM(method);
//			}
//			break;
//		case 2://search function
//			break;
//		case 3://modify function
//			repeatTimes = mChkRedundancyTimes(a);
//			if (repeatTimes > 1) {
//				existM(method);
//				chkValid = 0;
//			}
//		}
//		//check if valid ID entered
//		if (chkValid == 1)
//			chkValid = validDigit(a->mIC, MAX_CHAR_MEMBER_IC, method);
//	} while (chkValid == 0);
//}
//void getMemberEmail(Members* a, int use, char action[], char method[]) {
//	int chkValid, repeatTimes;
//	do {
//		chkValid = 1;
//		acceptMemberEmail(a, use, action, method);
//		switch (use) {
//		case 1://add function
//			if (mChkRedundancy(a)) {
//				chkValid = 0;
//				existM(method);
//			}
//			break;
//		case 2://search function
//			break;
//		case 3://modify function
//			repeatTimes = mChkRedundancyTimes(a);
//			if (repeatTimes > 1) {
//				existM(method);
//				chkValid = 0;
//			}
//		}
//		//check if valid ID entered
//		if (chkValid == 1)
//			chkValid = validString(a->mContact.email, strlen(a->mContact.email), '@', "EMAIL FORMAT");
//	} while (chkValid == 0);
//}
//void getMemberPhone(Members* a, int use, char action[], char method[]) {
//	int chkValid, repeatTimes;
//	do {
//		chkValid = 1;
//		acceptMemberPhone(a, use, action, method);
//		switch (use) {
//		case 1://add function
//			if (mChkRedundancy(a)) {
//				chkValid = 0;
//				existM(method);
//			}
//			break;
//		case 2://search function
//			break;
//		case 3://modify function
//			repeatTimes = mChkRedundancyTimes(a);
//			if (repeatTimes > 1) {
//				existM(method);
//				chkValid = 0;
//			}
//		}
//		//check if valid ID entered
//		if (chkValid == 1)
//			chkValid = validDigit(a->mContact.phone, MAX_CHAR_MEMBER_PHONE, "PHONE NUMBER");
//	} while (chkValid == 0);
//}
//void getMemberStatus(Members* a) {
//	strcpy(a->mStatus, "IRON");
//}
//void getMemberUpline(Members* a, int use, char action[], char method[]) {
//	acceptUplineID(a, use, action, method);
//	if (!chkUplineMember(a->mUpID))
//		strcpy(a->mUpID, DEFAULT_ID);
//}
//
////update data
//void updateUpline(Members* a, char uplineBefore[], int mLocation, int total) {
//	Members* starting;
//	starting = a - mLocation;
//	for (int i = 0; i < total; i++) {
//		if (!strcmp(starting->mUpID, uplineBefore)) {
//			strcpy(starting->mUpID, a->mID);
//		}
//		starting++;
//	}
//}
//
////clear data
//void clearData(Members* a, int total) {
//	char emptyString[100] = "\0";
//	for (int i = 0; i < total; i++) {
//		strncpy(a->mID, emptyString, MAX_CHAR_MEMBER_ID);
//		strncpy(a->mName, emptyString, MAX_CHAR_MEMBER_NAME);
//		strncpy(a->mIC, emptyString, MAX_CHAR_MEMBER_IC);
//		strncpy(a->mContact.email, emptyString, MAX_CHAR_MEMBER_EMAIL);
//		strncpy(a->mContact.phone, emptyString, MAX_CHAR_MEMBER_PHONE);
//		strncpy(a->mUpID, emptyString, MAX_CHAR_MEMBER_ID);
//		a->mGender = '\0';
//		a++;
//	}
//}
//
////messages
//void errorM(char what[]) {
//	space(); printf("%s\n", "!!! ERROR !!!");
//	space(); printf("*Invalid %s*\n\n", what);
//}
//void existM(char what[]) {
//	space(); printf("This %s exists.\n", what);
//}
//void inexistM() {
//	space(); printf("%s\n", "The MEMBER does not exists in the system");
//}
//void successM() {
//	space(); printf("%s\n", "~~ DONE ~~");
//}
//void addM() {
//	space(); printf("%s\n", "The MEMBER data has successfully added.");
//}
//void declineM() {
//	space(); printf("%s\n", "~~ DECLINED ~~");
//}
//void backM() {
//	printf("\n");
//	printf("%s\n", "Okay, let's back to MENU.");
//	system("pause");
//}
//void mMethod(char action[], char method[]) {
//	space(); printf("You have chosen METHOD : %s By %s.\n", action, method);
//	space(); printf("Please enter %s.\n", method);
//	space(); printf("> ");
//}
//
////get option
//int getOption(int maxOpt) {
//	char opt[100] = " ";
//	printf("\n");
//	space();
//	printf("Choose one > ");
//
//	gets(opt);
//	rewind(stdin);
//
//	return optValidation(opt, M_MIN_OPT, maxOpt);
//}
//int confirm(char action[]) {
//	char chkConfirm, yesNo[100] = " ";
//	printf("\n");
//	space();
//	printf("%s %s%s\n", "Confirm", action, "? (y / Y = YES, any other input = NO)");
//	space();
//	printf("> ");
//	gets(yesNo);
//	rewind(stdin);
//	yesNo[0] = toupper(yesNo[0]);
//	if (!strcmp(yesNo, "Y")) {
//		chkConfirm = 'Y';
//	}
//	else {
//		chkConfirm = 'N';
//	}
//	if (toupper(chkConfirm) == 'Y') {
//		printf("\n");
//		successM();
//		system("pause");
//		return 1;
//	}
//	else {
//		printf("\n");
//		declineM();
//		system("pause");
//		return 0;
//	}
//}
//int anymore(char action[]) {
//	char chkMore, yesNo[999] = " ";
//	printf("\n");
//	space();
//	printf("%s %s%s\n", "Continue", action, "? (y / Y = YES, any other input = NO)");
//	space();
//	printf("> ");
//
//	gets(yesNo);
//	rewind(stdin);
//	yesNo[0] = toupper(yesNo[0]);
//	if (!strcmp(yesNo, "Y")) {
//		chkMore = 'Y';
//	}
//	else {
//		chkMore = 'N';
//	}
//	if (toupper(chkMore) == 'Y') {
//		printf("\n");
//		space();
//		printf("%s %s%s\n", "Okay, Continue", action, ".");
//		system("pause");
//		system("cls");
//		return 1;
//	}
//	else {
//		printf("\n");
//		printf("%s\n", "Okay, let's back to MENU.");
//		system("pause");
//		system("cls");
//		return 0;
//	}
//}
////validation
//int optValidation(char opt[], int minOpt, int maxOpt) {
//	int length = 0, index = 0, wordLength;
//	wordLength = strlen(opt);
//	for (int i = 0; i < wordLength; i++) {
//		if (isdigit(opt[i])) {
//			length++;
//			index = i;
//		}
//		else if (!isspace(opt[i]))
//			length++;
//	}
//	if (length == 1) {
//		for (int i = 0; i <= 9; i++) {
//			if ((opt[index] < minOpt + 48) || (opt[index] > maxOpt + 48)) {
//				printf("Invalid Input!! Please Enter Integer (%d-%d) Only!!\n\n", minOpt, maxOpt);
//				return -1;
//			}
//			else if (opt[index] == i + 48)
//				return i;
//		}
//	}
//	else {
//		printf("Invalid Input!! Please Enter Integer (%d-%d) Only!!\n\n", minOpt, maxOpt);
//		return -1;
//	}
//}
//int validDigit(char text[], int length, char data[]) {
//	for (int i = 0; i < length; i++) {
//		if (!isdigit(text[i])) {
//			if (data != NULL) {
//				errorM(data);
//			}
//			return 0;
//		}
//	}
//	return 1;
//}
//int validString(char text[], int length, char mustInclude, char data[]) {
//	for (int i = 0; i < length; i++) {
//		if (text[i] == mustInclude) {
//			return 1;
//		}
//	}
//	if (data != NULL) {
//		errorM(data);
//	}
//	return 0;
//}
//int validGender(char gender, char data[]) {
//	if (gender != 'F' && gender != 'M') {
//		if (data != NULL) {
//			errorM(data);
//		}
//		return 0;
//	}
//	else
//		return 1;
//}
//int validName(char text[], char data[]) {
//	int length = strlen(text);
//	for (int i = 0; i < length; i++) {
//		if (isdigit(text[i])) {
//			if (data != NULL) {
//				errorM(data);
//			}
//			return 0;
//		}
//	}
//	return 1;
//}
//int validMemberID(char text[], int length, char data[]) {
//	for (int i = 0; i < length; i++) {
//		if (isspace(text[i]) || text[i] == '\0') {
//			if (data != NULL) {
//				errorM(data);
//			}
//			return 0;
//		}
//	}
//	return 1;
//}
////others
////formating
//void space() {
//	//printf("%30s", " ");
//}
//void gap() {
//	printf("%4s", " ");
//}
//void line() {
//	space();
//	for (int i = 0; i < PAGE_WIDTH; i++) {
//		printf(":");
//	}
//	printf("\n");
//}
//void spacing() {
//	for (int i = 0; i < 8; i++)
//		printf(" ");
//}
////formating words position
//void makeMiddle(char text[], int length) {
//	int right, left, sLength = strlen(text), odd, extraSpace;
//	odd = sLength % 2;
//	extraSpace = length % 2;
//	right = (length - (sLength - odd)) / 2;
//	left = right - odd + extraSpace;
//
//
//	for (int i = 0; i < left; i++) {
//		printf(" ");
//	}
//	printf("%s", text);
//	for (int i = 0; i < right; i++) {
//		printf(" ");
//	}
//
//}
//void makeIntFit(int num, char text[], int length) {
//	int left, right, sLength = strlen(text), odd, digit, count = 1, extraSpace;
//	odd = sLength % 2;
//	extraSpace = length % 2;
//	right = (length - (sLength - odd)) / 2;
//	left = right - odd + extraSpace;
//
//	digit = num;
//	do {
//		digit /= 10;
//		if (digit != 0)
//			count++;
//	} while (digit != 0);
//
//	for (int i = 0; i < left + sLength; i++) {
//		printf(" ");
//	}
//	for (int i = 0; i < count; i++)
//		printf("\b");
//	printf("%d", num);
//	for (int i = 0; i < right; i++) {
//		printf(" ");
//	}
//}
//void makeDbFit(double num, char text[], int length) {
//	int left, right, sLength = strlen(text), odd, digit, count = 4, extraSpace;
//	odd = sLength % 2;
//	extraSpace = length % 2;
//	right = (length - (sLength - odd)) / 2;
//	left = right - odd + extraSpace;
//	//remove fractional part
//	digit = num;
//
//	do {
//		digit /= 10;
//		if (digit != 0)
//			count++;
//	} while (digit != 0);
//
//	for (int i = 0; i < left + sLength; i++) {
//		printf(" ");
//	}
//	for (int i = 0; i < count; i++)
//		printf("\b");
//	printf("%.2f", num);
//	for (int i = 0; i < right; i++) {
//		printf(" ");
//	}
//}
////check existance
//int mChkRedundancy(Members* a) {
//	int count;
//	Members checking[MAX_MEMBER];
//	count = rData(checking);
//	for (int i = 0; i < count; i++) {
//		if (!strcmp(checking[i].mID, a->mID))
//			return ++i;
//		else if (!strcmp(checking[i].mIC, a->mIC))
//			return ++i;
//		else if (!strcmp(checking[i].mContact.email, a->mContact.email))
//			return ++i;
//		else if (!strcmp(checking[i].mContact.phone, a->mContact.phone))
//			return ++i;
//	}
//	return 0;
//}
//int mChkRedundancyTimes(Members* a) {
//	int count, redundancyTimes = 0;
//	Members checking[MAX_MEMBER];
//	count = rData(checking);
//	for (int i = 0; i < count; i++) {
//		if (!strcmp(checking[i].mID, a->mID))
//			redundancyTimes++;
//		else if (!strcmp(checking[i].mIC, a->mIC))
//			redundancyTimes++;
//		else if (!strcmp(checking[i].mContact.email, a->mContact.email))
//			redundancyTimes++;
//		else if (!strcmp(checking[i].mContact.phone, a->mContact.phone))
//			redundancyTimes++;
//	}
//	return redundancyTimes;
//}
//int chkUplineMember(char uplineID[]) {
//	int count;
//	Members checking[MAX_MEMBER];
//	count = rData(checking);
//	for (int i = 0; i < count; i++) {
//		if (!strcmp(checking[i].mID, uplineID))
//			return 1;
//	}
//	return 0;
//}
////title
//void title(char action[]) {
//	system("cls");
//	line();
//	space(); makeMiddle(action, PAGE_WIDTH); printf("\n");
//	line();
//}
////profile picture
//void male() {
//	space(); makeMiddle("                                   ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("                                   ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("            ----------             ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("          /            \\           ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("         /   =      =   \\          ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("        |    O  ||  O    |         ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("        |                |         ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("         \\      \\/      /          ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("         \\            /          ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("          ------------           ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("         /            \\          ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("        /              \\         ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("       /                \\        ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("      /                  \\       ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("     /                    \\      ", PAGE_WIDTH); spacing(); printf("\n");
//}
//void female() {
//	space(); makeMiddle("                                   ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("           ..::::::::..            ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("        .::::::::::::::::.         ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("       .::::::::/\\::::::::.        ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("      :::::/ _      _ \\:::::       ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("     :::::/  U  ||  U  \\:::::      ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("    .::::|      ||      |::::.     ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("    :::::|              |:::::     ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("    ::::::\\     VV     /::::::     ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("    :::::::\\__________/:::::::     ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("    :::::::/          \\:::::::     ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("    ::::::/            \\::::::     ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("         /              \\          ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("        /                \\         ", PAGE_WIDTH); spacing(); printf("\n");
//	space(); makeMiddle("       /                  \\        ", PAGE_WIDTH); spacing(); printf("\n");
//}
////cancel
//void cancel(char action[]) {
//	printf("\n");
//	space(); printf("%s %s.\n", "Cancel", action);
//}
////table format
//void tableLine(int length) {
//	for (int i = 0; i < length; i++) {
//		printf("=");
//	}
//	gap();
//}
//void tableHead() {
//	int num[] = { 9,20,12,30,10 }, count = 0;
//	line();
//	space();
//	printf("%-9s", "MEMBER ID"); count++;
//	gap();
//	printf("%-20s", "MEMBER NAME"); count++;
//	gap();
//	printf("%-12s", "MEMBER IC"); count++;
//	gap();
//	printf("%-30s", "EMAIL"); count++;
//	gap();
//	printf("%-10s", "PHONE NO"); count++;
//	space();
//	printf("\n");
//	for (int i = 0; i < count; i++) {
//		tableLine(num[i]);
//	}
//	printf("\n");
//}
////report layout format
//void rptLine(int width) {
//	rptLeft();
//	for (int i = 0; i < width; i++) {
//		printf(":");
//	}
//	rptRight();
//}
//int rptTitle(char title[], int width) {
//	int row = 0;
//	rptBlank(1, width);
//	rptTitleLine(width); row++;
//	rptTitleContent(title, width); row++;
//	rptTitleLine(width); row++;
//	rptBlank(1, width);
//	return row;
//}
//void rptTitleLine(int width) {
//	rptLeft();
//	spacing();
//	for (int i = 0; i < width - 16; i++) {
//		printf("=");
//	}
//	spacing();
//	rptRight();
//}
//void rptTitleContent(char title[], int width) {
//	rptLeft();
//	spacing();
//	makeMiddle(title, width - 16);
//	spacing();
//	rptRight();
//}
//void rptLeft() {
//	space();
//	printf("::");
//}
//void rptRight() {
//	printf("::");
//	printf("\n");
//}
//void rptBlank(int row, int width) {
//	for (int i = 0; i < row; i++) {
//		rptLeft();
//		for (int j = 0; j < width; j++) {
//			printf(" ");
//		}
//
//		rptRight();
//	}
//}
//void rptContentHead(char a[], char b[], int width) {
//	rptContentTitle(a, b, width / 2);
//	rptContentLine(strlen(a), strlen(b), width / 2);
//}
//void rptContentTitle(char a[], char b[], int width) {
//	rptLeft();
//	makeMiddle(a, width);
//	makeMiddle(b, width);
//	rptRight();
//}
//void rptContentLine(int leftLine, int rightLine, int width) {
//	char left[21] = " ";
//	char right[21] = " ";
//
//	for (int i = 0; i < leftLine; i++) {
//		left[i] = '=';
//	}
//	for (int i = 0; i < rightLine; i++) {
//		right[i] = '=';
//	}
//
//	rptLeft();
//	makeMiddle(left, width);
//	makeMiddle(right, width);
//	rptRight();
//}
////report content formating
//int rptUContent(UpLines* b, int total, int width, char intTitle[]) {
//	UpLines* test;
//	int count = 0;
//
//	for (int i = 0; i < total; i++) {
//		rptLeft();
//		test = b + i;
//		makeMiddle(test->upLineID, width / 2);
//		makeIntFit(test->noRecruit, intTitle, width / 2);
//		rptRight();
//		count++;
//	}
//
//	return count;
//}
//int rptDbContent(Power* b, int total, int width, char intTitle[]) {
//	Power* test;
//	int count = 0;
//
//	for (int i = 0; i < total; i++) {
//		rptLeft();
//		test = b + i;
//		makeMiddle(test->memberID, width / 2);
//		makeDbFit(test->sPower, intTitle, width / 2);
//		rptRight();
//		count++;
//	}
//
//	return count;
//}
//void rptIntContentFoot(char who[], char text[], int total, int width) {
//	int spaceAfterWords, count = 1, digit;
//	digit = total;
//	while (digit != 0) {
//		digit /= 10;
//		if (digit != 0)
//			count++;
//	}
//	spaceAfterWords = width - strlen(who) - strlen(text) - count - 3 - 8;
//	rptLeft();
//	spacing();
//	printf("%s %s %d.", who, text, total);
//	for (int i = 0; i < spaceAfterWords; i++) {
//		printf(" ");
//	}
//	rptRight();
//}
//void rptDbContentFoot(char who[], char text[], double total, int width) {
//	int spaceAfterWords, count = 1;
//	double digit;
//	digit = total;
//	while (digit != 0) {
//		digit /= 10;
//		if (digit != 0)
//			count++;
//	}
//	spaceAfterWords = width - strlen(who) - strlen(text) - count - 3 - 8 - 3;
//	rptLeft();
//	spacing();
//	printf("%s %s %.2f.", who, text, total);
//	for (int i = 0; i < spaceAfterWords; i++) {
//		printf(" ");
//	}
//	rptRight();
//}