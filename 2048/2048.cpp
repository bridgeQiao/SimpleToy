/*
Copyright (c) [2019] [Qiao Wang]
[2048] is licensed under the Mulan PSL v1.
You can use this software according to the terms and conditions of the Mulan PSL v1.
You may obtain a copy of Mulan PSL v1 at:
	http://license.coscl.org.cn/MulanPSL
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
PURPOSE.
See the Mulan PSL v1 for more details.
*/

#include <iostream>
#include <random>

using namespace std;

// -------------Global variable
// define CheckerBoard and direction, use wasd control
const int LEN = 4;
int board[LEN][LEN] = { 0 };
char direction = NULL;
// generate random number
default_random_engine rng;
uniform_int_distribution<> dist(0, LEN - 1);
using Range = uniform_int_distribution<>::param_type;

// ------------Function for 2048
bool isover();
void show();
void emege(char direction);

int main()
{
	board[LEN - 1][0] = 4;
	while (!isover())
	{
		show();
		cin >> direction;
		emege(direction);
	}
	return 0;
}

bool isover()
{
	for (int i = 0; i < LEN; ++i)
		for (int j = 0; j < LEN; ++j)
			if (board[i][j] == 0)
				return false;
	return true;
}

void emege(char direction)
{
	// 1. random generate 2 or 4 at ZERO position iff board[0] all is zero
	// 2. mege the same number

	int do_mege = false;
	int randi = rng() % 10;
	if (randi < 2)
		randi = 4;
	else
		randi = 2;
	switch (direction)
	{
	case 's':
		for (int i = 0; i < LEN; ++i)
		{
			if (board[0][i] != 0) {
				do_mege = true;
				break;
			}
		}
		// generate random number
		if (do_mege == false)
		{
			board[0][dist(rng)] = randi;
			break;
		}

		// do mege
		for (int x = 0; x < LEN; ++x)
			for (int y = 0; y < LEN - 1; ++y)
				if (board[y][x] == 0)
					continue;
				else if (board[y + 1][x] == 0)
				{
					board[y + 1][x] = move(board[y][x]);
					board[y][x] = 0;
				}
				else if (board[y][x] == board[y + 1][x])
				{
					board[y][x] = 0;
					board[y + 1][x] *= 2;
				}
		break;
	case 'd':
		for (int i = 0; i < LEN; ++i)
		{
			if (board[i][0] != 0) {
				do_mege = true;
				break;
			}
		}
		// generate random number
		if (do_mege == false)
		{
			board[dist(rng)][0] = randi;
			break;
		}

		// do mege
		for (int y = 0; y < LEN; ++y)
			for (int x = 0; x < LEN - 1; ++x)
				if (board[y][x] == 0)
					continue;
				else if (board[y][x + 1] == 0)
				{
					board[y][x + 1] = move(board[y][x]);
					board[y][x] = 0;
				}
				else if (board[y][x] == board[y][x + 1])
				{
					board[y][x] = 0;
					board[y][x + 1] *= 2;
				}
		break;
	case 'w':
		for (int i = 0; i < LEN; ++i)
		{
			if (board[LEN - 1][i] != 0) {
				do_mege = true;
				break;
			}
		}
		// generate random number
		if (do_mege == false)
		{
			board[LEN - 1][dist(rng)] = randi;
			break;
		}

		// do mege
		for (int x = 0; x < LEN; ++x)
			for (int y = LEN - 1; y > 0; --y)
				if (board[y][x] == 0)
					continue;
				else if (board[y - 1][x] == 0)
				{
					board[y - 1][x] = move(board[y][x]);
					board[y][x] = 0;
				}
				else if (board[y][x] == board[y - 1][x])
				{
					board[y][x] = 0;
					board[y - 1][x] *= 2;
				}
		break;
	case 'a':
		for (int i = 0; i < LEN; ++i)
		{
			if (board[i][LEN - 1] != 0) {
				do_mege = true;
				break;
			}
		}
		// generate random number
		if (do_mege == false)
		{
			board[dist(rng)][LEN - 1] = randi;
			break;
		}

		// do mege
		for (int y = 0; y < LEN; ++y)
			for (int x = LEN - 1; x > 0; --x)
				if (board[y][x] == 0)
					continue;
				else if (board[y][x - 1] == 0)
				{
					board[y][x - 1] = move(board[y][x]);
					board[y][x] = 0;
				}
				else if (board[y][x] == board[y][x - 1])
				{
					board[y][x] = 0;
					board[y][x - 1] *= 2;
				}
		break;
	case 'q':
		exit(0);
	default:
		break;
	}
}

void show()
{
#ifdef _WIN32
	system("cls");
#elif __linux__
	system("clear");
#endif // _WIN32

	// title
	cout << "  This is 2048, simple implementation\n" << endl;

	for (const auto& rows : board)
	{
		for (const auto& item : rows)
			cout << '\t' << item;
		cout << endl;
	}
}