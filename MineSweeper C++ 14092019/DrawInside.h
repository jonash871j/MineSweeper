#pragma once

void DrawInside()
{
	// Minefield sprite
	mineField.SpriteIdDraw('#');
	for (int i = 65; i < 74; i++) // Number | A - I
		mineField.SpriteIdDraw(char(i));

	// Mineblank sprite
	mineBlank.SpriteIdDraw('0');

	// Minecount number sprite
	mineCount01.SpriteIdDraw('1');
	mineCount02.SpriteIdDraw('2');
	mineCount03.SpriteIdDraw('3');
	mineCount04.SpriteIdDraw('4');
	mineCount05.SpriteIdDraw('5');
	mineCount06.SpriteIdDraw('6');
	mineCount07.SpriteIdDraw('7');
	mineCount08.SpriteIdDraw('8');

	// Mine sprite
	if (mineExplodesState == 0) mineField.SpriteIdDraw('o');
	mineExplosion.SpriteIdDraw('O');

	// Flag sprites
	mineFlag.SpriteIdDraw('*'); // Flag on default cell
	mineFlag.SpriteIdDraw('¤'); // Flag on mine
	for (int i = 97; i < 106; i++) // Flag on number | a - i
		mineFlag.SpriteIdDraw(char(i));

	// Flag wrong
	mineFlagWrong.SpriteIdDraw('-');
	// Cursor sprite
	if (cursorAtTop == false) cursor.SpriteDraw(xCus, yCus);
}