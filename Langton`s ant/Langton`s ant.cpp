#include <Windows.h>
#include <iostream>
#define HEIGHT 48
#define WIDTH  211
#define STARTY 24
#define STARTX 105
void turn(short& curr_y, short& curr_x, const short& orient) {
	switch (orient) {
	case 1: ++curr_x; break;
	case 2: --curr_y; break;
	case 3: --curr_x; break;
	case 4: ++curr_y; break;
	//default: std::cout << "problem";
	}
}
void setColor(const short& color, CHAR_INFO (&antSpace)[HEIGHT][WIDTH], const short &curr_y, const short &curr_x) {
	antSpace[curr_y][curr_x].Attributes = color;
}
int main()
{
	HANDLE hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwBufferSize = { WIDTH,HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, WIDTH - 1, HEIGHT - 1 };

	CHAR_INFO antSpace[HEIGHT][WIDTH];

	ReadConsoleOutput(hOutput, (CHAR_INFO*)antSpace, dwBufferSize,
		dwBufferCoord, &rcRegion);

	short orient = 2;
	short curr_y = STARTY, curr_x = STARTX;
	antSpace[curr_y][curr_x].Attributes = 0;
	WriteConsoleOutput(hOutput, (CHAR_INFO*)antSpace, dwBufferSize,
		dwBufferCoord, &rcRegion);
	try {
		while (true) {
			if (antSpace[curr_y][curr_x].Attributes != 194) {
				setColor(194, antSpace, curr_y, curr_x);
				(orient == 4) ? orient -= 3 : ++orient;
				turn(curr_y, curr_x, orient);
			}
			else {
				setColor(0, antSpace, curr_y, curr_x);
				//(orient == 4) ? orient -= 3 : ++orient;
				(orient == 1) ? orient += 3 : --orient;
				turn(curr_y, curr_x, orient);
			}
			Sleep(10);
			antSpace[0][0].Char.AsciiChar = orient + 48;
			//antSpace[curr_y][curr_x].Char.AsciiChar = 'o';
			WriteConsoleOutput(hOutput, (CHAR_INFO*)antSpace, dwBufferSize,
				dwBufferCoord, &rcRegion);
		}
	}
	catch (...) {
		exit(0);
	}
}