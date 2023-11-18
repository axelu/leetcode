
// 1819. Number of Different Subsequences GCDs
// https://leetcode.com/problems/number-of-different-subsequences-gcds/




class Solution {
public:
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 10^5
                             // 1 <= nums[i] <= 2 * 10^5

        int ans = 0;

        int cnt[200001];memset(cnt,0,sizeof cnt);
        for(int x: nums)
            ++cnt[x];

        // test every possible GCD
        for(int i = 1; i <= 200000; i++) {
            if( cnt[i] >= 1 ) {
                // subseqence of length 1 itself is a GCD
                ++ans;
            } else {

                int _gcd = 0;
                // test every multiple of i
                for(int j = i; j <= 200000; j += i) {
                    if( cnt[j] >= 1 )
                        _gcd = gcd(_gcd,j);
                    if( _gcd == i ) {
                        ++ans;
                        break;
                    }
                }
            }
        }

        return ans;
    }
};
