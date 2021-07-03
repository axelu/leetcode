
// 269. Alien Dictionary
// https://leetcode.com/problems/alien-dictionary/





class Solution {
private:

    void dfs(unordered_map<char,vector<char>>& g, char u,
             unordered_set<char>& seen, stack<char>& stck) {

        seen.insert(u);

        char v;
        for(int i = 0; i < g[u].size(); ++i) {
            v = g[u][i];
            if( !seen.count(v) ) dfs(g,v,seen,stck);
        }

        // push vertex onto stack
        // parents pushed onto stack after children
        stck.push(u);
    }


public:
    string alienOrder(vector<string>& words) {
        int n = words.size();


        // adjacency list
        unordered_map<char,vector<char>> g; // directed graph
        // add a node for every unique letter so that also nodes with no edges are in our graph
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < words[i].size(); ++j)
                g[words[i][j]] = {};


        // create an edge [chari,charj] from the sorted words
        unordered_set<string> edgelist; // uniqueness of edge
        string t;
        for(int i = 0; i < n-1; ++i) {
            for(int j = i+1; j < n; ++j) {
                int m = min(words[i].size(),words[j].size());
                int k = 0;
                for(; k < m; ++k) {
                    if( words[i][k] != words[j][k] ) {
                        t = "";
                        t += words[i][k];
                        t += words[j][k];
                        if( !edgelist.count(t) ) {
                            edgelist.insert(t);
                            g[words[i][k]].push_back(words[j][k]);
                        }
                        break;
                    }
                }
                if( k == m ) {
                    // we did not have a difference up to the word of smaller length
                    // From the problem description:
                    // "If the first min(s.length, t.length) letters are the same,
                    //  then s is smaller if and only if s.length < t.length."
                    if( words[i].size() > words[j].size() )
                        return "";
                }
            }
        }

        char u,v;

        /*
        // debug - print adjacency list
        for(auto it = g.begin(); it != g.end(); ++it) {
            u = it->first;
            cout << u << ": ";
            for(int i = 0; i < g[u].size(); ++i) {
                v = g[u][i];
                cout << v << " ";
            }
            cout << endl;
        }
        */



        // DFS
        stack<char> stck; // visited vertices in topological order
        unordered_set<char> seen;
        for(auto it = g.begin(); it != g.end(); ++it) {
            u = it->first;
            if( !seen.count(u) ) dfs(g,u,seen,stck);
        }


        string r = ""; // letters in topological order
        unordered_map<char,int> pos;
        int idx = 0;
        while(!stck.empty()) {
            pos[stck.top()] = idx;
            r.push_back(stck.top());
            ++idx;
            stck.pop();
        }


        for(auto it = g.begin(); it != g.end(); ++it) {
            u = it->first;      // parent
            for(int i = 0; i < g[u].size(); ++i) {
                v = g[u][i];    // child
                // parent (u) idx must be lower than child (v) idx else cyclic
                if( pos[u] > pos[v] )
                    return "";
            }
        }

        return r;
    }
};
