
// 2479. Maximum XOR of Two Non-Overlapping Subtrees
// https://leetcode.com/problems/maximum-xor-of-two-non-overlapping-subtrees/



// Aug 8 2023 passes 38/39 test cases, 39th test case TLE 


class Solution {
private:
    bool is_ancestor(int a, int b, int parent[]) {
        // is node a an ancestor of node b?

        // chase node b to root, if we don't see a along the way,
        // then a is not an ancestor of b
        while( parent[b] != -1 ) {
            b = parent[b];
            if( b == a )
                return true;
        }

        return false;
    }

    long long dfs(vector<int> g[], vector<int>& values, int u, int src, int parent[], unordered_map<long long,vector<int>>& um) {
        parent[u] = src;
        long long ret = values[u];

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( parent[v] != -1 || v == 0 )
                continue;
            ret += dfs(g,values,v,u,parent,um);
        }
        um[ret].push_back(u);
        return ret;
    }

public:
    long long maxXor(int n, vector<vector<int>>& edges, vector<int>& values) {
        // tree rooted in node 0
        vector<int> g[n];
        for(auto& v: edges) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        int parent[n];memset(parent,-1,sizeof parent);
        unordered_map<long long,vector<int>> um; // sum, nodes at which sum occurs
        dfs(g,values,0,-1,parent,um);

        auto cmp = [](const pair<long long,long long>& a, const pair<long long,long long>& b){
            return (a.first ^ a.second) < (b.first ^ b.second);
        };
        priority_queue<pair<long long,long long>,vector<pair<long long,long long>>,decltype(cmp)> pq(cmp);
        for(auto ito = um.begin(); ito != um.end(); ++ito) {
            for(auto iti = next(ito); iti != um.end(); ++iti) {
                pq.push({ito->first,iti->first});
            }
        }

        while( !pq.empty() ) {
            long long suma = pq.top().first;
            long long sumb = pq.top().second;
            pq.pop();

            // figure out if any of the nodes at which suma and sumb occurs are at different subtrees
            // if node a is not an ancestor of node b and node b is not an ancestor of node a, we have a winner
            for(int i = 0; i < um[suma].size(); ++i) {
                int nodea = um[suma][i];
                for(int j = 0; j < um[sumb].size(); ++j) {
                    int nodeb = um[sumb][j];

                    // is node a an ancestor of node b?
                    // is node b an ancestor of node a?
                    if( !is_ancestor(nodea,nodeb,parent) && !is_ancestor(nodeb,nodea,parent) )
                        return suma ^ sumb;
                }
            }
        }

        return 0LL;
    }
};
