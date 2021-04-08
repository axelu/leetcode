
// Lowest Common Ancesotr of a Binary Searh Tree
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
         if( root == nullptr || p == nullptr || q == nullptr ) return nullptr;
        _walk(root, p, q);

        TreeNode* r = nullptr;
        for(auto it = pq.rbegin(); it != pq.rend(); ++it) {
            auto f = pp.find(*it);
            if( f != pp.end() ) {
                r = *f;
                break;
            }
        }

        return r;
    }
private:
    bool fp = false;
    bool fq = false;
    unordered_set<TreeNode*> pp;
    vector<TreeNode*> pq;

    void _walk( TreeNode* root, TreeNode* p, TreeNode* q ) {
        if( root == nullptr ) return;
        // cout << "root val " << root->val << endl;
        if( fp && fq ) return;

        if ( !fp ) pp.insert(root);
        if ( !fq ) pq.push_back(root);

        if( root == p ) {
            // cout << "found p" << endl;
            fp = true;
        } else if( root == q ) {
            // cout << "found q" << endl;
            fq = true;
        }

        _walk(root->left, p, q);
        _walk(root->right, p ,q);

        if( !fp ) pp.erase(root);
        if( !fq ) pq.pop_back();
    }
};
