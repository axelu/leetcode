
// 894. All Possible Full Binary Trees
// https://leetcode.com/problems/all-possible-full-binary-trees/



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
    unordered_map<int,vector<TreeNode*>> mem;
public:
    vector<TreeNode*> allPossibleFBT(int n) {
        vector<TreeNode*> ans;
        if( n % 2 == 0 ) return {};

        if( mem[n].size() > 0 ) return mem[n];

        if( n == 1 ) {
            ans.push_back(new TreeNode());
        } else {
            for(int i = 1; i < n; i += 2) {
                vector<TreeNode*> left = allPossibleFBT(i);
                vector<TreeNode*> right = allPossibleFBT(n - i - 1);
                for(int l = 0; l < left.size(); ++l) {
                    for(int r = 0; r < right.size(); ++r) {
                        TreeNode* node = new TreeNode();
                        node->left = left[l];
                        node->right = right[r];
                        ans.push_back(node);
                    }
                }
            }
        }
        return mem[n] = ans;
    }
};
