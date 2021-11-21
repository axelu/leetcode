
// 1373. Maximum Sum BST in Binary Tree
// https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/




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
    struct R {
        int sum;
        bool isBST;
        int mx; // subtree max
        int mn; // subtree min
        R(int x) : sum(x), isBST(true), mx(x), mn(x) {}
    };

    int ans;

    R* dfs(TreeNode* root) {
        // cout << root->val << endl;
        if( nullptr == root->left && nullptr == root->right ) {
            // leaf node
            ans = max(ans,root->val);
            return new R(root->val);
        } else if( nullptr != root->left && nullptr == root->right ) {
             // we only have a left subtree
            R* l = dfs(root->left);
            if( l->isBST && l->mx < root->val ) {
                l->mx = root->val;
                l->sum = l->sum+root->val;
                ans = max(ans,l->sum);
            } else {
                l->isBST = false; // nothing else matters
            }
            return l;
        } else if( nullptr == root->left && nullptr != root->right ) {
            // we only have a right subtree
            R* r = dfs(root->right);
            if( r->isBST && r->mn > root->val ) {
                r->mn = root->val;
                r->sum = r->sum+root->val;
                ans = max(ans,r->sum);
            } else {
                r->isBST = false; // nothing else matters
            }
            return r;
        } else {
            // we have a left subtree AND a right subtree
            R* l = dfs(root->left);
            R* r = dfs(root->right);
            if( !l->isBST ) return l;
            if( !r->isBST ) return r;
            // both left and right are valid BST's
            // cout << root->val << " good left and right subtree" << endl;
            R* res = new R(root->val);
            if( l->mx < root->val && r->mn > root->val ) {
                // cout << root->val << " perfect left and right subtree" << endl;
                res->mn = l->mn;
                res->mx = r->mx;
                res->sum = root->val + l->sum + r->sum;
                ans = max(ans,res->sum);
            } else {
                res->isBST = false; // nothing else matters
            }
            return res;
        }
    }

public:
    int maxSumBST(TreeNode* root) {
        if( nullptr == root ) return 0;
        ans = -2147483648;
        dfs(root);
        return ans < 0 ? 0 : ans;
    }
};
