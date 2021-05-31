

// 1214. Two Sum BSTs
// https://leetcode.com/problems/two-sum-bsts/




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
    TreeNode* search(TreeNode* root, int target) {
        if( root == nullptr || root->val == target )
            return root;

        if( root->val < target )
            return search(root->right,target);

        return search(root->left,target);
    }

    // preorder traversal
    bool tt1(TreeNode* root1, TreeNode* root2, int target) {
        if( root1 == nullptr ) return false;

        if( search(root2,target-root1->val) ) return true;
        if( tt1(root1->left,root2,target) ) return true;
        return tt1(root1->right,root2,target);
    }

public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        if( tt1(root1,root2,target) ) return true;
        return tt1(root2,root1,target);
    }
};
