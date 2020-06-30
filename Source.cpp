#include <iostream>
#include "BitVector.h"

using namespace std;

int main() {
	int n, max = 0;
	cin >> n;
	BitVector* a = new BitVector[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (i == 0 || max < a[i].BitCount())
			max = a[i].BitCount();
	}
	BitVector bit0(max);
	bool* x = new bool[max];
	for (int i = 0; i < max; i++)
		x[i] = 1;
	BitVector bit1(max, x), bit(bit1);
	for (int i = 0; i < n; i++) {
		bit &= a[i];
	}
	if (bit != bit0)
		cout << "NO" << endl;
	else {
		int ind1 = -1, ind2 = -1;
		for (int i = 0; i < n; i++) {
			int x = i, y = -1;
			bit = bit1;
			for (int j = i; j < n; j++) {
				bit &= a[j];
				if (bit == bit0) {
					y = j + 1;
					break;
				}
			}
			if ((i == 0 || y - x < ind2 - ind1) && y >= 0) {
				ind2 = y;
				ind1 = x;
			}
		}
		for (int i = ind1; i < ind2; i++) {
			cout << a[i] << " ";
		}
		cout << endl;
	}
	return 0;
}