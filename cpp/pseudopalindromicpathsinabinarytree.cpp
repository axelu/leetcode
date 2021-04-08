
// 1457. Pseudo-Palindromic Paths in a Binary Tree
// https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/
// day 29 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/573/week-5-december-29th-december-31st/3585/

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
    int odd;
    int cnt[10];

    void dfs(TreeNode* root) {
        ++cnt[root->val];
        odd += cnt[root->val] % 2 == 1 ? 1 : -1;

        if( root->left == nullptr && root->right == nullptr) {
            // we are at a leaf node
            if( odd == 0 || odd == 1 ) ++ans;
        }

        // left
        if( root->left != nullptr) dfs(root->left);
        // right
        if( root->right != nullptr) dfs(root->right);
        // backtrack
        --cnt[root->val];
        odd += cnt[root->val] % 2 == 1 ? 1 : -1;
    }
public:
    int pseudoPalindromicPaths (TreeNode* root) {
        if( root == nullptr ) return 0;

        memset(cnt,0,sizeof cnt);
        ans = 0;
        odd = 0;
        dfs(root);

        return ans;
    }
};
