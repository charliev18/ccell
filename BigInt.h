#ifndef CCELL_BIGINT_H
#define CCELL_BIGINT_H

#include <string>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

class BigInt {
	string digits;
public:
	// Constructors:
	explicit BigInt(unsigned long long n = 0);
	explicit BigInt(string &);
	explicit BigInt(const char *);
	BigInt(const BigInt &);

	// Helper Functions:
	friend bool Null(const BigInt &);
	friend int Length(const BigInt &);
	int operator[](const int) const;

	// Multiplication
	friend BigInt &operator*=(BigInt &, const BigInt &);
	friend BigInt operator*(const BigInt &, const BigInt &);

	friend ostream &operator<<(ostream &,const BigInt &);
};


#endif //CCELL_BIGINT_H
