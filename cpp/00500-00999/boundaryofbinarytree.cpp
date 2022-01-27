
// 545. Boundary of Binary Tree
// https://leetcode.com/problems/boundary-of-binary-tree/




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
    void leftBoundary(TreeNode* root, vector<int>& ans) {
        if( root == nullptr ) return;

        if( root->left == nullptr && root->right == nullptr ) {
            return;
        } else {
            ans.push_back(root->val);
            if( root->left != nullptr ) {
                leftBoundary(root->left,ans);
            } else {
                leftBoundary(root->right,ans);
            }
        }
    }

    void leaves(TreeNode* root, vector<int>& ans) {
        if( root == nullptr ) return;

        if( root->left == nullptr && root->right == nullptr )
            ans.push_back(root->val);

        leaves(root->left,ans);
        leaves(root->right,ans);
    }

    void rightBoundary(TreeNode* root, vector<int>& ans) {
        if( root == nullptr ) return;

        if( root->left == nullptr && root->right == nullptr ) {
            return;
        } else {
            if( root->right != nullptr ) {
                rightBoundary(root->right,ans);
            } else {
                rightBoundary(root->left,ans);
            }
        }
        ans.push_back(root->val);
    }

public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        vector<int> ans;
        if( root == nullptr ) return ans;
        ans.push_back(root->val);
        leftBoundary(root->left,ans);
        leaves(root->left,ans);
        leaves(root->right,ans);
        rightBoundary(root->right,ans);
        return ans;
    }
};
