#pragma once
#include "Engine.h"

//Object create
Object mineSplashScreen;
Object backgroundOutside;
Object mineField;
Object mineShowAllExplosion;
Object mineExplosion;
Object mineExplosionAnimation;
Object mineBlank;
Object mineFlag;
Object mineFlagWrong;
Object mineCount01;
Object mineCount02;
Object mineCount03;
Object mineCount04;
Object mineCount05;
Object mineCount06;
Object mineCount07;
Object mineCount08;
Object cursor;

Object mineBorderLeftVertical;
Object mineBorderRightVertical;
Object mineBorderDownHorizontal;
Object mineBorderCornerDownLeft;
Object mineBorderCornerDownRight;
Object mineBorderCornerUpLeft;
Object mineBorderCornerUpRight;

Object mineFace;
Object mineNumCount1;
Object mineNumCount2;
Object mineNumCount3;
Object mineNumTime1;
Object mineNumTime2;
Object mineNumTime3;
Object mineCounterObjects[] = {mineNumCount1, mineNumCount2 , mineNumCount3, mineNumTime1, mineNumTime2, mineNumTime3 };

void ObjectSetSprite()
{
	//Object sprite
	mineField.SpriteImport("spr_mineField");
	mineExplosion.SpriteImport("spr_mineExplosion");
	mineShowAllExplosion.SpriteImport("spr_mineExplosion");
	mineBlank.SpriteImport("spr_mineBlank");
	mineFlag.SpriteImport("spr_mineFlag");
	mineFlagWrong.SpriteImport("spr_mineFlagWrong");
	cursor.SpriteImport("spr_mineCursor01");
	mineCount01.SpriteImport("spr_mineCount01");
	mineCount02.SpriteImport("spr_mineCount02");
	mineCount03.SpriteImport("spr_mineCount03");
	mineCount04.SpriteImport("spr_mineCount04");
	mineCount05.SpriteImport("spr_mineCount05");
	mineCount06.SpriteImport("spr_mineCount06");
	mineCount07.SpriteImport("spr_mineCount07");
	mineCount08.SpriteImport("spr_mineCount08");

	mineBorderLeftVertical.SpriteImport("spr_mineBorderLeftVertical");
	mineBorderRightVertical.SpriteImport("spr_mineBorderRightVertical");
	mineBorderDownHorizontal.SpriteImport("spr_mineBorderDownHorizontal");
	mineBorderCornerDownLeft.SpriteImport("spr_mineBorderCornerDownLeft");
	mineBorderCornerDownRight.SpriteImport("spr_mineBorderCornerDownRight");
	mineBorderCornerUpLeft.SpriteImport("spr_mineBorderCornerUpLeft");
	mineBorderCornerUpRight.SpriteImport("spr_mineBorderCornerUpRight");

	mineSplashScreen.SpriteImport("spr_mineSplashScreen");
	mineFace.SpriteImport("spr_mineHead01");
}