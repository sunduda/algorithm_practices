#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

class Solution_1 {
public:
	// Generate a sequence of primes
	static void prime_generator(vector<int>& primes, const int& m) {
		int i = 1, n = 3, j = 0, sqrtn = 1;
		primes.clear();
		primes.shrink_to_fit();
		primes.push_back(2);

		while (primes.back() <= m) {
			j = 0;
			sqrtn = sqrt(n);
			while (primes[j] <= sqrtn) {
				if (n%primes[j] == 0)
					break;
				j++;
			}
			if (primes[j] > sqrtn)
				primes.push_back(n);
			n += 2;
		}
	}

	// Check if a integer is a prime
	static bool is_prime(const int& x) {
		int sqrtx = sqrt(x);

		if (x <= 3)
			return true;
		if ((x + 1) % 6 != 0 && (x - 1) % 6 != 0)
			return false;

		for (int i = 5; i <= sqrtx; i += 6) {
			if (x%i == 0 || x % (i + 2) == 0)
				return false;
		}
		return true;
	}

	// Find the minimal prime larger than m
	static int find_min_prime(const int& m) {
		int x = m, d = 0;
		while (1) {
			d = x % 6;
			if (d == 0)
				x++;
			else if (d > 1 && d < 5)
				x += (5 - d);
			if (x > m && is_prime(x))
				break;
			else if (!is_prime(x) && (x + 1) % 6 == 0)
				x += 2;
			else
				x += 4;
		}
		return x;
	}

	static int hash_insert(vector<int*>& hash_table, const int& hashlength, const int& val) {
		int hashaddr = 0, i = -1, h1 = val % hashlength, h2 = val % (hashlength - 1) + 1;
		if (h1 < 0)
			h1 = h1 + hashlength;
		if (h2 < 0)
			h2 = h2 + hashlength;
		do {
			i++;
			hashaddr = (h1 + i * h2) % hashlength;
		} while (hash_table[hashaddr] != NULL);
		hash_table[hashaddr] = new int;
		*hash_table[hashaddr] = val;
		return hashaddr;
	}

	static int hash_search(vector<int*>& hash_table, const int& hashlength, const int& val) {
		int hashaddr = 0, h1 = val % hashlength, h2 = val % (hashlength - 1) + 1;
		if (h1 < 0)
			h1 = h1 + hashlength;
		if (h2 < 0)
			h2 = h2 + hashlength;
		for (int i = 0; i < hashlength; i++) {
			hashaddr = (h1 + i * h2) % hashlength;
			if (hash_table[hashaddr] == NULL)
				break;
			if (*hash_table[hashaddr] == val)
				return hashaddr;
		}
		return -1;
	}

	vector<int> twoSum(vector<int>& nums, int target) {
		int hashlength = find_min_prime(2 * nums.size());
		int hashaddr = 0, index_0 = -1, index_1 = -1;
		vector<int*> hash_table(hashlength, NULL);
		vector<int> idx_sequence(hashlength, -1);
		for (int i = 0; i < nums.size(); i++) {
			hashaddr = hash_search(hash_table, hashlength, nums[i]);
			if (hashaddr > -1) {
				index_0 = idx_sequence[hashaddr];
				index_1 = i;
				break;
			}
			hashaddr = hash_insert(hash_table, hashlength, target - nums[i]);
			idx_sequence[hashaddr] = i;
		}
		return { index_0, index_1 };
	}
};

int main()
{
	vector<int> nums({ 5,75,25 });
	Solution_1 slt;
	vector<int> ans;
	ans = slt.twoSum(nums, 100);
	cout << ans[0] << '\t' << ans[1];
	return 0;
}