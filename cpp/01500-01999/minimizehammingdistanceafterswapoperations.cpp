
// 1722. Minimize Hamming Distance After Swap Operations
// https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/



class Solution {
private:



    void dfs(vector<int> G[], vector<int>& source, int u, int seen[], unordered_map<int,int>& um, queue<int>& indicies) {
        seen[u] = 1;
        indicies.push(u);
        auto p = um.insert({source[u],1});
        if( !p.second )
            ++p.first->second;

        int v;
        for(int i = 0; i < G[u].size(); ++i) {
            v = G[u][i];
            if( !seen[v] )
                dfs(G,source,v,seen,um,indicies);
        }
    }

public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size(); // source.size() == target.size()

        // base case - we cannot make any swaps
        if( allowedSwaps.size() == 0 ) {
            int t = 0;
            for(int i = 0; i < n; ++i)
                if( source[i] != target[i] )
                    ++t;
            return t;
        }

        vector<int> G[n]; // undirected graph
        for(int i = 0; i < allowedSwaps.size(); ++i) {
            G[allowedSwaps[i][0]].push_back(allowedSwaps[i][1]);
            G[allowedSwaps[i][1]].push_back(allowedSwaps[i][0]);
        }


        int ans = 0; // Hamming distance

        int seen[n];memset(seen,0,sizeof seen);
        unordered_map<int,int> um; // value,count
        queue<int> indicies;
        for(int i = 0; i < n; ++i) {
            if( !seen[i] ) {
                // collect all values and indicies for the current component
                dfs(G,source,i,seen,um,indicies);

                // get hamming distance for the current component
                int idx;
                while( !indicies.empty() ) {
                    idx = indicies.front();
                    indicies.pop();
                    auto f = um.find(target[idx]);
                    if( f == um.end() ) {
                        ++ans;
                    } else {
                        --f->second;
                        if( f->second == 0 )
                            um.erase(f);
                    }
                }
                um.clear();
            }
        }


        return ans;
    }
};
