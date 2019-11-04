/*
Copyright (c) [2019] [Qiao Wang]
[2048] is licensed under the Mulan PSL v1.
You can use this software according to the terms and conditions of the Mulan PSL
v1. You may obtain a copy of Mulan PSL v1 at:
		http://license.coscl.org.cn/MulanPSL
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE. See the Mulan PSL v1 for more
details.
*/

#include <array>
#include <iomanip>
#include <iostream>
#include <random>
#include <stack>
using namespace std;
const unsigned length = 9;
array<int, length * length> chess{ 0 };    // store the chess board
array<bool, length * length> bchess{ 0 };  // for output, 1 refer to be checked
bool overd = false;                      // if the game is over
unsigned number = 5;                    // default the number of booms is 5
void generate_booms(unsigned n);         // generate booms assigned with -1
void generate_number();                  // generate number of booms surranded
void show_chess();
void update_chess(int x, int y);
bool find_all_mine();
int main() {
	int x, y;
	cout << "the length of bound, and the number of mine: ";
	cin >> number >> number;
	generate_booms(number);
	generate_number();
	while (!overd) {
		show_chess();
		if (find_all_mine()) break;
		cout << "Please input two number, example: 0 0, between 0 ~ "<< length-1 << endl;
		cin >> x >> y;
		if (0 <= x && x < length && 0 <= y && y < length) {
			update_chess(x, y);
		}
	}
	// over
	if (overd)
		cout << "Game Over!!!";
	else
		cout << "Congrations!!!";
	return 0;
}

void generate_booms(unsigned n) {
	default_random_engine e;
	e.seed(time(NULL));
	uniform_int_distribution<unsigned> gen(0, length * length - 1);
	unsigned pos;
	for (unsigned i = 0; i < n; ++i) {
		pos = gen(e);
		if (chess[pos] != -1) chess[pos] = -1;
	}
}

/*
		method: Implement convolution
				1. zero padding, surrand with one zero
				2. get index matrix
				3. add column as the convolution to full one matrix
*/
void generate_number() {
	// zero padding
	auto zero_pad_chess = array<int, (length + 2) * (length + 2)>{0};
	for (int row = 0; row < length; ++row)
		for (int col = 0; col < length; ++col)
			zero_pad_chess[(row + 1) * (length + 2) + col + 1] =
			chess[row * length + col];

	array<array<int, length * length>, 9> A;
	int count = 0;
	// get matrix A
	for (int i = 0; i < 9; ++i) {
		count = 0;
		if (4 == i) {
			A[i].fill(*chess.data());
			continue;
		}
		for (unsigned row = i / 3; row < length + i / 3; ++row)
			for (unsigned col = i % 3; col < length + i % 3; ++col)
				A[i][count++] = zero_pad_chess[row * (length + 2) + col];
	}
	// filling
	for (int k = 0; k < pow(length, 2); ++k) {
		count = 0;
		if (chess[k] != -1) {
			for (int i = 0; i < 9; ++i) count += A[i][k];
			chess[k] = -count;
		}
	}
}

void show_chess() {
	// first line
	cout << "    ";
	for (unsigned j = 0; j < length; ++j)
		cout << setw(2) << j <<"    ";
	cout << endl;
	cout << "  -------------------------------------------------------\n";
	// other lines
	for (unsigned i = 0; i < length; ++i) {
		cout << i << " | ";
		for (unsigned j = 0; j < length; ++j) {
			if (bchess[i * length + j] == false)
				cout << setw(2) << "    | ";
			else
				cout << setw(2) << chess[i * length + j] << "  | ";
		}
		cout << endl;
		cout << "  -------------------------------------------------------\n";
	}
}

stack<array<int, 2>> zeros;

// add pos to zeros
void add_to_zeros(int x, int y) {
	auto pos = x * length + y;
	if (bchess[pos] == false) {
		bchess[pos] = true;
		if (chess[pos] == 0) {
			zeros.push({ x,y });
		}
	}
}

void find_zero(int x, int y) {
	// upper line
	if (x - 1 >= 0) {
		if (y - 1 >= 0)
			add_to_zeros(x - 1, y - 1);
		add_to_zeros(x - 1, y);
		if (y + 1 < length)
			add_to_zeros(x - 1, y + 1);
	}
	// left and right position
	if (y - 1 >= 0)  add_to_zeros(x, y - 1);
	if (y + 1 < length)  add_to_zeros(x, y + 1);
	// down line
	if (x + 1 < length) {
		if (y - 1 >= 0)
			add_to_zeros(x + 1, y - 1);
		add_to_zeros(x + 1, y);
		if (y + 1 < length)
			add_to_zeros(x + 1, y + 1);
	}
}

void update_chess(int x, int y) {
	auto pos = x * length + y;
	// check input
	// set bckess
	bchess[pos] = true;
	if (chess[pos] == -1) {
		overd = true;
		return;
	}
	if (chess[pos] == 0) {
		find_zero(x, y);
		while (!zeros.empty()) {
			auto pos_top = zeros.top();
			zeros.pop();
			bchess[pos_top[0] * length + pos_top[1]] = true;
			find_zero(pos_top[0], pos_top[1]);
		}
	}
}

bool find_all_mine()
{
	unsigned count = 0;
	for (auto i : bchess)
		if (i == true)
			++count;
	if (count == length * length - number)return true;
	else
		return false;
}
