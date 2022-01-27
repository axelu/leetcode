
// 797. All Paths From Source to Target
// https://leetcode.com/problems/all-paths-from-source-to-target/


class Solution {
private:
    void dfs(vector<vector<int>>& graph, int idx, int target, vector<int>& path, vector<vector<int>>& ans) {
        path.push_back(idx);

        if( idx == target) {
            ans.push_back(path);
            path.pop_back(); // backtrack
            return;
        }

        for(int i = 0; i < graph[idx].size(); ++i) {
            dfs(graph,graph[idx][i],target,path,ans);
        }

        path.pop_back(); // backtrack
    }

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> ans;
        vector<int> path;
        dfs(graph,0,n-1,path,ans);
        return ans;
    }
};
