
// 1448. Count Good Nodes in a Binary Tree
// https://leetcode.com/problems/count-good-nodes-in-binary-tree/




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
    stack<int> stck;

    void dfs(TreeNode* root) {
        if( nullptr == root ) return;

        if( stck.empty() ) {
            ++ans;
            stck.push(root->val);
        } else {
            if( root->val >= stck.top() ) {
                ++ans;
                stck.push(root->val);
            }
        }

        dfs(root->left);
        dfs(root->right);

        if( stck.top() == root->val ) stck.pop();
    }

public:
    int goodNodes(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
};
