
// Invert a Binary Tree
// https://leetcode.com/problems/invert-binary-tree/


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
public:
    TreeNode* invertTree(TreeNode* root) {
        if( root == nullptr ) return root;
        if( root->left == nullptr && root->right == nullptr ) return root;

        TreeNode *pRn = root->right;
        root->right = invertTree(root->left);
        root->left = invertTree(pRn);

        return root;
    }
};
