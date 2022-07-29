
// 1530. Number of Good Leaf Nodes Pairs
// https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/




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
    void dfs1(TreeNode* tn, TreeNode* p,
              unordered_set<TreeNode*>& leafs,
              unordered_map<TreeNode*,TreeNode*>& parent) {

        // record parent
        parent.insert({tn,p});

        if( tn->left == nullptr && tn->right == nullptr ) {
            // we are at a leaf
            leafs.insert(tn);
            return;
        }

        if( tn->left != nullptr )
            dfs1(tn->left,tn,leafs,parent);
        if( tn->right != nullptr )
            dfs1(tn->right,tn,leafs,parent);
    }

    int dfs2(TreeNode* tn,
             TreeNode* src,
             int step,
             int distance,
             unordered_map<TreeNode*,TreeNode*>& parent) {

        if( step > distance )
            return 0;

        // we can go to our children or parent
        // just don't go back to where we came from (src)

        int ret = 0;

        if( tn->left == nullptr && tn->right == nullptr ) {
            // we are at a leaf node
            // src will be nullptr when we start search
            // step would be 0 also
            if( src != nullptr )
                ++ret;
        }

        if( tn->left != nullptr && tn->left != src )
            ret += dfs2(tn->left,tn,step+1,distance,parent);

        if( tn->right != nullptr && tn->right != src)
            ret += dfs2(tn->right,tn,step+1,distance,parent);

        TreeNode* p = parent[tn];
        if( p != nullptr && p != src )
            ret += dfs2(p,tn,step+1,distance,parent);

        return ret;
    }

public:
    int countPairs(TreeNode* root, int distance) {
        // DFS pass 1: collect leaf nodes and record parents
        // DFS pass 2: from each leaf node till number of steps done > distance

        unordered_set<TreeNode*> leafs;
        unordered_map<TreeNode*,TreeNode*> parent; // child,parent
        dfs1(root,nullptr,leafs,parent);

        int ans = 0;
        for(auto tn : leafs)
            ans += dfs2(tn,nullptr,0,distance,parent);

        return ans/2;
    }
};
