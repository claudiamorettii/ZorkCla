#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "game.h"

using namespace std;

#define RED_ "\033[1;31m"
#define _WHITE "\033[0m"

int main()
{
	cout << RED_ "----------- Welcome to ELOS!-----------\n" _WHITE << "--- Game created by Claudia Moretti ---\n" << RED_ "---------------------------------------\n" _WHITE;
    
	Game ELOS;

	ELOS.Run();

	cout << "\nThank you for playing my game!\n";
	return 0;
}