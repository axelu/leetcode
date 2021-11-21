
// 310. Minimum Height Trees
// day 4 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/564/week-1-november-1st-november-7th/3519/
// https://leetcode.com/problems/minimum-height-trees/


class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // base cases
        if (n < 2) {
            vector<int> r;
            for(int i = 0; i < n; i++)
                r.push_back(i);
            return r;
        }

        // edges -> adjacency list
        vector<int> al[n];
        auto N = edges.size();
        for(int i = 0; i < N; ++i) {
            al[edges[i][0]].push_back(edges[i][1]);
            al[edges[i][1]].push_back(edges[i][0]);
        }

        vector<int> leaves = {};

        // first layer of leaves
        for(int i = 0; i < n; ++i)
            if( al[i].size() == 1 ) leaves.push_back(i);

        // trim leaves until reaching the centroids
        int remainingNodes = n;
        while(remainingNodes > 2) {
            remainingNodes -= leaves.size();
            vector<int> newLeaves = {};

            // remove current leaves along with the edges
            for(int leaf : leaves) {
                for(int adjacentNode : al[leaf]) {

                    auto f = find(begin(al[adjacentNode]),end(al[adjacentNode]),leaf);
                    al[adjacentNode].erase(f);

                    if( al[adjacentNode].size() == 1 )
                        newLeaves.push_back(adjacentNode);
                }
            }

            leaves = newLeaves;
        }

        return leaves;
    }
};
