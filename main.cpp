#include <iostream>
#include <chrono>
#include <map>
#include <string>
#include <algorithm>
#include "BigInt.h"

using namespace std;

map<int, BigInt> cache;

BigInt check_cache(int key) {
	auto search = cache.find(key);
	if (search != cache.end())  return search->second;
	return *new BigInt();
}

int largest_pow_2_below(int num) {
	if (num < 1) return 0;

	int res = 1;

	// Try all powers starting from 2^1
	for (int i = 0; i < 8 * sizeof(int); i++) {
		int curr = 1 << i;

		// If current power is more than n, break
		if (curr > num)
			break;

		res = curr;
	}

	return res;
}

/*
 * Should only be called with a power that is a power of two
 */
BigInt efficient_pow(int base, int power) {
	if (power == 1) return BigInt(base);

	BigInt val = check_cache(power);
	if (!Null(val)) {
		return val;
	}

	BigInt sqrt = efficient_pow(base, power / 2);
	cache[power] = sqrt * sqrt;
	return cache[power];
}

BigInt pow(int base, int power) {
	if (power == 0) return BigInt(1);

	if (power == 1) return BigInt(base);

	int pow_2 = largest_pow_2_below(power);
	int remainder = power - pow_2;

	return efficient_pow(base, pow_2) * pow(base, remainder);
}

int main(int argc, char *argv[]) {
	// Default values
	int base = 54321;
	int power = 12345;

	// Read command line input
	if (argc > 1) {
		string cast = string(argv[1]);
		base = stoi(argv[1]);
		reverse(cast.begin(), cast.end());
		power = stoi(cast);
	}

	cout << "Calculating: " << base << endl;
	cout << "To the power: " << power << endl;

	auto start = chrono::high_resolution_clock::now();

	BigInt out = pow(base, power);

	auto end = chrono::high_resolution_clock::now();

	cout << "Value:" << endl;
	cout << out << endl;
	auto time_taken_secs = chrono::duration_cast<chrono::seconds>(end - start);
	cout << "Time taken: " << time_taken_secs.count() << "s" << endl;

	return 0;
}
