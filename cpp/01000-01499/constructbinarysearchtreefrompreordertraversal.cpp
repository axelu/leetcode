
// 1008. Construct Binary Search Tree from Preorder Traversal
// https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/



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

    TreeNode* bstFromPreorder(vector<int>& preorder, int& idx, int n, int mn, int mx) {
        if( idx >= n ) return nullptr;

        TreeNode* root = nullptr;
        if( preorder[idx] > mn && preorder[idx] < mx ) {
            root = new TreeNode(preorder[idx]);
            ++idx;
            root->left  = bstFromPreorder(preorder,idx,n,mn,root->val);
            root->right = bstFromPreorder(preorder,idx,n,root->val,mx);
        }
        return root;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {

        int idx = 0;
        return bstFromPreorder(preorder,idx,preorder.size(),INT_MIN,INT_MAX);
    }
};
