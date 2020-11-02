#include "ObjectMain.h"
#include "Functions.h"
#include "Mines.h"
#include "DrawOutside.h"
#include "DrawInside.h"

int main()
{
	// Setting custom console settings

	SetConsoleTitle("MineSweeper");
	UpdateConsoleBufferSize();
	UseDefaultCustomColorPalette();

	UseDefaultCustomColorPalette();
	GeneralFunctions();

	// Set startup sprite for objects
	ObjectSetSprite();

	// Show Splash Screen
	SplashScreen();

	// Update map array with empty cell
	for (int y = 0; y < nMineFieldHeight / 5; y++) {
		for (int x = 0; x < nMineFieldWidth / 5; x++) {
			mapArray[y][x] = '#';
		}
	}

	// Draw Outside from minefield
	DrawOutside();

	// Start time in thread
	using namespace std::literals::chrono_literals;
	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(1s);

	while (endState == false)
	{
		/**		Input & Logic		**/

		// Inputs when cursor is on the map
		if (cursorAtTop == false)
		{
			// Main controls
			if ((GetAsyncKeyState(VK_BACK) & 0x0001) && (generateMines == false)) { flagState = true; Sleep(50); }
			if ((GetAsyncKeyState(VK_RIGHT) & 0x0001) && (xCus < nMineFieldWidth - 5)) xCus += 5;
			if ((GetAsyncKeyState(VK_LEFT) & 0x0001) && (xCus > 0)) xCus -= 5;
			if ((GetAsyncKeyState(VK_DOWN) & 0x0001) && (yCus < nMineFieldHeight - 5)) yCus += 5;
			if (GetAsyncKeyState(VK_UP) & 0x0001) { if (yCus == 0) cursorAtTop = true; if (yCus > 0) yCus -= 5; }
			while ((GetAsyncKeyState(VK_RETURN) & 0x8000) && (mineExplodesState == 0))
			{
				// Check current time **
				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float> duration = end - start;
				timeAmount = duration.count() - timeAmountSubtrackt;
				if (timeAmount > 999) timeAmount = 999;

				// Draw while enter is pressed
				if (enterState == false) SoundPlay("./Sounds/ClickDown.wav");
				mineFace.SpriteImport("spr_mineHead02"); //Sets the face sprite to scared
				cursor.SpriteImport("spr_mineCursor02"); //Sets the cursor sprite to 10x10
				
				//Sets enterstate to true
				enterState = true;

				// Updates the game while enters is pressed
				DrawOutside();
				DrawInside();
				Update(true, true, true);
				Sleep(10);
			}
		}
		else // Inputs when cursor is on the face
		{
			// Changes the location cursor back to map
			if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && (mineExplodesState == 0)) cursorAtTop = false; 

			// Resets game
			if ((GetAsyncKeyState(VK_RETURN) & 0x8000)) 
			{
				mineInfoAmount = mineAmount;
				mineCount = mineAmount;
				generateMines = true;
				mineExplodesState = 0;
				ObjectSetSprite();

				// Update map array with empty cell
				for (int y = 0; y < nMineFieldHeight / 5; y++) {
					for (int x = 0; x < nMineFieldWidth / 5; x++) {
						mapArray[y][x] = '#';
					}
				}
			}
		}

		// Inputs at any time
		if (GetAsyncKeyState(VK_F11) & 0x0001) UpdateConsoleBufferSize();
		if ((GetAsyncKeyState(VK_ESCAPE) & 0x0001)) endState = true;

		// Change fontsize
		if ((GetAsyncKeyState('W') & 0x0001) && (fontSize < 32)) fontSize += 8;
		if ((GetAsyncKeyState('S') & 0x0001) && (fontSize > 8)) fontSize -= 8;

		// Debug only
		/*
		if (GetAsyncKeyState(VK_DELETE) & 0x8000) showDebugMap = false;
		if (GetAsyncKeyState(VK_INSERT) & 0x8000) showDebugMap = true;
		if (GetAsyncKeyState(VK_HOME) & 0x0001)
		{
			for (int y = 0; y < nMineFieldHeight / 5; y++) {
				for (int x = 0; x < nMineFieldWidth / 5; x++) {
					// Change default cell to blank
					if ((mapArray[y][x] == '#'))
						mapArray[y][x] = '0';

					// Show number
					for (int i = 65; i < 74; i++) {
						if (mapArray[y][x] == char(i))
							mapArray[y][x] = char(i - 16);
					}
				}
			}
		}*/
		/**		Logic		**/

		//Sets the cursor sprite to 5x5 **
		cursor.SpriteImport("spr_mineCursor01"); 

		///** Flag logic **
		if (flagState == true)
		{
			//Writes a flag to map array
			[&] {
				for (int y = 0; y < nMineFieldHeight / 5; y++) {
					for (int x = 0; x < nMineFieldWidth / 5; x++) {
						//Check if x & y is cursor position
						if ((x * 5 == xCus) && (y * 5 == yCus))
						{
							//Dealocate flag to original state **
							if (mapArray[y][x] == '*') { mapArray[y][x] = '#'; mineInfoAmount += 1; return; } // Flag on default cell
							if (mapArray[y][x] == '¤') { mapArray[y][x] = 'o'; mineInfoAmount += 1; return; } // Flag on mine

							for (int i = 97; i < 106; i++) // Flag on numbers | a - i = A - I
								if (mapArray[y][x] == char(i)) { mapArray[y][x] = char(i - 32); mineInfoAmount += 1; return; }

							// Alocate cell to flag **
							if ((mapArray[y][x] != '0') && (mapArray[y][x] != '1') && (mapArray[y][x] != '2') && //Checking if cell  
								(mapArray[y][x] != '3') && (mapArray[y][x] != '4') && (mapArray[y][x] != '5') && //is not been
								(mapArray[y][x] != '6') && (mapArray[y][x] != '7') && (mapArray[y][x] != '8') && //clicked on &
								(mineInfoAmount > 0))															 //mineInfoAmount > 0
							{
								if (mapArray[y][x] == '#') mapArray[y][x] = '*'; // Flag on default cell
								if (mapArray[y][x] == 'o') mapArray[y][x] = '¤'; // Flag on mine

								for (int i = 65; i < 74; i++) // Flag on numbers | a - i = A - I
									if (mapArray[y][x] == char(i)) mapArray[y][x] = char(i + 32);

								//Updates infoboard
								mineInfoAmount -= 1;
								SoundPlay("./Sounds/Flag.wav");
								return;
							}
						}
					}
				}
			}();
			flagState = false;
		}

		///** Map logic **
		if (enterState == true)
		{
			SoundPlay("./Sounds/ClickUp.wav");
			for (int y = 0; y < nMineFieldHeight / 5; y++) {
				for (int x = 0; x < nMineFieldWidth / 5; x++) {

					// Change default cell to blank
					if ((x * 5 == xCus) && (y * 5 == yCus) && (mapArray[y][x] == '#'))
					{
						mapArray[y][x] = '0';

						//Spawn mines on first click
						if (generateMines == true) spawnMines();
					}

					// Show number on map
					for (int i = 65; i < 74; i++) {
						if ((x * 5 == xCus) && (y * 5 == yCus) && (mapArray[y][x] == char(i)))
							mapArray[y][x] = char(i - 16);
					}

					// Check if cell is a mine
					if ((x * 5 == xCus) && (y * 5 == yCus) && (mapArray[y][x] == 'o'))
					{
						mapArray[y][x] = 'O';
						cursorAtTop = true;
						mineExplodesState += 1;
					}

					//Check for win
					if ((mapArray[y][x] != '#') && (mapArray[y][x] != 'A') && (mapArray[y][x] != 'B') &&   // Check if the map
						(mapArray[y][x] != 'C') && (mapArray[y][x] != 'D') && (mapArray[y][x] != 'E') &&   // dosn't contain
						(mapArray[y][x] != 'F') && (mapArray[y][x] != 'G') && (mapArray[y][x] != 'H') &&   // any onclicked 
						(mapArray[y][x] != 'I'))														   // Cells
					{
						cellCounterToWin++;
						if (cellCounterToWin == (nMineFieldWidth / 5) * (nMineFieldHeight / 5))
						{
							for (int y = 0; y < nMineFieldHeight / 5; y++) {
								for (int x = 0; x < nMineFieldWidth / 5; x++) {
									if ((mapArray[y][x] == 'o') || (mapArray[y][x] == '¤')) mapArray[y][x] = '¤';
								}
							}
							mineExplodesState = -1;
							cursorAtTop = true;
							generateMines = true;
							mineFace.SpriteImport("spr_mineHead04");
							SoundPlay("./Sounds/Clap.wav");
						}
					}
					mineCountAtCell = 0;
				}
			}
			cellCounterToWin = 0;
			enterState = false;
		}


		///** Timing **
		if (generateMines == true)
		{
			// Check how mush time to subtrack from current time **
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> duration = end - start;
			timeAmountSubtrackt = duration.count();
		}
		else
		{
			// Check current time **
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> duration = end - start;
			timeAmount = duration.count() - timeAmountSubtrackt;
			if (timeAmount > 999) timeAmount = 999;
		}

		/**		Mine explosion logic & animation	**/
		if (mineExplodesState > 0)
		{
			generateMines = true;
			switch (mineExplodesState)
			{
			case 1: mineFace.SpriteImport("spr_mineHead02"); break;
			case 3: Sleep(250); mineFace.SpriteImport("spr_mineHead03"); break;
			case 4: mineExplosion.SpriteImport("spr_mineExplodes01"); break;
			case 5: mineExplosion.SpriteImport("spr_mineExplodes02"); break;
			case 6: mineExplosion.SpriteImport("spr_mineExplodes03"); SoundPlay("./Sounds/Explosion.wav"); break;
			case 7: mineExplosion.SpriteImport("spr_mineExplodes04"); break;
			case 8: mineExplosion.SpriteImport("spr_mineExplodes05"); break;
			case 9: mineExplosion.SpriteImport("spr_mineExplosionEnd"); break;
			case 11: Sleep(250); break;
			case 12: 
				mineExplosion.SpriteImport("spr_mineExplosionDestroyer"); 
				mineShowAllExplosion.SpriteIdDraw('o'); 

				// Check is flag placement was rigth
				for (int y = 0; y < nMineFieldHeight / 5; y++) {
					for (int x = 0; x < nMineFieldWidth / 5; x++) {
						if ((mapArray[y][x] == 'a') || (mapArray[y][x] == 'b') || (mapArray[y][x] == 'c') ||
							(mapArray[y][x] == 'd') || (mapArray[y][x] == 'e') || (mapArray[y][x] == 'f') ||
							(mapArray[y][x] == 'g') || (mapArray[y][x] == 'h') || (mapArray[y][x] == 'i') ||
							(mapArray[y][x] == '*')) 
						{ mapArray[y][x] = '-'; }
					}
				}
				break;
			}
			if (mineExplodesState < 14) { mineExplodesState += 1; Sleep(90); }
		}
		if (mineExplodesState == 0) mineFace.SpriteImport("spr_mineHead01");

		/**		Update Arrays & screen	**/
		DrawOutside();
		DrawInside();
		Update(true, true, true);
	}
	
	return 0;
}