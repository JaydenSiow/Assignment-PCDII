#include<stdio.h>
#define PAGE_SIZE 110
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
void staffLogo() {
    makeMiddle("        .^7J5GGG5^         ", PAGE_SIZE); printf("\n");
    makeMiddle("       J#@@@@@@@@&7.       ", PAGE_SIZE); printf("\n");
    makeMiddle("      Y@@@@@&#P?!G@G.      ", PAGE_SIZE); printf("\n");
    makeMiddle("      B&7!~^:     G@^      ", PAGE_SIZE); printf("\n");
    makeMiddle("      55....:.:...7&:      ", PAGE_SIZE); printf("\n");
    makeMiddle("     :!.^...~~:..:::7.     ", PAGE_SIZE); printf("\n");
    makeMiddle("     .!^ .... .....~!.     ", PAGE_SIZE); printf("\n");
    makeMiddle("       !:         7^       ", PAGE_SIZE); printf("\n");
    makeMiddle("        ~^.     :!^        ", PAGE_SIZE); printf("\n");
    makeMiddle("     .:  :^~^^^~^.  :.     ", PAGE_SIZE); printf("\n");
    makeMiddle("   !5#&?    :~.    Y@#Y~   ", PAGE_SIZE); printf("\n");
    makeMiddle(" ^B@@@@@5  .#@P  .G@@@@@P: ", PAGE_SIZE); printf("\n");
    makeMiddle(".#@@@@@@@G: 5@7 ~#@@@@@@@G ", PAGE_SIZE); printf("\n");
    makeMiddle("^@@@@@@@@@#!B@57&@@@@@@@@#.", PAGE_SIZE); printf("\n");
    makeMiddle("^@@@@@@@@@@@@@@@@@@@@@@@@#.", PAGE_SIZE); printf("\n");
    makeMiddle("^@@@@@@@@@@@@@@@@@@@@@@@@#.", PAGE_SIZE); printf("\n");
    makeMiddle(":&@@@@@@@@@@@@@@@@@@@@@@@B ", PAGE_SIZE); printf("\n");
    makeMiddle(" ^YB&@@@@@@@@@@@@@@@@@&GJ: ", PAGE_SIZE); printf("\n");
    makeMiddle("    :~7JYPGGGBGGP5YJ7~:    ", PAGE_SIZE); printf("\n");
}
void stockLogo() {
    makeMiddle(".. ...... ..     :~??~:     ............", PAGE_SIZE); printf("\n");
    makeMiddle("  .. ..     .:!JPB##GBBPJ!:.     .. ..  ", PAGE_SIZE); printf("\n");
    makeMiddle(".. ..   .:!JPB#####G.:!JPBBGY!^.   .  ..", PAGE_SIZE); printf("\n");
    makeMiddle("  .  ^7YGB#########B.    .~?5GBGY7: ..  ", PAGE_SIZE); printf("\n");
    makeMiddle(".. .JB#############B. .     ^7G&#&G~ ...", PAGE_SIZE); printf("\n");
    makeMiddle(". :5###Y7YGB#######G.  .^75GBG5?~?#B~ ..", PAGE_SIZE); printf("\n");
    makeMiddle(" ^G#BB#?  .:!JPB###B!?PBBGY7^.    ?#B!  ", PAGE_SIZE); printf("\n");
    makeMiddle(" ^?~^G#?      .:!JP##BJ!^.     .^!J##G: ", PAGE_SIZE); printf("\n");
    makeMiddle("    .G#? .  ..    ~##B7    .^75GB##?~:  ", PAGE_SIZE); printf("\n");
    makeMiddle("... .G#? ........ ~####?~?5BBG5!Y#G.  ..", PAGE_SIZE); printf("\n");
    makeMiddle("..  :G#?  ..  ..  ~##?G#BPJ!^.  ?&G.  ..", PAGE_SIZE); printf("\n");
    makeMiddle("  . .G&5~:     .. ~##^:~:     :^5&G...  ", PAGE_SIZE); printf("\n");
    makeMiddle(".. ..^JPBBPJ~:.   ~##~   .:~JPBBPY^.  ..", PAGE_SIZE); printf("\n");
    makeMiddle(".....  .:!JPBBPY!:~##~:!JPBBPJ!:.  .....", PAGE_SIZE); printf("\n");
    makeMiddle("  .. ..     :~?PBBB##BBBP?!:     .. .. .", PAGE_SIZE); printf("\n");
    makeMiddle(".. ..  .. ..    .~?YY?~.    .  .. ..  ..", PAGE_SIZE); printf("\n");
}
void salesLogo() {
    makeMiddle("      .^^.    .^^.      ", PAGE_SIZE); printf("\n");
    makeMiddle("     :#@@#G55G#@@#:     ", PAGE_SIZE); printf("\n");
    makeMiddle("     ^@@@@@@@@@@@@^     ", PAGE_SIZE); printf("\n");
    makeMiddle("      !&@@@@@@@@&!      ", PAGE_SIZE); printf("\n");
    makeMiddle("     ^Y&@@@@@@@@&Y^     ", PAGE_SIZE); printf("\n");
    makeMiddle("    ?&@@@@&  @@@@@&?    ", PAGE_SIZE); printf("\n");
    makeMiddle("   5@@@@@@5  JP#@@@@5   ", PAGE_SIZE); printf("\n");
    makeMiddle("  5@@@@@G^ :.. J@@@@@5  ", PAGE_SIZE); printf("\n");
    makeMiddle(" 7@@@@@@! :B&@@@@@@@@@7 ", PAGE_SIZE); printf("\n");
    makeMiddle(".#@@@@@@G^ .:~Y&@@@@@@#.", PAGE_SIZE); printf("\n");
    makeMiddle("~@@@@@@@@@#G5. 7@@@@@@@~", PAGE_SIZE); printf("\n");
    makeMiddle("~@@@@@@@P??J?  J@@@@@@@~", PAGE_SIZE); printf("\n");
    makeMiddle("^@@@@@@@5..  7B@@@@@@@@^", PAGE_SIZE); printf("\n");
    makeMiddle(" G@@@@@@@@#  #@@@@@@@@G ", PAGE_SIZE); printf("\n");
    makeMiddle(" :P@@@@@@@@@@@@@@@@@@P: ", PAGE_SIZE); printf("\n");
    makeMiddle("   ~JG#&@@@@@@@@&#GJ~   ", PAGE_SIZE); printf("\n");
    makeMiddle("      .::^^~~^^::.      ", PAGE_SIZE); printf("\n");
}
void memberLogo(){
    makeMiddle("                         .^7??7^.                         ", PAGE_SIZE); printf("\n");
    makeMiddle("                        ?#&GPPG##Y.                       ", PAGE_SIZE); printf("\n");
    makeMiddle("         .:^:.         P@P:    .J@B:         :^:.         ", PAGE_SIZE); printf("\n");
    makeMiddle("       ~P##B##P~      ~@#.       5@Y      :5##B##G7       ", PAGE_SIZE); printf("\n");
    makeMiddle("      7@#!...!#@?     ?@G        ?@G     ~&@7:..~G@5      ", PAGE_SIZE); printf("\n");
    makeMiddle("     .#@~     ^@&:    ^@&:       P@J     P@J     .#@~     ", PAGE_SIZE); printf("\n");
    makeMiddle("     .&@^     :@@:     J@B~.   :5@G.     G@7      B@!     ", PAGE_SIZE); printf("\n");
    makeMiddle("      Y@G:   .5@5       ~#@#GGB@@J       7@#^    ?@B.     ", PAGE_SIZE); printf("\n");
    makeMiddle("       ?@&GPP&@Y.   .:~?P&B7~!~5&BY!^.    !&@BPP#@P.      ", PAGE_SIZE); printf("\n");
    makeMiddle("   :~7YB&G7?75&P..JGB#BPJ~      :75B##BP~ ?&B?77Y##P?~^.  ", PAGE_SIZE); printf("\n");
    makeMiddle(" ~B&BG57:     :^ G@5^:              .:!&@~.^     .~JPB##Y ", PAGE_SIZE); printf("\n");
    makeMiddle(".&@!            ~@#                    J@P            .B@7", PAGE_SIZE); printf("\n");
    makeMiddle("^@@J??????????! !@&???????????????????7P@G ~??????????7B@Y", PAGE_SIZE); printf("\n");
    makeMiddle(".JY55555555555J .JY5555555555555555555555! !555555555555Y~", PAGE_SIZE); printf("\n");
}