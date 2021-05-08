#include "../headers/game.h"
#include <limits>
using namespace std;

// game constructor
Game::Game()
{
	this-> option = 0;
	this-> playing = true;
}

// game destructor
Game::~Game()
{
	
}


// member function which displays the start menu
void Game::start_menu(Save& save_obj, Character& player, Inventory& inv)
{	
	do
	{
		cout << "WELCOME TO THE GAME! \n";
		cout << "--------------------- \n";
		cout << "Select an option: \n";
		cout << "[1] New Game! \n";
		cout << "[2] Continue! \n";
		cout << "[3] Quit! \n";
		cout << "Your choice: ";
		cin >> this -> option;
		
		switch(this -> option)
		{
			case 1:
				// start new game
				init_game(player);
				start_game();
				break;
			case 2:
				cout << "\n";
				if (save_obj.load_game(player) == 1)
				{
					this -> option = 0;
					cout << "\n";
					break;
				}
				else
				{
					break;	
				}
			case 3:
				quit_game();
				break;
			default:
				Game::valid_input();
				break;
		}	
	} while ((this -> option < 1) || (this -> option > 3));
}


// member function to initalize and create a new character
void Game::init_game(Character& player)
{
	string name;
	
	cout << "\n";	
	cout << "Please enter a name for your character: \n";
	cout << "Your name: ";
	getline(cin.ignore(1000, '\n'), name);
	cout << "\n";
	
	cout << "Character created! \n\n";
	player.init_char(name);
	
	game_instructions();
}


void Game::game_instructions()
{
	int count = 0;
	string str = "";
	string temp = "";
	
	ifstream f;
	f.open("./Txt/Instructions.txt");
	
	while(!f.peek() != EOF)
	{
		getline(f, str, '\n');
		temp = temp + '\n' + str;
		cout << temp;
		
		count++;
		
		if(count == 5)
		{
			cout << "\nPress Enter to continue" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			cout << endl;
			
			count = 0;
		}
	}
	
	cout << "Press any key to continue..\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl;
}

// GAMEPLAY MENU
// [1]: complete.
// [2]: not functional
// [3]: complete
// [4]: complete.
// GOAL: IMPORT TEXT FROM FILE
void Game::game_menu(Enemy& enemy, Character& player, Battle& battle, Inventory& inv_obj, Save& save_obj, Zone& zone_obj, string& string_obj, Map& game_map_obj, Item& item_obj, Interact& interact_obj)
{	
	do
	{
		cout << "\nGAME MENU \n";
		cout << "-------------- \n";
		cout << "[1]: View Character Sheet \n";
		cout << "[2]: View Inventory Sheet \n";
		cout << "[3]: View instructions \n";
		cout << "[4]: Save Game \n";
		cout << "[5]: Quit Game \n";;
		cout << "[6]: Continue Game \n";
		cout << "-------------- \n";
		cout << "Your choice: ";
		cin >> this -> option;
		
		switch(this -> option)
		{
			case 1:
				player.print_stats();
				break;
			case 2:
				cout << "\n";
				cout << "Viewing Inventory Sheet: \n\n";
				inv_obj.print();
				break;
			case 3:
				cout << "Call instructions function: STUB \n\n";
				break;
			case 4:
				save_menu(player, save_obj, string_obj);
				break;
			case 5:
				quit_game();
				break;
			case 6:
				game_map_obj.move(player, enemy, battle, inv_obj, zone_obj, item_obj, interact_obj);
				break;
			default:
				Game::valid_input();
				break;
		}
	} while((option < 1) || (option > 5));
}

// member function to quit the game
void Game::quit_game()
{
	cout << "\n";
	cout << "\n";
	cout << "Quitting game \n\n";
	playing = false;
}


// SAVE MENU
// [1]: complete
// [2]: complete
// GOAL: MIGRATE TO SAVE.CPP
// GOAL: IMPORT TEXT FROM FILE
void Game::save_menu(Character& player, Save& save_obj, string& string_obj)
{	
	do
	{
	
		cout << "SAVE MENU \n";
		cout << "--------- \n";
		cout << "Select an option: \n";
		cout << "[1] Save game \n";
		cout << "[2] Go back \n";
		cout << "Your choice: ";
		cin >> this -> option;
		
		switch(this -> option)
		{
			case 1:
				overwrite_menu(player, save_obj);
				break;
			case 2:
				cout << "\n";
				break;
			default:
				Game::valid_input();
				break;
		}
	} while((this -> option < 1) || (this -> option > 2));	
}

// [1]: complete
// [2]: complete
// GOAL: MIGRATE TO SAVE.CPP
// GOAL: IMPORT TEXT FROM FILE
void Game::overwrite_menu(Character& player, Save& save_obj)
{
	do 
	{
		cout << "\n";
		cout << "OVERWRITE MENU \n";
		cout << "-------------- \n";
		cout << "Would you like to overwrite your previous save file? \n";
		cout << "WARNING: THIS ACTION CANNOT BE UNDONE! \n";
		cout << "Select an option: \n";
		cout << "[1]: Yes. \n";
		cout << "[2]: No. \n";
		cout << "Your choice: ";
		cin >> this -> option;
		
		switch(this -> option)
		{
			case 1:
				cout << "\n";
				save_obj.save_game(player);
				cout << "\n";
				break;
			case 2:
				cout << "\n";
				break;
			default:
				Game::valid_input();
				break;
		}
	} while((this -> option < 1) || (this -> option > 2));	

}

// member function for input validation
void Game::valid_input()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	cout << "\nInvalid! please choose a vaild option: \n\n";
}

//tells the beginning of the story, before handing control
// over to the player.
void Game::start_game() 
{
	int count = 0;
	string str = "";
	ifstream file;
	
	// Opening the Beginning story file
	file.open("./Txt/StoryStart.txt");
	
	//Reading each line of the file and printing out the story.
	while (file.peek() != EOF)
	{
		if(count == 10)
		{
			cout << "\n\n";
			cout << "Press Enter to continue" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			count = 0;
		}
		
		getline(file, str, '\n');
		cout << str << endl;
		
		count++;
	}

	cout << "Press any key to continue..\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl;
	
}
