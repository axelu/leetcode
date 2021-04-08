
// Flatten Binary Tree to Linked List
// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/



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
    void flatten(TreeNode* root) {
        if( root == nullptr ) return;
        _walk(root);
        for(auto it = ft.rbegin(); it != ft.rend(); ++it) {
            if( it - ft.rbegin() == 0 ) {
                (*it)->right = nullptr;
                (*it)->left = nullptr;
                continue;
            }
            (*it)->right = *(it-1);
            (*it)->left = nullptr;
        }
    }
private:
    vector<TreeNode*> ft;

    void _walk(TreeNode* root) {
        if( root == nullptr ) return;

        ft.push_back(root);

        _walk(root->left);
        _walk(root->right);
    }
};
