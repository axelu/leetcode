
// 2497. Maximum Star Sum of a Graph
// https://leetcode.com/problems/maximum-star-sum-of-a-graph/




class Solution {
public:
    int maxStarSum(vector<int>& vals, vector<vector<int>>& edges, int k) {
        int n = vals.size();

        // collect neighbors
        vector<int> t[n]; // undirected graph
        for(auto& v: edges) {
            t[v[0]].push_back(v[1]);
            t[v[1]].push_back(v[0]);
        }

        int ans = INT_MIN;

        // process all nodes
        for(int u = 0; u < n; ++u) {

            int sum = 0; // max sum of neighbors, if we don't select any, we could have 0
            priority_queue<int,vector<int>,greater<int>> pq;
            for(int i = 0; i < t[u].size(); ++i) {
                int v = t[u][i];
                int v_val = vals[v];
                if( v_val > 0 ) {
                    sum += v_val;
                    pq.push(v_val);
                    if( pq.size() > k ) {
                        sum -= pq.top();
                        pq.pop();
                    }
                }
            }

            ans = max(ans, sum + vals[u]);
        }

        return ans;
    }
};
