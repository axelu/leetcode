
// 2363. Merge Similar Items
// https://leetcode.com/problems/merge-similar-items/


class Solution {
public:
    vector<vector<int>> mergeSimilarItems(vector<vector<int>>& items1, vector<vector<int>>& items2) {
        int sum[1001];memset(sum,0,sizeof sum);
        for(auto& v: items1)
            sum[v[0]] += v[1];
        for(auto& v: items2)
            sum[v[0]] += v[1];

        vector<vector<int>> ans;
        for(int i = 1; i <= 1000; ++i)
            if( sum[i] != 0 )
                ans.push_back({i,sum[i]});

        return ans;
    }
};
