#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

class Solution_0 {
public:
	struct list_node {
		int index;
		list_node* next_addr;
	};
	static void inserthash(vector<list_node> &hashmap, const int &hashlength, const int &val, const int &index) {
		list_node *cur_node = &hashmap[((val % hashlength) + hashlength) % hashlength];
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
	static int hashsearch(vector<int>& nums, vector<list_node>& hashmap, const int& hashlength, const int& val, const int& idx) {
		list_node *cur_node = &hashmap[((val % hashlength) + hashlength) % hashlength];
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
		vector<list_node> hashmap(hashlength, { -1,NULL });
		for (int i = 0; i < nums.size(); i++)
			inserthash(hashmap, hashlength, nums[i], i);
		for (int i = 0; i < nums.size(); i++) {
			index_1 = hashsearch(nums, hashmap, hashlength, target - nums[i], i);
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