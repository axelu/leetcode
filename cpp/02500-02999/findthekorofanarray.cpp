
// 2917. Find the K-or of an Array
// https://leetcode.com/problems/find-the-k-or-of-an-array/




class Solution {
public:
    int findKOr(vector<int>& nums, int k) {
        int ans = 0;
        int cnt[31];memset(cnt,0,sizeof cnt);
        for(int x: nums) {
            for(int i = 0; i < 31; ++i) {
                if( x & (1<<i) ) {
                    if( ++cnt[i] == k ) {
                        ans |= (1<<i);
                    }
                }
            }
        }
        return ans;
    }
};
