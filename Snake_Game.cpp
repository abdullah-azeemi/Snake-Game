#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<fstream>
#include<iomanip>
#include<ctime>
#include<string>
#include<time.h>
#include<mmsystem.h>
using namespace std;

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}

enum DIRECTION{UP, DOWN, LEFT, RIGHT};

struct position{

	int ri;
	int ci;
};
struct snake {

	position* ps;
	int size;
	int score;
	char sym;
	DIRECTION direction;
	int colour;
	string name;
	bool isAlive;

	int LEFTKEY, RIGHTKEY, UPKEY, DOWNKEY;
};
struct food {

	position fp;
	bool isAlive;
	int score;
	int colour;
	char sym;
};
struct stageCordinates{

	int ri[10];
	int ci[10];
	int current_stage;
};

bool isLegalCordinate(snake s, position p, int height, int width)
{
	for (int i = 0; i < s.size; i++)
	{
		if (s.ps[i].ri == p.ri && s.ps[i].ci == p.ci)
		{
			return false;
		}
	}
	if (p.ri == 0 || p.ri == height - 1 || p.ci == 0 || p.ci == width - 1)
	{
		return false;
	}
	return true;
}
bool isLegalCordinate2(snake s1, snake s2,snake s3, snake s4, position p, int height, int width)
{
	for (int i = 0; i < s1.size; i++)
	{
		if (s1.ps[i].ri == p.ri && s1.ps[i].ci == p.ci)
		{
			return false;
		}
	}
	for (int i = 0; i < s2.size; i++)
	{
		if (s2.ps[i].ri == p.ri && s2.ps[i].ci == p.ci)
		{
			return false;
		}
	}
	for (int i = 0; i < s3.size; i++)
	{
		if (s3.ps[i].ri == p.ri && s3.ps[i].ci == p.ci)
		{
			return false;
		}
	}
	for (int i = 0; i < s4.size; i++)
	{
		if (s4.ps[i].ri == p.ri && s4.ps[i].ci == p.ci)
		{
			return false;
		}
	}
	if (p.ri == 0 || p.ri == height - 1 || p.ci == 0 || p.ci == width - 1)
	{
		return false;
	}
	return true;
}
void generateFood(food& f, int height, int width, snake& s)
{
	do
	{
		f.fp.ri = rand() % height;
		f.fp.ci = rand() % width;
	} while (isLegalCordinate(s,f.fp, height, width)== false);

	f.isAlive = true;
	f.score = 1;
}
void generateFood2(food& f, int height, int width, snake& s1, snake & s2, snake &s3, snake & s4)
{
	do
	{
		f.fp.ri = rand() % height;
		f.fp.ci = rand() % width;
	} while (isLegalCordinate2(s1,s2,s3,s4, f.fp, height, width) == false);

	f.isAlive = true;
	f.score = 1;
}

