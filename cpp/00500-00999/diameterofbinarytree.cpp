
// 543. Diameter of Binary Tree
// https://leetcode.com/problems/diameter-of-binary-tree/

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
    int diameterOfBinaryTree(TreeNode* root) {
        d = 0;

        _walk(root);
        return d;
    }
private:
    int d;

    int _walk(TreeNode* root) {
        if( root == nullptr ) return 0;

        int l = _walk(root->left);
        int r = _walk(root->right);

        d = max(d, l + r);

        return max(l, r) + 1;
    }
};
