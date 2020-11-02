#pragma once
#include <stdlib.h>
#include <time.h>

// Variables
int mineAmount = 10; // Used to set the amount of mines on the map
int mineInfoAmount = mineAmount; // Used to show how many mines there has been found
int mineCount = mineAmount; // Used to check how many mines to spawn
int mineExplodesState = 0;
int xRandomMineSpawn, yRandomMineSpawn;
int mineCountAtCell = 0;
int cellCounterToWin = 0;

bool generateMines = true;

// Spawn mines randomly
void spawnMines()
{
	srand(time(NULL));
	for (int y = 0; y < nMineFieldHeight / 5; y++) {
		for (int x = 0; x < nMineFieldWidth / 5; x++) {

			if (mineCount > 0)
			{
				//While minespot is already taken
				while ((mapArray[yRandomMineSpawn][xRandomMineSpawn] == 'o') || (mapArray[yRandomMineSpawn][xRandomMineSpawn] == '0'))
				{
					xRandomMineSpawn = rand() % (nMineFieldWidth / 5);
					yRandomMineSpawn = rand() % (nMineFieldHeight / 5);
				}

				mapArray[yRandomMineSpawn][xRandomMineSpawn] = 'o';
				mineCount -= 1;
			}
		}
	}
	//Check how many mines there is at the cells area
	for (int y = 0; y < nMineFieldHeight / 5; y++) {
		for (int x = 0; x < nMineFieldWidth / 5; x++) {
			if (mapArray[y][x] != 'o')
			{
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						if ((y + i >= 0) && (x + j >= 0) && (y + i < nMineFieldHeight / 5) && (x + j < nMineFieldWidth / 5))
						{
							if (mapArray[y + i][x + j] == 'o')
								mineCountAtCell++;
						}
					}
				}
			}
			//Write number to maparray
			for (int i = 65; i < 73; i++) {
				if (mineCountAtCell == i - 64) mapArray[y][x] = char(i);
			}
			mineCountAtCell = 0;
		}
	}
	generateMines = false;
}