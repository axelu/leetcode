
// 94. Binary Tree Inorder Traversal
// https://leetcode.com/problems/binary-tree-inorder-traversal/


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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> r;
        inorderTraversal(root, &r);
        return r;
    }
private:
    void inorderTraversal(TreeNode* root, vector<int>* v) {
        if( root == nullptr ) return;

        inorderTraversal(root->left, v);
        v->push_back(root->val);
        inorderTraversal(root->right, v);
    }
};
