
// day 16 September 2020 challenge
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/556/week-3-september-15th-september-21st/3462/
// 421. Maximum XOR of Two Numbers in an Array
// https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/

#include <iostream>
#include <cassert>

#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

struct Trie {
    Trie* next[2];
    Trie() {
        next[0] = nullptr; // 0 bit
        next[1] = nullptr; // 1 bit
    }
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        auto ns =nums.size();
        if( ns < 2 ) return 0;
        if( ns == 2 ) return nums[0] ^ nums[1];

        int r = 0;

        Trie* root = new Trie();
        for(auto it = nums.begin(); it != nums.end(); ++it) {
            insert(root, *it);
            r = max(r, maxxor(root, *it));
        }

        return r;
    }
private:
    void insert(Trie* root, int num) {
        Trie* curr = root;

        for(int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if( curr->next[bit] == nullptr )
                curr->next[bit] = new Trie();
            curr = curr->next[bit];
        }
    }

    int maxxor(Trie* root, int num) {
        Trie* curr = root;

        int r = 0;

        for(int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;

            // looking for complements hence negating the bit
            // prefer opposite, but if not present, keep walking
            if( curr->next[!bit] ) {
                r += (1 << i); // count here based on the bit we are currently processing
                curr = curr->next[!bit];
            } else {
                curr = curr->next[bit];
            }
        }

        return r;
    }
};

int main() {
    Solution s;
    vector<int> nums;

    nums = {3, 10, 5, 25, 2, 8}; // 28
    cout << s.findMaximumXOR(nums) << endl;
    // cout << s.findMaximumXOR2(nums) << endl;
    // assert(s.findMaximumXOR(nums) == 28);

    // 2e31 = 2147483648
    nums = {2147483646, 2147483647}; // 1
    cout << s.findMaximumXOR(nums) << endl;
    // cout << s.findMaximumXOR2(nums) << endl;

    nums = {8,10,2}; // 10
    cout << s.findMaximumXOR(nums) << endl;
    // cout << s.findMaximumXOR2(nums) << endl;


    return 0;
}

