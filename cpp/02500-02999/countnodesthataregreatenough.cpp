
// 2792. Count Nodes That Are Great Enough
// https://leetcode.com/problems/count-nodes-that-are-great-enough/




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
    int ans; // count of great enough nodes

    multiset<int> rec(TreeNode* root, int k) {
        if( root == nullptr )
            return {};

        auto l = rec(root->left,k);
        auto r = rec(root->right,k);

        multiset<int> ret;
        int i = 0;
        auto itl = l.begin();
        auto itr = r.begin();
        while( i < k && (itl != l.end() || itr != r.end()) ) {
            if( itl != l.end() && itr != r.end() ) {
                if( *itl < *itr ) {
                    ret.insert(*itl);
                    ++itl;
                } else {
                    ret.insert(*itr);
                    ++itr;
                }
            } else if( itl != l.end() ) {
                ret.insert(*itl);
                ++itl;
            } else {
                ret.insert(*itr);
                ++itr;
            }
            ++i;
        }
        if( ret.size() == k && root->val > *ret.rbegin() )
            ++ans;
        ret.insert(root->val);
        if( ret.size() > k )
            ret.erase(prev(ret.end()));

        return ret;
    }

public:
    int countGreatEnoughNodes(TreeNode* root, int k) {
        ans = 0;

        rec(root,k);
        return ans;
    }
};
