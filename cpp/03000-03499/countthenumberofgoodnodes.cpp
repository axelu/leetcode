
// 3249. Count the Number of Good Nodes
// https://leetcode.com/problems/count-the-number-of-good-nodes/




class Solution {
private:
    int ans;

    int dfs(vector<int> t[], int u, int src) {
        // returns the number of nodes in the subtree rooted at u including u
        // determine if the current node u is a good node

        int ret = 1;

        // number of children
        int u_sz = u != 0 ? t[u].size() - 1 : t[u].size();

        if( u_sz == 0 ) {
            // we are at a leave
            // a leave is a good node
            ++ans;

        } else if( u_sz == 1 ) {
            // we have only 1 child, so we are a good node
            ++ans;
            for(int i = 0; i < t[u].size(); ++i) {
                int v = t[u][i];
                if( v == src )
                    continue;
                ret += dfs(t, v, u);
            }

        } else {
            // explore the first child
            int i = 0;
            int number_of_nodes_in_subtree_of_1st_child;
            for(; i < t[u].size(); ++i) {
                int v = t[u][i];
                if( v == src )
                    continue;
                number_of_nodes_in_subtree_of_1st_child = dfs(t, v, u);
                ret += number_of_nodes_in_subtree_of_1st_child;
                break;
            }
            // explore the remaining children
            ++i;
            bool is_good_node = true;
            for(; i < t[u].size(); ++i) {
                int v = t[u][i];
                if( v == src )
                    continue;
                int number_of_nodes_in_subtree_of_cur_child =  dfs(t, v, u);
                if( number_of_nodes_in_subtree_of_1st_child != number_of_nodes_in_subtree_of_cur_child )
                    is_good_node = false;
                ret += number_of_nodes_in_subtree_of_cur_child;
            }
            if( is_good_node )
                ++ans;
        }

        return ret;
    }

public:
    int countGoodNodes(vector<vector<int>>& edges) {
        // undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0
        int n = edges.size() + 1;
        vector<int> t[n];
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            t[u].push_back(v);
            t[v].push_back(u);
        }

        ans = 0;
        dfs(t, 0, -1);
        return ans;
    }
};
