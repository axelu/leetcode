
// 437. Path Sum III
// https://leetcode.com/problems/path-sum-iii/




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

// adapted from 113. Path Sum II https://leetcode.com/problems/path-sum-ii/

class Solution {
private:
    int ans;
    
    void dfs(TreeNode* root, long& sum, unordered_map<long,int>& mp, int& targetSum) {
        long val = root->val;
        
        sum += val;
        
        auto f = mp.find(sum - targetSum);
        if( f != mp.end() )
            ans += f->second;

        auto p = mp.insert({sum,1});
        if( !p.second )
            ++p.first->second;

        // left
        if( root->left != nullptr )
            dfs(root->left,sum,mp,targetSum);
        // right
        if( root->right != nullptr )
            dfs(root->right,sum,mp,targetSum);
        
        // backtrack
        if( !p.second )
            --p.first->second;
        else
            mp.erase(sum);
        sum -= val;
    }
    
    
public:
    int pathSum(TreeNode* root, int targetSum) {
        ans = 0;
        if( root == nullptr )
            return ans;
        
        
        long sum = 0;

        unordered_map<long,int> mp; // sum, number of occurences of sum
        mp.insert({0, 1});

        dfs(root,sum,mp,targetSum);
        return ans;
    }
};
