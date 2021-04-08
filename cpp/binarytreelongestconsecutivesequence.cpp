
// 298. Binary Tree Longest Consecutive Sequence
// https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/




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
    struct T{
        TreeNode* node;
        TreeNode* parent;
        int l;
        T(TreeNode* node, TreeNode* parent, int l) : node(node), parent(parent), l(l) {}
    };

public:
    int longestConsecutive(TreeNode* root) {

        int ans = 1;

        // BFS
        queue<T> q;
        if( root->left != nullptr ) q.push({root->left,root,1});
        if( root->right != nullptr ) q.push({root->right,root,1});
        while(!q.empty()) {
            T t = q.front();
            int l = t.l;
            q.pop();
            if( t.node->val == t.parent->val + 1 ) ++l;
            else l = 1;
            ans = max(ans,l);
            if( t.node->left != nullptr ) q.push({t.node->left,t.node,l});
            if( t.node->right != nullptr ) q.push({t.node->right,t.node,l});
        }
        return ans;
    }
};
