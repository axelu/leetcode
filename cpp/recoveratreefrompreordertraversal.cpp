
// 1028. Recover a Tree From Preorder Traversal
// https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/




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
    vector<vector<int>> s2v(string& s) {
        vector<vector<int>> ret;
        int depth = 0;
        string val = "";
        for(int i = 0; i < s.size(); ++i) {
            if( isdigit(s[i]) ) {
                val = val + s[i];
                // peek ahead
                if( i < s.size()-1 ) {
                    if( s[i+1] == '-' ) {
                        ret.push_back({depth,stoi(val)});
                        depth = 0;
                        val = "";
                    }
                } else {
                    ret.push_back({depth,stoi(val)});
                }
                continue;
            }
            ++depth;
        }
        return ret;
    }

    TreeNode* preorderReversal(vector<vector<int>>& t, int& idx) {

        TreeNode* root = new TreeNode(t[idx][1]);
        if( idx+1 == t.size() ) return root;
        int currDepth = t[idx][0];
        // peek ahead
        if( t[idx+1][0] > currDepth ) {
            // my left child
            ++idx;
            root->left = preorderReversal(t,idx);
        }
        if( idx+1 == t.size() ) return root;
        if( t[idx+1][0] > currDepth ) {
            // my right child
            ++idx;
            root->right = preorderReversal(t,idx);
        }
        return root;
    }
public:
    TreeNode* recoverFromPreorder(string& s) {
        if( s.empty() ) return nullptr;

        vector<vector<int>> t = s2v(s); // depth,val
        int idx = 0;
        return preorderReversal(t,idx);
    }
};
