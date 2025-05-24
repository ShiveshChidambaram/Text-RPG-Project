#include <conio.h>
#include <windows.h> 
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <chrono> //Add this include
#include <thread> //Add this include
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace chrono; //sleep_for, sleep_until
using namespace this_thread; // nanoseconds, system_clock, seconds

class Entity
{
	private:
		string type;
		string name;
		string gender;
		string trait;
		string state;
		string weapon;
		
		int health;
		int maxHealth;
		int coins;
		int souls;
		int level;
		
		bool alive;
	

	public:
	// Player
		Entity ()
		{
			string name = "";
			string gender = "";
			string trait = "";
			string state = "passive";
			string weapon = "none";
				
			int health = 0;
			int maxHealth = 0;
			int coins = 0;
			int souls = 0;
			int level = 1;
			bool alive = true;
		}

	// Entity
		Entity (string t, string n, int h, int mh, bool a)
		{
			type = t;
			name = n;
			health = h;
			maxHealth = h;
			alive = a;
		}
	
	// Getter Functions
		string getType ()
		{
			return type;
		}
	
		string getName ()
		{
			return name;
		}
	
		string getGender ()
		{
			return gender;
		}
	
		string getTrait ()
		{
			return trait;
		}
		
		string getState ()
		{
			return state;
		}
		
		string getWeapon ()
		{
			return weapon;
		}
	
		int getHealth ()
		{
			return health;
		}
		
		int getMaxHealth ()
		{
			return maxHealth;
		}
	
	
		int getCoins ()
		{
			return coins;
		}
	
		int getSouls ()
		{
			return souls;
		}
	
		int getLevel ()
		{
			return level;
		}
	
		bool isAlive ()
		{
			return alive;
		}
	
	// Setter Functions
		void setType (string t)
		{
			type = t;
		}
	
		void setName (string n)
		{
			name = n;
		}
	
		void setGender (string g)
		{
			gender = g;
		}
	
		void setTrait (string t)
		{
			trait = t;
		}
		
		void setState (string s)
		{
			state = s;
		}
		
		void setWeapon (string w)
		{
			weapon = w;
		}
	
		void setHealth (int h)
		{
			health = h;
		}
		
		void setMaxHealth (int m)
		{
			maxHealth = m;
		}
	
		void setCoins (int c)
		{
			coins = c;
		}
	
		void setSouls (int s)
		{
			souls = s;
		}
		
		void setLevel (int l)
		{
			level = l;
		}
	
		void playerDie ()
		{
			alive = false;
		}
		
		void playerRevive ()
		{
			alive = true;
		}
		
		void takeDamage (int d)
		{
			health -= d;
		}
		
		void healUp (int h)
		{
			health += h;
		}
};

// Prototypes

// States

void startScreen ();
bool bedroomStart ();
bool readNote ();
string nameScene ();
bool fightCookie ();
void emptyTown ();
bool fightMerchant ();
void townSquare ();
void gatesIntro ();
bool fightElf ();
bool keyScene ();
void enterGates ();
bool fightGatekeeper ();

string difficulty (string, Entity);

// Utility

void appearText (string);
void textBox(string, string);
void printBedroom ();
void sideWalk ();
void endScreen ();

void introNote ();
void cookie();
void deadCookie();
void initializeMap();
void printShop ();
void printGate ();
void printElf ();
void printGatekeeper ();


void shop ();

// Battle Screen

string handleInput(int);
void battleBox ();
void drawMenu(int);

void movePlayer ();


// Battle Choices

void choiceManager (string);
int attack ();
int pray ();
string item ();
bool trust (string);

//Color Thingamabobbers

const string RED = "\033[41m \033[0m"; 
const string YELLOW = "\033[43m \033[0m"; 
const string GREEN = "\033[42m \033[0m"; 
const string WHITE = "\033[47m*\033[0m"; 

// Inventory

string inventoryMenu ();
void displayInventory(int);

vector<string> inventory = {"None"};

// Globals

string menuOptions[4] = { "Fight", "Pray", "Item", "Trust" };
int selected = 0;
Entity player = Entity();

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 10;
char map[MAP_HEIGHT][MAP_WIDTH];
int playerXLoc = (MAP_WIDTH / 2) - 1;
int playerYLoc = (MAP_HEIGHT / 2) - 1;
int playerX = playerXLoc;
int playerY = playerYLoc;
int gatekeeperHP = 350;





int main ()
{
	system("");
	
	initializeMap();
	bool isHome;
	bool gameEnd = false;
	int seed = time(0);
	int save = 0;
	
	
	srand(seed);

	           
	player.setState("passive");
	
	do
	{
		if (save == 0)
		{
			startScreen();
		
			do
			{
				isHome = bedroomStart();
			} while (isHome);
			
			player.setName(nameScene());
		
			player.setTrait(difficulty(player.getName(), player));
		
			if (player.getTrait() == "Surgeon")
			{
				player.setTrait("s");
				player.setHealth(200);
				player.setMaxHealth(200);
				player.setCoins(200); 
			}
			else if (player.getTrait() == "Entrepreneur")
			{
				player.setTrait("e");
				player.setHealth(100);
				player.setMaxHealth(100);
				player.setCoins(400); 
			}
			else if (player.getTrait() == "Retail Worker")
			{
				player.setTrait("r");
				player.setHealth(150);
				player.setMaxHealth(150);
				player.setCoins(100);
			}
			save = 1;
		}
		if (save == 1)
		{
			do
			{
				player.playerRevive();
				fightCookie();
				
			} while (!player.isAlive());
			save = 2;
		}
		
		if (save == 2)
		{
			emptyTown ();
			save = 3;
		}
		
		if (save == 3)
		{
			do
			{
				player.playerRevive();
				fightMerchant ();
				
			} while (!player.isAlive());
			save = 4;
			
		} 
		
		if (save == 4)
		{
			townSquare();
			save = 5;
		}
		
		if (save == 5)
		{
			gatesIntro ();
			save = 6;
		}
		
		if (save == 6)
		{
			do
			{
				player.playerRevive();
				fightElf ();
				
			} while (!player.isAlive());
			save = 7;
		}
		
		if (save == 7)
		{
			gameEnd = keyScene ();
			if (gameEnd)
			{
				break;
			}
			else
			{
				save = 8;
			}
		}
		
		if (save == 8)
		{
			enterGates ();
			save = 9;
		}
		
		if (save == 9)
		{
			do
			{
				player.playerRevive();
				fightGatekeeper ();
				
			} while (!player.isAlive());
			
			gameEnd = true;
		}
		
		
		

	} while (!gameEnd);
	
	system("CLS");
	endScreen();
	
		
	
		
	
	
	return 0;

}

void initializeMap() 
{
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            map[y][x] = ' ';
        }
    }
}

void appearText(string text)
{
	
	int keyboardInput;
	bool trueText[text.length()];
	
	for (int i = 0; i < text.length(); i++)
	{
		trueText[i] = true;
	}
	
	for (int i = 0; i < text.length(); i++)
	{
		keyboardInput = kbhit();
		if (keyboardInput != 0)
		{
			break;
		}
		cout << text.at(i);
		trueText[i] = false;
		sleep_for(nanoseconds(50000000)); //Adjust value
	}
	
	for (int i = 0; i < text.length(); i++)
	{
		if (trueText[i])
		{
			cout << text.at(i);
		}
	}
}


void textBox(string speaker, string text)
{
    const int width = 72;
    vector<string> lines;
    string word, line;

    int i = 0;
    while (i < text.length())
    {
        while (i < text.length() && text[i] == ' ') 
            i++;
        int start = i;

        while (i < text.length() && text[i] != ' ') 
            i++;
        
        word = text.substr(start, i - start);

        if (line.length() + word.length() + 1 > width)
        {
            if (!line.empty())
            {
                lines.push_back(line);
            }
            line = word;
        }
        else
        {
            if (!line.empty()) line += " ";
            line += word;
        }
    }

    if (!line.empty()) lines.push_back(line);

    cout << "+" + string(width + 2, '-') + "+" << endl;

    if (!speaker.empty())
    {
        cout << "| " << left << setw(width) << (speaker + ":") << " |" << endl;
        cout << "|" + string(width + 2, ' ') + "|" << endl;
    }

    for (int i = 0; i < lines.size(); i++)
    {
        cout << "| " << left << setw(width) << lines[i] << " |" << endl;
    }

    cout << "+" + string(width + 2, '-') + "+" << endl;
}

void movePlayer ()
{
	while (true) {
        if (kbhit()) {
            char input = getch();

            if (!(playerX >= 1 && playerX < MAP_WIDTH - 1 && playerY >= 1 && playerY < MAP_HEIGHT - 1)) 
			{
				break;
			}

            if (input == 'w' && playerY > 0) 
			{
				playerY--;
				player.setHealth(player.getHealth() - 1);
			}
		    else if (input == 's' && playerY < MAP_HEIGHT - 1)
			{
				playerY++;
				player.setHealth(player.getHealth() - 1);
			} 
		    if (input == 'a' && playerX > 0) 
			{
		    	playerX--;
		    	player.setHealth(player.getHealth() - 1);
			}
		    if (input == 'd' && playerX < MAP_WIDTH - 1)
			{
				playerX++;
				player.setHealth(player.getHealth() - 1);
			} 
			
			if (player.getHealth() <= 0)
			{
				player.setHealth(0);
				player.playerDie();
				return;
			}
			
            battleBox ();
        }
    }
}

