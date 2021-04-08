
// Convert Sorted Array to Binary Search Tree
// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if ( nums.empty() ) return nullptr;
        return buildTree(nums.begin(), nums.end() - 1);
    }
private:
    TreeNode* buildTree(vector<int>::iterator itb, vector<int>::iterator ite) {

        if( itb == ite ) return new TreeNode(*itb);

        int middle = (ite - itb + 1)/2;
        TreeNode* root = new TreeNode(*(itb + middle));

        root->left = buildTree(itb, itb + middle - 1);
        if ( ite != itb + middle ) root->right = buildTree(itb + middle + 1, ite);

        return root;
    }
};
