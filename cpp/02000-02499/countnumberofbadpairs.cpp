
// 2364. Count Number of Bad Pairs
// https://leetcode.com/problems/count-number-of-bad-pairs/



class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int,long long> um;
        ++um[-nums[0]];

        long long ans = 0;

        for(int i = 1; i < n; ++i) {

            int diff = i - nums[i];

            // total possible pairs
            long long tp = i;

            // good pairs
            long long gp = um[diff];


            ans += tp - gp;

            ++um[diff];
        }

        return ans;
    }
};
