#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifdef _WIN32
	#include<windows.h>
	#define SLEEP(x) Sleep((x) * 1000)
	#define CLEAR_SCREEN() system("cls")
#else
	#include<unistd.h>
	#define SLEEP(x) usleep((x) * 1000000)
	#define CLEAR_SCREEN() system("clear")
#endif

#include "trie.h"

void printMenu();
void releaseWord();
void searchWord();
void viewSlangWithPrefix();
void viewSlang();
int containsSpace(char *str);
int countWords(char *str);
void printASCII();

TrieNode *root = NULL;

void (*functions[4])() = {releaseWord, searchWord, viewSlangWithPrefix, viewSlang};

int main()
{
	printMenu();
	
	return 0;
}

void printMenu()
{
	int input;
	do{
		input = 0; //reset input to prevent infinite loop when user enters non-integer value
		CLEAR_SCREEN();
		printf("1.	Release a new slang word\n"); 
		printf("2.	Search a slang word\n");
		printf("3.	View all slang words starting with a certain prefix word\n");
		printf("4.	View all slang words\n");
		printf("5.	Exit\n");
		printf("Enter Menu (1-5): ");
		
		if(scanf("%d", &input) != 1)
		{
			// Flush everything up to and including the next newline
			while(getchar() != '\n');

			CLEAR_SCREEN();
			printf("Input must be an Integer!\n");
			SLEEP(0.5);
		}
		else getchar(); // consume the newline left by a successful scanf
		
		if(input > 0 && input < 5) functions[input - 1]();
	} while(input != 5);

	CLEAR_SCREEN();
	printASCII();
	SLEEP(3);
	return;
}

int containsSpace(char *str) {
	int amntOfSpaces = 0;
   for(int i = 0; str[i] != '\0'; i++)
	{
      if(str[i] == ' ')
		{
			amntOfSpaces++;
			while(str[i] == ' ') i++;
		}
   }
   return amntOfSpaces;
}

int countWords(char *str)
{
	int count = 0;
	int len = strlen(str);
    char lastC;

    if(len > 0) lastC = str[0];
    for(int i = 0; i <= len; i++)
    {
        if((str[i] == ' ' || str[i] == '\0') && lastC != ' ') count++;
        lastC = str[i];
    }
    return count;
}

void releaseWord()
{
	CLEAR_SCREEN();
	char input[1000];
	
	do{
		printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
		scanf(" %[^\n]", input);
		getchar();
	} while(strlen(input) < 2 || containsSpace(input));
	
	char desc[1000];
	
	do{
		printf("Input a new slang word description [Must be more than 2 words]:  ");
		fgets(desc, sizeof(desc), stdin);
		desc[strlen(desc) - 1] = '\0'; //remove newline character from the end of the string
	} while(countWords(desc) <= 2);

	if(searchTrieNode(root, input).word != NULL)
	{
		printf("Slang word \"%s\"'s description has been updated!\nPress enter to continue...\n", input);
		getchar();
	}
	else
	{
		printf("Slang word \"%s\" has been added to the dictionary!\nPress enter to continue...\n", input);
		getchar();
	}
	insertTrieNode(&root, input, desc);
}

void searchWord()
{
	CLEAR_SCREEN();
	char input[1000];

	if(root == NULL)
	{
		printf("There is no slang word in the dictionary.\nPress enter to continue...");
		getchar();
		return;
	}

	do{
		printf("Input a slang word to search [Must be more than 1 characters and contains no space]: ");
		scanf(" %[^\n]", input);
		getchar();
	} while(strlen(input) < 2 || containsSpace(input));
	
	SlangWord result = searchTrieNode(root, input);
	if(result.word != NULL)
	{
		printf("Slang word: %s\nDescription: %s\nPress enter to continue...", result.word, result.description);
		getchar();
		return;
	}
	else
	{
		printf("There is no slang word \"%s\" in the dictionary.\nPress enter to continue...", input);
		getchar();
		return;
	}
}

void viewSlangWithPrefix()
{
	CLEAR_SCREEN();
	char input[1000];
	
	if(root == NULL)
	{
		printf("There is no slang word in the dictionary.\nPress enter to continue...");
		getchar();
		return;
	}
	
	do{
		printf("Input a prefix to be searched: ");
		scanf(" %[^\n]", input);
		getchar();
		if(containsSpace(input))
		{
			printf("Prefix must not contain space!\n");
			SLEEP(0.5);
		}
		if(strlen(input) == 0)
		{
			printf("Prefix must be more than 0 characters!\n");
			SLEEP(0.5);
		}
	} while(containsSpace(input) || strlen(input) == 0);
	
	if(findPrefixNode(root, (unsigned char*)input))
	{
		printf("Slang words starting with \"%s\":\n", input);
		printf("\n"); printPrefix(root, input); printf("\n");
		printf("Press enter to continue...");
		getchar();
	}
	else
	{
		printf("No slang words found starting with \"%s\".\n", input);
		printf("Press enter to continue...");
		getchar();
	}
}

