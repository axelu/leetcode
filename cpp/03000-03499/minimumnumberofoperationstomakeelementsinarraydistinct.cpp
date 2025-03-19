
// 3396. Minimum Number of Operations to Make Elements in Array Distinct
// https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/


class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int,int> um; // key: val value: cnt
        for(int i = 0; i < n; ++i)
            ++um[nums[i]];

        int ans = 0;

        int n_new = n;
        int i = 0;
        while( n_new != um.size() ) {
            ++ans;

            int i_new = i + 3;
            for(; i < min(i_new,n); ++i) {
                --um[nums[i]];
                if( um[nums[i]] == 0 )
                    um.erase(nums[i]);
            }
            n_new = max(0, n_new-3);
        }

        return ans;
    }
};
