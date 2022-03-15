
// 1218. Longest Arithmetic Subsequence of Given Difference
// https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/


class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int n = arr.size();

        int ans = 1;

        int dp[n];
        int ls[40001];           // last seen
        memset(ls,-1,sizeof ls); // initially we have not seen any
        int offset = 20000;
        int l;
        for(int i = 0; i < n; ++i) {
            l = 1;
            if( ls[arr[i]+offset-difference] != -1 )
                l = 1 + dp[ls[arr[i]+offset-difference]];

            dp[i] = l;
            ls[arr[i]+offset] = i;
            ans = max(ans,l);
        }

        return ans;
    }
};
