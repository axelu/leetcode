
// 236. Lowest Common Ancestor of a Binary Tree
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    bool foundP,foundQ;
    TreeNode* lca;

    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
        if( root == nullptr ) return false;
        if( foundP && foundQ ) return false;

        if( root == p ) {
            foundP = true;
            if( foundQ ) return true;
        } else if( root == q ) {
            foundQ = true;
            if( foundP ) return true;
        }

        bool l = dfs(root->left,p,q);
        if( l && ( root == p || root == q) ) {
            lca = root;
            return true;
        }
        bool r = dfs(root->right,p,q);
        if( r && ( root == p || root == q) ) {
            lca = root;
            return true;
        }

        if( l && r )
            lca = root;

        return l || r || root == p || root == q ? true : false;
    }


public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        foundP = false;
        foundQ = false;

        dfs(root,p,q);
        return lca;
    }
};
