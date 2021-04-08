
// 501. Find Mode in Binary Search Tree
// https://leetcode.com/problems/find-mode-in-binary-search-tree/



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
    void dfs(TreeNode* root, vector<int>& ans) {
        if( root == nullptr ) return;
        dfs(root->left,ans);
        ans.push_back(root->val);
        dfs(root->right,ans);
    }
public:
    vector<int> findMode(TreeNode* root) {
        if( root == nullptr ) return {};
        if( root->left == nullptr && root->right == nullptr ) return {root->val};

        vector<int> ans;
        dfs(root,ans);

        // ans will have values in ascending order if tree is a strict binary search tree
        sort(ans.begin(),ans.end()); // tree is not a 'strict' binary search tree, hence sorting
        // for(int i : ans) cout << i << " "; cout << endl;

        // get indicies where values change
        vector<int> indicies;
        for(int i = 1; i < ans.size(); ++i)
            if( ans[i-1] != ans[i] ) indicies.push_back(i);
        // for(int i : indicies) cout << i << " "; cout << endl;

        // get longest persistence length(s) of repeated values
        int mx = 1;
        int p = 0;
        vector<int> ret;
        for(int i = 0; i < indicies.size(); ++i) {
            if( indicies[i] - p > mx ) {
                mx = indicies[i] - p;
                ret.clear();
                ret.push_back(ans[indicies[i]-1]);
            } else if( indicies[i] - p == mx ) {
                ret.push_back(ans[indicies[i]-1]);
            }
            p = indicies[i];
        }
        // finish up
        if( ans.size() - p > mx ) {
            ret.clear();
            ret.push_back(ans.back());
        } else if( ans.size() - p == mx ) {
            ret.push_back(ans.back());
        }

        return ret;
    }
};
