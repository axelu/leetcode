
// 606. Construct String from Binary Tree
// https://leetcode.com/problems/construct-string-from-binary-tree/



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
    void tree2str(TreeNode* t, string& s) {
        // add myself to s
        bool isRoot = true;
        if( !s.empty() ) {
            s += '(';
            isRoot = false;
        }
        s += to_string(t->val);

        if( nullptr != t->left )
            tree2str(t->left,s);
        if( nullptr != t->right ) {
            if( nullptr == t->left ) s += "()";
            tree2str(t->right,s);
        }
        if( !isRoot )
            s += ')';
    }
public:
    string tree2str(TreeNode* t) {
        string ans = "";
        if( nullptr == t ) return ans;
        tree2str(t,ans);
        return ans;
    }
};
