
// Distribute Coins in Binary Tree
// https://leetcode.com/problems/distribute-coins-in-binary-tree/



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
    int distributeCoins(TreeNode* root) {
        _walk(root);
        return moves;
    }
private:
    int moves = 0;

    int _walk(TreeNode* root) {
        if( root == nullptr ) return 0;

        int l = _walk(root->left);
        int r = _walk(root->right);

        moves += abs(l) + abs(r);

        return root->val + l + r -1;
    }
};