void shop ()
{
	char choice;
	system ("CLS");
	
	do
	{
		do
		{
			system("CLS");
			
			cout << "Welcome to the shop, what would you like to buy?" << endl << endl;
			cout << "1. Quick Therapy - 100C" << endl;
			cout << "\t>> A video tape of a therapy session - Restores SANITY to Max." << endl;
			cout << "2. Throwable Knife - 50C" << endl;
			cout << "\t>> A... knife you can throw? - Deals 50 damage." << endl;
			cout << "\t>> A video tape of a therapy session - Restores SANITY to Max." << endl;
			cout << "3. Buyable Love - 200C" << endl;
			cout << "\t>> Money can't buy everything, but it might buy peace. - Ends Fight" << endl;
			cout << "4. Memory - 50C" << endl;
			cout << "\t>> You remember something that brings you peace. - Restores 50 SANITY" << endl;
			cout << "0. Leave Shop" << endl << endl;
			cout << "You have " << player.getCoins() << " COINS remaining.";
			
			choice = getch();
			
		} while (choice != '1' && choice != '2' && choice != '3' && choice != '4'  && choice != '0');
		
		if (choice == '1')
		{
			if (find(inventory.begin(), inventory.end(), "Quick Therapy") != inventory.end())
			{
				system("CLS");
				cout << "You have already purchased this item." << endl << endl;
				system("pause");
			}
			else if (player.getCoins() < 100)
			{
				system("CLS");
				cout << "You don't have enough money to purchase this item." << endl << endl;
				system("pause");
			}
			else
			{
				system("CLS");
				cout << "You have purchased Quick Therapy for 100C." << endl << endl;
				inventory.push_back("Quick Therapy");
				player.setCoins(player.getCoins() - 100);
				system("pause");
			}	
		}
		
		else if (choice == '2')
		{
			if (find(inventory.begin(), inventory.end(), "Throwable Knife") != inventory.end())
			{
				system("CLS");
				cout << "You have already purchased this item." << endl << endl;
				system("pause");
			}
			else if (player.getCoins() < 50)
			{
				system("CLS");
				cout << "You don't have enough money to purchase this item." << endl << endl;
				system("pause");
			}
			else
			{
				system("CLS");
				cout << "You have purchased a Throwable Knife for 50C." << endl << endl;
				inventory.push_back("Throwable Knife");
				player.setCoins(player.getCoins() - 50);
				system("pause");
			}	
		}
		
		else if (choice == '4')
		{
			if (find(inventory.begin(), inventory.end(), "Memory") != inventory.end())
			{
				system("CLS");
				cout << "You have already purchased this item." << endl << endl;
				system("pause");
			}
			else if (player.getCoins() < 50)
			{
				system("CLS");
				cout << "You don't have enough money to purchase this item." << endl << endl;
				system("pause");
			}
			else
			{
				system("CLS");
				cout << "You have purchased Memory for 50C." << endl << endl;
				inventory.push_back("Memory");
				player.setCoins(player.getCoins() - 50);
				system("pause");
			}	
		}
		
		else if (choice == '3')
		{
			if (find(inventory.begin(), inventory.end(), "Buyable Love") != inventory.end())
			{
				system("CLS");
				cout << "You have already purchased this item." << endl << endl;
				system("pause");
			}
			else if (player.getCoins() < 200)
			{
				system("CLS");
				cout << "You don't have enough money to purchase this item." << endl << endl;
				system("pause");
			}
			else
			{
				system("CLS");
				cout << "You have purchased Buyable Love for 200C." << endl << endl;
				inventory.push_back("Buyable Love");
				player.setCoins(player.getCoins() - 200);
				system("pause");
			}	
		}
	}while (choice != '0');
	
	
}


void printBedroom ()
{
	cout << "__________________________________________________________________________" << endl;
	cout << "| .-.-.  =..=  .-.-.  =..=  .-.-.  =..=  .-.-.  =..=  .-.-.  =..=  .-.-. |" << endl;
	cout << "| '. .' .'  '. '. .' .'  '. '. .' .'  '. '. .' .'  '. '. .' .'  '. '. .' |" << endl;
	cout << "|`-='=-`      `-='=-`      `-='=-`      `-='=-`      `-='=-`      `-='=-`|" << endl;
	cout << "|                                                                        |" << endl;
	cout << "|                                                       ** **            |" << endl;
	cout << "|          .-.-.                   .-.-.               *  *  *           |" << endl;
	cout << "|          '. .'  _____    _____   '. .'                *   *            |" << endl;
	cout << "|           =|=  _)   (    )   (_   =|=                   *              |" << endl;
	cout << "|            ^ _)      (__)      (_  ^          =====================    |" << endl;
	cout << "|            _)    _____  _____    (_            [__] .   (   . [__]     |" << endl;
	cout << "|          _)     (_____)(_____)     (_          [__] |  ( )  | [__]     |" << endl;
	cout << "|lc_______)_______%%%%%**%**%%%%_______(_________[__]/!\\@@@@@/!\\[__]_____|" << endl;
	cout << "                 %%%%%*%%*%%*%%%%               '===================' " << endl;
	cout << "                %%%%%%%*%%%*%%%%%% " << endl;
	cout << "      /\"\"\"\"\"\"\"\"%%%%%%%%%%*%%%%%%%%%\"\"\"\"\"\"\"\"\\ " << endl;
	cout << "     /<3==<3==%%%%%%%%%%%%%%%%%%%%%%3==<3==<3\\ " << endl;
	cout << "    /\"\"\"\"\"\"\"\"/||||||||||||||||||||||\"\"\"\"\"\"\"\"\\ " << endl;
	cout << "   /<3==<3==<||||||||||||||||||||||||<3==<3==<3\\ " << endl;
	cout << "  /\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\\ " << endl;
	cout << " /<3==<3==<3==<3==<3==<3==<3==<3==<3==<3==<3==<3=\\ " << endl;
	cout << " \"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\" " << endl;
}

void sideWalk ()
{
	cout << ":::::::::::::::::::::::::::::::::::::::::::::::-++**##*+++***#*+*++*++****" << endl;
    cout << ":::::::::::::::::::::::::::::::::::::::::::::::=*****##*++++*#####+**+*++*" << endl;
    cout << "::::::::::::::::::::::::::::::::::::::::::::-==+**####%%%#*****#%####*++*+" << endl;
    cout << "::::::::::::::::::::::::::::::::::::::::::::-+###%%%%%%%%#**+**#####+*##%%" << endl;
    cout << "....:---:::................................::-+*#%%#%%%%%*==++**+*#**##*%*" << endl;
    cout << "...::+=++==-:::::=====-:...................:-++####%%%%%%*+++****#+**#+#**" << endl;
    cout << "..:--=+**++*+**+===+++*=:...................:-*#%%%##%###+====+++#*=*#*#*#" << endl;
    cout << "..:=++*##*****#*+++++**++:.::...............:-+*####%%%#**=--:-==*#==#%###" << endl;
    cout << "..-==+*##***######*******=::-:..............-+*###%%%%%%%%+=++-:.-+==**+**" << endl;
    cout << ":-=++**############******+===-.....:-====-::-=*#*****#%%%#++++=:.:-===++*#" << endl;
    cout << "=**+*#*###*###%###***##*+=+***+=====+*****+*########%%%#+====-=-:-=+=+*##*" << endl;
    cout << "+###*#######%%%%##*+###**+**##*##*++*####*+=+***##%%%*==+*+-===++++=++*#%*" << endl;
    cout << "==**########%%####******+++*##*###***####**++++***#**+=++=+===+=*#****#%%%" << endl;
    cout << "###*##%###%%%%####%%#*+++**####%%####%%%%******##%#+++++**+=++*++*#+=+*#%#" << endl;
    cout << "%%####%#########*****+=+*##*#%%%%%%%#**##*+**######+=+*###*===*###*+####%%" << endl;
    cout << "****++*++++++===+++++********#***+++===++++****++++==+**###+===*##**#*##%%" << endl;
    cout << "======*=========-------------------=*###%%%%%######%########**+*####***#%%" << endl;
    cout << "---===+==--====-------=-----========*%%%%@@@%%%%%@@@@@@@@@%%%%%#+######%*%" << endl;
    cout << "======================***###***##*****#####%%%%%%%%%%%%%%%%%######+*####%#" << endl;
    cout << "==================---::::::::-==++=======+===================+++++==+++*#%" << endl;
    cout << "=========================-:::::::::--==++++===+++=====++++++=*+++++++++++#" << endl;
    cout << "=============================--:::::::::--==+++======+++++++=*++++++++++=#" << endl;
    cout << "================================--:::::::::::--==+++++++++++=*++++++++**+#" << endl;
    cout << "=====================+=============--:::::::::----=+=++++++++**+++*++=*#*#" << endl;
    cout << "==========+======+==++++====+=====+=---::::::::::::--=++***#**###*#**++#*#" << endl;
    cout << "=======+++====++++====++++++==++++++--::::::::::::::----::::---===------:+" << endl;
    cout << "=+++++++==+==++++++++++++++++=+++=++--:::::::::::---------..............:+" << endl;
    cout << "+++=+=+++++++=+++++++++++++++====+**=-:::::::::-::::----:--:......--==*#+*" << endl;
    cout << "+++++++++++++++++++++++++++===+++**=-:::::::::::::::::------::++**+++*+*=*" << endl;
    cout << "++++++++++++=+++++++++++++++++++*#+--:::::::::::::::::::-----=+++++****+**" << endl;
    cout << "+++++++++++++++++++++++++++++++*#*=-----::::::::::::::--------==+++++++*++" << endl;
    cout << "+++++++++++++++++++++++++++++*#%*+----::::::::::::::::--::::---=+++**+++==" << endl;
    cout << "+++++++++++++**+++++++++++++*##+---::::::::::::::::::::::-------=+++++++++" << endl;
    cout << "+*++++**+****++++++++++++++*##*=-::::::::::::::::::::::-::------=++++++++*" << endl;
    cout << "++++***+****+++++++++++++++##+=-:::::::::::::::::::::::::::::---=+********" << endl;
    cout << "***+++***+++*++*++++++++*#%#*=--------------::::::::::::::::::---++***++++" << endl;
    cout << "**********+++++++***++*#%%#+=-::::::::::::::::::::::::-----------=+*******" << endl;
    cout << "***+++****++*++**+++++*##*+=-::::::::::::::::::::::::::::::::::--=+****+*+" << endl;
    cout << "*****+***********+***#%#*=------:::::::::::::::::::::::::::::::--=+++***++" << endl;
    cout << "*+*++******##*+***##%%*+--:::::::::::::::::::::::::::::::::::-----+++***++" << endl << endl;
}

