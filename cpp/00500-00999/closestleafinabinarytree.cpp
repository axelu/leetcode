
// 742. Closest Leaf in a Binary Tree
// https://leetcode.com/problems/closest-leaf-in-a-binary-tree/



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
    pair<int,TreeNode*> getMin(pair<int,TreeNode*>& a, pair<int,TreeNode*>& b) {
        return a.first < b.first ? a : b;
    }

    pair<int,TreeNode*> findClosestLeafInSubtree(TreeNode* root) {
        if( nullptr == root) return make_pair(INT_MAX,nullptr);
        if( nullptr == root->left && nullptr == root->right ) return make_pair(0,root);

        pair<int,TreeNode*> l = findClosestLeafInSubtree(root->left);
        pair<int,TreeNode*> r = findClosestLeafInSubtree(root->right);
        pair<int,TreeNode*> mn = getMin(l,r);
        mn.first += 1;
        return mn;
    }

    pair<int,TreeNode*> findClosestLeaf(TreeNode* root, int& k, TreeNode* anc[], int idx) {
        if( nullptr == root ) return make_pair(INT_MAX,nullptr);

        if( root->val == k ) {
            // find closest leaf in subtree of node with value k
            pair<int,TreeNode*> ans = findClosestLeafInSubtree(root);

            // traverse ancestors to see if a parent gives better answer
            pair<int,TreeNode*> t;
            for(int i = idx-1; i >= 0; --i) {
                t = findClosestLeafInSubtree(anc[i]);
                t.first += idx - i; // adjust distance for needed upward hops
                ans = getMin(ans,t);
            }
            return ans;
        }

        anc[idx] = root;
        pair<int,TreeNode*> l = findClosestLeaf(root->left,k,anc,idx+1);
        pair<int,TreeNode*> r = findClosestLeaf(root->right,k,anc,idx+1);
        return getMin(l,r);
    }
public:
    int findClosestLeaf(TreeNode* root, int k) {
        TreeNode* anc[1000];
        pair<int,TreeNode*> ans = findClosestLeaf(root,k,anc,0);
        return nullptr == ans.second ? 0 : ans.second->val;
    }
};
