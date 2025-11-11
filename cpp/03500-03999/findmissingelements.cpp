
// 3731. Find Missing Elements
// https://leetcode.com/problems/find-missing-elements/description/


class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int n = nums.size(); // 2 <= n <= 100

        int mn = INT_MAX;
        int mx = INT_MIN;
        bool seen[101]; memset(seen,false,sizeof seen);
        for(int i = 0; i < n; ++i) {
            mn = min(mn, nums[i]);
            mx = max(mx, nums[i]);
            seen[nums[i]] = true;
        }

        vector<int> ans;
        for(int i = mn+1; i < mx; ++i) {
            if( !seen[i] )
                ans.push_back(i);
        }

        return ans;
    }
};
