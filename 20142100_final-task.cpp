#include <iostream>
#include <iomanip>
#include<vector>
#include<string>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <numeric>

using namespace std;

int board[4][4];

typedef struct {
	int x, y;
}Vec2;

vector<int> turn;

Vec2 GetPos() {
	Vec2 blankPos = { -1, -1 };
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			if (16 == board[y][x])
				blankPos = { x ,y };

	return blankPos;
}

int GetAngle(int X, int Y) {
	if (board[Y - 1][X] == 16)
		return 0;
	else if (board[Y][X + 1] == 16)
		return 1;
	else if (board[Y + 1][X] == 16)
		return 2;
	else if (board[Y][X - 1] == 16)
		return 3;
	else return -1;
}

void MoveBlank(int X, int Y) {
	if (X < 0 || X >= 4 || Y < 0 || Y >= 4) {
		return;
	}
	else if (GetAngle(X, Y) == 0) {
		board[Y - 1][X] = board[Y][X];
		board[Y][X] = 16;
	}
	else if (GetAngle(X, Y) == 1) {
		board[Y][X + 1] = board[Y][X];
		board[Y][X] = 16;
	}
	else if (GetAngle(X, Y) == 2) {
		board[Y + 1][X] = board[Y][X];
		board[Y][X] = 16;
	}
	else if (GetAngle(X, Y) == 3) {
		board[Y][X - 1] = board[Y][X];
		board[Y][X] = 16;
	}
	else if (GetAngle(X, Y) == -1) {
		return;
	}
}

random_device rd;
mt19937 gen(rd());

int random(int low, int high)
{
	uniform_int_distribution<> dist(low, high);
	return dist(gen);
}

int main() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			board[y][x] = y * 4 + x + 1;
		}
	}

	for (int i = 0; i < 1000; ++i) {
		MoveBlank(random(0, 3), random(0, 3));
	}
	
	cout << endl;

	/*while (1)*/
	for (int i = 1; i <= 3000; ++i){
		system("cls");
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				if (board[y][x] == 16)
					printf("   ");
				else
					printf("%3d", board[y][x]);
			}
			cout << endl;
		}
		cout << endl;

		turn.push_back(1);
		cout << "turn " << accumulate(turn.begin(), turn.end(), -1) << endl;

		Vec2 blankPos = GetPos();
		Vec2 movePos = blankPos;
		switch (_getch()) {
		case 'w':
			++(movePos.y);
			break;
		case 's':
			--(movePos.y);
			break;
		case 'a':
			++(movePos.x);
			break;
		case 'd':
			--(movePos.x);
			break;
		}
		MoveBlank(movePos.x, movePos.y);
	}
	_getch();
	return 0;
}

			
