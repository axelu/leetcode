
// 2445. Number of Nodes With Value One
// https://leetcode.com/problems/number-of-nodes-with-value-one/




class Solution {
private:
    int N;
    int * nodes;

    int dfs(int nd, int cnt) {
        if( nd > N )
            return 0;

        int ret = 0;

        cnt = cnt + nodes[nd];
        if( cnt % 2 )
            ret = 1;;

        // go left
        ret += dfs(nd*2,cnt);

        // go right
        ret += dfs(nd*2+1,cnt);

        return ret;
    }

public:
    int numberOfNodes(int n, vector<int>& queries) {
        N = n;

        // count the number of times how often a node and its subtree was flipped
        int _nodes[n+1]; memset(_nodes,0,sizeof _nodes); nodes = _nodes;
        for(int nd: queries)
            ++nodes[nd];

        return dfs(1,0);
    }
};
