
// 2374. Node With Highest Edge Score
// https://leetcode.com/problems/node-with-highest-edge-score/


class Solution {
public:
    int edgeScore(vector<int>& edges) {
        int n = edges.size();

        long edge_score[n];memset(edge_score,0,sizeof edge_score);

        for(int u = 0; u < n; ++u) {
            int v = edges[u];

            // there is an edge from u to v
            edge_score[v] += u;
        }

        int u = -1;
        long mx_edge_score = -1;
        for(int i = 0; i < n; ++i)
            if( edge_score[i] > mx_edge_score ) {
                u = i;
                mx_edge_score = edge_score[i];
            }

       return u;
    }
};
