
// 563. Binary Tree Tilt
// https://leetcode.com/problems/binary-tree-tilt/

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
    int findTilt(TreeNode* root) {
        if( root == nullptr ) return 0;

        _walk(root);

        return _tilt;
    }
private:
    int _tilt = 0;

    int _walk(TreeNode* root) {
        if( root == nullptr ) return 0;

        int l = _walk(root->left);
        int r = _walk(root->right);

        _tilt += abs( l - r );

        return l + r + root->val;
    }
};
