#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "game.h"

using namespace std;

int main()
{
	cout << "\033[1;31m----------- Welcome to ELOS!-----------\n\033[0m" //\033[0m back to normal, \033[1;31m bold and red
	    << "--- Game created by Claudia Moretti ---\n"
	   	<< "\033[1;31m---------------------------------------\n\033[0m"
		<< "\nFor a list of available commands type \033[1;32m\"help.\"\033[0m\n"
	    << "\n---------------------------------------------------------------------\n";
	    
	Game ELOS;

	ELOS.Run();

	cout << "\nThank you for playing my game! :)\n";

	cout << "\n\033[1;33m===============================================\033[0m\n";

	cout << "\nPress Enter to close the game...";

	string finalInput;
	getline(cin, finalInput);

	return 0;
}