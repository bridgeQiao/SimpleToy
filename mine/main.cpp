// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <iomanip>
#include <random>
#include <array>
#include <stack>
using namespace std;
const unsigned length = 9;
array<int, length*length> chess{ 0 };	// store the chess board
array<bool, length*length> bchess{0};	// for output, 1 refer to be checked
bool overd = false;						// if the game is over
unsigned number = 10;				// default the number of booms is 5
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

/* 
	method: Implement convolution
		1. zero padding, surrand with one zero
		2. get index matrix
		3. add column as the convolution to full one matrix
*/
void generate_number()
{
	// zero padding
	auto zero_pad_chess = array<int, (length + 2)*(length+2)>{0};
	for (int row = 0; row < length; ++row)
		for (int col = 0; col < length; ++col)
			zero_pad_chess[(row + 1) * (length+2) + col + 1] = chess[row * length + col];

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
				A[i][count++] = zero_pad_chess[row * (length+2) + col];
	}
	// filling
	for (int k = 0; k < pow(length,2); ++k) {
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
		{
			if(bchess[i*length+j] == false)
				cout << setw(2) << "    | ";
			else
				cout << setw(2) << chess[i * length + j] << "  | ";
		}
		cout << endl;
	}
}

stack<array<int,2>> zeros;

void update_chess(int x, int y)
{
	auto pos = x*length+y;
	// check input
	// set bckess
	bchess[pos] = true;
	if(chess[pos] == -1) {
		over = true;
		break;
	}
	if(chess[pos] == 0)

}

find_zero(int x, int y)
{
	// bound condition
	if(x == 0)
}