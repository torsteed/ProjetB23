// ConsoleApplication1.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

void Gotoxy(int column, int row)
{
	COORD c;

	c.X = column;
	c.Y = row;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main()
{
	int x, y;

	x = 20;
	y = 10;

	Gotoxy(x, y);

	printf("C program to change cursor position.");

	_getch();
	return 0;
}

