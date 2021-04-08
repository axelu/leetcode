
// Maximum Binary Tree
// https://leetcode.com/problems/maximum-binary-tree/


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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return _build(nums.begin(), nums.end());
    }
private:
    TreeNode* _build(vector<int>::iterator itb, vector<int>::iterator ite) {
        if( ite - itb == 0 ) return nullptr;

        auto me = max_element(itb, ite);
        TreeNode* r = new TreeNode(*me);

        r->left = _build(itb, me);
        r->right = _build(me + 1, ite);

        return r;
    }
};
