
// 2551. Put Marbles in Bags
// https://leetcode.com/problems/put-marbles-in-bags/





class Solution {
public:
    long long putMarbles(vector<int>& weights, int k) {
        int n = weights.size();
        if( k == 1 || (n == 2 && k == 2 ) )
            return 0;

        long long fst = weights[0];
        long long lst = weights[n-1];

        // collect endpoint pairs of [subarrayendpoint,subarraystartingpoint]
        // we have k subarrays, so we need k-1 pairs as we are always have first and last points
        vector<long long> pairs(n-1);
        for(int i = 0; i < n-1; ++i)
            pairs[i] = weights[i]+weights[i+1];

        sort(pairs.begin(),pairs.end());

        // min
        long long mn = fst + lst;
        for(int i = 0; i <= k-2; ++i)
            mn += pairs[i];

        // max
        long long mx = fst + lst;
        for(int i = n-2; i >= (n-2)-(k-2); --i)
            mx += pairs[i];

        return mx - mn;
    }
};
