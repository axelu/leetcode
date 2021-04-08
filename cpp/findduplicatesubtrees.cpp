
// 652. Find Duplicate Subtrees
// https://leetcode.com/problems/find-duplicate-subtrees/



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
    vector<TreeNode*> ans;
    unordered_map<string,int> um;

    string serialize(TreeNode* root) {
        if( root == nullptr ) return "#";

        string s = to_string(root->val) + "," + serialize(root->left)
            + "," + serialize(root->right);

        pair<unordered_map<string,int>::iterator,bool> p;
        p = um.insert({s,1});
        if( !p.second ) {
            ++p.first->second;
            if( p.first->second == 2 ) ans.push_back(root);
        }
        return s;
    }
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        serialize(root);
        return ans;
    }
};
