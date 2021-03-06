#include "BigInt.h"

BigInt::BigInt(string & s) {
	digits = "";
	int n = s.size();
	for (int i = n - 1; i >= 0;i--) {
		if(!isdigit(s[i]))
			throw("ERROR");
		digits.push_back(s[i] - '0');
	}
}

BigInt::BigInt(unsigned long long nr) {
	do{
		digits.push_back(nr % 10);
		nr /= 10;
	} while (nr);
}

BigInt::BigInt(const char *s) {
	digits = "";
	for (int i = strlen(s) - 1; i >= 0;i--)
	{
		if(!isdigit(s[i]))
			throw("ERROR");
		digits.push_back(s[i] - '0');
	}
}

BigInt::BigInt(const BigInt & a) {
	digits = a.digits;
}

bool Null(const BigInt& a){
	if(a.digits.size() == 1 && a.digits[0] == 0)
		return true;
	return false;
}

int Length(const BigInt & a){
	return a.digits.size();
}

int BigInt::operator[](const int index) const {
	if(digits.size() <= index || index < 0)
		throw("ERROR");
	return digits[index];
}

BigInt &operator*=(BigInt &a, const BigInt &b) {
	if(Null(a) || Null(b)){
		a = BigInt();
		return a;
	}

	int n = a.digits.size(), m = b.digits.size();
	vector<int> v(n + m, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			v[i + j] += (a.digits[i]) * (b.digits[j]);
		}
	}
	n += m;
	a.digits.resize(v.size());
	for (int s, i = 0, t = 0; i < n; i++) {
		s = t + v[i];
		v[i] = s % 10;
		t = s / 10;
		a.digits[i] = v[i] ;
	}
	for (int i = n - 1; i >= 1 && !v[i];i--) {
		a.digits.pop_back();
	}
	return a;
}

BigInt operator*(const BigInt&a, const BigInt&b) {
	BigInt temp;
	temp = a;
	temp *= b;
	return temp;
}

ostream &operator<<(ostream &out, const BigInt &a) {
	for (int i = a.digits.size() - 1; i >= 0; i--)
		cout << (short)a.digits[i];
	return cout;
}
