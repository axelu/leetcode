
// 1136. Parallel Courses
// https://leetcode.com/problems/parallel-courses/
// day 29 March 2021 bonus challenge
// https://leetcode.com/explore/challenge/card/march-leetcoding-challenge-2021/592/week-5-march-29th-march-31st/3688/




class Solution {
private:
    int ans;
    int hasCycle;

    int dfs(vector<int> g[], int idx, int visited[], int path[], int mem[]) {

        if( hasCycle ) return -1;
        if( path[idx] ) {
            hasCycle = true;
            return -1;
        }

        if( mem[idx] != -1 ) return mem[idx];
        visited[idx] = 1;
        path[idx] = 1;

        int res = 0;
        for(int i = 0; i < g[idx].size(); ++ i) {
            res = max(res,dfs(g,g[idx][i],visited,path,mem));
            if( hasCycle ) return -1;
        }

        path[idx] = 0; // backtrack
        ans = max(ans,res+1);
        return mem[idx] = res+1;
    }
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        // graph with n vertices from 1 to n, 1 <= n <= 5000
        // graph is a directed acyclic graph (DAG) with one or more connected components
        // if any connected component has a cycle, it cannot be completed (return -1)

        vector<int> g[n+1];
        for(int i = 0; i < relations.size(); ++i)
            g[relations[i][0]].push_back(relations[i][1]);

        int visited[n+1];
        int path[n+1];     // used to detect cycle
        int mem[n+1];
        for(int i = 1; i <= n; ++i) {
            visited[i] = 0;
            path[i] = 0;
            mem[i] = -1;
        }

        ans = 1;
        hasCycle = false;
        for(int i = 1; i <= n; ++i) {
            if( !visited[i] )
                dfs(g,i,visited,path,mem);
            if( hasCycle ) return -1;
        }
        return ans;
    }
};
