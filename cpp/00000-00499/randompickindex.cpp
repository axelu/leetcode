
// 398. Random Pick Index
// https://leetcode.com/problems/random-pick-index/




class Solution {
private:
    unordered_map<int,vector<int>> um;

public:
    Solution(vector<int>& nums) {
        srand(time(nullptr)); // use current time as seed for random generator
        int n = nums.size();
        for(int i = 0; i < n; ++i)
            um[nums[i]].push_back(i);
    }

    int pick(int target) {
        int mod = um[target].size();
        return um[target][rand()%mod];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
