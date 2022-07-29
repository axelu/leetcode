
// 1591. Strange Printer II
// https://leetcode.com/problems/strange-printer-ii/



class Solution {
private:
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

    bool has_cycle(vector<int> g[], stack<int>& stck) {
        unordered_map<int, int> pos;
        int i = 0;
        int n = stck.size();
        while( !stck.empty() ) {
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

public:
    bool isPrintable(vector<vector<int>>& targetGrid) {
        // get the unique colours in the grid and for each
        // color record the xmin,ymin,xmax,ymax
        // each color represents a node
        // we create a directed graph
        // there is an edge between color a and color b
        // if color b has a cell 'inside' color a
        // if we then to a topological sort and
        // see if there is a cycle, the answer is false

        struct T {
            int id;
            int xmin;
            int ymin;
            int xmax;
            int ymax;
            T(int id, int x, int y) : id(id), xmin(x), ymin(y), xmax(x), ymax(y) {}
        };

        int id = 0;
        unordered_map<int,T*> um;
        for(int i = 0; i < targetGrid.size(); ++i)          // row
            for(int j = 0; j < targetGrid[0].size(); ++j) { // col
                // cout << "i " << i << " j " << j << endl;
                T * t = um[targetGrid[i][j]];
                if( t == nullptr ) {
                    um[targetGrid[i][j]] = new T(id,i,j);
                    ++id;
                } else {
                    t->xmin = min(t->xmin,i);
                    t->ymin = min(t->ymin,j);
                    t->xmax = max(t->xmax,i);
                    t->ymax = max(t->ymax,j);
                }
            }

        vector<int> g[um.size()]; // or g[id];

        for(auto ita = um.begin(); ita != um.end(); ++ita) {
            /*
            cout << ita->first << " ";
            cout << ita->second->id << " ";
            cout << ita->second->xmin << " ";
            cout << ita->second->ymin << " ";
            cout << ita->second->xmax << " ";
            cout << ita->second->ymax << " ";
            cout << endl;
            */

            for(auto itb = next(ita); itb != um.end(); ++itb) {
                int xmax = min(ita->second->xmax,itb->second->xmax);
                int xmin = max(ita->second->xmin,itb->second->xmin);
                int ymax = min(ita->second->ymax,itb->second->ymax);
                int ymin = max(ita->second->ymin,itb->second->ymin);
                bool shows_a = false, shows_b = false;
                if( xmax - xmin >= 0 && ymax - ymin >= 0 ) {
                    // we have an overlap
                    // which of the two colors shows within the overlap determines
                    // the direction of our edge
                    // if both show we already know there is no solution
                    for(int i = xmin; i <= xmax; ++i) {
                        for(int j = ymin; j <= ymax; ++j) {
                            if( targetGrid[i][j] == ita->first )
                                shows_a = true;
                            else if( targetGrid[i][j] == itb->first )
                                shows_b = true;
                        }
                    }
                    if( shows_a && shows_b )
                        return false;
                    if( shows_a )
                        g[itb->second->id].push_back(ita->second->id);
                    else if( shows_b )
                        g[ita->second->id].push_back(itb->second->id);
                }
            }
        }

        // topological sort
        stack<int> stck; // visited vertices in topological order
        int seen[um.size()];memset(seen,0,sizeof seen);
        for(int u = 0; u < um.size(); ++u)
            if( !seen[u] )
                dfs(g,u,seen,stck);

        // do we have a cycle?
        return !has_cycle(g,stck);
    }
};
