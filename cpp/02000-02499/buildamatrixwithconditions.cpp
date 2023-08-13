
// 2392. Build a Matrix With Conditions
// https://leetcode.com/problems/build-a-matrix-with-conditions/





class Solution {
private:
    // debug
    void printVector(vector<int>& v) {
        for(int x: v)
            cout << x << " ";
        cout << endl;
    }

    // debug
    void print2DVector(vector<vector<int>>& v2d) {
        for(auto &v : v2d)
            printVector(v);
    }

    void dfs(vector<int> g[], int u, int seen[], stack<int>& stck) {

        seen[u] = 1;

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( !seen[v] )
                dfs(g,v,seen,stck);
        }

        // push vertex onto stack
        // parents pushed onto stack after children
        stck.push(u);
    }

    bool has_cycle(vector<int> g[], stack<int>& stck, vector<int>& to) {
        // to will be filled with the nodes in topological order
        unordered_map<int, int> pos;
        int i = 0;
        int n = stck.size();
        while( !stck.empty() ) {
            to.push_back(stck.top());
            pos[stck.top()] = i;
            ++i;
            stck.pop();
        }

        for(int u = 0; u < n; ++u) {
            for(auto v : g[u]) {
                // if parent vertex does not appear first
                if( pos[u] > pos[v] ) {
                    // the we have a cycle exists
                    return true;
                }
            }
        }

        return false;
    }

    vector<int> solve(int k, vector<vector<int>> conditions) {
        // topological sort cycle detection

        // build a compare matrix to detect contradicting conditions
        // ordinal: [a][b] = -1 -> a < b; [a][b] = 0 -> a == b; [a][b] = 1 -> a > b;
        vector<vector<int>> cmp(k+1,vector<int>(k+1,0));

        vector<int> g[k+1];
        for(auto& condition: conditions) {
            int u = condition[0];
            int v = condition[1];
            // u < v aka u comes before v
            if( cmp[u][v] == 1 )
                return {};
            cmp[u][v] = -1;
            cmp[v][u] = 1;
            g[v].push_back(u);
        }

        // topological sort
        stack<int> stck; // visited vertices in topological order
        int seen[k+1];memset(seen,0,sizeof seen);
        for(int u = 1; u <= k; ++u)
            if( !seen[u] )
                dfs(g,u,seen,stck);

        vector<int> to; // values in topological order
        bool is_cyclic = has_cycle(g,stck,to);
        if( is_cyclic )
            return {};
        return to;
    }

public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<int> rows = solve(k,rowConditions);
        if( rows.empty() )
            return {};
        vector<int> cols = solve(k,colConditions);
        if( cols.empty() )
            return {};

        reverse(rows.begin(),rows.end());
        reverse(cols.begin(),cols.end());
        unordered_map<int,int> coldic;
        for(int i = 0; i < k; ++i)
            coldic.insert({cols[i],i});

        vector<vector<int>> ans(k,vector<int>(k,0));

        for(int i = 0; i < k; ++i) {            // row
            int val = rows[i];                  // val
            int j = coldic.find(val)->second;   // col
            ans[i][j] = val;
        }

        return ans;
    }
};
