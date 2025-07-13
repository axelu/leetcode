
// 3543. Maximum Weighted K-Edge Path
// https://leetcode.com/problems/maximum-weighted-k-edge-path/


class Solution {
private:
    vector<array<int,2>> g[300];
    int k, t;

    int ans;

    // u 300 sum 600 steps 300 => 54,000,000 
    // 300 binary  100101100  9 digits
    // 600 binary 1001011000 10 digits

    unordered_set<int> seen;

    void rec(int u, int sum, int steps) {
        cout << "rec u " << u << " sum " << sum << " steps " << steps << endl;
        if( sum >= t )
            return;
        
        if( steps == k ) {
            ans = max(ans, sum);
            return;
        }

        int key = (u<<19) + (sum<<9) + steps;
        if( !seen.insert(key).second ) {
            cout << "hit" << endl;
            return;
        }

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i][0];
            int weight = g[u][i][1];
            rec(v, sum + weight, steps + 1);
        }

        return;
    }

public:
    int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
        // 1 <= n <= 300

        if( k == 0 )
            return 0;

        this->k = k;
        this->t = t;

        // Directed Acyclic Graph (DAG) n nodes labeled from 0 to n - 1
        for(auto& edge :edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            g[u].push_back({v, weight});
        }
        
        ans = 0;

        /*
        // brute force small constraint
        // consider every node as a starting point
        for(int u = 0; u < n; ++u) {
            cout << "starting at " << u << endl;
            rec(u, 0, 0);
        }
        */

        set<int> _cur[300]; set<int> * cur = _cur;

        set<int> _pre[300]; set<int> * pre = _pre;
        for(int u = 0; u < n; ++u)
            pre[u] = {0};

        for(int i = 0; i < k; ++i) {    // step

            for(int u = 0; u < n; ++u) {
                for(int j = 0; j < g[u].size(); ++j) {
                    int v = g[u][j][0];
                    int weight = g[u][j][1];
            
                    for(int dist : pre[u])
                        if( dist + weight < t ) 
                            cur[v].insert(dist + weight);
                }
            }
            // swap
            swap(cur, pre);
            for(int u = 0; u < n; ++u)
                cur[u].clear();
        }

        for(int u = 0; u < n; ++u) {
            if( !pre[u].empty() )
                ans = max(ans, *(pre[u].rbegin()));
        }

        return ans != 0 ? ans : -1;
    }
};


// passes 950/959 test cases as of 5/272025, then TLE

class Solution {
private:
    bool seen[300];
    vector<array<int,2>> g[300];
    int k, t;

    int ans;

    void rec(int u, int sum, int steps) {
        if( sum >= t )
            return;

        if( steps == k ) {
            ans = max(ans, sum);
            return;
        }

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i][0];
            int weight = g[u][i][1];
            rec(v, sum + weight, steps + 1);
        }

        return;
    }

public:
    int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
        // 1 <= n <= 300

        if( k == 0 )
            return 0;

        this->k = k;
        this->t = t;

        // Directed Acyclic Graph (DAG) n nodes labeled from 0 to n - 1
        for(auto& edge :edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            g[u].push_back({v, weight});
        }

        ans = 0;

        // brute force small constraint
        // consider every node as a starting point
        for(int u = 0; u < n; ++u)
            rec(u, 0, 0);

        return ans != 0 ? ans : -1;
    }
};
