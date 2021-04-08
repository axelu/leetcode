
// All Elements in Two Binary Search Trees
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/554/week-1-september-1st-september-7th/3449/


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
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        // if( root1 == nullptr && root2 == nullptr ) return {};

        vector<int> r;
        _walk(root1, r);
        _walk(root2, r);
        sort(r.begin(),r.end());

        return r;
    }
private:
    void _walk (TreeNode* root, vector<int>& r) {
        if( root == nullptr ) return;

        r.push_back(root->val);
        _walk(root->left, r);
        _walk(root->right, r);
    }
};
