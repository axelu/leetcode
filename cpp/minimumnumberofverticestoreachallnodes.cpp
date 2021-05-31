
// 1557. Minimum Number of Vertices to Reach All Nodes
// https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/




class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        // counting incoming edges for each node
        int cnt[n]; memset(cnt,0,sizeof cnt);
        int i;
        for(i = 0; i < edges.size(); ++i)
            ++cnt[edges[i][1]];

        vector<int> ans;
        for( i = 0; i < n; ++i)
            if( cnt[i] == 0 ) ans.push_back(i);

        return ans;
    }
};
