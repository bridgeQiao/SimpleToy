#include "mine.h"

using namespace std;

int main() {
	int x, y;
	const unsigned length = 9;
	unsigned number = 5;  // default numbers
	cout << "the length of bound is " << length << ", and the number of mine: ";
	cin >> number;
	qwer::Chess<length> m_chess(number);
	while (!m_chess.has_end()) {
		m_chess.show_chess();
		cout << "Please input two number, example: 0 0, between 0 ~ " << length - 1 << endl;
		cin >> x >> y;
		if (0 <= x && x < length && 0 <= y && y < length) {
			m_chess.update_chess(x, y);
		}
	}
	// over
	if (m_chess.find_all_mine())
		cout << "Congrations!!!";
	else
		cout << "Game Over!!!";
	return 0;
}