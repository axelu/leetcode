
// 1026. Maximum Difference Between Node and Ancestor
// day 9 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/565/week-2-november-8th-november-14th/3525/
// https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/



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
    int mxdif;
    void explore(TreeNode* root,int mn, int mx) {
        if( root == nullptr ) return;

        mn = min(mn,root->val);
        mx = max(mx,root->val);
        mxdif= max(mxdif,mx-mn);

        explore(root->left,mn,mx);
        explore(root->right,mn,mx);
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        mxdif = 0;
        int mn = 100001;
        int mx = -1;

        explore(root,mn,mx);
        return mxdif;
    }
};
