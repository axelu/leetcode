
// 1315. Sum of Nodes with Even-Valued Grandparent
// https://leetcode.com/problems/sum-of-nodes-with-even-valued-grandparent/


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
    int ans;

    void dfs(TreeNode* root, TreeNode* parent, TreeNode* gp) {
        if( root == nullptr ) return;

        if( gp != nullptr && gp->val % 2 == 0 )
            ans += root->val;

        dfs(root->left,root,parent);
        dfs(root->right,root,parent);
    }

public:
    int sumEvenGrandparent(TreeNode* root) {
        ans = 0;
        dfs(root,nullptr,nullptr);
        return ans;
    }
};
