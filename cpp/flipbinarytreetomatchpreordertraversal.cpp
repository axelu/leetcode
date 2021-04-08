
// 971. Flip Binary Tree To Match Preorder Traversal
// https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/
// day 29 March 2021 Challenge
// https://leetcode.com/explore/challenge/card/march-leetcoding-challenge-2021/592/week-5-march-29th-march-31st/3689/




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
    int n;
    void preorder(TreeNode* root, int& idx, vector<int>& voyage, vector<int>& ans) {
        // when we get here, we would have already made a flip if needed
        // in other words: root will match the element at idx in voyage

        // cout << "root->val " << root->val << " idx " << idx << endl;

        if( (!ans.empty() && ans[0] == -1) || idx == n-1 ) return;
        if( root->left == nullptr && root->right == nullptr ) {
            // there is nowhere we can go, so we just return
            return;
        }
        // we either have a left node or a right node or both
        ++idx; // advance idx

        if( root->left == nullptr ) {
            // we have no left node
            // right node must match nxt as we have nothing to flip
            if( root->right == nullptr || root->right->val != voyage[idx] ) {
                ans = {-1};
                return;
            }
            preorder(root->right,idx,voyage,ans);
            return;
        } else {
            // we have a left node
            // if it matches nxt, we go there
            if( root->left->val == voyage[idx] ) {
                preorder(root->left,idx,voyage,ans);
                // now check right node
                if( (!ans.empty() && ans[0] == -1) || idx == n-1 ) return;
                if( root->right == nullptr ) return;
                ++idx;
                if( root->right->val != voyage[idx] ) {
                    ans = {-1};
                    return;
                }
                preorder(root->right,idx,voyage,ans);
                return;
            } else {
                // we have a left node, but it does NOT match
                // if we have a right node AND it matches, we go there 1st
                ans.push_back(root->val); // record the flip
                if( root->right == nullptr || root->right->val != voyage[idx] ) {
                    ans = {-1};
                    return;
                }
                preorder(root->right,idx,voyage,ans);
                // now check left node
                // cout << "check left " << idx << " " << ans[0] << endl;
                if( (!ans.empty() && ans[0] == -1) || idx == n-1 ) return;
                ++idx;
                if( root->left->val != voyage[idx] ) {
                    ans = {-1};
                    return;
                }
                preorder(root->left,idx,voyage,ans);
                return;
            }
        }
    }

public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        n = voyage.size();  // n == voyage.length
                            // 1 <= n <= 100
        if( voyage[0] != root->val ) return {-1};
        vector<int> ans;
        int idx = 0;
        preorder(root,idx,voyage,ans);
        // cout << "n " << n << " idx " << idx << endl;
        if( idx != n-1 ) return {-1};
        return ans;
    }
};
