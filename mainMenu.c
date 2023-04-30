#include<stdio.h>
#include<stdlib.h>
#include "Declarations.h"
#pragma warning(disable:4996)

void main() {
	int opt;
    StaffLogin();
	do {
		CLS;
		mainLogo();ENTER;
        line(); ENTER;
        makeMiddle("MAIN MENU", PAGE_WIDTH); ENTER; ENTER;
		line();
		printf(
			"1. Staff Information Module\n"
			"2. Member Information Module\n"
			"3. Sales Information Module\n"
			"4. Stock Information Module\n"
			"0. EXIT\n"
		);
	
		do {
			switch (opt = promptInteger("\nEnter your selection (0-4) : ")) {
			case 1:
				CLS; StaffMenu(); break;
			case 2:
				CLS; membermain();  break;
			case 3:
				CLS; salesmain(); break;
			case 4:
				CLS; stockmain(); break;
			case 0:
				exit(-1); break;
			default:
				errorM("Input Please Enter Integer (0-4) Only");break;
			}
		} while (opt < 0 || opt>4);
	} while (opt != 0);
}

void mainLogo() {
	line(); ENTER;
	makeMiddle("                 ~!                         ", PAGE_WIDTH); ENTER;
	makeMiddle("              :?P&P                         ", PAGE_WIDTH); ENTER;
	makeMiddle("           :^ ^&@@P            :^           ", PAGE_WIDTH); ENTER;
	makeMiddle("         ~Y#? ^#&&P            :BP7:        ", PAGE_WIDTH); ENTER;
	makeMiddle("       :G&@@? ^#&&P            :B@&G:       ", PAGE_WIDTH); ENTER;
	makeMiddle("   ^!  Y@&&@? ^#&@P            :B&&@J  :?!: ", PAGE_WIDTH); ENTER;
	makeMiddle("!5#&7!&& &&@? ^#&@P            :B&&&&~7@&BY:", PAGE_WIDTH); ENTER;
	makeMiddle("^#@&&BB&&&&@? ^#&@P            :B&&&&GB&&&&^", PAGE_WIDTH); ENTER;
	makeMiddle("^#&&&&&&&&&@? ^#&@P            :B&&&&&&&&&#^", PAGE_WIDTH); ENTER;
	makeMiddle("^#&&#&&&#&&@? ^#&@P            :B&&&#&&#&&#^", PAGE_WIDTH); ENTER;
	makeMiddle("^#&&55BY5&&@? ^#&@P            :B&&B?#5Y@&#^", PAGE_WIDTH); ENTER;
	makeMiddle("^#&@Y : 5@&@? ^#&@P            :B&&B:: J@&#^", PAGE_WIDTH); ENTER;
	makeMiddle("^&&@Y   5@&@? ^#&@P      :^^^: :B&&B:  Y@&&^", PAGE_WIDTH); ENTER;
	makeMiddle("^G#@5   5@&@? ^#&@P      !###J :B&&B:  Y@&G^", PAGE_WIDTH); ENTER;
	makeMiddle("  ^?7   P@&@? ^#&@P      !&&@Y :B&&B:  7J~  ", PAGE_WIDTH); ENTER;
	makeMiddle("        J#&@? ^#&@P      ~&&@Y :#@&G:       ", PAGE_WIDTH); ENTER;
	makeMiddle("         ^757 ^&@&#J~: ^7P&&@Y :PJ!:        ", PAGE_WIDTH); ENTER;
	makeMiddle("              :JG&@@&BG#@@@#G7              ", PAGE_WIDTH); ENTER;
	makeMiddle("                 ~?P#@@&B57^                ", PAGE_WIDTH); ENTER;
	makeMiddle("                    ^7?~:                   ", PAGE_WIDTH); ENTER; ENTER;
	makeMiddle(" /$$$$$$$   /$$$$$$$  /$$$$$$   /$$$$$$  /$$   /$$ /$$   /$$", PAGE_WIDTH); ENTER;
	makeMiddle("| $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$| $$  /$$/| $$  | $$", PAGE_WIDTH); ENTER;
	makeMiddle("| $$  \\ $$| $$  \\ $$| $$  \\__/| $$  \\__/| $$ /$$/ | $$  | $$", PAGE_WIDTH); ENTER;
	makeMiddle("| $$$$$$$ | $$  | $$|  $$$$$$ |  $$$$$$ | $$$$$/  | $$  | $$", PAGE_WIDTH); ENTER;
	makeMiddle("| $$__ $$ | $$  | $$ \\____  $$ \\____  $$| $$  $$  | $$  | $$", PAGE_WIDTH); ENTER;
	makeMiddle("| $$  \\ $$| $$  | $$ /$$  \\ $$ /$$  \\ $$| $$\\  $$ | $$  | $$", PAGE_WIDTH); ENTER;
	makeMiddle("| $$$$$$$/|  $$$$$$/|  $$$$$$/|  $$$$$$/| $$ \\  $$|  $$$$$$/", PAGE_WIDTH); ENTER;
	makeMiddle("|_______/  \\______/  \\______/  \\______/ |__/  \\__/ \\______/ ", PAGE_WIDTH); ENTER;
}