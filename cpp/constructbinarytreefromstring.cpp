
// 536. Construct Binary Tree from String
// https://leetcode.com/problems/construct-binary-tree-from-string/



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
    pair<TreeNode*,int> str2tree(string& s, size_t& n, int idx) {

        string val = "";
        int i = idx;
        char c;
        for(; i < n; ++i) {
            c = s[i];
            if( '-' == c || isdigit(c) ) val += c;
            else break;
        }
        TreeNode* root = new TreeNode(stoi(val));
        if( i < n && s[i] == '(' ) {
            // i have a left child
            pair<TreeNode*,int> l = str2tree(s,n,i+1);
            root->left = l.first;
            i = l.second;
        }
        if( i < n && s[i] == '(' ) {
            // i have a right child
            pair<TreeNode*,int> r = str2tree(s,n,i+1);
            root->right = r.first;
            i = r.second;
        }

        return {root,i+1};
    }
public:
    TreeNode* str2tree(string& s) {
        size_t n = s.size();
        if( 0 == n ) return nullptr;
        pair<TreeNode*,int> ans = str2tree(s,n,0);
        return ans.first;
    }
};
