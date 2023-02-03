#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <conio.h>
#include "mylib.h"

using namespace std;

bool lose = false;
int score = 0;
int snakeSize = 4;

//1=UP; 2=RIGHT; 3=DOWN; 4=LEFT
int direction = 2;

struct snake {
	int x, y;
};

struct food {
	int x, y;
	bool exist = false;
};

vector<snake> Snake;
snake beforeStep;
food Food;

void noteGame() {
	cout << "help move: " << endl;
	cout << "\tw: UP" << endl;
	cout << "\td: RIGHT" << endl;
	cout << "\ts: DOWN" << endl;
	cout << "\ta: LEFT" << endl;

	gotoXY(50, 15);
	cout << "press P to play game";
}

void drawWall() {
	for (int x = 10; x <= 110; x++) {
		gotoXY(x, 1);
		cout << char(176);
		gotoXY(x, 29);
		cout << char(176);
	}

	for (int y = 1; y <= 29; y++) {
		gotoXY(10, y);
		cout << char(176);
		gotoXY(110, y);
		cout << char(176);
	}
}

void creatSnake() {
	for (int i = 0; i < snakeSize; i++) {
		snake temp;
		temp.x = 11 + i;
		temp.y = 15;
		Snake.push_back(temp);
	}
}

void drawSnake() {
	for (snake i : Snake)
	{
		gotoXY(i.x, i.y);
		SetColor(2);
		cout << "o";
	}
}

void increaseSnakcSize(snake nextStep) {
	snakeSize++;
	Snake.push_back(nextStep);
}

void addFood() {
	if (!Food.exist) {
		Food.x = 11 + (rand() % (109 - 11 + 1));
		Food.y = 2 + (rand() % (28 - 2 + 1));
		gotoXY(Food.x, Food.y);
		cout << char(1);
		Food.exist = true;
	}
}

bool suicide() {
	int x = Snake[snakeSize - 1].x;
	int y = Snake[snakeSize - 1].y;

	for (int i = 0; i < snakeSize - 1; i++) {
		if ((x == Snake[i].x) && (y == Snake[i].y)) {
			return true;
			break;
		}
		else
			return false;
	}
}

int checkAddress(snake nextStep) {
	int x = nextStep.x;
	int y = nextStep.y;

	if ((x == 10) || (x == 110) || (y == 1) || (y == 29))
		return 0;
	else if (suicide())
		return 0;
	else if ((x == Food.x) && (y == Food.y))
		return 1;
	else 
		return 2;
}

void check(snake nextStep) {
	int check = checkAddress(nextStep);

	if (check == 0)
		lose = true;
	else if (check == 1) {
		Food.exist = false;
		score += 10;
		increaseSnakcSize(nextStep);
	}
		
}

void moveUp() {
	snake nextStep;
	beforeStep = Snake[0];

	nextStep.x = Snake[snakeSize - 1].x;
	nextStep.y = Snake[snakeSize - 1].y - 1;
	for (int i = 0; i < snakeSize - 1; i++) {
		Snake[i] = Snake[i + 1];
	}
	Snake[snakeSize - 1] = nextStep;

	check(nextStep);
}

void moveRight() {
	snake nextStep;
	beforeStep = Snake[0];

	nextStep.x = Snake[snakeSize - 1].x + 1;
	nextStep.y = Snake[snakeSize - 1].y;
	for (int i = 0; i < snakeSize - 1; i++) {
		Snake[i] = Snake[i + 1];
	}
	Snake[snakeSize - 1] = nextStep;

	check(nextStep);
}

void moveDown() {
	snake nextStep;
	beforeStep = Snake[0];

	nextStep.x = Snake[snakeSize - 1].x;
	nextStep.y = Snake[snakeSize - 1].y + 1;
	for (int i = 0; i < snakeSize - 1; i++) {
		Snake[i] = Snake[i + 1];
	}
	Snake[snakeSize - 1] = nextStep;

	check(nextStep);
}

void moveLeft() {
	snake nextStep;
	beforeStep = Snake[0];

	nextStep.x = Snake[snakeSize - 1].x - 1;
	nextStep.y = Snake[snakeSize - 1].y;
	for (int i = 0; i < snakeSize - 1; i++) {
		Snake[i] = Snake[i + 1];
	}
	Snake[snakeSize - 1] = nextStep;

	check(nextStep);
}

void updateDisplay() {
	gotoXY(0, 0);
	cout << "score: " << score;
	gotoXY(beforeStep.x, beforeStep.y);
	cout << " ";
	addFood();
	drawSnake();
}

void gameOver() {
	gotoXY(40, 13); cout << "========= Game Over ==========";
	gotoXY(40, 14); cout << "          score: " << score;
	gotoXY(40, 15); cout << "||                          ||";
	gotoXY(40, 16); cout << "||   Press P to exit game   ||";
	gotoXY(40, 17); cout << "==============================";

	while (true)
	{
		if (_kbhit()) {
			char p = _getch();
			if (p = 'p') {
				system("cls");
				exit(0);
			}
		}
	}
}

void run() {
	while (true)
	{
		//Sleep(250);
		if (_kbhit()) 
		{
			char p = _getch();
			if (direction == 1) {
				switch (p)
				{
				case 'a':
					direction = 4;
					break;
				case 'd':
					direction = 2;
					break;
				}
			}
			else if (direction == 2) {
				switch (p)
				{
				case 'w':
					direction = 1;
					break;
				case 's':
					direction = 3;
					break;
				}
			}
			else if (direction == 3) {
				switch (p)
				{
				case 'a':
					direction = 4;
					break;
				case 'd':
					direction = 2;
					break;
				}
			}
			else if (direction == 4) {
				switch (p)
				{
				case 'w':
					direction = 1;
					break;
				case 's':
					direction = 3;
					break;
				}
			}
		}

		if (direction == 1) {
			Sleep(200);
			moveUp();
		}
		else if (direction == 2) {
			Sleep(100);
			moveRight();
		}
		else if (direction == 3) {
			Sleep(200);
			moveDown();
		}
		else if (direction == 4) {
			Sleep(100);
			moveLeft();
		}
		updateDisplay();

		if (lose) {
			gameOver();
		}
	}
}

void Start() {
	gotoXY(0, 0);
	cout << "score: " << score;
	drawWall();
	creatSnake();
	drawSnake();
	addFood();
	run();
}
void gamePlay() {
	ShowCur(0);
	noteGame();

	while (true)
	{
		if (_kbhit()) {
			char p = _getch();
			if (p == 'p') {
				system("cls");
				break;
			}
		}
	}

	Start();
}