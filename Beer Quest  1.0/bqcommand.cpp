#pragma once

#include "stdafx.h"
#include "bqgame.h"


char Command::Get()
{
	int c = 0;
	time_t start, end;
	time(&start);
	while (!_kbhit())
	{
		/*if (activePlace != NULL)
		{
			time(&end);
			elapsedTime = difftime(end, start);
			if (elapsedTime == TIME_ENERGY)
			{
				if (energy >= MAX_ENERGY)
				{
					player->SetEnergy(-player->GetEnergy());
					player->SetEnergy(100);
				}
				else player->SetEnergy(INC_ENERGY);

				time(&start);
				elapsedTime = 0;
			}
		}*/
	}
	time(&end);
	elapsedTime = difftime(end, start);
	c = _getch();
	c = toupper(c);
	system("cls");
	return char(c);
}