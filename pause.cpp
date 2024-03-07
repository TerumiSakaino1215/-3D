//=============================================================================
//
// É|Å[ÉYâÊñ èàóù [pause.cpp]
// Author : GP11A341 12 ã´ñÏãPé¿
//
//=============================================================================
#include "main.h"
#include "pause.h"
#include "input.h"
#include "game.h"

bool	pauseswitch;
MODE	mode;

void InitPause(void)
{
	pauseswitch = false;
	mode = MODE_PAUSE;
}

void UninitPause(void)
{

}

void UpdatePause(void)
{
	if (pauseswitch == false && GetKeyboardTrigger(DIK_SPACE))
	{	
		pauseswitch = true;
		SetMode(MODE_PAUSE);
	}
	if(pauseswitch == true && GetKeyboardTrigger(DIK_SPACE))
	{
		pauseswitch = false; 
		mode = MODE_GAME;
	}

	//if (GetKeyboardTrigger(DIK_SPACE))
	//{
	//	SetMode(MODE_GAME);
	//}
}

void DrawPause(void)
{
	DrawGame();
}

MODE SetGameReturn(void)
{
	return mode;
}