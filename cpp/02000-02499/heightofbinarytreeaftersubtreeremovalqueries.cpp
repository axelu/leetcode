
// 2458. Height of Binary Tree After Subtree Removal Queries
// https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    int parent[100001];     // parent of node with val i
    int lft[100001];        // is left child
    int depth_lft[100001];  // depth of left subtree of node with val i
    int depth_rgt[100001];  // depth of right subtree of node with val i

    int dfs(TreeNode* tn, int src, int is_left) {
        // record parent
        parent[tn->val] = src;
        // record if we are a left child
        lft[tn->val] = is_left;

        depth_lft[tn->val] = 0;
        if( tn->left != nullptr )
            depth_lft[tn->val] = dfs(tn->left, tn->val, 1);

        depth_rgt[tn->val] = 0;
        if( tn->right != nullptr )
            depth_rgt[tn->val] = dfs(tn->right, tn->val, 0);

        return max(depth_lft[tn->val],depth_rgt[tn->val]) + 1;
    }

public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        dfs(root,-1,-1);

        int m = queries.size();
        vector<int> ans(m);
        for(int i = 0; i < m; ++i) {

            // we are removing node with val queries[i]
            int nd = queries[i];
            // cout << nd << " ";

            // walk to the root
            int t = 0;
            while( parent[nd] != -1 ) {
                int is_left_child = lft[nd];

                // if we are equal or less than what the other child contributes,
                // we can exit and return the max depth seen at the root
                // but if we are removing the subtree that contributed the max depth
                // we need to keep track of the max depth the other child contributes
                // on the way to root

                // cout << parent[nd] << " ";
                nd = parent[nd];

                int _depth_lft, _depth_rgt;
                if( is_left_child ) {
                    _depth_lft = t;
                    _depth_rgt = depth_rgt[nd];
                } else {
                    _depth_lft = depth_lft[nd];
                    _depth_rgt = t;
                }

                t = max(_depth_lft, _depth_rgt) + 1;
            }
            // cout << endl;
            ans[i] = t - 1; // don't add one from the root
        }

        return ans;
    }
};
