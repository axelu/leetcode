
// 1120. Maximum Average Subtree
// https://leetcode.com/problems/maximum-average-subtree/




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
    double ans;

    // postorder traversal
    pair<int,int> dfs(TreeNode* root) {
        if( root == nullptr ) return make_pair(0,0);

        pair<int,int> pl = dfs(root->left);
        pair<int,int> pr = dfs(root->right);

        int cnt = pl.second + pr.second + 1;
        int sum = pl.first + pr.first + root->val;
        double ave = (double)sum/(double)cnt;

        ans = max(ans,ave);
        return make_pair(sum,cnt);

    }
public:
    double maximumAverageSubtree(TreeNode* root) {
        ans = 0.0;
        dfs(root);
        return ans;
    }
};
