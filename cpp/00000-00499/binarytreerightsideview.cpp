
// 199. Binary Tree Right Side View
// https://leetcode.com/problems/binary-tree-right-side-view/


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
public:
    vector<int> rightSideView(TreeNode* root) {
        if( root == nullptr ) return {};

        _walk(root,0,0);

        vector<int> r;
        for(auto it = t.rbegin(); it != t.rend(); ++it) {
            r.push_back(it->second.second);
        }

        return r;
    }
private:
    map<int,pair<int,int>> t; // keyed by row x val

    void _walk(TreeNode* root, int x, int y) {
        if( root == nullptr ) return;

        auto r = t.find(y);
        if( r != t.end() ) {
            if( r->second.first < x ) {
                r->second = make_pair(x, root->val);;
            }
        } else {
            t.insert({y,make_pair(x, root->val)});
        }

        int xl;
        int xr;

        if( x < 0 ) {
            xl = 2 * x;
            xr = xl + 1;
        } else if ( x > 0 ) {
            xr = 2 * x;
            xl = xr - 1;
        } else {
            // x == 0
            xl = x - 1;
            xr = x + 1;
        }

        _walk(root->left, xl, y - 1);
        _walk(root->right, xr, y - 1);
    }
};
