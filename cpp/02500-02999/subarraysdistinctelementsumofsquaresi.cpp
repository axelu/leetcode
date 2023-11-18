
// 2913. Subarrays Distinct Element Sum of Squares I
// https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/


// 0 1 2 3 4 5 6 7 8 9 
//               -----


class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        
        // brute force
        int ans = 0;
        int t;
        int cnt[101];
        for(int l = 1; l <= n; ++l)
            for(int i = 0; i <= n-l; ++i) {
                memset(cnt,0,sizeof cnt);
                t = 0;
                for(int j = i; j < i+l; ++j)
                    if( ++cnt[nums[j]] == 1 )
                        ++t;
                ans += t * t;
            }
        
        return ans;
    }
};