void init(snake& S,food &f, int height, int width, stageCordinates &sc)
{
	S.ps = new position[3];
	S.ps[0].ri = height / 2;
	S.ps[0].ci = width / 2;

	S.ps[1].ri = height / 2;
	S.ps[1].ci = width / 2-1;

	S.ps[2].ri = height / 2;
	S.ps[2].ci = width / 2-1;

	S.size = 3;
	S.score = 0;
	S.colour = 4;
	S.sym = -37;
	S.direction = RIGHT;
	S.name = "saanp";
	S.isAlive = true;

	S.RIGHTKEY = 77;
	S.LEFTKEY = 75;
	S.UPKEY = 72;
	S.DOWNKEY = 80;

	f.colour = 5;
	f.sym = '#';
	sc.current_stage = 0;
	generateFood(f, height, width, S);
}
void init2(snake& S1, snake &S2, snake & S3, snake & S4, food& f, int height, int width, int & nop, stageCordinates & sc) 
{
	gotoRowCol(85,0);
	cout << "\n Enter the Number of Players : ";
	cin >> nop;
	string name;
	 
	if (nop > 1 || nop == 1)
	{
		// Snake 1
		S1.ps = new position[3];
		S1.ps[0].ri = height / 2;
		S1.ps[0].ci = width / 2;

		S1.ps[1].ri = height / 2;
		S1.ps[1].ci = width / 2 - 1;

		S1.ps[2].ri = height / 2;
		S1.ps[2].ci = width / 2 - 1;

		S1.size = 3;
		S1.score = 0;
		S1.colour = 4;
		S1.sym = -37;
		S1.direction = RIGHT;
		cout << "\n Enter the Player's 1 name : ";
		cin >> name;
		S1.name = name;
		S1.isAlive = true;

		S1.RIGHTKEY = 77;
		S1.LEFTKEY = 75;
		S1.UPKEY = 72;
		S1.DOWNKEY = 80;
	}
	if (nop > 2 || nop == 2)
	{
		// Snake 2
		S2.ps = new position[3];
		S2.ps[0].ri = height / 4;
		S2.ps[0].ci = width / 4;

		S2.ps[1].ri = height / 4;
		S2.ps[1].ci = width / 4 - 1;

		S2.ps[2].ri = height / 4;
		S2.ps[2].ci = width / 4 - 1;

		S2.size = 3;
		S2.score = 0;
		S2.colour = 3;
		S2.sym = -37;
		S2.direction = RIGHT;
		cout << "\n Enter the Player's 2 name : ";
		cin >> name;
		S2.name = name;
		S2.isAlive = true;

		S2.RIGHTKEY = 100;
		S2.LEFTKEY = 97;
		S2.UPKEY = 119;
		S2.DOWNKEY = 115;
	}
	if (nop > 3 || nop == 3)
	{
		// Snake 3
		S3.ps = new position[3];
		S3.ps[0].ri = height / 1.5;
		S3.ps[0].ci = width / 1.5;

		S3.ps[1].ri = height / 1.5 - 1;
		S3.ps[1].ci = width / 1.5;

		S3.ps[2].ri = height / 1.5 - 2;
		S3.ps[2].ci = width / 1.5;

		S3.size = 3;
		S3.score = 0;
		S3.colour = 12;
		S3.sym = -37;
		S3.direction = DOWN;
		cout << "\n Enter the Player's 3 name : ";
		cin >> name;
		S3.name = name;
		S3.isAlive = true;

		S3.RIGHTKEY = 54;
		S3.LEFTKEY = 52;
		S3.UPKEY = 56;
		S3.DOWNKEY = 53;
	}
	if (nop == 4)
	{
		// Snake 4
		S4.ps = new position[3];
		S4.ps[0].ri = height / 8;
		S4.ps[0].ci = width / 8;

		S4.ps[1].ri = height / 8 - 1;
		S4.ps[1].ci = width / 8;

		S4.ps[2].ri = height / 8 - 2;
		S4.ps[2].ci = width / 8;

		S4.size = 3;
		S4.score = 0;
		S4.colour = 10;
		S4.sym = -37;
		S4.direction = DOWN;
		cout << "\n Enter the Player's 4 name : ";
		cin >> name;
		S4.name = name;
		S4.isAlive = true;

		S4.RIGHTKEY = 108;
		S4.LEFTKEY = 106;
		S4.UPKEY = 105;
		S4.DOWNKEY = 107;
	}
	
	system("cls");
	f.colour = 5;
	f.sym = '#';
	sc.current_stage = 0;
	generateFood(f, height, width, S1);
}
void displaySnake(const snake& S)
{
	if (S.isAlive == true)
	{
		for (int i = 0; i < S.size; i++)
		{
			gotoRowCol(S.ps[i].ri, S.ps[i].ci);
			SetClr(S.colour);
			if (i == 0)
				cout << 'O';
			else if (i != 0)
				cout << S.sym;

		}
	}
}
void displayFood(food& f)
{
	gotoRowCol(f.fp.ri, f.fp.ci);
	SetClr(f.colour);
	cout << f.sym;
}
void undisplayFood(food& f)
{
	gotoRowCol(f.fp.ri, f.fp.ci);
	SetClr(f.colour);
	cout << ' ';
}
void foodTimer(int &x, food& f, int height, int width, snake & s1, snake & s2, snake & s3, snake & s4)
{
	if (x > 50)
	{
		undisplayFood(f);
		generateFood2(f, height, width, s1, s2, s3, s4);
		x = 0;
	}
}
void foodTimer2(int& x, food& f, int height, int width, snake& s1, snake& s2, snake& s3, snake& s4, bool &giyab)
{
	if (x > 800)
	{
		undisplayFood(f);
		generateFood2(f, height, width, s1, s2, s3, s4);
		x = 0;
		giyab = true;
	}
}
void timer(int &x)
{
	//for (long long i = 0; i < 100000 * x; i++);
	// Sleep(1000);
	x += 10;
}


void eraseSnake(const snake& S)
{
	if (S.isAlive == true)
	{
		for (int i = 0; i < S.size; i++)
		{
			gotoRowCol(S.ps[i].ri, S.ps[i].ci);
			SetClr(S.colour);
			cout << " ";
		}
	}
}
void moveSnake(const snake& S, int height, int width)
{
	if (S.isAlive == true)
	{
		for (int i = S.size - 1; i - 1 >= 0; i--)
		{
			S.ps[i] = S.ps[i - 1];
		}
		switch (S.direction)
		{
		case UP:
			S.ps[0].ri--;
			if (S.ps[0].ri == 0)
			{
				S.ps[0].ri = height - 1 - 1;
			}
			break;
		case DOWN:
			S.ps[0].ri++;
			if (S.ps[0].ri == height - 1)
			{
				S.ps[0].ri = 1;
			}
			break;
		case LEFT:
			S.ps[0].ci--;
			if (S.ps[0].ci == 0)
			{
				S.ps[0].ci = width - 1 - 1;
			}
			break;
		case RIGHT:
			S.ps[0].ci++;
			if (S.ps[0].ci == width - 1)
			{
				S.ps[0].ci = 1;
			}
			break;
		}
	}
}
void changeDirection(snake& S, char key)
{
	if (S.isAlive == true)
	{
		if (key == S.LEFTKEY)
			if (S.direction != RIGHT)
			{
				S.direction = LEFT;
			}
		if (key == S.RIGHTKEY)
			if (S.direction != LEFT)
			{
				S.direction = RIGHT;
			}
		if (key == S.UPKEY)
			if (S.direction != DOWN)
			{
				S.direction = UP;
			}
		if (key == S.DOWNKEY)
			if (S.direction != UP)
			{
				S.direction = DOWN;
			}
	}	
}
bool foodEaten(food& f, snake& S)
{
	if (S.ps[0].ri == f.fp.ri && S.ps[0].ci == f.fp.ci)
	{
		return true;
	}
	return false;
}
void growSnake(snake& S)
{
	if (S.isAlive == true)
	{
		position* newSnake = new position[S.size + 1];
		for (int i = 0; i < S.size; i++)
		{
			newSnake[i] = S.ps[i];
		}
		newSnake[S.size] = S.ps[S.size - 1];
		S.size += 1;
		delete S.ps;
		S.ps = newSnake;
		S.score += 10;
	}
}

