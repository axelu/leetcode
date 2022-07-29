
// 2196. Create Binary Tree From Descriptions
// https://leetcode.com/problems/create-binary-tree-from-descriptions/



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
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {

        unordered_map<int,pair<TreeNode*,TreeNode*>> um;
        for(auto& v : descriptions) {
            int parent_val = v[0];
            int child_val  = v[1];

            TreeNode* parent;
            auto p = um.find(parent_val);
            if( p != um.end() ) {
                parent = p->second.first;
            } else {
                parent = new TreeNode(parent_val);
                um[parent_val] = {parent,nullptr};
            }

            TreeNode* child;
            auto c = um.find(child_val);
            if( c != um.end() ) {
                child = c->second.first;
                c->second.second = parent;
            } else {
                child = new TreeNode(child_val);
                um[child_val] = {child,parent};
            }

            if( v[2] )
                parent->left = child;
            else
                parent->right = child;
        }

        TreeNode* root;
        for(auto p : um)
            if( p.second.second == nullptr ) {
                root = p.second.first;
                break;
            }

        return root;
    }
};
