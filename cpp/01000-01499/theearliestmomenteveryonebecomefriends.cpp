
// 1101. The Earliest Moment When Everyone Become Friends
// https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/





class Solution {
private:
    bool isAcquainted(vector<int> g[], int N, int src, int dest) {
        // returns true if there is a path from src to dest in g otherwise false

        // BFS shortest path
        int seen[N]; memset(seen,0,sizeof seen);

        queue<int> q;
        q.push(src);
        seen[src] = 1;
        int curr,i;
        while(!q.empty()) {
            curr = q.front();
            q.pop();
            for(i = 0; i < g[curr].size(); ++i) {
                if( g[curr][i] == dest ) return true;
                if( !seen[g[curr][i]] ) {
                    seen[g[curr][i]] = 1;
                    q.push(g[curr][i]);
                }
            }
        }
        return false;
    }

public:
    int earliestAcq(vector<vector<int>>& logs, int N) {
        int cc = N;       // initial nuber of connected components = number of nodes
        vector<int> g[N]; // bi-directional graph

        // sort the log items by timestamp ascending
        sort(logs.begin(),logs.end(),[](const vector<int>& a, const vector<int>& b){
           return a[0]<b[0];
        });

        int i;
        for(i = 0; i < logs.size(); ++i) {
            if( !isAcquainted(g,N,logs[i][1],logs[i][2]) ) --cc;
            if( cc == 1 ) break;
            g[logs[i][1]].push_back(logs[i][2]);
            g[logs[i][2]].push_back(logs[i][1]);
        }
        return cc == 1 ? logs[i][0] : -1;
    }
};
