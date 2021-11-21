
// 368. Largest Divisible Subset
// https://leetcode.com/problems/largest-divisible-subset/
// day 15 Nov 2021 challenge



// solution approach #3 recursion with memoization
class Solution {
private:
    vector<int> rec(vector<int>& nums, int i, vector<int> mem[]) {

        if( !mem[i].empty() )
            return mem[i];

        vector<int> maxSubset;
        // find the largest divisible subset of previous elements
        for(int k = 0; k < i; ++k) {
            if( nums[i] % nums[k] == 0 ) {
                vector<int> subset = rec(nums,k,mem);
                if( subset.size() > maxSubset.size() )
                    maxSubset = subset;
            }
        }

        // add our element
        maxSubset.push_back(nums[i]);

        return mem[i] = maxSubset;
    }


public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        if( n == 0 )
            return {};

        sort(nums.begin(),nums.end());

        vector<int> ans;

        vector<int> mem[n];
        for(int i = 0; i < n; ++i) {
            vector<int> subset = rec(nums,i,mem);
            if( subset.size() > ans.size() )
                ans = subset;
        }

        return ans;
    }
};
