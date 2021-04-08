
// 1059. All Paths from Source Lead to Destination
// https://leetcode.com/problems/all-paths-from-source-lead-to-destination/





class Solution {
private:
    bool hasCycle;
    bool hasDeadEnd;
    bool reachedDest;

    void go(int src, vector<int> t[], unordered_set<int>& path, int dest, int seen[]) {
        if( hasCycle || hasDeadEnd ) return;
        if( src == dest ) {
            reachedDest = true;
            return;
        }
        if( path.find(src) != path.end() ) {
            hasCycle = true;
            return;
        }
        if( t[src].empty() ) {
            hasDeadEnd = true;
            return;
        }
        if( seen[src] ) return;
        seen[src] = 1;
        path.insert(src);
        for(int i = 0; i < t[src].size(); ++i) {
            go(t[src][i],t,path,dest,seen);
            if( hasCycle ) return;
        }
        // back track
        path.erase(src);
    }

public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        int m = edges.size();
        if( n == 1 )
            return m == 0 ? true : false;

        vector<int> t[n];
        for(int i = 0; i < m; ++i)
            t[edges[i][0]].push_back(edges[i][1]);

        if( !t[destination].empty() ) return false; // dest has outgoing edge(s)
        if( destination == source   ) return true;
        if( t[source].empty()      ) return false; // source has no outgoing edge(s)

        hasCycle = false;
        hasDeadEnd = false;
        reachedDest = false;
        unordered_set<int> path;
        path.insert(source);
        int seen[n]; memset(seen,0,sizeof seen);

        for(int i = 0; i < t[source].size(); ++i)
            go(t[source][i],t,path,destination,seen);

        return !hasCycle && !hasDeadEnd && reachedDest;
    }
};
