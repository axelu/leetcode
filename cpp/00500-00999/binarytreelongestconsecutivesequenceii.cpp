
// 549. Binary Tree Longest Consecutive Sequence II
// https://leetcode.com/problems/binary-tree-longest-consecutive-sequence-ii/




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


        pair<int,int> pl,pr;
        int la = 1, ld = 1, ra = 1, rd = 1;
        // left
        if( root->left != nullptr ) {
            pl = dfs(root->left);
            if( root->left->val == root->val+1 ) {
                la = pl.first+1;
            } else if( root->left->val == root->val-1 ) {
                ld = pl.second+1;
            }
        }
        // right
        if( root->right != nullptr ) {
            pr = dfs(root->right);
            if( root->right->val == root->val+1 ) {
                ra = pr.first+1;
            } else if( root->right->val == root->val-1 ) {
                rd = pr.second+1;
            }
        }


        if( root->left != nullptr && root->right != nullptr ) {
            // paths through our node
            if( root->left->val == root->val-1 && root->right->val == root->val+1) {
                ans = max(ans,pl.second+pr.first+1);
            }
             if( root->left->val == root->val+1 && root->right->val == root->val-1) {
                ans = max(ans,pl.first+pr.second+1);
            }
        }

        int a = max(la,ra);
        int d = max(ld,rd);
        ans = max({ans,a,d});
        return make_pair(a,d);
    }

public:
    int longestConsecutive(TreeNode* root) {
        ans = 1;
        dfs(root);
        return ans;
    }
};
