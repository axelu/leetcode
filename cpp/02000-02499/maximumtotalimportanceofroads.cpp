
// 2285. Maximum Total Importance of Roads
// https://leetcode.com/problems/maximum-total-importance-of-roads/



class Solution {
public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        vector<long> cnt(n,0L);               // degree of each node

        for(auto& v : roads) {
            ++cnt[v[0]];
            ++cnt[v[1]];
        }

        // each node will be reached by others the number of times
        // roads connect to it (= degree). So if we start assigning
        // highest importance along highest degrees we get optimal score

        // sort degrees respectively counts
        sort(cnt.begin(),cnt.end());

        long ans = 0L;

        for(long i = n; i >= 1; --i)   // importance
            ans += i * cnt[i-1];

        return ans;
     }
};