void cookie ()
{
	cout << "                 @@@@@@@@@@@@@@@=                      " << endl;
	cout << "             @@%#=:::. +  ... .+@@                    " << endl;
	cout << "           @@#=:-:....=@@.+*+:@...@@                  " << endl;
	cout << "          @%:.--+***#+...=   .=--...@                " << endl;
	cout << "         @+-=:==      +#  #@@  :+--..@                " << endl;
	cout << "        @=-=:.*   @@@  @  @@@@  *---.%@               " << endl;
	cout << "       @%:-:::%   @@   %       .*---: @               " << endl;
	cout << "       @:-:.::-@     .=-=%-  .#*=:--- @               " << endl;
	cout << "       @...::.:.+%#=:..@:..:-+=------ @@@-           " << endl;
	cout << "       @@-.::+@-:.=@@..  .@@@.:-::--: @  @@@         " << endl;
	cout << "     =@@@.:.....:-..@@@@@@@%..:.   .. @   @@@=       " << endl;
	cout << "    =@@ @:::.:::-::.   ...  .--:@@@+ @@    :@        " << endl;
	cout << "    @@  @@-:-..::---:..  ..:--:..@*.-@                " << endl;
	cout << "    @@@  %@=.==.   .::.@:.::...:.  +@                " << endl;
	cout << "    @@@    @@-...@@....@@-...@  ..@@                  " << endl;
	cout << "             @@*@@@.:..   :.@@@ @@                    " << endl;
	cout << "                @@@@@@@@@@%@@@@@                      " << endl;
	cout << "        @      @@              @@@    @@@@           " << endl;
	cout << "       @@@@   @@                 @@@  @@@@           " << endl;
	cout << "       @@@@@@@@                    @@@@@@@           " << endl;
	cout << "         @@@@                         :@             " << endl;


}

void deadCookie ()
{
	cout << "            ...              ... ..            " << endl;
	cout << "             .         .  ...     .            " << endl;
	cout << "             . .:  =    :.    .-               " << endl;
	cout << "       ... .- .::-:. -+*:#*..:  %%#%%:         " << endl;
	cout << "          #=.... +##%###  **:   %@@#=#%#       " << endl;
	cout << "   ..  .-#   #-    *.-= .*.:*#  @=..@=-##      " << endl;
	cout << "   . .*#    .==%%+::--+ :+:%%=  +=:@@..%@=     " << endl;
	cout << "  ..  -  *#@@::#*:.#@++@##%%%*- %-:-==*+=%=    " << endl;
	cout << "        =%:.%%+@@.#%-*+@-.  **.+@*+.*:::=#=    " << endl;
	cout << "      .@@==@:....%%+--%@+#.*.%* -#%%%##*#%:    " << endl;
	cout << "      %%=-%---+*-: .  =:  @@@@*     @@#*+#-    " << endl;
	cout << "     *%@=.##:=++=+*##+-.%.  . .+ #=   ..@@.    " << endl;
	cout << "    *@*@%+@+.:.:=++*-+@ @@=--+@@%*%@@%=.       " << endl;
	cout << "    .%-=+---*%#+-*#= %%+@.*%*=..:*=::=*%*      " << endl;
	cout << "    *@-##-:%+:-##-     .@@@%:=%#@*=:..=@*.     " << endl;
	cout << "     @%=@%%#:=%+.%# .%#+%.+..:+...=:#::+=      " << endl;
	cout << "      @%-.-@%%+ ..-@@:...@@@@*=--..-#-+#=      " << endl;
	cout << "      .@@**.   -...:-*-:.+. :@:-@@@--*+#.      " << endl;
	cout << "        @@@ @%#%@@@==#+@@@+. .*-...+*%%.       " << endl;
	cout << "          %@*#@::::===...-=%# -%:*%#@-         " << endl;
	cout << "           =@@*--:.*-.--.-=:#-@%@@%            " << endl;
	cout << "             #@@@%#+%:#==#%@@%@-               " << endl;
	cout << "                +@@@@@@@@@@=                  " << endl;

}

void printMerchant ()
{
	cout << "                    ................                    " << endl;
    cout << "                  .=-:::-:::::::::--+                   " << endl;
    cout << "                  --:::::::::::....:=*                  " << endl;
    cout << "                 =-:::..........:::...*                 " << endl;
    cout << "                -:..:....         .:..:+:               " << endl;
    cout << "               -::.....  -%%%%#- .:..:..==              " << endl;
    cout << "              :-.....:**-..  .-+*-.-.....-=             " << endl;
    cout << "             .:.  .=+.          :++: .....=+            " << endl;
    cout << "             ...=++              .=*+.  ...-+           " << endl;
    cout << "             :+*++.               .:+#+  ...:+          " << endl;
    cout << "           .**+++- =@@@@@    .@@@@@.:=+*+- ..:+.        " << endl;
    cout << "           #+===+=   +@@       ..   .=+=++++:..*.       " << endl;
    cout << "          #+====+*%                .+*+=--=:=+=-+       " << endl;
    cout << "         ++==-====+%*           ..:*+++-:--=-:-=*#      " << endl;
    cout << "        .*-----=====*+          . =++==-::::-=..:=-     " << endl;
    cout << "        #=-----=--==+*            =+===:::::::-=:.=     " << endl;
    cout << "       #=-----:===-==+-        ...*+=--:.:::..::-==-    " << endl;
    cout << "      .*-:::--:=----=+*-         =+=----.......:::-*.   " << endl;
    cout << "     =*=-------:-==---+*#+    .+*++-::::........:::-#   " << endl;
    cout << "    %*----::::-------====+#%%#*+=--::::-..........:=%   " << endl;
    cout << "    .-::--:--::---------=======--::::::-.....:..::-+    " << endl;
    cout << "    .:::::-::::::::::---====-:::::::::::.......:::.-.   " << endl;
    cout << " +*==-::::::::-:::::::::---:::::::::::::..........-===. " << endl;
    cout << " ..--..:::::::--:::::::::::::::.::::::::.........=-...: " << endl;
    cout << "....  ..--:::-::...:....:......  ..            .==   .=-" << endl;
    cout << ".==++-  .-:..:-===++++++++***##*********=-=+****- :*%%#: " << endl;
    cout << ".----=+*- :======-::::...............::--==.    .*%@  :." << endl;
    cout << ".-------=-:===--::::::::::::::::::::::.::::==++=*% .. =." << endl;
    cout << ".---------==--::::---::::::::::::::::::::::-:---+.  # .." << endl;
    cout << " ........... .                   .      ........-**+-:. " << endl << endl;
}

void printShop ()
{
	cout << ":+++++++*%:::@@:.@@:::@@:::@@:::@@::=@@::+@@.:@@+::@@::.@@ ::@=..#*==-=---." << endl;
    cout << "+@@@@@%@@@-:@@:::@@::@@@--@@@::@@@-:@@@:-@@@:-@@@:-=@@::@@@::@@%:@@@@%@%%%-" << endl;
    cout << "+@%@%@@@@-:@@*-:@@#-:@@:-:@@%-:@@@-:@@@:-@@@:-:@@:-:@@@::@@::.@@::@@@%%@%%-" << endl;
    cout << "+@%@@@@@-:@@@::@@@::@@@:-+@@:-:@@%-:@@@:-+@@:=:@@@:-@@@:::@@:::@@::@@@@%%%=" << endl;
    cout << "+@%@@@@-:@@@::@@@::-@@:-:@@@--=@@:#:@@@:-:@@+-:@@@:-.@@@::@@@.::@@::-@@@@%-" << endl;
    cout << "+%@@@-:@@@:::@@@:-=@@@--@@@+--@@@:*:@@@:*:@@@-=+@@@--@@@@--@@@-:.@@@:-@@@%-" << endl;
    cout << "+%@::%@@*.:@@@@.:#@@@.::@@@.-:@%@.=:@#@.#.@#@.= @%@::.@@@%:.*@@@..:@@@::@@-" << endl;
    cout << "+%@:-@@@@--@@@@--+@@@---@@@-==@@@:--@@@---@@@---@@@--:@@@@--@@@@--@@@@-:@%-" << endl;
    cout << "=@@ .    :-  .*-:..  =-    -:.   :-    ::.   .-:    -:    --    -:    . @%-" << endl;
    cout << "=%@@@@@@@@+@.:+ @@@  . @@@  @@  @@- +@  @@  @@@  @@  @@   @@  @ %@@@@@@@@%-" << endl;
    cout << "=%%@@%@@@@@@@+-@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@. @@@@@%%%@%%%-" << endl;
    cout << "=%%@%@@@@%@@@::%@@@- @@@@@@@@@%@%@@@@@@@%@@@@%%@@@%@@@@ @@@@  @@@%@%@%%%%%-" << endl;
    cout << "=%%%%@%@@@@@@*:%@@@*#@@@@@@@@@%@@@@@@%@@@@@@@@@@%@@@@@@ %@%@ .@@%%@%%%%%%%-" << endl;
    cout << "=%%%%%%@@@@@@+:%@@*    @@@@@@@@@@@@@@@%@@@%%@@@@@@@@@@@ @@@@ .@@@@%%%%%%%%:" << endl;
    cout << "-%%%%%%%@%@@@-:%@**=.@@@@@.=#@@@@@@@@@@@@@@@@@.+@@@@@@@ @@=@.:@@%%%%%%%%%%:" << endl;
    cout << "-%%@@@%%%%%%@*-%@@:@--.--@@@@ ...        .   @%#@ ...:= +  @::@@%%%%%@@%%%:" << endl;
    cout << "-%@%%@@@%@%%@::**  @@@-  @+-@=@@@@@@@@@@@@@@%@- @ --::: =%*% -@@%%%@@%%%%%:" << endl;
    cout << "-%%%%%%%%@%@@-:#@@@@%@@@@@@@@##:-@@=  -%#+ @+@#%@@@@@@@@@-@@.-@@%#%%%%%%%#." << endl;
    cout << ":%%%%%%@%%%%@-.##                    @                    @.  @@@%%%%%%%%@:" << endl;
    cout << ":%%%%%@%%%%%@-.@+  :=---%@#%#*#%%%@= = .-+*%##%%#+##%#*+- -=..@@%%%%#%%%%#." << endl;
    cout << ".#%%%%%%%%%%@+.@* .#*+%%+=*#*#*****%#. +*@%#**++*-+%=+#%%. *.-@@%%%%%%%%%# " << endl;
    cout << ".%@%%%%%%%%@@=.@@@@@@@@%**###%@@@@@@@@@@@+-=*%@@%%@@@@@@%#@@-+@@%%%%@%%%%% " << endl;
    cout << "-%%%%%@@@@%%@-.=:.-...:-====@=..........:--:.. .  .     -... =@@@@@@@@@@@@." << endl;
    cout << " +##%#+=####@+:%%@#%%#+##*##+=#%%#%%#%###%%%%@@@@%%%@@@@%%%@.%---:: :-:::= " << endl;
    cout << ".%%#==%##%%-#+.@#++++=+*#*+**#+==##+=++**+-#: . :::-:--:.:-= @: ...    ::  " << endl;
}

