
// 847. Shortest Path Visiting All Nodes
// https://leetcode.com/problems/shortest-path-visiting-all-nodes/

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        // undirected connected graph of n nodes labeled from 0 to n - 1
        int n = graph.size(); // 1 <= n <= 12
        if( n == 1 )
            return 0;
        
        // BFS
        
        // we will store the visited nodes in a bit mask
        // a set bit indicates that we visited the node (rightmost bit = node 0)
        // the state is determined by the current node and the nodes already visited
        queue<array<int,2>> q;
        int seen[n][1<<n];memset(seen,0,sizeof seen);
        
        // push our source vertex into queue
        // we are starting from every vertex 0 to n-1
        int mask;
        for(int i = 0; i < n; ++i) {
            mask = 0 ^ (1 << i); // set the ith bit = mark our source vertex as visited
            q.push({i,mask});
            seen[i][mask] = 1;    // mark state as seen
        }
        
        
        int step = 0;
        int u,v,mask_new;
        while( !q.empty() ) {
            
            queue<array<int,2>> q_new;
            while( !q.empty() ) {
                u    = q.front()[0];
                mask = q.front()[1];
                q.pop();
                
                if( mask == (1<<n)-1 ) // all nodes visited
                    return step;
                
                for(int v : graph[u]) {
                    mask_new = mask | (1<<v);
                    
                    // have we been here before?
                    // must have been at an equal or earlier step
                    if( seen[v][mask_new] )
                        continue;
                    
                    seen[v][mask_new] = 1;
                    q_new.push({v,mask_new});
                }                    
            }
            ++step;
            q = q_new;
        }
        
        return -1; // satisfy compiler
    }
};
