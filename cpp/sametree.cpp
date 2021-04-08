
// Same Tree
// https://leetcode.com/problems/same-tree/


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
    bool isSameTree(TreeNode* p, TreeNode* q) {

        // early exits
        if ( p == nullptr && q == nullptr ) return true;
        if ( p == nullptr && q != nullptr ) return false;
        if ( p != nullptr && q == nullptr ) return false;
        if ( p->val != q->val ) return false;

        // ideally we don't visit the entire tree but abort at the first difference
        return (isSameTree(p->left,q->left) && isSameTree(p->right, q->right)) ? true : false;
    }
};
