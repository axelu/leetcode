
// 1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit
// https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/


class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();

        int ans = 1;

        map<int,int> mp;

        int i = 0;                      // left index
        for(int j = 0; j < n; ++j) {    // right index
            ++mp[nums[j]];

            if( mp.rbegin()->first - mp.begin()->first <= limit ) {
                ans = max(ans, j - i + 1);

            } else {

                while( mp.rbegin()->first - mp.begin()->first > limit) {
                    --mp[nums[i]];
                    if( mp[nums[i]] == 0 )
                        mp.erase(nums[i]);
                    ++i;
                }
            }
        }

        return ans;
    }
};
