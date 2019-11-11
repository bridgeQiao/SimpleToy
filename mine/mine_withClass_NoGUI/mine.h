/*
	mine code, rewriten with OO
*/

#pragma once

#include <array>
#include <iomanip>
#include <iostream>
#include <random>
#include <stack>

namespace qwer {

	template<unsigned length>
	class Chess {
	public:
		explicit Chess(unsigned num_mines) : num_mines_(num_mines) {
			generate_booms();
			generate_number();
		}
		void show_chess();
		void update_chess(unsigned x, unsigned y);
		bool has_end();
		bool find_all_mine();
	private:
		void generate_booms();           // generate booms assigned with -1
		void generate_number();                    // generate number of booms surranded
		void add_to_zeros(int x, int y);
		void find_zero(int x, int y);

		std::array<int, length * length> chess{ 0 };
		std::array<bool, length * length> bchess{ 0 };
		const unsigned num_mines_;
		std::stack<std::array<int, 2>> zeros;
		bool end_{false};
	};

	/*
			method: generate booms
			args:
				n input the number of booms
	*/
	template<unsigned length>
	void Chess<length>::generate_booms() {
		// random engine
		std::default_random_engine e;
		e.seed(static_cast<unsigned>(time(NULL)));
		std::uniform_int_distribution<unsigned> gen(0, length * length - 1);
		unsigned pos;

		// generate n booms
		unsigned count = 0;
		while (count != num_mines_) {
			pos = gen(e);
			if (chess[pos] != -1) {
				chess[pos] = -1;
				++count;
			}
		}
	}

	/*
			method: Implement convolution
					1. zero padding, surrand with one zero
					2. get index matrix
					3. add column as the convolution to full one matrix
	*/
	template<unsigned length>
	void Chess<length>::generate_number() {
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

	template<unsigned length>
	void Chess<length>::show_chess() {
		// first line
		cout << "    ";
		for (unsigned j = 0; j < length; ++j)
			cout << setw(2) << j << "    ";
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

	/* ----------------------------------------------------------------------------
	   Update chess. If the check position isn't 0, just set the
	 position of bchess to true. If the position is 0, check surround
	 positions, find the all zeros and set the value to true.
	---------------------------------------------------------------------------- */

	// add pos to zeros
	template<unsigned length>
	void Chess<length>::add_to_zeros(int x, int y) {
		auto pos = x * length + y;
		if (bchess[pos] == false) {
			bchess[pos] = true;
			if (chess[pos] == 0) {
				zeros.push({ x,y });
			}
		}
	}

	template<unsigned length>
	void Chess<length>::find_zero(int x, int y) {
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
		// lower line
		if (x + 1 < length) {
			if (y - 1 >= 0)
				add_to_zeros(x + 1, y - 1);
			add_to_zeros(x + 1, y);
			if (y + 1 < length)
				add_to_zeros(x + 1, y + 1);
		}
	}

	template<unsigned length>
	void Chess<length>::update_chess(unsigned x, unsigned y) {
		auto pos = x * length + y;
		// check input
		// set bckess
		bchess[pos] = true;
		if (chess[pos] == -1) {
			end_ = true;
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

	template<unsigned length>
	inline bool Chess<length>::has_end()
	{
		if (end_ || find_all_mine())
			return true;
		else
			return false;
	}

	// ----------------------------------------------------------------------------

	/*
			method: find all mines
				if all mine was found, return true.
	*/
	template<unsigned length>
	bool Chess<length>::find_all_mine()
	{
		unsigned count = 0;
		for (auto i : bchess)
			if (i == true)
				++count;
		if (count == length * length - num_mines_)return true;
		else
			return false;
	}

}