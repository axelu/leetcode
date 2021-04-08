
// Balanced Binary Tree
// https://leetcode.com/problems/balanced-binary-tree/

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
    bool isBalanced(TreeNode* root) {
        if ( root == nullptr ) return true;
        if ( root->left == nullptr && root->right == nullptr ) return true;

        balanced = true;

        int l = explore(root->left);
        int r = explore(root->right);

        return ( abs(l-r) > 1 || !balanced ) ? false : true;
    }
private:
    bool balanced;
    int explore(TreeNode* root) {

        if (root == nullptr) return 0;

        int l = explore(root->left);
        int r = explore(root->right);

        if ( abs(l-r) > 1 ) balanced = false;

        return max(l,r) + 1;
    }
};
