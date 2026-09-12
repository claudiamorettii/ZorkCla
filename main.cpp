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
		<< "\nFor a list of available commands, type \"\\help.\"\n"
	    << "\n---------------------------------------------------------------------\n";
    
	Game ELOS;

	ELOS.Run();

	cout << "\nThank you for playing my game!\n";
	return 0;
}