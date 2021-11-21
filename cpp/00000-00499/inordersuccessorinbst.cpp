
// 285. Inorder Successor in BST
// https://leetcode.com/problems/inorder-successor-in-bst/
// BST Binary Search Tree



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    TreeNode* ans;

    TreeNode* inorderTraversal(TreeNode* root) {
        if( root == nullptr ) return nullptr;

        TreeNode* res = inorderTraversal(root->left);
        return res != nullptr ? res : root;
    }


    void search(TreeNode* root, int target) {
        if( root == nullptr ) return;

        if( root->val == target ) {
            // if we have a right child, the answer is the 1st element of an
            // inorder traversal starting at the right child
            if( root->right != nullptr ) ans = inorderTraversal(root->right);
        } else if( root->val > target ) {
            // target must lie in the left subtree
            // root maybe the smallest key greater than target
            ans = root;
            search(root->left,target);
        } else {
            // target must lie in the right subtree
            search(root->right,target);
        }
    }
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        // All Nodes will have unique values.
        int target = p->val;

        ans = nullptr;
        search(root,target);
        return ans;
    }
};
