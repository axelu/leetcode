
// 2685. Count the Number of Complete Components
// https://leetcode.com/problems/count-the-number-of-complete-components/



class Solution {
private:
    void dfs(int u, unordered_set<int> t[], int seen[], vector<int>& cc) {
        if( seen[u] )
            return;

        seen[u] = 1;
        cc.push_back(u);

        for(auto it = t[u].begin(); it != t[u].end(); ++it)
            dfs(*it,t,seen,cc);

    }

public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        if( n == 1 )
            return 1;

        unordered_set<int> t[n];
        for(int i = 0; i < edges.size(); ++i) {
            t[edges[i][0]].insert(edges[i][1]);
            t[edges[i][1]].insert(edges[i][0]);
        }
        int seen[n]; memset(seen,0,sizeof seen);

        int ans = 0;
        for(int i = 0; i < n; ++i)
            if( !seen[i] ) {
                vector<int> cc; // nodes in our connected component (cc)
                dfs(i,t,seen,cc);

                int cc_sz = cc.size(); // nbr nodes in cc
                // if there are nbr_nodes in our cc
                // each node needs to have nbr_nodes - 1 neighbors
                bool is_complete = true;
                for(int j = 0; j < cc_sz; ++j)
                    if( t[cc[j]].size() != cc_sz - 1 ) {
                        is_complete = false;
                        break;
                    }

                if( is_complete )
                    ++ans;
            }

        return ans;
    }
};
