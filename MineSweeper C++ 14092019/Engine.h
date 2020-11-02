#pragma once
#include <fstream>

const int nMineFieldWidth = 9 * 5;
const int nMineFieldHeight = 9 * 5;
const int nScreenWidth = nMineFieldWidth + 4;
const int nScreenHeight = nMineFieldHeight + 18;
int posX, posY;
int xCus, yCus;
int yOffset = 16;
int xOffset = 2;
int timeAmount = 0;
int timeAmountSubtrackt = 0;

char mainArray[nMineFieldHeight][nMineFieldWidth];
char mainColorArray[nMineFieldHeight][nMineFieldWidth];
char OutsideArray[nScreenHeight][nScreenWidth];
char OutsideColorArray[nScreenHeight][nScreenWidth];

char mapArray[nMineFieldWidth / 5][nMineFieldWidth / 5];
char xCounter, yCounter;

bool endState = false;
bool enterState = false;
bool flagState = false;

class Object
{

public:
	int spriteWidth, spriteHeight;
	char** spriteArray;
	char** spriteColorArray;

	void SpriteImport(std::string fileName)
	{
		//Delete old arrays
		DeleteArrays();

		std::ifstream inFile;
		inFile.open("./sprites/" + fileName + ".acspr");
		if (inFile.fail()) return;

		//Reads the sprite width and sprite height
		inFile >> spriteWidth;
		inFile.ignore(1, '\n');
		inFile >> spriteHeight;
		inFile.ignore(1, '\n');

		//Defines the size of the arrays
		spriteArray = new char* [spriteHeight];
		for (int i = 0; i < spriteHeight; i++)
			spriteArray[i] = new char[spriteWidth];

		spriteColorArray = new char* [spriteHeight];
		for (int i = 0; i < spriteHeight; i++)
			spriteColorArray[i] = new char[spriteWidth];

		//Reads the sprite- and color array
		for (int i = 0; i < spriteHeight; i++)
		{
			inFile.read(spriteArray[i], spriteWidth);
			inFile.ignore(1, '\n');
		}
		inFile.ignore(1, '\n');

		for (int i = 0; i < spriteHeight; i++)
		{
			inFile.read(spriteColorArray[i], spriteWidth);
			inFile.ignore(1, '\n');
		}
		inFile.close();
	}

	void SpriteDraw(int posX, int posY)
	{
		for (int y = 0; y < spriteHeight; y++) {
			for (int x = 0; x < spriteWidth; x++) {
				if (spriteArray[y][x] != ' ')
				{
					if ((posY + y >= 0) && (posY + y < nScreenHeight) && (posX + x >= 0) && (posX + x < nScreenWidth))
					{
						mainColorArray[y + posY][x + posX - 1] = mainColorArray[y + posY][x + posX - 1];
						mainArray[y + posY][x + posX - 1] = mainArray[y + posY][x + posX - 1];

						mainColorArray[y + posY][x + posX] = spriteColorArray[y][x];
						mainArray[y + posY][x + posX] = spriteArray[y][x];
					}
				}
			}
		}
	}

	void SpriteDrawOutside(int posX, int posY)
	{
		for (int y = 0; y < spriteHeight; y++) {
			for (int x = 0; x < spriteWidth; x++) {
				if (spriteArray[y][x] != ' ')
				{
					if ((posY + y >= 0) && (posY + y < nScreenHeight) && (posX + x >= 0) && (posX + x < nScreenWidth))
					{
						OutsideColorArray[y + posY][x + posX - 1] = OutsideColorArray[y + posY][x + posX - 1];
						OutsideArray[y + posY][x + posX - 1] = OutsideArray[y + posY][x + posX - 1];

						OutsideColorArray[y + posY][x + posX] = spriteColorArray[y][x];
						OutsideArray[y + posY][x + posX] = spriteArray[y][x];
					}
				}
			}
		}
	}


	void SpriteIdDraw(char charId)
	{
		for (int bY = 0; bY < nMineFieldWidth / 5; bY++) {
			for (int bX = 0; bX < nMineFieldWidth / 5; bX++) {
				for (int y = 0; y < spriteHeight; y++) {
					for (int x = 0; x < spriteWidth; x++) {
						if ((mapArray[bY][bX] == charId) && (spriteArray[y][x] != ' '))
						{
							mainColorArray[y + (bY * spriteHeight)][x + (bX * spriteWidth)] = spriteColorArray[y][x];
							mainArray[y + (bY * spriteHeight)][x + (bX * spriteWidth)] = spriteArray[y][x];
						}
					}
				}
			}
		}
	}

	void SpriteDrawBackground()
	{
		for (int bY = 0; bY < floor(nMineFieldHeight / spriteHeight); bY++) {
			for (int bX = 0; bX < floor(nMineFieldWidth / spriteWidth); bX++) {
				for (int y = 0; y < spriteHeight; y++) {
					for (int x = 0; x < spriteWidth; x++) {
						if (spriteArray[y][x] != ' ')
						{
							mainColorArray[y + (bY * spriteHeight)][x + (bX * spriteWidth)] = spriteColorArray[y][x];
							mainArray[y + (bY * spriteHeight)][x + (bX * spriteWidth)] = spriteArray[y][x];
						}
						else mainColorArray[y + (bY * spriteHeight)][x + (bX * spriteWidth)] = char(0);
					}
				}
			}
		}
	}

	void DrawBackground(char backgroundCharacter, int Color)
	{
		for (int y = 0; y < nMineFieldHeight; y++) {
			for (int x = 0; x < nMineFieldWidth; x++) {
				mainColorArray[y][x] = Color;
				mainArray[y][x] = backgroundCharacter;
			}
		}
	}

	void DrawBackgroundOutside(char backgroundCharacter, int Color)
	{
		for (int y = 0; y < nScreenHeight; y++) {
			for (int x = 0; x < nScreenWidth; x++) {
				OutsideColorArray[y][x] = Color;
				OutsideArray[y][x] = backgroundCharacter;
			}
		}
	}

	void DeleteArrays()
	{
		for (int i = 0; i < spriteHeight; i++)
			delete[] spriteArray[i];

		for (int i = 0; i < spriteHeight; i++)
			delete[] spriteColorArray[i];

		delete[] spriteArray;
		delete[] spriteColorArray;
	}
};

