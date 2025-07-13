
// 3584. Maximum Product of First and Last Elements of a Subsequence
// https://leetcode.com/problems/maximum-product-of-first-and-last-elements-of-a-subsequence/




class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        int n = nums.size();

        if( m == 1 ) {
            long long mx = *(max_element(nums.begin(), nums.end()));
            long long mn = *(min_element(nums.begin(), nums.end()));
            return max(mx*mx, mn*mn);
        }

        if( m == n ) {
            return (long long)nums[0] * (long long)nums[n-1];
        }

        map<int,int> mp;
        int j = m-1;
        for(; j < n; ++j)
            ++mp[nums[j]];


        long long ans = LLONG_MIN;

        j = m-1;
        for(int i = 0; i <= n-m; ++i) {
            ans = max(ans, (long long)nums[i] * (long long)mp.begin()->first);
            ans = max(ans, (long long)nums[i] * (long long)mp.rbegin()->first);

            --mp[nums[j]];
            if( mp[nums[j]] == 0 )
                mp.erase(nums[j]);
            ++j;
        }

        return ans;
    }
};
