#pragma once
#include <iostream>
class BitVector
{
	bool* a;
	int n;
	friend std::istream& operator>>(std::istream& in, BitVector& v);
	friend std::ostream& operator<<(std::ostream& out, BitVector& v);
public:
	explicit BitVector(int n = 1);
	BitVector(int n, bool* a);
	BitVector(const BitVector& v);
	~BitVector();
	BitVector& operator=(const BitVector& v);
	bool operator[](int k) const;
	bool& operator[](int k);
	bool operator==(const BitVector& v) const;
	bool operator!=(const BitVector& v) const;
	BitVector& operator|=(const BitVector& v);
	BitVector& operator&=(const BitVector& v);
	BitVector operator|(const BitVector& v) const;
	BitVector operator&(const BitVector& v) const;
	BitVector& operator<<=(int k);
	BitVector& operator>>=(int k);
	BitVector operator<<(int k) const;
	BitVector operator>>(int k) const;
	BitVector& operator+=(const BitVector& v);
	BitVector operator+(const BitVector& v) const;
	int BitCount() {
		return n;
	}
};