
// 2171. Removing Minimum Number of Magic Beans
// https://leetcode.com/problems/removing-minimum-number-of-magic-beans/



class Solution {
public:
    long long minimumRemoval(vector<int>& beans) {
        int n = beans.size();

        sort(beans.begin(),beans.end());

        vector<long long> prefixSum(n+1,0LL);
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + beans[i-1];

        long long ans = LLONG_MAX;

        for(long long i = 0; i < n; ++i) {

            long long t = prefixSum[i] + (prefixSum[n] - prefixSum[i] - (n-i) * beans[i]);
            ans = min(ans,t);
        }

        return ans;
    }
};
