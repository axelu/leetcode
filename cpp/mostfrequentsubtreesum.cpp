
// 508. Most Frequent Subtree Sum
// https://leetcode.com/problems/most-frequent-subtree-sum/




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
    unordered_map<int,int> m;

    int dfs(TreeNode* root) {
        if( root == nullptr ) return 0;

        int l = dfs(root->left);
        int r = dfs(root->right);
        int t = root->val + l + r;
        auto p = m.insert({t,1});
        if( !p.second ) ++p.first->second;

        return t;
    }
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        if( root == nullptr ) return {};
        if( root->left == nullptr && root->right == nullptr ) return {root->val};
        dfs(root);

        vector<int> ans;
        int mx = 0;
        for(auto it = m.begin();it != m.end(); ++it) {
           if( it->second > mx ) {
               mx = it->second;
               ans.clear();
               ans.push_back(it->first);
           } else if(it->second == mx) {
               ans.push_back(it->first);
           }
        }
        return ans;

    }
};
