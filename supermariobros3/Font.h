#pragma once

#include <unordered_map>
#include "Sprites.h"

#define FONT_SIZE 8

#define FONT_0 50013
#define FONT_1 50014
#define FONT_2 50015
#define FONT_3 50016
#define FONT_4 50017
#define FONT_5 50018
#define FONT_6 50019
#define FONT_7 50020
#define FONT_8 50021
#define FONT_9 50022
#define FONT_A 50023
#define FONT_B 50024
#define FONT_C 50025
#define FONT_D 50026
#define FONT_E 50027
#define FONT_F 50028
#define FONT_G 50029
#define FONT_H 50030
#define FONT_I 50031
#define FONT_J 50032
#define FONT_K 50033
#define FONT_L 50034
#define FONT_M 50035
#define FONT_N 50036
#define FONT_O 50037
#define FONT_P 50038
#define FONT_Q 50039
#define FONT_R 50040
#define FONT_S 50041
#define FONT_T 50042
#define FONT_U 50043
#define FONT_V 50044
#define FONT_W 50045
#define FONT_X 50046
#define FONT_Y 50047
#define FONT_Z 50048

class CFont
{
	unordered_map<char, LPSPRITE> fonts;

public:
	CFont();
	LPSPRITE Map(char c);
	vector<LPSPRITE> StringToSprites(string str);
};

