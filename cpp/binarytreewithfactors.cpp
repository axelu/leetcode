
// 823. Binary Tree With Factors
// https://leetcode.com/problems/binary-trees-with-factors/
// day 13 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/589/week-2-march-8th-march-14th/3670/


// solution approach #1
class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(),arr.end());

        long dp[n];
        for(int i = 0; i < n; ++i) dp[i] = 1L;

        unordered_map<int,int> idx;
        for(int i = 0; i < n; ++i)
            idx.insert({arr[i],i});
        unordered_map<int,int>::iterator f;
        unordered_map<int,int>::iterator ie = idx.end();

        int mod = 1000000007;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < i; ++j) {
                if( arr[i] % arr[j] == 0 ) { // A[j] is left child
                    int right = arr[i] / arr[j];
                    f = idx.find(right);
                    if( f != ie )
                        dp[i] = (dp[i] + dp[j] * dp[f->second]) % mod;
                }
            }

        long ans = 0;
        for(int i = 0; i < n; ++i)
            ans += dp[i];

        return (int)(ans % mod);
    }
};
