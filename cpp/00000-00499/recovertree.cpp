
// 99. Recover Binary Search Tree
// https://leetcode.com/problems/recover-binary-search-tree/


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
    TreeNode* minParent;
    TreeNode* badNode1;
    TreeNode* badNode2;

    void explore(TreeNode* root) {
        // handle nullptr
        if( root == nullptr ) return;

        // left
        explore(root->left);

        if( minParent != nullptr && root->val < minParent->val ) {
            if( badNode1 == nullptr )
                badNode1 = minParent;
            if( badNode1 != nullptr )
                badNode2 = root;
        }

        minParent = root; // setting a minimum before going right
        // right
        explore(root->right);
    }
public:
    void recoverTree(TreeNode* root) {
        minParent = nullptr;
        badNode1 = nullptr;
        badNode2 = nullptr;

        explore(root);

        int t = badNode2->val;
        badNode2->val = badNode1->val;
        badNode1->val = t;
    }
};
