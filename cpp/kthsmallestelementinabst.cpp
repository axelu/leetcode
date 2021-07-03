
// 230. Kth Smallest Element in a BST (Binary Search Tree)
// https://leetcode.com/problems/kth-smallest-element-in-a-bst/




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
    // inorder traversal
    int kthSmallest(TreeNode* root, int k, int& cnt) {
        if( root == nullptr )
            return -1;

        int ret = kthSmallest(root->left,k,cnt);
        if( ret != -1 ) return ret;

        ++cnt;
        if( cnt == k ) return root->val;

        return kthSmallest(root->right,k,cnt);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        int cnt = 0;
        return kthSmallest(root,k,cnt);
    }
};
