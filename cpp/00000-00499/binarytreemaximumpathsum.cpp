
// 124. Binary Tree Maximum Path Sum
// https://leetcode.com/problems/binary-tree-maximum-path-sum/



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
    int ans;

    int dfs(TreeNode* root) {
        // compare me + right subtree and + left subtree to ans
        // return upwards the max of either me plus my left or me plus right subtree

        if( nullptr == root ) return 0;

        int l = max(0,dfs(root->left));  // not going left is an option
        int r = max(0,dfs(root->right)); // not going right is an option

        ans = max({ans,root->val+l+r});
        return max(root->val+l,root->val+r);
    }


public:
    int maxPathSum(TreeNode* root) {
        ans = -30000001;
        dfs(root);
        return ans;
    }
};
