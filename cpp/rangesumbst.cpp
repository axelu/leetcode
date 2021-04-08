
// 938. Range Sum of BST
// https://leetcode.com/problems/range-sum-of-bst/
// day 15 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/566/week-3-november-15th-november-21st/3532/



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
    int r;
    void dfs(TreeNode* root, int& low, int& high) {
        if( root == nullptr ) return;

        if( root->val >= low && root->val <= high ) r += root->val;

        if( root->val >= low ) dfs(root->left,low,high);
        if( root->val <= high) dfs(root->right,low,high);
    }
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        r = 0;
        dfs(root,low,high);
        return r;
    }
};
