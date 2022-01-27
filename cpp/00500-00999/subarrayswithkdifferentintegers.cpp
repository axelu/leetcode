
// 992. Subarrays with K Different Integers
// https://leetcode.com/problems/subarrays-with-k-different-integers/




class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;

        // brute force
        int cnt[n+1];
        int d;
        for(int i = 0; i <= n-k; ++i) {
            if( i > 1 && d < k )
                break;
            d = 0;
            memset(cnt,0,sizeof cnt);
            for(int j = i; j < n; ++j) {
                //cout << "i " << i << " j " << j << endl;
                if( ++cnt[nums[j]] == 1 )
                    ++d;
                if( j-i < k-1)
                    continue;
                if( d == k ) {
                    ++ans;
                    //cout << "hit" << endl;
                }
                if( d > k ) break;
            }
        }

        return ans;
    }
};
