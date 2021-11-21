
// 1743. Restore the Array From Adjacent Pairs
// https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/





class Solution {
private:
    bool dfs(unordered_map<int,pair<int,vector<int>>>& G, int u, int n, int step,
             unordered_set<int>& seen, vector<int>& ans) {

        ans.push_back(u);
        ++step;
        if( step == n )
            return true;

        seen.insert(u);

        vector<int> * pNeighbors = &G.find(u)->second.second;
        int v;
        for(int i = 0; i < pNeighbors->size(); ++i) {
            v = (*pNeighbors)[i];
            if( !seen.count(v) )
                if( dfs(G,v,n,step,seen,ans) )
                    return true;
        }

        // backtrack
        ans.pop_back();
        seen.erase(u);
        return false;
    }

public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        // undirected graph
        unordered_map<int,pair<int,vector<int>>> G;

        int n = adjacentPairs.size() + 1;
        int u,v;
        pair<unordered_map<int,pair<int,vector<int>>>::iterator,bool> p;
        for(int i = 0; i < n-1; ++i) {
            u = adjacentPairs[i][0];
            v = adjacentPairs[i][1];

            p = G.insert({u,{1,{v}}});
            if( !p.second ) {
                ++p.first->second.first;
                p.first->second.second.push_back(v);
            }
            p = G.insert({v,{1,{u}}});
            if( !p.second ) {
                ++p.first->second.first;
                p.first->second.second.push_back(u);
            }
        }

        // find root aka our 1st element of array
        int root;
        for(auto it = G.begin(); it != G.end(); ++it)
            if( it->second.first == 1 ) {
                root = it->first;
                break;
            }

        vector<int> ans;
        unordered_set<int> seen;
        dfs(G,root,n,0,seen,ans);

        return ans;
    }
};
