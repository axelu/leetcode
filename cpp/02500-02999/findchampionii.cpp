
// 2924. Find Champion II
// https://leetcode.com/problems/find-champion-ii/




class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges) {
        // directed acyclic graph

        int indegree[n];memset(indegree,0,sizeof indegree);
        for(vector<int>& edge: edges)
            ++indegree[edge[1]];

        int cnt_indegree_zero = 0;
        int winner = -1;

        for(int i = 0; i < n; ++i) {
            if( indegree[i] == 0 && cnt_indegree_zero != 0 ) {
                return -1;
            } else if( indegree[i] == 0 ) {
                winner = i;
                ++cnt_indegree_zero;
            }
        }

        return winner;
    }
};
