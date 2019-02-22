#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	bool is_prime(const int& x) {
		int d = x % 6;
		int sqrtx = sqrt(x);
		if (x <= 1)
			return false;
		if (x < 4)
			return true;
		if (d != 1 && d != 5)
			return false;
		for (int i = 5; i < sqrtx; i += 6)
			if (x%i == 0 || x % (i + 2) == 0)
				return false;
		return true;
	}

	int find_min_prime(const int& m) {
		int prime = m;
		int d = 0;
		if (m <= 0)
			return 2;
		if (m < 4)
			return m;
		while (true) {
			d = prime % 6;
			if (d == 0)
				prime += 1;
			else if (d > 1 && d < 5)
				prime += 5 - d;
			if (is_prime(prime))
				break;
			if (d == 1)
				prime += 4;
			else if (d == 5)
				prime += 2;
		}
		return prime;
	}

	int find_max_prime(const int& m) {
		int prime = m;
		int d = 0;
		if (m < 4)
			return 2;
		while (true) {
			d = prime % 6;
			if (d == 0)
				prime -= 1;
			else if (d > 1 && d < 5)
				prime += 1 - d;
			if (is_prime(prime))
				break;
			if (d == 1)
				prime -= 2;
			else if (d == 5)
				prime -= 4;
		}
		return prime;
	}
	int hash_insert(vector<int*> &hash_table, const int& hash_length, const int& lesser_prime, const int& val) {
		int h1 = (val-32) % hash_length;
		int h2 = lesser_prime - (val - 32) % lesser_prime;
		int hashaddr = 0;
		for (int i = 0; i < hash_length; i++) {
			hashaddr = (h1 + i * h2) % hash_length;
			if (hash_table[hashaddr] == NULL) {
				hash_table[hashaddr] = new int;
				*hash_table[hashaddr] = val;
				break;
			}
		}
		return hashaddr;
	}
	int hash_search(vector<int*> &hash_table, const int& hash_length, const int& lesser_prime, const int& val) {
		int h1 = (val - 32) % hash_length;
		int h2 = lesser_prime - (val - 32) % lesser_prime;
		int hashaddr = 0;
		for (int i = 0; i < hash_length; i++) {
			hashaddr = (h1 + i * h2) % hash_length;
			if (hash_table[hashaddr] == NULL)
				break;
			else if (*hash_table[hashaddr] == val)
				return hashaddr;
		}
		return -1;
	}

	int lengthOfLongestSubstring(string s) {
		const char invalid = 32;
		vector<int> char_pos(128 - invalid - 1, -1);
		string tmp = "", ans = "a";
		int si = 0, cur_key = -1, cr = 0;
		if (s.size() == 0)
			return 0;
		while(si<s.size()){
			cur_key = s[si]- invalid;
			if (char_pos[cur_key] < 0) {
				char_pos[cur_key] = si;
				tmp += s[si];
				si++;
			}
			else if (si + ans.size() >= s.size())
				break;
			else if (si + 1 < s.size() && s[si] == s[si + 1]) {
				if (tmp.size() > ans.size())
					ans = tmp;
				for (int j = 0, rb = char_pos[cur_key] - char_pos[tmp[0] - invalid]; j < tmp.size(); j++) {
					if (j == rb)
						char_pos[tmp[j] - invalid] = si + 1;
					else
						char_pos[tmp[j] - invalid] = -1;
				}
				tmp = s[si];
				si += 2;
			}
			else {
				int init_pos = char_pos[tmp[0] - invalid];
				int repeat_begin = char_pos[cur_key];
				if (tmp.size() > ans.size())
					ans = tmp;
				cr = 1;
				while (si + cr < s.size() && repeat_begin + cr < init_pos + tmp.size() && s[char_pos[cur_key] + cr] == s[si + cr])
					cr++;
				if (si + cr < s.size())
					break;
				for (int j = 0; j <= repeat_begin - init_pos; j++) {
					char_pos[tmp[j] - invalid] = -1;
					if (j == repeat_begin - init_pos)
						for (int k = 0; k < cr; k++)
							char_pos[tmp[j + k] - invalid] = si + k;
				}

				tmp = tmp.substr(repeat_begin - init_pos, cr);
				si += cr;
			}
		}

		if (tmp.size() > ans.size())
			ans = tmp;
		return ans.size();
	}
};

int main() {
	Solution slt;
	string a = "mpesjbcxgdfucjbrazpzpzdrlnepyiikzoeirghxkmsoytgyuxxjycdmqhbqrjasyhapnkpzyjowewuztt";
	cout << slt.lengthOfLongestSubstring(a) << endl;
	//system("pause");
	return 0;
}