
// 530. Minimum Absolute Difference in BST
// https://leetcode.com/problems/minimum-absolute-difference-in-bst/




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
    set<long> s;

    void dfs(TreeNode* root) {
        if(root == nullptr) return;
        s.insert((long)root->val);
        dfs(root->left);
        dfs(root->right);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        dfs(root);
        long ans = 4294967295; // |INT_MIN - INT_MAX|
        for(auto it = next(s.begin()); it != s.end(); ++it)
            if( *it-*prev(it) < ans ) ans = *it-*prev(it);
        return ans;
    }
};
