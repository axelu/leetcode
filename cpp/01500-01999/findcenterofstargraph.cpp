
// 1791. Find Center of Star Graph
// https://leetcode.com/problems/find-center-of-star-graph/




class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        int p1 = edges[0][0];
        int p2 = edges[0][1];
        int p3 = edges[1][0];
        int p4 = edges[1][1];

        if( p1 == p3 ) return p1;
        if( p1 == p4 ) return p1;
        return p2;
    }
};
