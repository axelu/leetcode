
// 2331. Evaluate Boolean Binary Tree
// https://leetcode.com/problems/evaluate-boolean-binary-tree/



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
    bool evaluateTree(TreeNode* root) {
        // every node has either zero or two children
        if( root->left == nullptr ) // we are at a leaf
            return root->val;

        bool l = evaluateTree(root->left);
        bool r = evaluateTree(root->right);

        if( root->val == 2 )
            return l || r;
        return l && r;
    }
};