void displayScores(snake S1, snake S2, snake S3, snake S4, int height, int width, int nop)
{
	SetClr(15);
	gotoRowCol(1, width+5);
	cout << "The Scores : ";
	for (int i = 1; i <= nop; i++)
	{
		gotoRowCol(0+i*2+1, width + 5);
		if (i == 1)
		cout << " " << S1.name << " : " << S1.score;
		else if(i == 2)
		cout << " " << S2.name << " : " << S2.score;
		else if(i == 3)
		cout << " " << S3.name << " : " << S3.score;
		else if(i == 4)
		cout << " " << S4.name << " : " << S4.score;
	}
}
bool isMarrGaya(snake& s1, stageCordinates sc, int height, int width)
{
	if (sc.current_stage == 1)
	{
		if ((((s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= 3 * height / 4 + 1 && s1.ps[0].ri < height - 1) && s1.ps[0].ci == width / 2))
		{
			return true;
		}
		return false;
	}
	if (sc.current_stage == 2)
	{
		if ((((s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= 3 * height / 4 + 1 && s1.ps[0].ri < height - 1) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= height / 4 + 1 && s1.ps[0].ri < height / 2) && s1.ps[0].ci == width / 4)
		{
			return true;
		}
		return false;
	}
	if (sc.current_stage == 3)
	{
		if ((((s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= 3 * height / 4 + 1 && s1.ps[0].ri < height - 1) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= height / 4 + 1 && s1.ps[0].ri < height / 2) && s1.ps[0].ci == width / 4 || (s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 4)
		{
			return true;
		}
		return false;
	}
	if (sc.current_stage == 4)
	{
		if ((((s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= 3 * height / 4 + 1 && s1.ps[0].ri < height - 1) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= height / 4 + 1 && s1.ps[0].ri < height / 2) && s1.ps[0].ci == width / 4 || (s1.ps[0].ri >= height / 2 + 1 && s1.ps[0].ri < height) && s1.ps[0].ci == width / 4 || (s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == 3 * width / 4)
		{
			return true;
		}
		return false;
	}
	if (sc.current_stage == 5)
	{
		if ((((s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= 3 * height / 4 + 1 && s1.ps[0].ri < height - 1) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= height / 4 + 1 && s1.ps[0].ri < height / 2) && s1.ps[0].ci == width / 4 || (s1.ps[0].ri >= height / 2 + 1 && s1.ps[0].ri < height) && s1.ps[0].ci == width / 4 || (s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == 3 * width / 4 || (s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2)
		{
			return true;
		}
		return false;
	}
}
bool isMarrGaya2(snake& s1,snake &s2, snake&s3, snake &s4, stageCordinates sc, int height, int width)
{
	if (sc.current_stage == 1)
	{
		if ((((s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= 3 * height / 4 + 1 && s1.ps[0].ri < height - 1) && s1.ps[0].ci == width / 2))
		{
			return true;
		}
		if ((((s2.ps[0].ri >= 0 && s2.ps[0].ri < height / 4) && s2.ps[0].ci == width / 2) || (s2.ps[0].ri >= 3 * height / 4 + 1 && s2.ps[0].ri < height - 1) && s2.ps[0].ci == width / 2))
		{
			return true;
		}
		if ((((s3.ps[0].ri >= 0 && s3.ps[0].ri < height / 4) && s3.ps[0].ci == width / 2) || (s3.ps[0].ri >= 3 * height / 4 + 1 && s3.ps[0].ri < height - 1) && s3.ps[0].ci == width / 2))
		{
			return true;
		}
		if ((((s4.ps[0].ri >= 0 && s4.ps[0].ri < height / 4) && s4.ps[0].ci == width / 2) || (s4.ps[0].ri >= 3 * height / 4 + 1 && s4.ps[0].ri < height - 1) && s4.ps[0].ci == width / 2))
		{
			return true;
		}
		return false;
	}
	else if (sc.current_stage == 2)
	{
		if ((((s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= 3 * height / 4 + 1 && s1.ps[0].ri < height - 1) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= height / 4 + 1 && s1.ps[0].ri < height / 2) && s1.ps[0].ci == width / 4)
		{
			return true;
		}
		if ((((s2.ps[0].ri >= 0 && s2.ps[0].ri < height / 4) && s2.ps[0].ci == width / 2) || (s2.ps[0].ri >= 3 * height / 4 + 1 && s2.ps[0].ri < height - 1) && s2.ps[0].ci == width / 2) || (s2.ps[0].ri >= height / 4 + 1 && s2.ps[0].ri < height / 2) && s2.ps[0].ci == width / 4)
		{
			return true;
		}
		if ((((s3.ps[0].ri >= 0 && s3.ps[0].ri < height / 4) && s3.ps[0].ci == width / 2) || (s3.ps[0].ri >= 3 * height / 4 + 1 && s3.ps[0].ri < height - 1) && s3.ps[0].ci == width / 2) || (s3.ps[0].ri >= height / 4 + 1 && s3.ps[0].ri < height / 2) && s3.ps[0].ci == width / 4)
		{
			return true;
		}
		if ((((s4.ps[0].ri >= 0 && s4.ps[0].ri < height / 4) && s4.ps[0].ci == width / 2) || (s4.ps[0].ri >= 3 * height / 4 + 1 && s4.ps[0].ri < height - 1) && s4.ps[0].ci == width / 2) || (s4.ps[0].ri >= height / 4 + 1 && s4.ps[0].ri < height / 2) && s4.ps[0].ci == width / 4)
		{
			return true;
		}
		return false;
	}
	else if (sc.current_stage == 3)
	{
		if ((((s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= 3 * height / 4 + 1 && s1.ps[0].ri < height - 1) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= height / 4 + 1 && s1.ps[0].ri < height / 2) && s1.ps[0].ci == width / 4 || (s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 4)
		{
			return true;
		}
		if ((((s2.ps[0].ri >= 0 && s2.ps[0].ri < height / 4) && s2.ps[0].ci == width / 2) || (s2.ps[0].ri >= 3 * height / 4 + 1 && s2.ps[0].ri < height - 1) && s2.ps[0].ci == width / 2) || (s2.ps[0].ri >= height / 4 + 1 && s2.ps[0].ri < height / 2) && s2.ps[0].ci == width / 4 || (s2.ps[0].ri >= 0 && s2.ps[0].ri < height / 4) && s2.ps[0].ci == width / 4)
		{
			return true;
		}
		if ((((s3.ps[0].ri >= 0 && s3.ps[0].ri < height / 4) && s3.ps[0].ci == width / 2) || (s3.ps[0].ri >= 3 * height / 4 + 1 && s3.ps[0].ri < height - 1) && s3.ps[0].ci == width / 2) || (s3.ps[0].ri >= height / 4 + 1 && s3.ps[0].ri < height / 2) && s3.ps[0].ci == width / 4 || (s3.ps[0].ri >= 0 && s3.ps[0].ri < height / 4) && s3.ps[0].ci == width / 4)
		{
			return true;
		}
		if ((((s4.ps[0].ri >= 0 && s4.ps[0].ri < height / 4) && s4.ps[0].ci == width / 2) || (s4.ps[0].ri >= 3 * height / 4 + 1 && s4.ps[0].ri < height - 1) && s4.ps[0].ci == width / 2) || (s4.ps[0].ri >= height / 4 + 1 && s4.ps[0].ri < height / 2) && s4.ps[0].ci == width / 4 || (s4.ps[0].ri >= 0 && s4.ps[0].ri < height / 4) && s4.ps[0].ci == width / 4)
		{
			return true;
		}

		return false;
	}
	else if (sc.current_stage == 4)
	{
		if ((((s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= 3 * height / 4 + 1 && s1.ps[0].ri < height - 1) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= height / 4 + 1 && s1.ps[0].ri < height / 2) && s1.ps[0].ci == width / 4 || (s1.ps[0].ri >= height / 2 + 1 && s1.ps[0].ri < height) && s1.ps[0].ci == width / 4 || (s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == 3 * width / 4)
		{
			return true;
		}
		if ((((s2.ps[0].ri >= 0 && s2.ps[0].ri < height / 4) && s2.ps[0].ci == width / 2) || (s2.ps[0].ri >= 3 * height / 4 + 1 && s2.ps[0].ri < height - 1) && s2.ps[0].ci == width / 2) || (s2.ps[0].ri >= height / 4 + 1 && s2.ps[0].ri < height / 2) && s2.ps[0].ci == width / 4 || (s2.ps[0].ri >= height / 2 + 1 && s2.ps[0].ri < height) && s2.ps[0].ci == width / 4 || (s2.ps[0].ri >= 0 && s2.ps[0].ri < height / 4) && s2.ps[0].ci == 3 * width / 4)
		{
			return true;
		}
		if ((((s3.ps[0].ri >= 0 && s3.ps[0].ri < height / 4) && s3.ps[0].ci == width / 2) || (s3.ps[0].ri >= 3 * height / 4 + 1 && s3.ps[0].ri < height - 1) && s3.ps[0].ci == width / 2) || (s3.ps[0].ri >= height / 4 + 1 && s3.ps[0].ri < height / 2) && s3.ps[0].ci == width / 4 || (s3.ps[0].ri >= height / 2 + 1 && s3.ps[0].ri < height) && s3.ps[0].ci == width / 4 || (s3.ps[0].ri >= 0 && s3.ps[0].ri < height / 4) && s3.ps[0].ci == 3 * width / 4)
		{
			return true;
		}
		if ((((s4.ps[0].ri >= 0 && s4.ps[0].ri < height / 4) && s4.ps[0].ci == width / 2) || (s4.ps[0].ri >= 3 * height / 4 + 1 && s4.ps[0].ri < height - 1) && s4.ps[0].ci == width / 2) || (s4.ps[0].ri >= height / 4 + 1 && s4.ps[0].ri < height / 2) && s4.ps[0].ci == width / 4 || (s4.ps[0].ri >= height / 2 + 1 && s4.ps[0].ri < height) && s4.ps[0].ci == width / 4 || (s4.ps[0].ri >= 0 && s4.ps[0].ri < height / 4) && s4.ps[0].ci == 3 * width / 4)
		{
			return true;
		}

		return false;
	}
	else if (sc.current_stage == 5)
	{
		if ((((s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= 3 * height / 4 + 1 && s1.ps[0].ri < height - 1) && s1.ps[0].ci == width / 2) || (s1.ps[0].ri >= height / 4 + 1 && s1.ps[0].ri < height / 2) && s1.ps[0].ci == width / 4 || (s1.ps[0].ri >= height / 2 + 1 && s1.ps[0].ri < height) && s1.ps[0].ci == width / 4 || (s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == 3 * width / 4 || (s1.ps[0].ri >= 0 && s1.ps[0].ri < height / 4) && s1.ps[0].ci == width / 2)
		{
			return true;
		}
		if ((((s2.ps[0].ri >= 0 && s2.ps[0].ri < height / 4) && s2.ps[0].ci == width / 2) || (s2.ps[0].ri >= 3 * height / 4 + 1 && s2.ps[0].ri < height - 1) && s2.ps[0].ci == width / 2) || (s2.ps[0].ri >= height / 4 + 1 && s2.ps[0].ri < height / 2) && s2.ps[0].ci == width / 4 || (s2.ps[0].ri >= height / 2 + 1 && s2.ps[0].ri < height) && s2.ps[0].ci == width / 4 || (s2.ps[0].ri >= 0 && s2.ps[0].ri < height / 4) && s2.ps[0].ci == 3 * width / 4 || (s2.ps[0].ri >= 0 && s2.ps[0].ri < height / 4) && s2.ps[0].ci == width / 2)
		{
			return true;
		}
		if ((((s3.ps[0].ri >= 0 && s3.ps[0].ri < height / 4) && s3.ps[0].ci == width / 2) || (s3.ps[0].ri >= 3 * height / 4 + 1 && s3.ps[0].ri < height - 1) && s3.ps[0].ci == width / 2) || (s3.ps[0].ri >= height / 4 + 1 && s3.ps[0].ri < height / 2) && s3.ps[0].ci == width / 4 || (s3.ps[0].ri >= height / 2 + 1 && s3.ps[0].ri < height) && s3.ps[0].ci == width / 4 || (s3.ps[0].ri >= 0 && s3.ps[0].ri < height / 4) && s3.ps[0].ci == 3 * width / 4 || (s3.ps[0].ri >= 0 && s3.ps[0].ri < height / 4) && s3.ps[0].ci == width / 2)
		{
			return true;
		}
		if ((((s4.ps[0].ri >= 0 && s4.ps[0].ri < height / 4) && s4.ps[0].ci == width / 2) || (s4.ps[0].ri >= 3 * height / 4 + 1 && s4.ps[0].ri < height - 1) && s4.ps[0].ci == width / 2) || (s4.ps[0].ri >= height / 4 + 1 && s4.ps[0].ri < height / 2) && s4.ps[0].ci == width / 4 || (s4.ps[0].ri >= height / 2 + 1 && s4.ps[0].ri < height) && s4.ps[0].ci == width / 4 || (s4.ps[0].ri >= 0 && s4.ps[0].ri < height / 4) && s4.ps[0].ci == 3 * width / 4 || (s4.ps[0].ri >= 0 && s4.ps[0].ri < height / 4) && s4.ps[0].ci == width / 2)
		{
			return true;
		}

		return false;
	}
}
bool isDie(snake s1, int height, int width, stageCordinates sc)
{
	if (s1.score >= 40)
	{
		if (isMarrGaya(s1, sc, height, width) == true)
		{
			return true;
		}
	}
	if (s1.score > 100)
	{
		if (s1.ps[0].ri == height - 1-1 || s1.ps[0].ci == width - 1-1 || s1.ps[0].ri == 1 || s1.ps[0].ci == 1)
		{
			return true;
		}
		for (int i = 0; i < s1.size / 2; i++)
		{
			for (int j = s1.size - 1; j >= s1.size / 2; j--)
			{
				if (i != j)
				{
					if (s1.ps[i].ri == s1.ps[j].ri && s1.ps[i].ci == s1.ps[j].ci)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	else
	{
		for (int i = 0; i < s1.size / 2; i++)
		{
			for (int j = s1.size - 1; j >= s1.size / 2; j--)
			{
				if (i != j)
				{
					if (s1.ps[i].ri == s1.ps[j].ri && s1.ps[i].ci == s1.ps[j].ci)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	return false;
}
bool isDie2(snake s1, snake s2, snake s3, snake s4, int height, int width, stageCordinates sc)
{
	if (s1.score >= 40)
	{
		if (isMarrGaya2(s1,s2,s3,s4, sc, height, width) == true)
		{
			return true;
		}
	}
	if (s1.score > 100)
	{
		if (s1.ps[0].ri == height - 1 - 1 || s1.ps[0].ci == width - 1 - 1 || s1.ps[0].ri == 1 || s1.ps[0].ci == 1)
		{
			return true;
		}
		for (int i = 0; i < s1.size / 2; i++)
		{
			for (int j = s1.size - 1; j >= s1.size / 2; j--)
			{
				if (i != j)
				{
					if (s1.ps[i].ri == s1.ps[j].ri && s1.ps[i].ci == s1.ps[j].ci)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	else
	{
		for (int i = 0; i < s1.size / 2; i++)
		{
			for (int j = s1.size - 1; j >= s1.size / 2; j--)
			{
				if (i != j)
				{
					if (s1.ps[i].ri == s1.ps[j].ri && s1.ps[i].ci == s1.ps[j].ci)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	return false;
}
void checkDies1(snake& S1, int height, int width, stageCordinates sc)
{
	if (isDie(S1, height, width,sc) == true)
	{
		S1.isAlive = false;
	}
}
void checkDies2(snake& S1, snake& S2, snake& S3, snake& S4, int height, int width, stageCordinates sc)
{
	if (isDie2(S1,S2,S3,S4, height, width, sc) == true)
	{
		S1.isAlive = false;
	}
}
void checkDies(snake& S1, snake& S2, snake& S3, snake& S4, int height, int width, stageCordinates sc)
{
	if (isDie(S1,height, width,sc) == true)
	{
		S1.isAlive = false;
	}
	if (isDie(S2, height, width,sc) == true)
	{
		S2.isAlive = false;
	}
	if (isDie(S3, height, width,sc) == true)
	{
		S3.isAlive = false;
	}
	if (isDie(S4, height, width,sc) == true)
	{
		S4.isAlive = false;
	}
}

void stageupdate(snake& s1, snake& s2, snake& s3, snake& s4, int &current_stage, int nop, bool &stager)
{
	if (nop == 1)
	{
		if (s1.score == 40 || s1.score == 60 || s1.score == 70 || s1.score == 90 || s1.score == 110)
		{
			current_stage += 1;
			stager = true;
		}
	}
	else if (nop == 2)
	{
		if (s1.score == 40 || s1.score == 60 || s1.score == 70 || s1.score == 90 || s1.score == 110 || s2.score == 40 || s2.score == 60 || s2.score == 70 || s2.score == 90 || s2.score == 110)
		{
			current_stage += 1;
			stager = true;
		}
	}
	else if (nop == 3)
	{
		if (s1.score == 40 || s1.score == 60 || s1.score == 70 || s1.score == 90 || s1.score == 110 || s2.score == 40 || s2.score == 60 || s2.score == 70 || s2.score == 90 || s2.score == 110 || s3.score == 40 || s3.score == 60 || s3.score == 70 || s3.score == 90 || s3.score == 110)
		{
			current_stage += 1;
			stager = true;
		}
	}
	else if (nop == 4)
	{
		if (s1.score == 40 || s1.score == 60 || s1.score == 70 || s1.score == 90 || s1.score == 110 || s2.score == 40 || s2.score == 60 || s2.score == 70 || s2.score == 90 || s2.score == 110 || s3.score == 40 || s3.score == 60 || s3.score == 70 || s3.score == 90 || s3.score == 110 || s4.score == 40 || s4.score == 60 || s4.score == 70 || s4.score == 90 || s4.score == 110)
		{
			current_stage += 1;
			stager = true;
		}
	}
}
void printStages(int height, int width, int stage)
{
	SetClr(4);

	if (stage == 1)
	{
		for (int ri = 0; ri < height; ri++)
		{
			for (int ci = 0; ci < width; ci++)
			{
				if (ci == width / 2 && (ri > 0 && ri < height / 4) || ci == width / 2 && (ri > 3 * height / 4 && ri < height - 1))
				{
					gotoRowCol(ri, ci);
					cout << char(-37);
				}
			}
		}
	}
	else if (stage == 2)
	{
		for (int ri = 0; ri < height; ri++)
		{
			for (int ci = 0; ci < width; ci++)
			{
				if (ci == width / 2 && (ri > 0 && ri < height / 4) || ci == width / 2 && (ri > 3 * height / 4 && ri < height - 1) || ci == width / 4 && (ri > height/4 && ri < height / 2))
				{
					gotoRowCol(ri, ci);
					cout << char(-37);
				}
			}
		}
	}
	else if (stage == 3)
	{
		for (int ri = 0; ri < height; ri++)
		{
			for (int ci = 0; ci < width; ci++)
			{
				if (ci == width / 2 && (ri > 0 && ri < height / 4) || ci == width / 2 && (ri > 3 * height / 4 && ri < height - 1) || ci == width / 4 && (ri > height / 4 && ri < height / 2) || ci == width / 4 && (ri > 0 && ri < height / 4))
				{
					gotoRowCol(ri, ci);
					cout << char(-37);
				}
			}
		}
	}
	else if (stage == 4)
	{
		for (int ri = 0; ri < height; ri++)
		{
			for (int ci = 0; ci < width; ci++)
			{
				if (ci == width / 2 && (ri > 0 && ri < height / 4) || ci == width / 2 && (ri > 3 * height / 4 && ri < height - 1) || ci == width / 8 && (ri > height / 4 && ri < height / 2) || ci == width / 4 && (ri > 0 && ri < 3* height / 4) || ci == 3* width / 4 && (ri > height/2 && ri < height - 1))
				{
					gotoRowCol(ri, ci);
					cout << char(-37);
				}
			}
		}
	}
	else if (stage == 5)
	{
		for (int ri = 0; ri < height; ri++)
		{
			for (int ci = 0; ci < width; ci++)
			{
				if (ci == width / 2 && (ri > 0 && ri < height / 4) || ci == width / 2 && (ri > 3 * height / 4 && ri < height - 1) || ci == width / 8 && (ri > height / 4 && ri < height / 2) || ci == width / 4 && (ri > 0 && ri < 3 * height / 4) || ci == 3 * width / 4 && (ri > height / 2 && ri < height - 1) || ri == 4 * width / 10 && (ci > 3*height/10 && ci < 7 * height / 10))
				{
					gotoRowCol(ri, ci);
					cout << char(-37);
				}
			}
		}
	}

}
void printBoundary(int height, int width)
{
	for (int ri = 0; ri < height; ri++)
	{
		for (int ci = 0; ci < width; ci++)
		{
			if (ri == 0 || ci == 0 || ri == height - 1 || ci == width - 1)
			{
				gotoRowCol(ri, ci);
				SetClr(4);
				cout << char(-37);
			}
		}
	}
	SetClr(15);
}


int main85()
{
	srand(time(0));
	int height = 80, width = 80;
	snake S,s1,s2,s3;
	stageCordinates sc;
	food f;
	printBoundary(height, width);
	init(S,f, height, width, sc);
	displayFood(f);
	char ch;
	int nop = 1;
	bool stager = false;
	while (true)
	{
		if (_kbhit())
		{
			PlaySound(TEXT("move"), NULL, SND_ASYNC);
			ch = _getch();
			if (ch == -32)
			{
				ch = _getch();
				changeDirection(S, ch);

			}
		}
		if (S.isAlive == true)
		{
			displaySnake(S);
		}
		Sleep(100);
		if (S.isAlive == true)
		{
			eraseSnake(S);
			moveSnake(S, height, width);
		}
		if (foodEaten(f, S) == true)
		{
			PlaySound(TEXT("eat"), NULL, SND_ASYNC);
			generateFood(f, height, width, S);
			growSnake(S);
			displayFood(f);
			stageupdate(S, s1, s2, s3,sc.current_stage, nop, stager);
		}
		checkDies1(S, height, width,sc);
		gotoRowCol(0, 85);
		SetClr(15);
		cout << "The score is : " << S.score;
		if (S.score > 20 && stager == true)
		{
			stager = false;
			printStages(height, width, sc.current_stage);
		}
		if (S.isAlive == false)
		{
			gotoRowCol(0, 103);
			cout << "Rip :(";
		}
	}
	return 0;
}
int main()
{
	PlaySound(TEXT("intro"), NULL, SND_ASYNC);
	srand(time(0));
	int height = 60, width = 80, nop =0;
	snake S1,S2,S3,S4;
	stageCordinates sc;
	food f;
	bool stager = false;
	bool gayab = false;
	init2(S1,S2,S3,S4, f, height, width, nop, sc);
	printBoundary(height, width);
	displayFood(f);
	char ch;
	int time=0;
	if (nop == 1)
	{
		while (true)
		{
			if (_kbhit())
			{
				//PlaySound(TEXT("move"), NULL, SND_SYNC);
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					changeDirection(S1, ch);

				}
			}
			displaySnake(S1);

			Sleep(100);
			eraseSnake(S1);

			moveSnake(S1, height, width);

			displayScores(S1, S2, S3, S4, height, width, nop);

			if (foodEaten(f, S1) == true || gayab == true)
			{
				//PlaySound(TEXT("eat"), NULL, SND_ASYNC);
				generateFood2(f, height, width, S1, S2, S3, S4);
				growSnake(S1);
				displayFood(f);
				stageupdate(S1, S2, S3, S4, sc.current_stage, nop, stager);
				gayab = false;
			}
			checkDies2(S1, S2, S3, S4,height,width,sc);
			if (stager == true)
			{
				stager = false;
				printStages(height, width, sc.current_stage);
			}
			//timer(time);
			time += 10;
			foodTimer2(time, f, height, width, S1, S2, S3, S4, gayab);

		}
	}
	if (nop == 2)
	{
		while (true)
		{
			if (_kbhit())
			{
			//	PlaySound(TEXT("move"), NULL, SND_ASYNC);
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					changeDirection(S1, ch);

				}
				if (ch == 119 || ch == 97 || ch == 115 || ch == 100)
				{
					changeDirection(S2, ch);
				}
				
			}
			displaySnake(S1);
			displaySnake(S2);

			Sleep(100);
			eraseSnake(S1);
			eraseSnake(S2);

			moveSnake(S1, height, width);
			moveSnake(S2, height, width);
			
			displayScores(S1, S2, S3, S4, height, width, nop);

			if (foodEaten(f, S1) == true)
			{
			//	PlaySound(TEXT("eat"), NULL, SND_ASYNC);
				generateFood2(f, height, width, S1, S2, S3, S4);
				growSnake(S1);
				displayFood(f);
				stageupdate(S1, S2, S3, S4, sc.current_stage, nop, stager);
			}
			else if (foodEaten(f, S2) == true)
			{
				//PlaySound(TEXT("eat"), NULL, SND_ASYNC);
				generateFood2(f, height, width, S1, S2, S3, S4);
				growSnake(S2);
				displayFood(f);
				stageupdate(S1, S2, S3, S4, sc.current_stage, nop, stager);
			}
			checkDies2(S1, S2, S3, S4, height, width,sc);
			if (stager == true)
			{
				stager = false;
				printStages(height, width, sc.current_stage);
			}
		}
	}
	if (nop == 3)
	{
		while (true)
		{
			if (_kbhit())
			{
			//	PlaySound(TEXT("move"), NULL, SND_ASYNC);
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					changeDirection(S1, ch);

				}
				if (ch == 119 || ch == 97 || ch == 115 || ch == 100)
				{
					changeDirection(S2, ch);
				}
				if (ch == 56 || ch == 52 || ch == 53 || ch == 54)
				{
					changeDirection(S3, ch);
				}
			}

			displaySnake(S1);
			displaySnake(S2);
			displaySnake(S3);

			Sleep(100);
			eraseSnake(S1);
			eraseSnake(S2);
			eraseSnake(S3);

			moveSnake(S1, height, width);
			moveSnake(S2, height, width);
			moveSnake(S3, height, width);

			displayScores(S1, S2, S3, S4, height, width, nop);

			if (foodEaten(f, S1) == true)
			{
				//PlaySound(TEXT("eat"), NULL, SND_ASYNC);
				generateFood2(f, height, width, S1, S2, S3, S4);
				growSnake(S1);
				displayFood(f);
				stageupdate(S1, S2, S3, S4, sc.current_stage, nop, stager);
			}
			else if (foodEaten(f, S2) == true)
			{
				//PlaySound(TEXT("eat"), NULL, SND_ASYNC);
				generateFood2(f, height, width, S1, S2, S3, S4);
				growSnake(S2);
				displayFood(f);
				stageupdate(S1, S2, S3, S4, sc.current_stage, nop, stager);
			}
			else if (foodEaten(f, S3) == true)
			{
				//PlaySound(TEXT("eat"), NULL, SND_ASYNC);
				generateFood2(f, height, width, S1, S2, S3, S4);
				growSnake(S3);
				displayFood(f);
				stageupdate(S1, S2, S3, S4, sc.current_stage, nop, stager);
			}
			checkDies2(S1, S2, S3, S4, height, width,sc);
			if (stager == true)
			{
				stager = false;
				printStages(height, width, sc.current_stage);
			}
		}
	}
	if (nop == 4)
	{
		while (true)
		{
			if (_kbhit())
			{
				//PlaySound(TEXT("move"), NULL, SND_ASYNC);
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					changeDirection(S1, ch);

				}
				if (ch == 119 || ch == 97 || ch == 115 || ch == 100)
				{
					changeDirection(S2, ch);
				}
				if (ch == 56 || ch == 52 || ch == 53 || ch == 54)
				{
					changeDirection(S3, ch);
				}
				if (ch == 105 || ch == 106 || ch == 107 || ch == 108)
				{
					changeDirection(S4, ch);
				}
			}

			displaySnake(S1);
			displaySnake(S2);
			displaySnake(S3);
			displaySnake(S4);

			Sleep(100);
			eraseSnake(S1);
			eraseSnake(S2);
			eraseSnake(S3);
			eraseSnake(S4);

			moveSnake(S1, height, width);
			moveSnake(S2, height, width);
			moveSnake(S3, height, width);
			moveSnake(S4, height, width);

			displayScores(S1, S2, S3, S4, height, width, nop);

			if (foodEaten(f, S1) == true)
			{
				//PlaySound(TEXT("eat"), NULL, SND_ASYNC);
				generateFood2(f, height, width, S1, S2, S3, S4);
				growSnake(S1);
				displayFood(f);
				stageupdate(S1, S2, S3, S4, sc.current_stage, nop, stager);
			}
			else if (foodEaten(f, S2) == true)
			{
				//PlaySound(TEXT("eat"), NULL, SND_ASYNC);
				generateFood2(f, height, width, S1, S2, S3, S4);
				growSnake(S2);
				displayFood(f);
				stageupdate(S1, S2, S3, S4, sc.current_stage, nop, stager);
			}
			else if (foodEaten(f, S3) == true)
			{
				//PlaySound(TEXT("eat"), NULL, SND_ASYNC);
				generateFood2(f, height, width, S1, S2, S3, S4);
				growSnake(S3);
				displayFood(f);
				stageupdate(S1, S2, S3, S4, sc.current_stage, nop, stager);
			}
			else if (foodEaten(f, S4) == true)
			{
				//PlaySound(TEXT("eat"), NULL, SND_ASYNC);
				generateFood2(f, height, width, S1, S2, S3, S4);
				growSnake(S4);
				displayFood(f);
				stageupdate(S1, S2, S3, S4, sc.current_stage, nop, stager);
			}
			checkDies2(S1, S2, S3, S4, height, width,sc);
			if (stager == true)
			{
				stager = false;
				printStages(height, width, sc.current_stage);
			}

		}
	}

	return 0;
}

