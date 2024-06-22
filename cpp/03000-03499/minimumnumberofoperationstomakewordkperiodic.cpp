
// 3137. Minimum Number of Operations to Make Word K-Periodic
// https://leetcode.com/problems/minimum-number-of-operations-to-make-word-k-periodic/





class Solution {
public:
    int minimumOperationsToMakeKPeriodic(string word, int k) {
        int n = word.size();

        unordered_map<string,int> dic;
        for(int i = 0; i < n; i += k)
            ++dic[word.substr(i,k)];

        int mx = 0;
        for(auto& p: dic)
            mx = max(mx, p.second);


        return n / k - mx;
    }
};
