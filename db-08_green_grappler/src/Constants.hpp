#pragma once

enum Damage 
{
	Damage_Physical,
	Damage_Fire,
	Damage_Ice,
	Damage_Lighting,
	Damage_Cure,
	Damage_Hack
};

enum Faction 
{
	Faction_Player,
	Faction_Enemy,
	Faction_None,
};

enum Buttons
{
	Button_ToggleFullscreen,
	Button_ToggleSlowMotion,
	Button_ToggleVSync,
	Button_ToggleWideScreen,
	Button_Exit,
	Button_Jump,
	Button_Fire,
	Button_Left,
	Button_Right,
	Button_Up,
	Button_Down,
	Button_ForceQuit
};

enum Direction
{	
	Direction_None = 0,
	Direction_Left = 1,
	Direction_Right = 2,
	Direction_Up = 4,
	Direction_Down = 8
};

enum DialoguePlacement
{
	DialoguePlacement_None,
	DialoguePlacement_Top,
	DialoguePlacement_Bottom,
	DialoguePlacement_Battle
};