
// 3784. Minimum Deletion Cost to Make All Characters Equal
// https://leetcode.com/problems/minimum-deletion-cost-to-make-all-characters-equal/



class Solution {
public:
    long long minCost(string s, vector<int>& cost) {
        int n = s.size(); // s.size == cost.size

        long long total = 0LL;
        long long sum[26]; memset(sum, 0, sizeof sum);
        for(int i = 0; i < n; ++i) {
            sum[s[i]-'a'] += (long long)cost[i];
            total += (long long)cost[i];
        }

        long long ans = LLONG_MAX;
        for(int i = 0; i < 26; ++i)
            ans = min(ans, total - sum[i]);

        return ans;
    }
};
