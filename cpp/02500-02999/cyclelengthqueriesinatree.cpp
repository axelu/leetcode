
// 2509. Cycle Length Queries in a Tree
// https://leetcode.com/problems/cycle-length-queries-in-a-tree/



class Solution {
private:
    stack<int> path2root(int node) {
        stack<int> stck;
        stck.push(node);

        while( node > 1 ) {
            node /= 2;
            stck.push(node);
        }

        return stck;
    }

public:
    vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries) {
        // 2 <= n <= 30
        // complete binary tree with 2^n - 1 nodes
        // 2^n - 1 -> n = 30 -> 1073741823 nodes

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            stack<int> a = path2root(queries[i][0]);
            stack<int> b = path2root(queries[i][1]);

            int lvl_a = a.size(); // cout << "lvl_a " << lvl_a << endl;
            int lvl_b = b.size(); // cout << "lvl_b " << lvl_b << endl;

            // level of lowest common ancestor
            int lvl_lca = 0;
            while( !a.empty() && !b.empty() && a.top() == b.top() ) {
                ++lvl_lca;
                a.pop();
                b.pop();
            }
            // cout << "lvl_lca " << lvl_lca << endl;
            ans[i] = (lvl_a - lvl_lca) + (lvl_b - lvl_lca) + 1;

        }

        return ans;
    }
};
