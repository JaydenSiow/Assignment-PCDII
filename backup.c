//#include<stdio.h>
//#include<stdlib.h>
//#include<ctype.h>
//#include<string.h>
//#pragma warning(disable:4996)
//
//
//typedef struct {
//	char email[31];
//	char phone[11];
//}Contacts;
//typedef struct {
//	char mID[6];
//	char mName[21];
//	char mGender;
//	char mIC[13];
//	Contacts mContact;
//	char mStatus[10];
//	char mUpID[6];
//}Members;
//
//void main() {
//	Members membersList[10] = {
//		{"M0001", "John Doe", 'M', "010101101010", {"johntheBest1132@gmail.com","0123456781"}, "IRON", "AAAAA"},
//		{"M0002", "Jane Smith", 'F', "020202202020", {"J4neDaB34uty@gmail.com","0123456782"}, "IRON", "M0001"},
//		{"M0003", "Mike Johnson", 'M', "030303303030", {"MikeNotNike2333@gmail.com","0123456783"}, "IRON", "M0002"},
//		{"M0004", "Emily Brown", 'F', "040404404040", {"3milyBlue@gmail.com","0123456784"}, "IRON", "M0003"},
//		{"M0005", "David Lee", 'M', "050505505050", {"bruceLeeFans@gmail.com","0123456785"}, "IRON", "M0002"},
//		{"M0006", "Sarah Kim", 'F', "060606606060", {"s4r4hkeem4392@gmail.com","0123456786"}, "IRON", "AAAAA"},
//		{"M0007", "Kevin Chen", 'M', "070707707070", {"chenkevinOHOR@gmail.com","0123456787"}, "IRON", "M0004"},
//		{"M0008", "Linda Wang", 'F', "080808808080", {"laoWangLINDA@gmail.com","0123456788"}, "IRON", "M0003"},
//		{"M0009", "Steven Wu", 'M', "090909909090", {"StevenWUKANG@gmail.com","0123456789"}, "IRON", "M0007"},
//		{"M0010", "Amanda Ng", 'F', "101010101010", {"cuteC4tAMANDA@gmail.com","0123456790"}, "IRON", "M0005"}
//	};
//	FILE* backup = fopen("member.bin", "wb");
//	for (int i = 0; i < 10; i++) {
//		fwrite(&membersList[i], sizeof(Members), 1, backup);
//	}
//	printf("done.");
//}
