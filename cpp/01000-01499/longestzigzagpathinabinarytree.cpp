
// 1372. Longest ZigZag Path in a Binary Tree
// https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/


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
    int longestZigZag(TreeNode* root) {
        _walk(root, left, 0);
        return l;
    }
private:
    enum direction {left, right};
    int l = 0;
    int marker = 0;

    void _walk(TreeNode* root, direction d, int y) {
        if( root == nullptr ) return;

        l = max(l, marker - y);

        if( d == left ) {
            _walk(root->left, right, y - 1);
        } else {
            _walk(root->right, left, y - 1);
        }
        marker = y;
        if( d == left ) {
            _walk(root->right, left, y - 1);
        } else {
            _walk(root->left, right, y - 1);
        }
    }
};
