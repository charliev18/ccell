#include <iostream>
#include <chrono>
#include <map>
#include <string>
#include <algorithm>
#include "BigInt.h"

using namespace std;

// Maps exponents to the value of the current base raised to that power
map<int, BigInt> cache;

/*
 * Checks if the given key is in the cache, returns the corresponding value if yes, null otherwise
 */
BigInt check_cache(int key) {
	auto search = cache.find(key);
	if (search != cache.end())  return search->second;
	return *new BigInt();
}

/*
 * Returns the largest power of two below a given integer
 * Runs in O(n) where n is the bit length of the input
 */
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
 * Returns base ^ power
 * CONDITION: power must be a power of 2
 */
BigInt efficient_pow(int base, int power) {
	// Base case
	if (power == 1) return BigInt(base);

	// Check if base^power has already been calculated
	BigInt val = check_cache(power);
	if (!Null(val)) {
		return val;
	}

	// Recursive step to calculate base ^ power/2
	BigInt sqrt = efficient_pow(base, power / 2);
	cache[power] = sqrt * sqrt;
	return cache[power];
}

/*
 * Returns base ^ power
 */
BigInt pow(int base, int power) {
	// Base case 1
	if (power == 0) return BigInt(1);

	// Base case 2
	if (power == 1) return BigInt(base);

	// Get largest power of 2 below the given power to run the efficient exponentiation algorithm
	int pow_2 = largest_pow_2_below(power);
	int remainder = power - pow_2;

	// Multiply the result of efficient exponentiation with the remaining exponent
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

	// Start timer
	auto start = chrono::high_resolution_clock::now();

	// Calculate output
	BigInt out = pow(base, power);

	// Stop timer
	auto end = chrono::high_resolution_clock::now();

	cout << "Value:" << endl;
	cout << out << endl;
	auto time_taken_secs = chrono::duration_cast<chrono::seconds>(end - start);
	cout << "Time taken: " << time_taken_secs.count() << "s" << endl;

	return 0;
}
