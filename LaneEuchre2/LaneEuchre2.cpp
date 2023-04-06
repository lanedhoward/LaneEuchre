// LaneEuchre.cpp : Defines the entry point for the application.
//

#pragma once
#include "LaneEuchre2.h"

int main()
{
	ConsoleUtils::Print("Welcome to Lane's Euchre Game");

	Game g = Game();

	g.Run();


	ConsoleUtils::Print();

	ConsoleUtils::WaitForKeyPress();

	return 0;
}
