#ifndef blocksInclude
#define blocksInclude
#include "ctypes.h"
typedef struct _blocktype{
	vec2i image[6];
	bool drawtype;
	float height;
	bool transparency;
}blocktype;

const blocktype air = 		{{																		},0,0		,1};
const blocktype grass = 	{{{3,0}	,{3,0},	{12,12},	{3,0},	{3,0},	{2,0}		},1,0		,0};
const blocktype dirt =		{{{2,0}	,{2,0},	{2,0},	{2,0},	{2,0},	{2,0}		},1,0		,0};
const blocktype stone = 	{{{1,0}	,{1,0},	{1,0},	{1,0},	{1,0},	{1,0}		},1,0		,0};
const blocktype dirt_snow ={{{4,4}	,{4,4},	{2,4},	{4,4},	{4,4},	{2,0}		},1,0		,0};
const blocktype oak_wood =	{{{4,1}	,{4,1},	{5,1},	{4,1},	{4,1},	{5,1}		},1,0		,0};
const blocktype leave =		{{{4,3}	,{4,3},	{4,3},	{4,3},	{4,3},	{4,3}		},1,0		,1};
const blocktype water =		{{{13,12},{13,12},{13,12},	{13,12},	{13,12},	{13,12}	},1,0.125,1};
const blocktype oak_plank ={{{4,0}	,{4,0},	{4,0},	{4,0},	{4,0},	{4,0}		},1,0		,0};
const blocktype sand =		{{{2,1}	,{2,1},	{2,1},	{2,1},	{2,1},	{2,1}		},1,0		,0};
const blocktype ice =		{{{3,4}	,{3,4},	{3,4},	{3,4},	{3,4},	{3,4}		},1,0		,0};
const blocktype snow =		{{{2,4}	,{2,4},	{2,4},	{2,4},	{2,4},	{2,4}		},1,0.875,0};
const blocktype cactus =	{{{6,4}	,{6,4},	{5,4},	{6,4},	{6,4},	{5,4}		},1,0		,1};

blocktype blockarray[256] = {
	air,		//0
	grass,		//1
	dirt,		//2
	stone,		//3
	dirt_snow,	//4
	oak_wood,	//5
	leave,		//6
	water,		//7
	oak_plank,	//8
	sand,		//9
	ice,		//10
	snow,		//11
	cactus		//12
};

#endif


