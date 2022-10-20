
// 675. Cut Off Trees for Golf Event
// https://leetcode.com/problems/cut-off-trees-for-golf-event/


class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        int m = forest.size();      // rows
        int n = forest[0].size();   // cols
        
        // get all trees and build graph
        map<int,int> trees; // height,idx
        vector<int> g[m*n]; // bidirectional graph
        // directions   R  D  L  U
        int dirR[4] = { 0, 1, 0,-1};
        int dirC[4] = { 1, 0,-1, 0};
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j) {
                int u = i*n+j;
                if( forest[i][j] > 1 ) 
                    trees[forest[i][j]] = u;
                if( forest[i][j] > 0 ) {
                    for(int k = 0; k < 4; ++k) {
                        int i_new = i + dirR[k];
                        if( i_new < 0 || i_new == m )
                            continue;

                        int j_new = j + dirC[k];
                        if( j_new < 0 || j_new == n )
                            continue;

                        if( forest[i_new][j_new] == 0 )
                            continue;
                    
                        int v = i_new*n+j_new;
                        g[u].push_back(v);
                    }
                }
            }
        
        int ans = 0;
        
        // BFS
        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            return a[0] > b[0];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);
        
        int seen[m*n];memset(seen,0,sizeof seen);
        
        pq.push({0,0});
        seen[0] = 1;
        
        auto t = trees.begin();
        
        while( !pq.empty() ) {
            auto[steps,u] = pq.top();
            pq.pop();
            
            if( u == t->second ) {
                ans += steps;
                ++t;                        // next tree to reach
                if( t == trees.end() )      // no more trees reach, we are done
                    return ans;
                memset(seen,0,sizeof seen); // reset seen
                while ( !pq.empty() )       // clear queue
                    pq.pop();
                steps = 0;                  // reset steps, current cell is new start
            }
            
            for(int v: g[u]) {
                if( seen[v] )
                    continue;
                
                seen[v] = 1;
                pq.push({steps+1,v});
            }
        }
        
        return -1;
    }
};
