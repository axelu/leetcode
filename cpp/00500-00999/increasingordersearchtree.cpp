
// 897. Increasing Order Search Tree
// https://leetcode.com/problems/increasing-order-search-tree/
// day 3 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/569/week-1-december-1st-december-7th/3553/


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
    TreeNode* cur;
    void inorder(TreeNode* node) {
        if( node == nullptr ) return;
        inorder(node->left);
        node->left = nullptr;
        cur->right = node;
        cur = node;
        inorder(node->right);
    }
public:
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode* tn = new TreeNode(0);
        cur = tn;
        inorder(root);
        return tn->right;
    }
};