void printGate ()
{
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "@@@@@@@@@@@@@@@@@@%#**********************#@@@@@@@@@@@@@@@@@@" << endl;
	cout << "@@@@@@@@@@@@%*##************#****#*********+**#**@@@@@@@@@@@@" << endl;
	cout << "@@@@@@@@@@@@@@@@%###*###%###%#%%#%########*##@@@@@@@@@@@@@@@@" << endl;
	cout << "@@@@@@%**+********%#*#*#####%%%##%####*###*+++++++++++*%@@@@@" << endl;
	cout << "#####**********#**%%*#%%%%%%%%%%%%%%##%%%#****++++++++++*####" << endl;
	cout << "@@@#*************#@@#@@@@@@@@@@@@@@@@@@@@%******+++++++++*%@@" << endl;
	cout << "@@@@%*#*#*#*######@@#@@@@@@@@@@@@@@@@@@@@%####***********@@@@" << endl;
	cout << "@@@@%#@@@@@@@@@@@@@%#@@@@@@@@@@@@@@@@@@@@%*@@@@@@@@@@@@*+@@@@" << endl;
	cout << "@@@@##@@@@@@@@@@@@@%#@@@@@@@@@@@@@@@@@@@%#*@@@@@@@@@@@@*+%@@@" << endl;
	cout << "@@@@##@@@@@@@@@@@@@%*@@@@@@@@@@@@@@@@@@@%#*@@@@@@@@@@@@*+%@@@" << endl;
	cout << "@@@%##@@@@@@@@@@@@%%#%@@@@@@@@@@@@@@@@@@%#*@@@@@@@@@@@@*+#%@@" << endl;
	cout << "@%****%@@@@@@@@@@@***#@@@@@@@@@@@@@@@@@%***@@@@@@@@@@@@*+++%@" << endl;
	cout << "@@%@%@@@@@@@@@@@@@@@%@@@@@@@@@@@@@@@@@@@%%%@@@@@@@@@@@@%%@%@@" << endl;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

}

void printElf ()
{
	cout << "                                                                " << endl;
	cout << "                                                                " << endl;
	cout << "                             ......                             " << endl;
	cout << "                         .............                          " << endl;
	cout << "                        ................                        " << endl;
	cout << "                       ..................                       " << endl;
	cout << "                      ...::..........:...                       " << endl;
	cout << "                      ..:::::.....:::::...                      " << endl;
	cout << "                     ..:::::::::::::::::..                      " << endl;
	cout << "                     ..::=#+:::::::+#=::..                      " << endl;
	cout << "                   .:.:::::::::::::::::::.::                    " << endl;
	cout << "                   .::::::%%-:::::-%%::::::.                    " << endl;
	cout << "                   .:::::::-:::::::-:::::::.                    " << endl;
	cout << "                    .:::::::::-:::::::::::.                     " << endl;
	cout << "                     ..:::::::::::::::::..                      " << endl;
	cout << "                     ...:::::::::::::::...                      " << endl;
	cout << "                     ....:::::::::::::....                      " << endl;
	cout << "                     ......::::::::::.....                      " << endl;
	cout << "                     ......::-:::--:......                      " << endl;
	cout << "                     ......:::::::::......                      " << endl;
	cout << "                   .-=++++++++***++++++++=-.                    " << endl;
	cout << "                :+++++++++++*******+++++++++++:.                " << endl;
	cout << "             .-++++++++++*************++++++++++-.              " << endl;
	cout << "            .++++++++++*****************++++++++++:            " << endl;
	cout << "           :+++++++++*********************+++++++++-           " << endl;
	cout << "          -++++++++*************************++++++++-          " << endl;
	cout << "         :+++++++*****************************+++++++:         " << endl;
	cout << "        .++++++*********************************++++++.        " << endl;
	cout << "       .+++++*************************************+++++.       " << endl;
	cout << "       =+++*****************************************+++=       " << endl;
	cout << "      -+++*******************************************+++-      " << endl;
	cout << "     .++***********************************************++.     " << endl;
	cout << "    .++*********++****************************+*********++.    " << endl;
	cout << "   .=+**********++***************************++**********+=.   " << endl;

}

void printGatekeeper ()
{
	cout << "                                             .                            " << endl;
	cout << "                                            ...-.                         " << endl;
	cout << "                              .-#+#%%%%#=::-.:##-                         " << endl;
	cout << "                   .=::#+-. :*%%*=.....:=*%@@%++:..                       " << endl;
	cout << "                    .:-#@@@@#*.:.      .+-.:-#@%==*..                     " << endl;
	cout << "                   .---+%%%#%#. ..     ...:-...-#@%*%:                    " << endl;
	cout << "                  ..=+%@%@@*.:.::.  .*-=+....: .:-@#=.                    " << endl;
	cout << "                ....*@#@@#*::. ..-- .:#@@-.... ....+*#..%-                " << endl;
	cout << "               .*@*%%@@%+-+..-....==@@@@::... .-:*.:@**:.                 " << endl;
	cout << "               .++-+@###=...:....-@@@@@=-.#=.-:..+=:@*.                   " << endl;
	cout << "               ..+#@@@%+*#..:..::=#@@@*#:..... :*++%%#-..                 " << endl;
	cout << "                .=#*@@#%*:+%=::.:--=%*+:=-...=#+.+#@@%+.                  " << endl;
	cout << "                .-#*%%#.=%@@%%@*===+%#=:--**@@@@%=-#%###..                " << endl;
	cout << "                :-#%@#*%*@@@@@@@@@@@++%@@@@@@@@@@*%*%@-.:.                " << endl;
	cout << "                .=%*@@#++@@@@@@@@@@#*=*@@@@@@@@@@@+*%@%=.                 " << endl;
	cout << "              .+.-@@@@=-#@@@@@@@@*##@@#*+@@@@@@@@@==@@@%.                 " << endl;
	cout << "               ...**@@*#@@%+-...=#=@@@@**#-.:=%@@@+#@@@+...               " << endl;
	cout << "              .. ..*%***-::=-==:-@*@@@@%@=.=+-:-:-+*+%%*-...              " << endl;
	cout << "               *-.-:###+#@@@%@@#-.-*@@*=.-+*@@@@@@#+%@+=-=.               " << endl;
	cout << "               . .:*=@@@@@@@@@@+*..::-:..==#@@@@@@@@@@#+...               " << endl;
	cout << "                  ..+@@@%@%@@@@%%%#%=+*+%%%%@@@@@%@@@@@@:..               " << endl;
	cout << "                 .*@@@@@%@%%@@===..-:.-.--+%@@@%@@@@@@@..-:.              " << endl;
	cout << "                  .@=#@@@#*-@@-#*%@@%%%@@#*+@@*+#%@@-......               " << endl;
	cout << "                 .::.-#%@%+-%@@@@@@@@@@@@@@@@@==%@@%#+....               " << endl;
	cout << "                    :.+@%#:*%@@@@@@@@@@@@@@@@%+.*@@%..::.                 " << endl;
	cout << "                   .:.=%%#*=@@*#@@@@@@@@@@*#@@=%+%@@%--.                  " << endl;
	cout << "                 .. .:+*@%*-+@*=#@@@@@@@@*=*%++-#@@*:.-                   " << endl;
	cout << "                .:.  ..=%@@@**@*+:=*#@*-==%@#+@@@@#. .:                   " << endl;
	cout << "                   ...:..*@@@@-@@%-=::==#%@-@@@@#.=*.: ...                " << endl;
	cout << "                    .=- .%@@@%#+*=%%#%%%===%%@@*-.-.                      " << endl;
	cout << "                    ..-:*@#@@@@%=.:....:=+%@#%@=:..  .%.                  " << endl;
	cout << "                      - .%@@=.-=@+-+@@+-=@-%--*-:     .                   " << endl;
	cout << "                      . .-#@::=.:*%@%%@@=..+.:-::.. ..                    " << endl;
	cout << "                        .-+%-:=:.+-+#+*@-..+ : ::                         " << endl;
	cout << "                         -::.:-*.=.-:.*.-..+ : .:                         " << endl;
	cout << "                         -:: :+-...+:+%.-..= : ..                         " << endl;
	cout << "                         ... := .-.--.* .... . .                          " << endl;

}

void startScreen ()
{
	system("CLS");

	cout << "___________.__             ___________      .__                                   _____  " << endl;
	cout << "\\__    ___/|  |__   ____   \\_   _____/ ____ |  |__   ____   ____   ______   _____/ ____\\ " << endl;
	cout << "  |    |   |  |  \\_/ __ \\   |    __)__/ ___\\|  |  \\ /  _ \\_/ __ \\ /  ___/  /  _ \\   __\\  " << endl;
	cout << "  |    |   |   Y  \\  ___/   |        \\  \\___|   Y  (  <_> )  ___/ \\___ \\  (  <_> )  |    " << endl;
	cout << "  |____|   |___|  /\\_____> /_______  /\\_____>___|  /\\____/ \\_____>______>  \\____/|__|    " << endl << endl;

	cout << "    __________                             ___.                                     " << endl;
	cout << "    \\______   \\ ____   _____   ____   _____\\_ |______________    ____   ____  ____  " << endl;
	cout << "     |       _// __ \\ /     \\_/ __ \\ /     \\| __ \\_  __ \\__  \\  /    \\_/ ___\\/ __ \\ " << endl;
	cout << "     |    |   \\  ___/|  Y Y  \\  ___/|  Y Y  \\ \\_\\ \\  | \\// __ \\|   |  \\  \\__\\  ___/ " << endl;
	cout << "     |____|_  /\\_____>__|_|__/\\_____>__|_|__/_____/__|  (______/___|__/\\_____>_____>" << endl << endl << endl << endl << endl << endl << endl;

	system("pause");

}

void endScreen ()
{
	cout << " _____ _   _ _____   _____ _   _ ____    _   _   _ " << endl;
	cout << "|_   _| | | | ____| | ____| \\ | |  _ \\  | | | | | |" << endl;
	cout << "  | | | |_| |  _|   |  _| |  \\| | | | | | | | | | |" << endl;
	cout << "  | | |  _  | |___  | |___| |\\  | |_| | |_| |_| |_|" << endl;
	cout << "  |_| |_| |_|_____| |_____|_| \\_|____/  (_) (_) (_)" << endl;
}

