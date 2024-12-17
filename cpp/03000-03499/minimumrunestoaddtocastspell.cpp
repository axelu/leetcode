
// 3383. Minimum Runes to Add to Cast Spell
// https://leetcode.com/problems/minimum-runes-to-add-to-cast-spell/





class Solution {
private:
    vector<bool> seen;

    void dfs(vector<vector<int>>& g, int u) {
        // cout << "dfs u " << u << endl;
        seen[u] = true;

        for(auto it = g[u].begin(); it != g[u].end(); ++it) {
            int v = *it;
            if( !seen[v] )
                dfs(g, v);
        }

        return;
    }

    void dfs(vector<vector<int>>& g, int u, stack<int>& stck) {
        seen[u] = true;

        for(auto it = g[u].begin(); it != g[u].end(); ++it) {
            int v = *it;
            if( !seen[v] )
                dfs(g, v, stck);
        }

        // push vertex onto stack
        // parents pushed onto stack after children
        stck.push(u);
    }

public:
    int minRunesToAdd(int n, vector<int>& crystals, vector<int>& flowFrom, vector<int>& flowTo) {
        // if there is a crystal in every focus point, then no edges need to be added
        int crystals_sz = crystals.size();
        if( crystals_sz == n )
            return 0;

        // idea
        //     do a DFS from every crystal keeping track of seen
        //     if we have unseen nodes left,
        //     those are either part of a disconnected component w/o a crystal OR
        //     those maybe connected, but the direction of the connection made them not
        //     reachable from a crystal
        //     we will start a topological sort for the remaining

        vector<vector<int>> g(n); // directed graph
        int runes_sz = flowFrom.size(); // flowFrom.size() == flowTo.size()
        for(int i = 0; i < runes_sz; ++i)
            g[flowFrom[i]].push_back(flowTo[i]);

        seen.assign(n,false);
        for(int i = 0; i < crystals_sz; ++i) {
            // cout << "starting dfs from crystal i " << i << " at " << crystals[i] << endl;
            if( !seen[crystals[i]] )
                dfs(g, crystals[i]);
        }

        // TODO we could know here already if we even need to go further
        // if there are no unseen nodes, then we are done -> ans = 0 no edges to add

        // topological sort of all unseen nodes
        stack<int> stck; // visited vertices in topological order
        for(int u = 0; u < n; ++u)
            if( !seen[u] )
                dfs(g, u, stck);

        // traverse in topological order
        if( stck.size() == 0 )
            return 0;

        int ans = 0;

        seen.assign(n,false); // reset seen
        while( !stck.empty() ) {
            int u = stck.top();
            stck.pop();
            if( !seen[u] ) {
                ++ans;
                dfs(g, u);
            }
        }

        return ans;
    }
};
