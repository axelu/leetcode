
// 1676. Lowest Common Ancestor of a Binary Tree IV
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iv/



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
    TreeNode* lca;

    // binary search
    bool search(vector<TreeNode*>& nodes, int s, int e, int t) {
        if( s > e ) return false;

        int mid = s + ((e - s)/2);
        if( nodes[mid]->val == t ) {
            return true;
        } else if( nodes[mid]->val > t ) {
            return search(nodes,s,mid-1,t);
        } else {
            return search(nodes,mid+1,e,t);
        }
    }

    bool dfs(TreeNode* root, vector<TreeNode*>& nodes) {
        if( root == nullptr ) return false;

        bool f = search(nodes,0,nodes.size()-1,root->val);
        if( f && nodes.size() == 1 ) {
            lca = root;
            return true;
        }

        bool l = dfs(root->left,nodes);
        if( l && f ) {
            lca = root;
            return true;
        }
        bool r = dfs(root->right,nodes);
        if( r && f ) {
            lca = root;
            return true;
        }

        if( l && r )
            lca = root;

        return l || r || f ? true : false;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*>& nodes) {
        sort(nodes.begin(),nodes.end(),[](TreeNode* a, TreeNode* b){
            return a->val < b->val;
        });

        dfs(root,nodes);
        return lca;
    }
};