void introNote()
{
	system ("CLS");

	cout << "__________________________________________________________________________" << endl;
	cout << "|                                                                        |" << endl;
	cout << "|\t If you are reading this you must have fell into the same trap I |" << endl;
	cout << "| did. This world is cruel, relentless, kind of like the world I used t- |" << endl;
	cout << "| o live in. In fact, you must have lived in that world as well.         |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "|\t Let me give you some advice, some advice I wish I would've tak- |" << endl;
	cout << "| en. You absolutely have to listen, if you don't theres a chance you    |" << endl;
	cout << "| may be stuck in this accursed world forever.                           |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "|\t The only thing you really need to know is that this world has   |" << endl;
	cout << "| rules. As I breathe my dying breaths, I need you to understand this.   |" << endl;
	cout << "| I don't want you to go through the same fate I have.                   |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "|                                 RULES                                  |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "| 1. Instead of health, this world seems to use your SANITY as a measur- |" << endl;
	cout << "| ment of your well-being. Always keep a calm head, try not to go insane |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "| 2. Don't trust anyone. If you ever fall for that mistake, you're no b- |" << endl;
	cout << "| etter than I am. Some things are a given, if you trusted nothing you   |" << endl;
	cout << "| wouldn't go anywhere in life. But don't be too trusting, everything is |" << endl;
	cout << "| trying to use you, to drive you to the point of breaking.              |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "| 3. Always try to get back to the real world. No matter how cruel it    |" << endl;
	cout << "| was to you, no matter how evil it may have been to you, I guarantee t- |" << endl;
	cout << "| his world is worse. You must remember. And I figured out exactly how   |" << endl;
	cout << "| to get back. They figured out and tried to kill me, but I managed to   |" << endl;
	cout << "| atleast write this.                                                    |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "| 4. In order to escape this world, you must obtain a key. Although I n- |" << endl;
	cout << "| ever found its actual location, many encounters have led me to this    |" << endl;
	cout << "| conclusion.                                                            |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "| 5. The last rule of this world is to always remember. This can be a s- |" << endl;
	cout << "| imple act like writing your name or writing down how sane you are. You |" << endl;
	cout << "| can try doing that on this letter.                                     |" << endl;
	cout << "|                                                                        |" << endl;
	cout << "| Please survive, I don't want you repeating my tragic fate. Farewell... |" << endl;
	cout << "|________________________________________________________________________|" << endl;

}

void drawMenu(int character) 
{
	system("CLS");
	if (character == 0)
	{
		cookie ();
		cout << endl << endl;
	}
	
	else if (character == 1)
	{
		printMerchant ();
		cout << endl;
	}
	
	else if (character == 2)
	{
		printElf ();
		cout << endl << endl;
	}
	
	else if (character == 3)
	{
		printGatekeeper ();
		cout << endl << endl;
	}
	cout << "SANITY: " << player.getHealth() << " / " << player.getMaxHealth() << endl << endl;
    cout << "   ";

    for (int i = 0; i < 4; i++) {
        if (i == selected) {
            cout << "> " << menuOptions[i] << "   ";
        } else {
            cout << "  " << menuOptions[i] << "   ";
        }
    }

    cout << endl << endl;
    cout << "Use arrow keys <- -> to move. Press Enter to select." << endl;
}


string handleInput(int character)
 {
 	while (true)
 	{
 		
 		drawMenu(character);
 	
	    char key = getch();
	    string choice = " ";
	
	    if (key == -32) { // Arrow key prefix
	        key = getch();
	
	        if (key == 75 && selected > 0) { // Left arrow
	            selected--;
	        } else if (key == 77 && selected < 3) { // Right arrow
	            selected++;
	        }
	    } else if (key == '\r') { // Enter key
	        choice = menuOptions[selected];
	        return choice;
	    }
	}
}

void battleBox ()
{
    system("CLS");
    
    cout << "SANITY: " << player.getHealth() << " / " << player.getMaxHealth() << endl << endl;
    cout << "   ";
    
    cout << "+" << string(MAP_WIDTH, '-') << "+" << endl;

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        cout << "|";
        for (int x = 0; x < MAP_WIDTH; ++x) {
            if (x == playerX && y == playerY) {
                cout << "@";
            } else {
                cout << map[y][x];
            }
        }
        cout << "|" << endl;
    }

    
    cout << "+" << string(MAP_WIDTH, '-') << "+" << endl;
    cout << "Use WASD to move." << endl;
}

int attack ()
{
	system("CLS");	
  	const int barWidth = 21;
    const int center = barWidth / 2;
    int position = 0;
    bool forward = true;
    bool stopped = false;

    cout << "Time your attack! Press SPACE to strike." << endl;

    while (!stopped) {
        cout << "[";

        for (int i = 0; i < barWidth; ++i) {
            if (i == position) {
                cout << WHITE; // moving marker
            } else if (abs(i - center) <= 1) {
                cout << GREEN; // crit zone
            } else if (abs(i - center) <= 4) {
                cout << YELLOW; // hit zone
            } else {
                cout << RED; // miss zone
            }
        }

        cout << "]\r";
        cout.flush();

        Sleep(50);

        if (forward) {
            position++;
            if (position >= barWidth - 1) forward = false;
        } else {
            position--;
            if (position <= 0) forward = true;
        }

        if (_kbhit()) {
            char key = _getch();
            if (key == ' ') stopped = true;
        }
    }

    cout << endl;

    int distance = abs(position - center);
    int damage = rand() % 10 + 8;

    if (distance <= 1) {
        cout << "\033[1;32mCRITICAL HIT!\033[0m" << endl;
        damage *= 2;
    } else if (distance <= 4) {
        cout << "\033[1;33mHIT!\033[0m" << endl;
    } else {
        cout << "\033[1;31mMISS!\033[0m" << endl;
        damage *= 0;
    }
    return damage;

}

int pray ()
{
	int heal;
	
	int chanceToHeal = (rand() % 2) + 1;
	
	if (chanceToHeal == 1)
	{
		cout << "Your prayer did not work. Gained back 0 SANITY." << endl << endl;
		system("pause");
		return -1;
	}
	else 
	{
		heal = (rand() % 20) + 5;
		player.setHealth(player.getHealth() + heal);
		if (player.getHealth() >= player.getMaxHealth())
		{
			cout << "Your prayer came true! Gained back max SANITY." << endl << endl;
			player.setHealth(player.getMaxHealth());
			system("pause");
		}
		else 
		{
			cout << "Your prayer came true! Gained back " << heal << " SANITY." << endl << endl;
			system("pause");
		}
		return heal;
	}
}

bool trust (string character, int health, int maxHealth)
{
	appearText("You decided to trust " + character + ".");
	cout << endl;
	int trustChance = (rand() % maxHealth) + (maxHealth - health);
	if (trustChance == maxHealth || maxHealth == 200)
	{
		appearText(character + " can be TRUSTED. "); 
		cout << endl << endl;
		system("pause");
		return true;
	}
	else 
	{
		appearText(character + " backstabbed you."); 
		cout << endl;
		appearText("You lost 10 SANITY...");
		cout << endl << endl;
		player.setHealth(player.getHealth() - 10);
		return false;
	}
	
}


void displayInventory(int selectedIndex)
{
    system("cls");
    cout << "=== INVENTORY ===" << endl;

    for (int i = 0; i < inventory.size(); ++i) {
        if (i == selectedIndex) {
            cout << "> " << inventory[i] << endl;
        } else {
            cout << "  " << inventory[i] << endl;
        }
    }

    cout << "\nUse W/S to move, Enter to select." << endl;
}

string inventoryMenu() 
{
    int selectedIndex = 0;

    while (true) {
        displayInventory(selectedIndex);

        char input = _getch();
        if (input == 'w' || input == 'W') {
            selectedIndex = (selectedIndex - 1 + inventory.size()) % inventory.size();
        } else if (input == 's' || input == 'S') {
            selectedIndex = (selectedIndex + 1) % inventory.size();
        } else if (input == '\r') { // Enter key
            system("CLS");
            if (selectedIndex == 0) {
                cout << "You chose to use nothing." << endl;
                return inventory[selectedIndex];
            } else {
                cout << "You used: " << inventory[selectedIndex] << endl;
                return inventory[selectedIndex];
            }
            break;
        }
    }
}

bool bedroomStart ()
{
	char choice;

	system("CLS");



	printBedroom();

	cout << endl;


	appearText ("You find yourself in a bedroom with no memory of how you got here...\nYou can't seem to remember anything...\nTheres a note under your bed...\n\n");

	system("pause");


	do
	{
		system("CLS");

		printBedroom();

		cout << endl;



		appearText ("Do you want to read the note?\n\n1. Yes\n2. No\n");

		choice = getch();
	} while (choice != '1' && choice != '2');

	if (choice == '2')
	{
		system("CLS");

		printBedroom();

		cout << endl;



		appearText ("You chose not to read the note\n\n\n\n");

		system("pause");

		return true;


	}
	else if (choice == '1')
	{
		bool readingNote;

		do
		{
			readingNote = readNote();
		} while (readingNote);
	}

	return false;


	cout << endl;




}

bool readNote ()
{
	introNote();
	cout << endl;
	system("pause");
	char choice;
	do
	{
		system("CLS");
		printBedroom();
		cout << endl;
		appearText("That was a long letter, you can't help but feel like you might have missed some info");
		cout << endl;
		appearText("Did you scroll up and read the entire letter?\n\n1. Yes\n2. No\n");

		choice = getch();
	} while (choice != '1' && choice != '2');
	if (choice == '1')
	{
		system("CLS");
		printBedroom();
		cout << endl;
		appearText("You reassured yourself that you have read the letter, it seems as if you don't need to reread it");
		cout << endl << endl;
		system("pause");

	}
	else if (choice == '2')
	{
		do
		{
			system("CLS");
			printBedroom();
			cout << endl;
			appearText("You get a chilling feeling, tempting you to reread the note");
			cout << endl;
			appearText("Do you want to reread the letter?\n\n1. Yes\n2. No\n");
			choice = getch();
		} while (choice != '1' && choice != '2');
		if (choice == '1')
		{
			return true;
		}
	}
	return false;
}

string nameScene ()
{
	char answer;
	string name;
	system("CLS");
	printBedroom();
	cout << endl;
	appearText("After reading the note a thought passes your mind...");
	cout << endl;
	appearText("It seems as if you must try and remember any detail about your past, maybe you should start with your name");
	cout << endl << endl;
	system("pause");

	do
	{
		system("CLS");
		appearText("What is your name: ");
		cin >> name;
		do
		{
			system("CLS");
			printBedroom();
			cout << endl;
			appearText("So your name is ");
			appearText(name);
			appearText("?\n\n1. Yes\n2. No\n");
			answer = getch();
			cout << endl;
		} while (answer != '1' && answer != '2');

	} while (answer == '2');

	return name;
}

