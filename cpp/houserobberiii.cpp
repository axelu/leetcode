
// 337. House Robber III
// https://leetcode.com/problems/house-robber-iii/
// day 23 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/567/week-4-november-22nd-november-28th/3541/


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
    unordered_map<TreeNode*,int> robbed;
    unordered_map<TreeNode*,int> notRobbed;

    int _rob(TreeNode* root, bool parentRobbed) {
        if( root == nullptr ) return 0;

        if( parentRobbed ) {
            auto search = robbed.find(root);
            if( search != end(robbed) ) return search->second;

            int r = _rob(root->left,false) + _rob(root->right,false);
            robbed.insert({root,r});
            return r;
        } else {
            auto search = notRobbed.find(root);
            if( search != end(notRobbed) ) return search->second;

            int rob     = root->val + _rob(root->left,true)  + _rob(root->right,true);
            int not_rob =             _rob(root->left,false) + _rob(root->right,false);
            int r = max(rob, not_rob);
            notRobbed.insert({root,r});
            return r;
        }
    }
public:
    int rob(TreeNode* root) {
        return _rob(root,false);
    }
};
