// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <iomanip>
#include <random>
#include <array>
using namespace std;
const unsigned length = 9;
array<int, length*length> chess{ 0 };	// store the chess board
bool overd = 0;						// if the game is over
unsigned number = 5;				// default the number of booms is 5
void generate_booms(unsigned n);	// generate booms assigned with -1
void generate_number();				// generate number of booms surranded
void show_chess();
void update_chess(int x, int y);
int main()
{
	int x, y;
	unsigned count = 0;
    std::cout << "----------------scanning booms------------------\n";
	generate_booms(number);
	generate_number();
	while (!overd)
	{
		show_chess();
		cin >> x >> y;
		update_chess(x, y);
		if (++count == 2 * length - number) break;
	}
	// over
	if (overd) cout << "Game Over!!!";
	else cout << "Congrations!!!";
	return 0;
}

void generate_booms(unsigned n) {
	default_random_engine e;
	uniform_int_distribution<unsigned> gen(0, length*length-1);
	unsigned pos;
	for (unsigned i = 0; i < n; ++i) {
		pos = gen(e);
		if (chess[pos] != -1)
			chess[pos] = -1;
	}
}

void generate_number()
{
	auto zero_pad_chess = array<int, (length + 1) ^ 2>{0};
	array<array<int, length * length>, 9> A;
	int count = 0;
	// get matrix A
	for (int i = 0; i < 9; ++i) {
		count = 0;
		if (4 == i)
			A[i] = chess;
		for (unsigned row = i / 3; row < length - 1 + i / 3; ++row)
			for (unsigned col = i % 3; col < length - 1 + i % 3; ++col)
				A[i][count++] = zero_pad_chess[row * length + col];
	}
	// filling
	for (int k = 0; k < length ^ 2; ++k) {
		count = 0;
		if (chess[k] != -1) {
			for (int i = 0; i < 9; ++i) count += A[i][k];
			chess[k] = -count;
		}
		
	}
}

void show_chess() {
	for (unsigned i = 0; i < length; ++i) {
		cout << "| ";
		for (unsigned j = 0; j < length; ++j)
			cout << setw(2) << chess[i * length + j] << "  | ";
		cout << endl;
	}
}

void update_chess(int x, int y)
{
}
