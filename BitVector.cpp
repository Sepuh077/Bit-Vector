#include "BitVector.h"
#include <iostream>
#include <algorithm>
#include <string>

std::istream& operator>>(std::istream& in, BitVector& v) {
	std::string s;
	in >> s;
	v.n = s.length();
	v.a = new bool[v.n];
	for (int i = 0; i < v.n; i++) {
		v.a[i] = s[i] - '0';
	}
	return in;
}
std::ostream& operator<<(std::ostream& out, BitVector& v) {
	for (int i = 0; i < v.n; i++) {
		out << v.a[i];
	}
	return out;
}
BitVector::BitVector(int n) {
	if (n < 1)
		n = 1;
	this->n = n;
	a = new bool[n];
	for (int i = 0; i < n; i++)
		a[i] = 0;
}
BitVector::BitVector(int n, bool* a) {
	this->n = n;
	this->a = new bool[n];
	for (int i = 0; i < n; i++)
		this->a[i] = a[i];
}
BitVector::BitVector(const BitVector& v) {
	n = v.n;
	a = new bool[n];
	for (int i = 0; i < n; i++) {
		a[i] = v.a[i];
	}
}
BitVector::~BitVector() {
	n = 0;
	delete[] a;
}
BitVector& BitVector::operator=(const BitVector& v) {
	delete[] a;
	n = v.n;
	a = new bool[n];
	for (int i = 0; i < n; i++) {
		a[i] = v.a[i];
	}
	return *this;
}
bool BitVector::operator[](int k) const {
	if (k < 0)
		k = 0;
	if (k >= n)
		k = n - 1;
	return a[k];
}
bool& BitVector::operator[](int k) {
	if (k < 0)
		k = 0;
	if (k >= n) {
		bool* arr = new bool[n];
		for (int i = 0; i < n; i++) {
			arr[i] = a[i];
		}
		delete[] a;
		a = new bool[k + 1];
		a = arr;
		n = k + 1;
	}
	return a[k];
}
bool BitVector::operator==(const BitVector& v) const {
	if (n != v.n)
		return 0;
	for (int i = 0; i < n; i++) {
		if (a[i] != v.a[i])
			return 0;
	}
	return 1;
}
bool BitVector::operator!=(const BitVector& v) const {
	if (*this == v)
		return 0;
	return 1;
}
BitVector& BitVector::operator|=(const BitVector& v) {
	for (int i = 0; i < v.n; i++) {
		if (i >= n)
			a[i] = v.a[i];
		else {
			if (a[i] == 0 && v.a[i] == 1)
				a[i] = 1;
		}
	}
	return *this;
}
BitVector& BitVector::operator&=(const BitVector& v) {
	int l = std::min(n, v.n);
	for (int i = 0; i < l; i++) {
		if (a[i] == 1 && v.a[i] == 1)
			a[i] = 1;
		else
			a[i] = 0;
	}
	int k = std::max(n, v.n); 
	for (int i = l; i < k; i++) {
		a[i] = 0;
	}
	return *this;
}
BitVector BitVector::operator|(const BitVector& v) const {
	BitVector b;
	b = *this;
	return (b |= v);
}
BitVector BitVector::operator&(const BitVector& v) const {
	BitVector b;
	b = *this;
	return (b &= v);
}
BitVector& BitVector::operator>>=(int k) {
	for (int i = n - k; i >= 0; i--) {
		a[i + k] = a[i];
	}
	for (int i = 0; i < std::min(k, n); i++) {
		a[i] = 0;
	}
	return *this;
}
BitVector& BitVector::operator<<=(int k) {
	for (int i = k; i < n; i++) {
		a[i - k] = a[i];
	}
	for (int i = std::max(0,n - k); i < n; i++)
		a[i] = 0;
	return *this;
}
BitVector BitVector::operator<<(int k) const{
	BitVector b(*this);
	return (b <<= k);
}
BitVector BitVector::operator>>(int k) const {
	BitVector b(*this);
	return (b >>= k);
}
BitVector& BitVector::operator+=(const BitVector& v) {
	bool* x = new bool[n];
	for (int i = 0; i < n; i++)
		x[i] = a[i];
	delete[] a;
	a = new bool[n + v.n];
	for (int i = 0; i < n + v.n; i++) {
		if (i < n)
			a[i] = x[i];
		else
			a[i] = v.a[i - n];
	}
	n += v.n;
	delete[] x;
	return *this;
}
BitVector BitVector::operator+(const BitVector& v) const {
	BitVector b(*this);
	return (b += v);
}