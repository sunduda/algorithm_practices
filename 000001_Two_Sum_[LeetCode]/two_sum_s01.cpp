#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

class Solution_1 {
public:
     // Generate a sequence of primes
    static void prime_generator(vector<int>& primes, const int& m){
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
            if (is_prime(x))
                break;
            else if (!is_prime(x) && (x + 1) % 6 == 0)
                x += 2;
            else
                x += 4;
        }
        return x;
    }
    
    static vector<int> hash_map(const int& key, const int& si){
        
    }
	static void insert_hash(vector<int> &hash_table) {
		list_node *cur_node = &hash_table[((val % hashlength) + hashlength) % hashlength];
		list_node *prev_node = NULL;
		while ((cur_node != NULL) && (cur_node->index > -1)) {
			prev_node = cur_node;
			cur_node = cur_node->next_addr;
		}
		if (cur_node == NULL)
			cur_node = new list_node;
		cur_node->index = index;
		cur_node->next_addr = NULL;
		if(prev_node!= NULL)
			prev_node->next_addr = cur_node;
	}
	static int hash_search(vector<int>& nums, vector<list_node>& hash_table, const int& hashlength, const int& val, const int& idx) {
		list_node *cur_node = &hash_table[((val % hashlength) + hashlength) % hashlength];
		while ((cur_node != NULL) && (cur_node->index > -1)) {
			if (cur_node->index == idx) {
				cur_node = cur_node->next_addr;
				continue;
			}
			else if (nums[cur_node->index] == val)
				return cur_node->index;
			else
				cur_node = cur_node->next_addr;
		}
		return -1;
	}
	vector<int> twoSum(vector<int>& nums, int target) {
		int hashlength = 10;
		int index_0 = -1;
		int index_1 = -1;
		vector<list_node> hash_table(hashlength, { -1,NULL });
		for (int i = 0; i < nums.size(); i++)
			insert_hash(hash_table, hashlength, nums[i], i);
		for (int i = 0; i < nums.size(); i++) {
			index_1 = hash_search(nums, hash_table, hashlength, target - nums[i], i);
			if (index_1 != -1) {
				index_0 = i;
				break;
			}
		}
		return { index_0, index_1 };
	}
};

int main()
{
	vector<int> nums({ 3,2,4 });
	Solution_0 slt;
	vector<int> ans;
	ans = slt.twoSum(nums, 6);
	cout << ans[0] << '\t' << ans[1];
	return 0;
}