// Beer Quest  1.0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "bqgame.h"

using namespace std;

int Command::elapsedTime = 0;

int main()
{
	Game game;
	game.Play();
	return 0;
}

