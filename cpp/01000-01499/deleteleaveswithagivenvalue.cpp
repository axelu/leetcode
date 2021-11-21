
// 1325. Delete Leaves With a Given Value
// https://leetcode.com/problems/delete-leaves-with-a-given-value/





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
    // post order traversal
    void postorder(TreeNode* root, TreeNode* parent, int& target) {
        if( root == nullptr ) return;

        postorder(root->left,root,target);
        postorder(root->right,root,target);

        if( root->left == nullptr && root->right == nullptr && root->val == target) {
            // tell my parent
            if( parent != nullptr ) {
                if( parent->left == root ) parent->left = nullptr;
                else parent->right = nullptr;
            }
        }
    }
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        postorder(root,nullptr,target);
        return root->val == target && root->left == nullptr && root->right == nullptr ? nullptr : root;
    }
};
