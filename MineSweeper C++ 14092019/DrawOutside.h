#pragma once
byte timeBarArray[3];
byte mineCountArray[3];
std::string spriteNum = "spr_mineNum0";
bool cursorAtTop = false;

void SplashScreen()
{
	Update(true, true, false);
	Sleep(1000);
	//Splash Screen
	for (int i = 48; i > 12; i--)
	{
		mineSplashScreen.DrawBackgroundOutside(char(219), 0);
		mineSplashScreen.SpriteDrawOutside(2, (nScreenHeight / 2) - i);
		Update(true, true, false);
		Sleep(5);
	}
	Sleep(2500);
	for (int i = 12; i > -36; i--)
	{
		mineSplashScreen.DrawBackgroundOutside(char(219), 0);
		mineSplashScreen.SpriteDrawOutside(2, (nScreenHeight / 2) - i);
		Update(true, true, false);
		Sleep(5);
	}
}

void DrawOutside()
{
	//Draw Outside from minefield
	backgroundOutside.DrawBackgroundOutside(char(219), 7);
	
	mineBorderCornerUpLeft.SpriteDrawOutside(0, 0);
	mineBorderCornerUpRight.SpriteDrawOutside(nScreenWidth - 2, 0);
	mineBorderCornerDownLeft.SpriteDrawOutside(0, nScreenHeight-2);
	mineBorderCornerDownRight.SpriteDrawOutside(nScreenWidth-2, nScreenHeight - 2);
	
	mineCounterObjects[0].SpriteDrawOutside((nScreenWidth / 2) - 21, (yOffset / 2) - 5);
	mineCounterObjects[1].SpriteDrawOutside((nScreenWidth / 2) - 16, (yOffset / 2) - 5);
	mineCounterObjects[2].SpriteDrawOutside((nScreenWidth / 2) - 11, (yOffset / 2) - 5);
	
	mineFace.SpriteDrawOutside((nScreenWidth / 2) - 5, (yOffset / 2) - 5);
	if (cursorAtTop == true)
	{
		cursor.SpriteImport("spr_mineCursor03");
		cursor.SpriteDrawOutside((nScreenWidth / 2) - 5, (yOffset / 2) - 5);
	}

	mineCounterObjects[3].SpriteDrawOutside((nScreenWidth / 2) + 7, (yOffset / 2) - 5);
	mineCounterObjects[4].SpriteDrawOutside((nScreenWidth / 2) + 12, (yOffset / 2) - 5);
	mineCounterObjects[5].SpriteDrawOutside((nScreenWidth / 2) + 17, (yOffset / 2) - 5);
	
	//Update time- & minecount bar
	mineCountArray[2] = mineInfoAmount % 10;
	mineCountArray[1] = mineInfoAmount / 10 % 10;
	mineCountArray[0] = mineInfoAmount / 100 % 10;
	
	timeBarArray[2] = timeAmount % 10;
	timeBarArray[1] = timeAmount / 10 % 10;
	timeBarArray[0] = timeAmount / 100 % 10;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 48; j < 58; j++){
			spriteNum += char(j);
			if ((mineCountArray[i] == j - 48) && (i < 3)) mineCounterObjects[i].SpriteImport(spriteNum);
			if ((timeBarArray[i-3] == j - 48) && (i >= 3)) mineCounterObjects[i].SpriteImport(spriteNum);
			spriteNum = "spr_mineNum0";
		}
	}

	//Draw borders
	for (int y = 0; y < nScreenHeight; y++) {
		for (int x = 0; x < nScreenWidth; x++) {
			if ((y > 1) && (y < nScreenHeight - 6))
			{
				mineBorderLeftVertical.SpriteDrawOutside(0, y);
				mineBorderRightVertical.SpriteDrawOutside(nScreenWidth - 2, y);
			}

			if ((x > 1) && (x < nScreenWidth - 5))
			{
				mineBorderDownHorizontal.SpriteDrawOutside(x, nScreenHeight-2);
				mineBorderDownHorizontal.SpriteDrawOutside(x, yOffset-2);
				mineBorderDownHorizontal.SpriteDrawOutside(x, 0);
			}
		}
	}
}