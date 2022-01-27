
// 572. Subtree of Another Tree
// https://leetcode.com/problems/subtree-of-another-tree/



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
    bool isIdentical(TreeNode* s, TreeNode* t) {
        if( s == nullptr && t == nullptr ) return true;
        if( s == nullptr || t == nullptr ) return false;
        if( s->val != t->val ) return false;

        if( !isIdentical(s->left,t->left) ) return false;
        return isIdentical(s->right,t->right);
    }
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        // constraint: s != nullptr and t != nullptr

        // bfs
        queue<TreeNode*> q;
        q.push(s);
        while( !q.empty() ) {
            TreeNode* root = q.front();
            q.pop();
            if( isIdentical(root,t) ) return true;
            if( root->left != nullptr ) q.push(root->left);
            if( root->right != nullptr ) q.push(root->right);
        }
        return false;
    }
};