string difficulty (string name, Entity player)
{
	char answer;
	string diff;
	string text;
	char response;

	system("CLS");
	printBedroom();
	cout << endl;
	appearText("Remembering you name seemed to have cleared up your mind a bit...");
	cout << endl;
	appearText("You start trying to remember more things about yourself...");
	cout << endl << endl;
	system("pause");
	system("CLS");
	printBedroom();
	cout << endl;
	appearText("Suddenly, you feel something touch you from behind.");
	cout << endl;
	appearText("You turn around, scared to find out what it could be...");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	appearText("It seems to be... A cookie?");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Hey there, I'm Cookie!");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "You don't look like your from this place. There just seems to be something a bit off about you...");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Oh! You don't remember anything about where you're from? Judging by how you look, I would say you're from the human realm.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Don't worry, we get a lot of people like... you. Every once in a while a human ends up in this abandoned town with no memory of his past life.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "It's okay though, I can help you. I'll show you how it works around here.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "First things first, tell me your name?");
	cout << endl;
	system("pause");
	
	text = "So your name is " + name + "? That's a beautiful name!";
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", text);
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Alright, I'll help you now. Everybody who lands in this world remembers something from their past life.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "That memory is their job. The reason? Because jobs reflect human desires. Their boundaries, their passions. Their SANITY.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Let me give you some options so that you can remember easier.");
	cout << endl;
	system("pause");
	
	do
	{
		do
		{
			system("CLS");
		
			cout << "So... which one of these was your past job";
			cout << endl << endl;
			cout << "+--------------------------------------------------------------------------+" << endl;
		    cout << "| 1. Surgeon:                                                              |" << endl;
		    cout << "|                                                                          |" << endl;
		    cout << "| Pretty wealthy in your past life huh, stable hands too.                  |" << endl;
		    cout << "|        " << setw(3) << 200 << " SANITY                                                        |" << endl;
		    cout << "|        " << setw(3) << 200  << " COINS                                                         |" << endl;
		    cout << "+--------------------------------------------------------------------------+" << endl;
			cout << endl << endl;
			cout << "+--------------------------------------------------------------------------+" << endl;
		    cout << "| 2. Entrepreneur                                                          |" << endl;
		    cout << "|                                                                          |" << endl;
		    cout << "| All that mattered was the money, not a very good mental state though.    |" << endl;
		    cout << "|        " << setw(3) << 100 << " SANITY                                                        |" << endl;
		    cout << "|        " << setw(3) << 400  << " COINS                                                         |" << endl;
		    cout << "+--------------------------------------------------------------------------+" << endl;
			cout << endl << endl;
			cout << "+--------------------------------------------------------------------------+" << endl;
		    cout << "| 3. Retail Worker                                                         |" << endl;
		    cout << "|                                                                          |" << endl;
		    cout << "| You definitely weren't expecting this on your night shift, huh?          |" << endl;
		    cout << "|        " << setw(3) << 150 << " SANITY                                                        |" << endl;
		    cout << "|        " << setw(3) << 100  << " COINS                                                         |" << endl;
		    cout << "+--------------------------------------------------------------------------+" << endl;
		
			answer = getch();
		} while (answer != '1' && answer != '2' && answer != '3');
		
		
		if (answer == '1')
		{
			diff = "Surgeon";
		}
		else if (answer == '2')
		{
			diff = "Entrepreneur";
		}
		else if (answer == '3')
		{
			diff = "Retail Worker";
		}
		
		do
		{
			system("CLS");
			cookie ();
			cout << endl;
			textBox("Cookie", "So you were a " + diff + " in your past life?");
			cout << endl;
			appearText("1. Yes");
			cout << endl;
			appearText("2. No");
			response = getch();
		} while (response != '1' && response != '2');
	} while (response == '2');
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Haha I knew it, you just seem like that type of person.");
	cout << endl;
	system("pause");
	
	
	return diff;
}

bool fightCookie ()
{
	int damage;
	string action = " ";
	double damageDealt = 0;
	int cookieHP = 200;
	int cookieMax = 200;
	int heal;
	bool isDead = false;
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Now that I know a bit about you, let me explain one rule of this world.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "If you want to live, and escape this world, you have to be able to fight and trust.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Allow me to show you how...");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Inhabitants of this town, such as myself will try to hurt you, and deplete your SANITY. Just like this.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	appearText("COOKIE attacks you, depleting 10 SANITY...");
	player.takeDamage(10);
	cout << endl;
	appearText("SANITY: " + to_string(player.getHealth()) + " / " + to_string(player.getMaxHealth()));
	cout << endl << endl;
	system("pause");
	
	
	
	if (player.getHealth() <= 0)
	{
		system("CLS");
		appearText("You ran out of sanity.");
		cout << endl;
		appearText("You start losing your mind and suddenly get transported back to a familiar sighting.");
		cout << endl << endl;
		system("pause");
		player.setHealth(player.getMaxHealth());
		player.playerDie();
		
		return false;
	}
	
	
	drawMenu (0);
	cout << endl;
	textBox("Cookie", "Now it's your turn to make a move.");		
	cout << endl;
	system("pause");
	
	drawMenu (0);
	cout << endl;
	textBox("Cookie", "How about we start with FIGHT.");		
	cout << endl;
	system("pause");
	
	action = handleInput(0);
	
	while (action != "Fight")
	{
		drawMenu (0);
		cout << endl;
		textBox("Cookie" ,"You have to FIGHT if you want to survive.");		
		cout << endl;
		system("pause");
		action = handleInput(0);
	}
	
	
	damage = attack();

	
	
	if (damage != 0)
	{
		cout << "You dealt " << damage << " damage to COOKIE." << endl;
		cookieHP -= damage;
		cout << "COOKIE has " << cookieHP << " health left..." << endl << endl;
		system("pause");
		drawMenu (0);
		cout << endl;
		textBox("Cookie", "Nice attack buddy your a natural.");		
		cout << endl;
		system("pause");
	}
	
	else 
	{	
		cout << "You dealt " << damage << " damage to COOKIE." << endl;
		cookieHP -= damage;
		cout << "COOKIE has " << cookieHP << " health left..." << endl << endl;
		system("pause");
		drawMenu (0);
		cout << endl;
		textBox("Cookie", "Wow man your pretty bad at this.");
		cout << endl;
		system("pause");
	}
	
	drawMenu (0);
	cout << endl;
	textBox("Cookie", "Now that you've learnt how to FIGHT, lets try PRAY next.");		
	cout << endl;
	system("pause");
	
	drawMenu (0);
	cout << endl;
	textBox("Cookie", "In a world where you can trust no one, you must atleast try to believe in your luck and faith.");		
	cout << endl;
	system("pause");
	
	drawMenu (0);
	cout << endl;
	textBox("Cookie", "The PRAY action gives you a chance to regain some SANITY for free.");		
	cout << endl;
	system("pause");
	
	action = handleInput(0);
	
	while (action != "Pray")
	{
		drawMenu (0);
		cout << endl;
		textBox("Cookie" ,"You must PRAY to keep your SANITY intact.");		
		cout << endl;
		system("pause");
		action = handleInput(0);
	}
	
	heal = pray ();
	
	if (heal == -1)
	{
		drawMenu (0);
		cout << endl;
		textBox("Cookie", "What an unlucky soul you are...");		
		cout << endl;
		system("pause");
	}
	else 
	{
		
		
		drawMenu (0);
		cout << endl;
		textBox("Cookie", "Wow! Maybe there is hope for you after all...");		
		cout << endl;
		system("pause");
	}
	
	drawMenu (0);
	cout << endl;
	textBox("Cookie", "Now that you know how to PRAY, lets check out your ITEMS.");		
	cout << endl;
	system("pause");
	
	drawMenu (0);
	cout << endl;
	textBox("Cookie", "You shouldn't have any items right now, but whats the harm in checking?");		
	cout << endl;
	system("pause");
	
	action = handleInput(0);
	
	while (action != "Item")
	{
		drawMenu (0);
		cout << endl;
		textBox("Cookie" ,"You should check out your ITEMS first.");		
		cout << endl;
		system("pause");
		action = handleInput(0);
	}
	
	
	inventoryMenu();
	
	cout << endl;
	
	system("pause");
	
	drawMenu (0);
	cout << endl;
	textBox("Cookie", "You will pick up some items along the way, don't worry. For now lets look at the final option.");		
	cout << endl;
	system("pause");
	
	drawMenu (0);
	cout << endl;
	textBox("Cookie", "Finally, and the most important option, is TRUST.");		
	cout << endl;
	system("pause");
	
	drawMenu (0);
	cout << endl;
	textBox("Cookie", "Lets see if you can TRUST me.");
	cout << endl;
	system("pause");
	
	action = handleInput(0);
	
	while (action != "Trust")
	{
		drawMenu (0);
		cout << endl;
		textBox("Cookie" ,"Come on, TRUST me already.");		
		cout << endl;
		system("pause");
		action = handleInput(0);
	}
	
	trust("COOKIE", cookieHP, cookieMax);
	
	drawMenu (0);
	cout << endl;
	textBox("Cookie", "See, told you I could be trusted.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Now lets get you out of here.");
	cout << endl;
	system("pause");
	
	return true;
}

