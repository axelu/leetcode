

// 250. Count Univalue Subtrees
// https://leetcode.com/problems/count-univalue-subtrees/




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

    pair<int,int> dfs(TreeNode* root) {
        if( root->left == nullptr && root->right == nullptr ) {
            // leave node
            ++ans;
            return make_pair(root->val,root->val);
        }
        pair<int,int> pl = root->left  != nullptr ? dfs(root->left)  : make_pair(root->val,root->val);
        pair<int,int> pr = root->right != nullptr ? dfs(root->right) : make_pair(root->val,root->val);

        int mn = min({root->val,pl.first,pr.first});
        int mx = max({root->val,pl.second,pr.second});
        if( mn == mx ) ++ans;
        return make_pair(mn,mx);
    }

public:
    int countUnivalSubtrees(TreeNode* root) {
        ans = 0;
        if( root == nullptr ) return ans;
        dfs(root);
        return ans;
    }
};
