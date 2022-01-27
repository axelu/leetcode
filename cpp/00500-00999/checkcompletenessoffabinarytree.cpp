

// 958. Check Completeness of a Binary Tree
// https://leetcode.com/problems/check-completeness-of-a-binary-tree/



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
    bool isCompleteTree(TreeNode* root) {

        vector<string> r;
        vector<TreeNode*> v = {root};

        _flatten(v, &r);

        // strip trailing null's
        while ( r.back() == "null" )
            r.pop_back();

        return ( find(r.begin(), r.end(), "null") != r.end() ) ? false : true;
    }
private:
    void _flatten(vector<TreeNode*> v, vector<string>* r) {

        vector<TreeNode*> z;

        for (TreeNode* t : v) {

            if ( t == nullptr ) {
                r->push_back("null");
            } else {
                r->push_back(to_string(t->val));
                z.push_back(t->left);
                z.push_back(t->right);
            }
        }

        if ( !z.empty() ) _flatten(z, r);
    }
};