void viewSlang()
{
	CLEAR_SCREEN();
	if(root == NULL)
	{
		printf("There is no slang word yet in the dictionary.\nPress enter to continue...\n");
		getchar();
		return;
	}
	
	printf("List of all slang words in the dictionary:\n");
	printf("\n"); printTrieNode(root); printf("\n");
	printf("Press enter to continue...");
	getchar();
}

void printASCII()
{
	const char *art[] = {
        "llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll",
        "llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll",
        "lllllllllllllllllllllllllllllllllllllllllllllllcccccclllllllllllllllllllllllllllllllllllllllllllllll",
        "llllllllllllllllllllllllllllllllllllllllcccccc:::;;;:::cccccclllllllllllllllllllllllllllllllllllllll",
        "llllllllllllllllllllllllllllllllllcccccccccc::;,,ll,,;::ccccccccccclllllllllllllllllllllllllllllllll",
        "lllllllllllllllllllllllllllllcccccccccccccc:;;'cdkkxl',;:cccccccccccccccllllllllllllllllllllllllllll",
        "lllllllllllllllllllllllllccccccclccccccc::;,,'lkkkkkkd,',;:::cccccccccccccclllllllllllllllllllllllll",
        "lllllllllllllllllccc:::cccccccccccc:::::;;,':xOkOOkkkkkl',;;;:::ccccccccccccc::::cccllllllllllllllll",
        "llllllllllllllllcc;;,,;::ccccccc::::;;;,,'';OOOOOOOOOOOOc.',,;;;:::cccccccc::;,;;;:cclllllllllllllll",
        "lllllllllllllllcc:,'do,,;::::::::;;;,,ccl::kO0OOdccoOOO0Oc..,:',;;:::::::::;;,lx;,;:clllllllllllllll",
        "lllllllllllllllc:;,.xkd;',,;;;;;;;,'cxo:::O0000l,;:;ck00O0c,:lkl',;;::::;,,';okx,';:clllllllllllllll",
        "llllllllllllllc::;,.okkkdl,',,,;,,,xOl;;;O000x:;l;,l:;d000k;,;cOk:',;;,,,,coxkkx',;::cllllllllllllll",
        "llllllllccccccc:::,.ckkkkOkdc''''oO0l;;;k000l;:o'..'ll,cO000,;;:OOx,''':dxkkkkkd.,;::cccccccclllllll",
        "lllllcc:::::::::::;''xkkkOOOOkdcx00x;;;l0KKd;cO,.''.'kl;lKK0o.,;o00OcdxOOOkkkkx:.,;::::::::::cclllll",
        "lllllc:;,lc'',,;,,,'''''',,,:d00000c;''OKKO;c0;',,,,',Ol;xKK0'...O0000k:,,,'''''',,;;,,,'cd:;:ccllll",
        "lllllc:;';kddl;''''''''''''...;KKKO',dOKXX:;Od.,;;:;,'lK:;0KK0x:.lK00l...'''''''''''';lodxc',:ccllll",
        "lllllc:;,':xkkkxxdoo::;'''''..;kOOo,,:0XXx,cK,';::::;''0d;lXXKc;,cOOkd;;,;;;,:coooddxkxxkl'';:clllll",
        "llllllc:;''lkkkkkkkOOOOkkkxxdollccccldXXX:;xK',;:ccc:,'ok;,KXXxlcccclloodxxxkkOOkkkkkkxxd'',:cllllll",
        "llllllc:;;''ckkkOOOOOOO00000KKKKXXXXXXXXX,;k0.,:cccc:,'oK;;kXXXXXKKKKKK000000OOOkOkkkkkl'',;:cllllll",
        "llllllcc::;,';xkdc::cc::cccc::ccdk0XXXXX0,;OK.,;::c:;,'xX,;dXXXXXOxlc:;;;,,,,,,,,,:okk:'';:::cllllll",
        "llllllcccc:;,','...':;.............';OXXK,;ON;',;;;;,'.KK;;xXXK;'.'.................','',:ccccllllll",
        "llllllccccc:;,,,'''llllodddkO00000,..'KXX,.lNk.;;,',;'cN0;;kXX:...O0000Okdddolccl,'',,,;::ccccllllll",
        "llllllccccc::;;;,,',o00000KKKKKXXX,..'NXNc.,NXxc'''':kKXc.,KXX:...KXXK0KK000000x,',;;;:::cccccclllll",
        "lllllcccclcc::::;;;'',k000d,'''OXXl.'OXXXKcxNK:..''..;kNOcONXXK;.;NXK'',;l000O;'',;:::::ccclccclllll",
        "lllllcccclcc:::::::;,',c;'....'XXX0.',;XXXXXk,.o'...l.'oXNXXKc,,.dXXX;....',:,',;:::::::ccclccclllll",
        "lllllccccccc:::::cc:;,'....'cd0XXX0'...lNXNo'..':d,,,...cNNNo....kXXXKxl'....',;::cc:::::cclccclllll",
        "llllllccccc::::::cc:;,'cddk0KKXKl;,'','':0c....,l;:x:....;kl'',,'';:0KKK0kxdl,,;:ccc::::ccccccclllll",
        "llllllccccccc:::::::;,'',l0KKK0;.'',;;,,',...;xd,..,lkc...,',,;;,,'.,OKKK0o;'',,;:c:::ccccccccclllll",
        "llllllccclccc::::::;,''...',ll,.'',,;;;;,'.o0k;'''''';dOo.'',;;;;,,'.,:d;'....',;::::::cccccccllllll",
        "llllllccccccc::::;;,'':....,.''''',,,,;,';OKl,',;;;,,'':X0c',;;,,,'''..''....;,',;;:::ccccccccllllll",
        "lllllllccclccc:::;;,'',dl';o..'''xo'''''xXKc'',;;;;,,''.;KXO;','';k,'''.:o.cd;'',;;:::ccclccccllllll",
        "lllllllcccclcc:::;;,,,',dkOk....xX:.'..dXXd.',;;;;;,,'...cKX0'...'KO'...d0kk,'',;;;:::ccccccclllllll",
        "llllllllcccclccc:;;;;,,'';O0xd;;K0'...oKXk'.',,,;;,''0:...dKXO....0Kl,ox0Ol'',,;;;:::ccllcccclllllll",
        "lllllllllcccccc:::::;;,,'.c00O00KKd,.,XKKc..'k:',,,'.kXl..'0KKc.'cK00O00Oo''',;;::::::ccccccllllllll",
        "llllllllllccc:::::::;;;,'..d0O0000K0OOKKKc..dXc.'''..xK0..'0KK0OOK000O0Ok,.',;;::::::::cccclllllllll",
        "lllllllllllc::::::::::;;,'.,xd,l00000000K0OOKK0xddddd0KKOO0K00000000o,ck:.',;;::::::::::ccllllllllll",
        "llllllllllllccccccccc::;;,,',x,.l0O00000000000K00K000K00000000000O0x.'x:',,;;::cccccccccclllllllllll",
        "lllllllllllllccccclccc:::;;,'',..ok;,,xO000000000000000000O00k;,,xd'.,,',;;;::cccclcccclllllllllllll",
        "lllllllllllllllccccclcc:::;;,,''.'l;..,k00o:dO000OO000Ok::OOk;..'o'.'',,;;:::cccccccclllllllllllllll",
        "llllllllllllllllcccccccccc:::;;,''',...,kOO'.'cd''',kOx'.xOd,...','',;;::::cccccccccllllllllllllllll",
        "lllllllllllllllllllcccccccccc::;;,,,'''.':kc...,...;Ok'.;d,'.''',,,;;::cccccccccccllllllllllllllllll",
        "lllllllllllllllllllllcccccccccc:::;;;,,,'.;d.......lO:..;'.',,;;;;:::cccclccccccllllllllllllllllllll",
        "lllllllllllllllllllllllcccccccccccc:::;;,'';..'''..do...'',;;::::cccccccccccclllllllllllllllllllllll",
        "llllllllllllllllllllllllllcccccccccccc::;;,,'','''.l,.'',;::ccccccccccccccllllllllllllllllllllllllll",
        "llllllllllllllllllllllllllllllcccccccccc:::;;;;,,'.;'',;:cccccccccccccclllllllllllllllllllllllllllll",
        "llllllllllllllllllllllllllllllllllccccccc::::::;;,',',;::cccccccccllllllllllllllllllllllllllllllllll",
        "llllllllllllllllllllllllllllllllllllllllccccccc:;;,,;;::ccccllllllllllllllllllllllllllllllllllllllll",
        "lllllllllllllllllllllllllllllllllllllllllllllllcccccccccllllllllllllllllllllllllllllllllllllllllllll",
        "llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll",
        "llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll"
	};
	

	int n = sizeof(art) / sizeof(art[0]);
	for(int i = 0; i < n; i++)	{
		printf("%s\n", art[i]);
		SLEEP(0.02);
	}

	printf("Read Lord of The Mysteries if you haven't already!\n");
}


