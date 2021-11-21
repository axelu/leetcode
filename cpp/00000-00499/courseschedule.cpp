
// 207. Course Schedule
// https://leetcode.com/problems/course-schedule/




class Solution {
private:
    vector<int> * pAl;
    int * pVisited;
    stack<int> stck;    // visited vertices in topologial sort

    void dfs(int u) {
        pVisited[u] = 1;  // mark as visited

        for(int c : pAl[u])
            if( pVisited[c] == 0 ) dfs(c);

        // push vertex onto stack
        // parents pushed onto stack after children
        stck.push(u);
    }

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // determine if graph is cyclic via topologial sort
        // student cannot finish if there is a cycle

        // adjacency list
        vector<int> al[numCourses];
        pAl = al;

        // prerequisites = edge list -> adjacency list
        auto n = prerequisites.size();
        for(int i = 0; i < n; ++i)
            al[prerequisites[i][1]].push_back(prerequisites[i][0]);

        // init visited
        int visited[numCourses];
        for(int i = 0; i < numCourses; ++i) visited[i] = 0;
        pVisited = visited;

        // dfs
        for(int i = 0; i < numCourses; ++i)
            if( visited[i] == 0 ) dfs(i);

        unordered_map<int,int> pos;
        int idx = 0;
        while(!stck.empty()) {
            pos[stck.top()] = idx;
            ++idx;
            stck.pop();
        }

        for(int i = 0; i < numCourses; ++i)
            for(int j : al[i]) {
                // parent (i) idx must be lower than child (j) idx else cyclic
                if( pos[i] > pos[j] )
                    return false;
            }

        return true;
    }
};
