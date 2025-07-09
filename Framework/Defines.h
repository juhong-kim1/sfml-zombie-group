#pragma once

#define DEF_DEV

enum class SortingLayers
{
	Background,
	Foreground,
	Default,
	UI,
};

enum class Gametitle
{
	title,
	mode,
	exit,

};

enum class Origins
{
	TL, TC, TR,	// 0 1 2
	ML, MC, MR,	// 3 4 5
	BL, BC, BR, // 6 7 8
	Custom
};

enum SceneIds
{
	None =-1,
	Title,
	Mode,
	Game1,
	Game2,
	Game3,
	Game4,
	Game5,
	Game6,
	Select,
	Count,
};

enum class Sides
{
	Left,
	Right,
	None,
};