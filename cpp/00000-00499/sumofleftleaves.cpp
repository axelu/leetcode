
// day 24 August 2020 challenge
// 404. Sum of Left Leaves
// https://leetcode.com/problems/sum-of-left-leaves

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
    int sumOfLeftLeaves(TreeNode* root) {
        if ( root == nullptr ) return 0;

        walk(root, false);
        return ls;
    }
private:
   int ls = 0;

    void walk(TreeNode* tn, bool l) {
        if( tn->left == nullptr && tn->right == nullptr ) {
            // at leaf node
            if ( l ) ls += tn->val;
            return;
        }

        if( tn->left != nullptr ) walk(tn->left, true);
        if( tn->right != nullptr ) walk(tn->right, false);
    }
};