void emptyTown ()
{
	system("CLS");
	sideWalk ();
	appearText("You find yourself walking through an abandoned town accompanied by COOKIE...");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "If we keep going down this path, we should be arriving at the townsquare in no time.");
	cout << endl;
	system("pause");
	
	system("CLS");
	sideWalk ();
	appearText("5 minutes pass by and you still haven't arrived at the townsquare...");
	cout << endl;
	appearText("You ask COOKIE if it's sure it knows where it's going.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Of course I know where I'm going, just have some patience.");
	cout << endl;
	system("pause");
	
	system("CLS");
	sideWalk ();
	appearText("While walking, a mysterious hooded figure catches your eyes.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	printMerchant ();
	appearText("He seems to be staring at you, a deep abyss beyond those eyes...");
	cout << endl;
	appearText("Then he begins to talk to you.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	printMerchant ();
	cout << endl;
	textBox("???", "Who... are... you? You don't... belong... here.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Oh hey there merchant! This here is my good friend " + player.getName() + ".");
	cout << endl;
	system("pause");
	
	system("CLS");
	printMerchant ();
	cout << endl;
	textBox("Merchant", "This... friend? I don't... believe.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printMerchant ();
	cout << endl;
	textBox("Merchant", player.getName() + ", you... are... friend? I am... merchant.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printMerchant ();
	cout << endl;
	textBox("Merchant", "I am only one... who knows where townsquare is.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	appearText("Cookie looks at you, embarrassed...");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Okay... so I may or may not have lied about knowing where townsquare is, but atleast we found merchant!");
	cout << endl;
	system("pause");
	
	system("CLS");
	printMerchant ();
	cout << endl;
	textBox("Merchant", "I will tell... where townsquare is... if you prove worth to me...");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Welp looks like we'll have to fight him before we can reach the townsquare.");
	cout << endl;
	system("pause");
	
}

bool fightMerchant ()
{
	string action;
	int merchantHP = 80;
	int merchantMax = 80;
	int damage;
	bool t = false;
	int heal;
	
	system("CLS");
	printMerchant ();
	cout << endl;
	appearText ("MERCHANT, wants to fight!");
	cout << endl << endl;
	system("pause");
	
	
	do
	{
		action = handleInput(1);
		
		if (action == "Fight")
		{
			damage = attack ();
			cout << "You dealt " << damage << " damage to MERCHANT." << endl;
			
			merchantHP -= damage;
			if (merchantHP <= 0)
			{
				merchantHP = 0;
				cout << "MERCHANT has fallen" << endl << endl;
				system("pause");
				break;
			}
			cout << "MERCHANT has " << merchantHP << " health left..." << endl << endl;
			system("pause");
		
		}
		
		else if (action == "Pray")
		{
			heal = pray ();
		}
		
		else if (action == "Item")
		{
			inventoryMenu();
			cout << endl;
	
			system("pause");
		}
		
		else if (action == "Trust")
		{
			t = trust("MERCHANT", merchantHP, merchantMax);
			cout << endl << endl;
			system("pause");
			
			if (player.getHealth() <= 0)
			{
				system("CLS");
				appearText("You ran out of sanity.");
				cout << endl;
				appearText("You start losing your mind and suddenly get transported back to a familiar sighting.");
				cout << endl << endl;
				system("pause");
				player.setHealth(player.getMaxHealth());
				
				return false;
			}
			if (t)
			{
				break;
			}
		}
		
		system("CLS");
		printMerchant ();
		cout << endl;
		appearText("MERCHANT attacks you, depleting 20 SANITY...");
		player.takeDamage(20);
		if (player.getHealth() <= 0)
		{
			player.setHealth(0);
		}
		cout << endl;
		appearText("SANITY: " + to_string(player.getHealth()) + " / " + to_string(player.getMaxHealth()));
		cout << endl << endl;
		system("pause");
		
		
		if (player.getHealth() <= 0)
		{
			system("CLS");
			appearText("You ran out of sanity.");
			cout << endl;
			appearText("You start losing your mind and suddenly get transported back to a familiar sighting.");
			cout << endl << endl;
			system("pause");
			player.setHealth(player.getMaxHealth());
			player.playerDie();
			
			return false;
		}
	}
	while (merchantHP > 0);
	
	system("CLS");
	printMerchant ();
	cout << endl;
	appearText ("You proved your worth to MERCHANT");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "You beat Merchant!!!");		
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Now we can check out townsquare!");		
	cout << endl;
	system("pause");
	
	system("CLS");
	printMerchant ();
	cout << endl;
	textBox("Merchant", player.getName() + "... is very good fighter...");
	cout << endl;
	system("pause");
	
	system("CLS");
	printMerchant ();
	cout << endl;
	textBox("Merchant", "I take you... to townsquare now.");
	cout << endl;
	system("pause");
	
	
	return true;
	
	
}

void townSquare ()
{
	char checkShop;
	
	system("CLS");
	printShop ();
	cout << endl;
	appearText ("Suddenly you feel your body get transported to another place.");
	cout << endl;
	appearText ("It seems as if merchant has teleported you to the townsquare.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	printShop ();
	cout << endl;
	textBox("Merchant", "This is... my shop...");
	cout << endl;
	system("pause");
	
	system("CLS");
	printShop ();
	cout << endl;
	textBox("Merchant", "Please support... family business... by buying...");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Come on you heard him. You should probably buy something to help you out.");
	cout << endl;
	system("pause");
	
	do
	{
		do
		{
			system("CLS");
			printShop();
			cout << endl;
			appearText ("Do you want to check out MERCHANTS shop?");
			cout << endl << endl;
			cout << "1. Yes" << endl;
			cout << "2. No" << endl;
			
			checkShop = getch();
		} while (checkShop != '1' && checkShop != '2');
		
		if (checkShop == '1')
		{
			shop ();
		}
		
	} while (checkShop != '2');
	
	system("CLS");
	printMerchant ();
	cout << endl;
	textBox("Merchant", "Thank you... friend...");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Now we finally have ITEMS for your inventory!");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Thank you Merchant, but we have to get going now.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printMerchant ();
	cout << endl;
	textBox("Merchant", "Goodbye... friend...");
	cout << endl;
	system("pause");
	
}

void gatesIntro ()
{
	system("CLS");
	sideWalk ();
	appearText("After leaving MERCHANTS shop, you continue walking through the town with COOKIE.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	sideWalk ();
	appearText("You remember the letter you read when you first came here mentioning something about a key.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	sideWalk ();
	appearText("You wonder if you should tell COOKIE about the letter.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Hey " + player.getName() + " since your going to leave this place there's something important I need to tell you.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Long ago there was a man, maybe he could've been an ancestor to you.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "He arrived at this place, in the same room I met you.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Me and him became close friends, and lived in peace.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "However, after a while of staying in this void, he wanted to leave.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Being his friend, I supported him and wanted to leave with him.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "However, we didn't know something.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "If we wanted to leave, we would have to FIGHT the GATEKEEPER.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "The GATEKEEPER is the one who guards the memorys of those who enter.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "When we went to FIGHT him, he messed with my friends mind beyond the point of recognition.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "My friend lost all of his SANITY, and started attacking me.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "So, please think about this, do you really want to ESCAPE?.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "You don't have to answer right now, but think about it.");
	cout << endl;
	system("pause");
	
	system("CLS");
	sideWalk ();
	appearText("COOKIES words echo in your head. However, you need to escape and continue on your journey.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	sideWalk ();
	appearText("Then, after walking for what seemed to be an eternity, you arrived at the GATE.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	printGate ();
	cout << endl;
	appearText("The tall GATE looms over you.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Well we're nearing the end of our journey, I guess we just have to walk through.");
	cout << endl;
	system("pause");
	
	
	system("CLS");
	printGate ();
	cout << endl;
	appearText("As you admire the GATES a sense of unease washes over you.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	printElf ();
	cout << endl;
	appearText("That little kid keeps... staring at you.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	printElf ();
	cout << endl;
	textBox("???", "Who are you people and what are you doing at the GATE?");
	cout << endl;
	system("pause");
	
	system("CLS");
	printElf ();
	cout << endl;
	textBox("???", "Could you be... trying to ESCAPE?");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Why would you need to know?");
	cout << endl;
	system("pause");
	
	system("CLS");
	printElf ();
	cout << endl;
	textBox("???", "Because I control which people can pass through this gate to fight the GATEKEEPER.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printElf ();
	cout << endl;
	textBox("Elf", "I am the ELF, the only one with the key.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printElf ();
	cout << endl;
	textBox("Elf", "Many have fallen to the GATEKEEPER, so if you want to meet him, I must test your battle prowess.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Hmmm, it seems if we want to leave, we have to fight this guy first, be careful though");
	cout << endl;
	system("pause");
}

bool fightElf ()
{
	string action;
	int elfHP = 115;
	int elfMax = 115;
	int damage;
	bool t = false;
	int heal;
	string itemPicked;
	
	system("CLS");
	printElf ();
	cout << endl;
	appearText ("ELF, wants to fight!");
	cout << endl << endl;
	system("pause");
	
	do
	{
		action = handleInput(2);
		
		if (action == "Fight")
		{
			damage = attack ();
			cout << "You dealt " << damage << " damage to ELF." << endl;
			
			elfHP -= damage;
			if (elfHP <= 0)
			{
				elfHP = 0;
				cout << "ELF has fallen" << endl << endl;
				system("pause");
				break;
			}
			cout << "ELF has " << elfHP << " health left..." << endl << endl;
			system("pause");
		
		}
		
		else if (action == "Pray")
		{
			heal = pray ();
		}
		
		else if (action == "Item")
		{
			itemPicked = inventoryMenu();
			cout << endl;
			
			if (itemPicked == "Quick Therapy")
			{
				auto itemRemoved = find(inventory.begin(), inventory.end(), "Quick Therapy");
				appearText("You watched the therapy session, it makes you feel relaxed.");
				cout << endl;
				appearText("Restored max SANITY.");
				cout << endl;
				player.setHealth(player.getMaxHealth());
				inventory.erase(itemRemoved);
			}
			else if (itemPicked == "Throwable Knife")
			{
				auto itemRemoved = find(inventory.begin(), inventory.end(), "Throwable Knife");
				appearText("You pick up your knife and throw it at ELF.");
				cout << endl << endl;
				inventory.erase(itemRemoved);
				cout << "You dealt " << 50 << " damage to ELF." << endl;
			
				elfHP -= 50;
				if (elfHP <= 0)
				{
					elfHP = 0;
					cout << "ELF has fallen" << endl << endl;
					system("pause");
					break;
				}
				cout << "ELF has " << elfHP << " health left..." << endl << endl;		
			}
			else if (itemPicked == "Buyable Love")
			{
				auto itemRemoved = find(inventory.begin(), inventory.end(), "Buyable Love");
				appearText("You show ELF your money and bribe him to give you the key.");
				cout << endl;
				appearText("It works!");
				cout << endl << endl;
				system ("pause");
				inventory.erase(itemRemoved);
				break;
		
			}
			else if (itemPicked == "Memory")
			{
				auto itemRemoved = find(inventory.begin(), inventory.end(), "Memory");
				appearText("You remember a calming memory.");
				cout << endl;
				appearText("Restored 50 SANITY.");
				cout << endl;
				player.setHealth(player.getHealth() + 50);
				if (player.getHealth() >= player.getMaxHealth())
				{
					player.setHealth(player.getMaxHealth());
				}
				inventory.erase(itemRemoved);
			}
			
	
			system("pause");
		}
		
		else if (action == "Trust")
		{
			t = trust("ELF", elfHP, elfMax);
			cout << endl << endl;
			system("pause");
			
			if (player.getHealth() <= 0)
			{
				system("CLS");
				appearText("You ran out of sanity.");
				cout << endl;
				appearText("You start losing your mind and suddenly get transported back to a familiar sighting.");
				cout << endl << endl;
				system("pause");
				player.setHealth(player.getMaxHealth());
				
				return false;
			}
			if (t)
			{
				break;
			}
		}
		
		system("CLS");
		printElf ();
		cout << endl;
		appearText("ELF attacks you, depleting 30 SANITY...");
		player.takeDamage(30);
		if (player.getHealth() <= 0)
		{
			player.setHealth(0);
		}
		cout << endl;
		appearText("SANITY: " + to_string(player.getHealth()) + " / " + to_string(player.getMaxHealth()));
		cout << endl << endl;
		system("pause");
		
		
		if (player.getHealth() <= 0)
		{
			system("CLS");
			appearText("You ran out of sanity.");
			cout << endl;
			appearText("You start losing your mind and suddenly get transported back to a familiar sighting.");
			cout << endl << endl;
			system("pause");
			player.setHealth(player.getMaxHealth());
			player.playerDie();
			
			return false;
		}
	}
	while (elfHP > 0);
	
	system("CLS");
	printElf ();
	cout << endl;
	appearText ("You bested ELF!");
	cout << endl << endl;
	system("pause");	
	
	system("CLS");
	printElf ();
	cout << endl;
	textBox("Elf", "Listen, I know you beat me, but are you sure you really want to fight the GATEKEEPER?");
	cout << endl;
	system("pause");
	
	return true;
}

bool keyScene ()
{
	char answer;
	
	system("CLS");
	printElf ();
	cout << endl;
	textBox("Elf", "The GATEKEEPER controls everything in this realm.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printElf ();
	cout << endl;
	textBox("Elf", "Considering you want to leave, he probably has your past memories.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printElf ();
	cout << endl;
	textBox("Elf", "That means you don't remember anything from your past.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printElf ();
	cout << endl;
	textBox("Elf", "You can start a new life, here.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Come on " + player.getName() + ", he has a point.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "I can't lose another one of my friends.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printElf ();
	cout << endl;
	textBox("Elf", "So, before I give you this key, let me ask you one last time...");
	cout << endl;
	system("pause");
	
	system("CLS");
	appearText ("Are you sure you want to fight the GATEKEEPER?");
	cout << endl << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	answer = getch();
	
	while (answer != '1' && answer != '2')
	{
		system("CLS");
		cout << "Are you sure you want to fight the GATEKEEPER?";
		cout << endl << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		answer = getch();
	}
	
	if (answer == '1')
	{
		system("CLS");
		printElf ();
		cout << endl;
		textBox("Elf", "Then so be it, but I gave you a warning.");
		cout << endl;
		system("pause");
		
		system("CLS");
		printElf ();
		cout << endl;
		appearText("You recieve the KEY from ELF, ready to FIGHT the GATEKEEPER.");
		cout << endl << endl;
		system("pause");
		
		system("CLS");
		printElf ();
		cout << endl;
		appearText("But thoughts keep ringing through your brain. Did you really make the right decision...");
		cout << endl << endl;
		system("pause");
		
		system("CLS");
		cookie ();
		cout << endl;
		textBox("Cookie", "Well then, lets get going.");
		cout << endl;
		system("pause");
		
		player.setHealth(player.getMaxHealth());
		
		return false;
	}
	
	else if (answer == '2')
	{
		system("CLS");
		printElf ();
		cout << endl;
		textBox("Elf", "You made the right decision.");
		cout << endl;
		system("pause");
		
		system("CLS");
		cookie ();
		cout << endl;
		textBox("Cookie", "Well then " + player.getName() + " let's go back home...");
		cout << endl;
		system("pause");
		
		return true;
	}
	
	return false;
}

void enterGates ()
{
	system("CLS");
	printGate ();
	cout << endl;
	appearText("You begin walking towards the gate as it slowly opens. However, suddenly you get stopped.");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	textBox("???", "You foolish human. How many must come before me searching for their memories...");
	cout << endl;
	system("pause");
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	textBox("???", "How many must I shut down...");
	cout << endl;
	system("pause");
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	textBox("???", "And you... Cookie... I thought you learnt your lesson the last time you challenged me.");
	cout << endl;
	system("pause");
	
	system("CLS");
	cookie ();
	cout << endl;
	textBox("Cookie", "Listen here, no matter what happens I will help " + player.getName() + " escape.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	textBox("???", "I've grown tired of you Cookie.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	appearText("Suddenly, COOKIE gets crushed into pieces");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	deadCookie ();
	cout << endl;
	appearText("You wonder what cookie did to deserve that fate...");
	cout << endl << endl;
	system("pause");
	
	system("CLS");
	deadCookie ();
	cout << endl;
	textBox("Gatekeeper", "Take a look at your friends dead, crushed up body.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	textBox("Gatekeeper", "This is what it means to challenge me.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	textBox("Gatekeeper", "Now then, since you came all this way...");
	cout << endl;
	system("pause");
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	textBox("Gatekeeper", "I suppose it wouldn't hurt to play with you...");
	cout << endl;
	system("pause");
}

bool fightGatekeeper ()
{
	string action;
	int gatekeeperMax = 350;
	int damage;
	bool t = false;
	int heal;
	string itemPicked;
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	appearText ("GATEKEEPER, wants to fight!");
	cout << endl << endl;
	system("pause");
	
	do
	{
		action = handleInput(3);
		
		if (action == "Fight")
		{
			damage = attack ();
			cout << "You dealt " << damage << " damage to gatekeeper." << endl;
			
			gatekeeperHP -= damage;
			if (gatekeeperHP <= 0)
			{
				gatekeeperHP = 0;
				cout << "GATEKEEPER has fallen" << endl << endl;
				system("pause");
				break;
			}
			cout << "GATEKEEPER has " << gatekeeperHP << " health left..." << endl << endl;
			system("pause");
		
		}
		
		else if (action == "Pray")
		{
			heal = pray ();
		}
		
		else if (action == "Item")
		{
			itemPicked = inventoryMenu();
			cout << endl;
			
			if (itemPicked == "Quick Therapy")
			{
				auto itemRemoved = find(inventory.begin(), inventory.end(), "Quick Therapy");
				appearText("You watched the therapy session, it makes you feel relaxed.");
				cout << endl;
				appearText("Restored max SANITY.");
				cout << endl;
				player.setHealth(player.getMaxHealth());
				inventory.erase(itemRemoved);
			}
			else if (itemPicked == "Throwable Knife")
			{
				auto itemRemoved = find(inventory.begin(), inventory.end(), "Throwable Knife");
				appearText("You pick up your knife and throw it at GATEKEEPER.");
				cout << endl << endl;
				inventory.erase(itemRemoved);
				cout << "You dealt " << 50 << " damage to GATEKEEPER." << endl;
			
				gatekeeperHP -= 50;
				if (gatekeeperHP <= 0)
				{
					gatekeeperHP = 0;
					cout << "GATEKEEPER has fallen" << endl << endl;
					system("pause");
					break;
				}
				cout << "GATEKEEPER has " << gatekeeperHP << " health left..." << endl << endl;		
			}
			else if (itemPicked == "Buyable Love")
			{
				auto itemRemoved = find(inventory.begin(), inventory.end(), "Buyable Love");
				appearText("You show GATEKEEPER your money and bribe him to let you go.");
				cout << endl;
				appearText("It works!");
				cout << endl << endl;
				system ("pause");
				inventory.erase(itemRemoved);
				break;
		
			}
			else if (itemPicked == "Memory")
			{
				auto itemRemoved = find(inventory.begin(), inventory.end(), "Memory");
				appearText("You remember a calming memory.");
				cout << endl;
				appearText("Restored 50 SANITY.");
				cout << endl;
				player.setHealth(player.getHealth() + 50);
				if (player.getHealth() >= player.getMaxHealth())
				{
					player.setHealth(player.getMaxHealth());
				}
				inventory.erase(itemRemoved);
			}
			
	
			system("pause");
		}
		
		else if (action == "Trust")
		{
			t = trust("GATEKEEPER", gatekeeperHP, gatekeeperMax);
			cout << endl << endl;
			system("pause");
			
			if (player.getHealth() <= 0)
			{
				system("CLS");
				appearText("You ran out of sanity.");
				cout << endl;
				appearText("But you can't let yourself die just yet.");
				cout << endl << endl;
				system("pause");
				player.setHealth(player.getMaxHealth());
				
				return false;
			}
			if (t)
			{
				break;
			}
		}
		
		system("CLS");
		printGatekeeper ();
		cout << endl;
		appearText("GATEKEEPER attacks you, depleting 50 SANITY...");
		player.takeDamage(50);
		if (player.getHealth() <= 0)
		{
			player.setHealth(0);
		}
		cout << endl;
		appearText("SANITY: " + to_string(player.getHealth()) + " / " + to_string(player.getMaxHealth()));
		cout << endl << endl;
		system("pause");
		
		
		if (player.getHealth() <= 0)
		{
			system("CLS");
			appearText("You ran out of sanity.");
			cout << endl;
			appearText("But you can't let yourself die just yet.");
			cout << endl << endl;
			system("pause");
			player.setHealth(player.getMaxHealth());
			player.playerDie();
			
			return false;
		}
	}
	while (gatekeeperHP > 0);
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	appearText ("You finally beat GATEKEEPER!");
	cout << endl << endl;
	system("pause");	
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	textBox("Gatekeeper", "No, NO I CAN'T ACCEPT THIS!");
	cout << endl;
	system("pause");
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	textBox("Gatekeeper", "Me... God of this realm... Bested by a mere human...");
	cout << endl;
	system("pause");
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	textBox("Gatekeeper", "Fine then, you can escape this realm and get your memories back.");
	cout << endl;
	system("pause");
	
	system("CLS");
	printGatekeeper ();
	cout << endl;
	appearText("You walk through the gates, saying goodbye to this world.");
	cout << endl << endl;
	system("pause");
	
	return true;
}

