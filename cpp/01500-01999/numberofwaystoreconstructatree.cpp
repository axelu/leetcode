
// 1719. Number Of Ways To Reconstruct A Tree
// https://leetcode.com/problems/number-of-ways-to-reconstruct-a-tree/



class Solution {
private:
    int cnt[501];                     // nbr of appearances of each node
    int related[501][501];            // quick lookup if pair of node exists
    unordered_map<int,vector<int>> g; // not a graph, but 'skip adjacency' list
    int seen[501];

    int dfs(int u, vector<int>& path) {
        // returns 0 if we cannot built a tree rooted in u
        // returns 1 if we can build one tree rooted in u
        // returns 2 if we can build more than one tree rooted in u

        // cout << "dfs u " << u << endl;

        if( seen[u] ) // avoid a loop
            return 1;

        seen[u] = 1;

        // our current node u needs to be related to all nodes in path
        for(int node : path)
            if( !related[node][u] )
                return 0;

        int ret = 1;

        // add the current node u to path
        path.push_back(u);
        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];

            int t = dfs(v,path);
            if( t == 0 )
                return 0;

            // if we stumble on connected pair with same count,
            // we could swap those nodes and with that build
            // two different trees
            if( t == 2 || cnt[u] == cnt[v] )
                ret = 2;
        }
        // backtrack
        path.pop_back();

        return ret;
    }

public:
    int checkWays(vector<vector<int>>& pairs) {
        // constraints from from the problem description:
        //     1 <= pairs.length <= 10^5
        //     1 <= xi < yi <= 500
        //     a pair [x,y] exists if x is an ancestor of y or y is an ancestor of x

        // insight:
        //     a tree has a root
        //     a root is a node that all other nodes are descendents from
        //     respectively a root is an ancestor of all nodes
        //     so a root needs to be mentioned n-1 times (n == nbr of nodes)
        //     Note: in this problem there could be more than one 'root',
        //           that could be swapped,
        //           but there has to be at least one!
        //     hence a root is a node that exist in all pairs given
        //     also, nbr of mentions from root to leaves descreases
        //     a leave has no descendants

        memset(cnt,0,sizeof cnt);
        memset(related,0,sizeof related);

        for(auto& v : pairs) {
            // v[0] -> v[1]
            g[v[0]].push_back(v[1]);
            ++cnt[v[0]];
            // v[1] -> v[0]
            g[v[1]].push_back(v[0]);
            ++cnt[v[1]];
            // record the pair
            related[v[0]][v[1]] = 1;
            related[v[1]][v[0]] = 1;
        }

        int n = g.size(); // number of nodes
        int root = -1;
        for(auto it = g.begin(); it != g.end(); ++it) {
            if( cnt[it->first] == n-1 ) {
                // found a root
                root = it->first;
            }

            // based on insight that nbr of mentions from root to leaves descreases
            // and we plan a DFS, sort our 'skip adjacent' nodes by their mentions desc
            sort(it->second.begin(),it->second.end(),[cnt = cnt] (int a, int b) {
                return cnt[a] > cnt[b];
            });
        }

        if( root == -1 )
            return 0;

        // DFS
        vector<int> path;
        memset(seen,0,sizeof seen);
        return dfs(root,path);
    }
};
