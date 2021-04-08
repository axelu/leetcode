
// Binary Tree Pruning
// https://leetcode.com/problems/binary-tree-pruning/


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
    TreeNode* pruneTree(TreeNode* root) {
        int a = _walk(root);

        if( root->left == nullptr && root->right == nullptr && root->val == 0 ) {
            return nullptr;
        } else {
            return root;
        }
    }
private:
    int _walk(TreeNode* root) {
        if( root == nullptr ) return 0;

        int l = _walk(root->left);
        int r = _walk(root->right);

        if( l == 0 && root->left != nullptr ) root->left = nullptr;
        if( r == 0 && root->right != nullptr ) root->right = nullptr;

        return root->val + l + r;
    }
};
