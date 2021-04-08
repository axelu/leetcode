
// 98. Validate Binary Search Tree
// https://leetcode.com/problems/validate-binary-search-tree/
// day 16 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/571/week-3-december-15th-december-21st/3568/



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
    bool dfs(TreeNode* root, long mx, long mn) {
        if( root == nullptr ) return true;

        if( (long)root->val >= mx || (long)root->val <= mn ) return false;

        // left
        if( !dfs(root->left,root->val,mn) ) return false;
        // right
        return dfs(root->right,mx,root->val);
    }
public:
    bool isValidBST(TreeNode* root) {
        return dfs(root,LONG_MAX,LONG_MIN);
    }
};
