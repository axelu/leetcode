
// 1512. Number of good Pairs
// https://leetcode.com/problems/number-of-good-pairs/


class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int r = 0;

        if( nums.size() < 2 ) return r;

        auto ne = nums.end();
        for(auto it = nums.begin(); it != ne - 1; ++it) {
            r += count(it + 1, ne, *it);
        }

        return r;
    }
};
