
// 2838. Maximum Coins Heroes Can Collect
// https://leetcode.com/problems/maximum-coins-heroes-can-collect/





class Solution {
public:
    vector<long long> maximumCoins(vector<int>& heroes, vector<int>& monsters, vector<int>& coins) {
        int n = heroes.size();
        int m = monsters.size(); // monsters.size() == coins.size()

        vector<long long> ans(n);

        // preprocess monsters
        vector<pair<int,long long>> mc(m); // monsters[i],coins[i]
        for(int i = 0; i < m; ++i)
            mc[i] = {monsters[i],coins[i]};
        // sort by power of monster asc
        sort(mc.begin(),mc.end(),[](const pair<int,int>& a, const pair<int,int>& b){
            return a.first < b.first;
        });

        // proprocess heroes
        vector<pair<int,int>> hi(n); // heroes[i],i
        for(int i = 0; i < n; ++i)
            hi[i] = {heroes[i],i};
        // sort by power of heroes asc
        sort(hi.begin(),hi.end(),[](const pair<int,int>& a, const pair<int,int>& b){
            return a.first < b.first;
        });

        long long sum = 0LL;
        int j = -1; // index in mc
        for(int i = 0; i < n; ++i) {
            // advance in monsters up to the last monster
            // that can be defeated by the current hero
            while( j+1 < m && mc[j+1].first <= hi[i].first )
                sum += mc[++j].second;
            ans[hi[i].second] = sum;
        }

        return ans;
    }
};
