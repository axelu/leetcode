
// 2415. Reverse Odd Levels of Binary Tree
// https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/


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
    TreeNode* reverseOddLevels(TreeNode* root) {
        
        
        deque<pair<TreeNode*,int>> dq;
        dq.push_back({root,0});
        while( !dq.empty() ) {
            deque<pair<TreeNode*,int>> dq_new;
            int level = dq.front().second;
            
            while( !dq.empty() ) {
                if( dq.front().first->left == nullptr )
                    break;
                
                dq_new.push_back({dq.front().first->left,level+1});
                dq_new.push_back({dq.front().first->right,level+1});
                
                dq.pop_front();
            }
            
            if( !dq_new.empty() && level % 2 == 0 ) {
                auto it = dq_new.cbegin();
                auto itr = dq_new.crbegin();
                while( it < itr.base() ) {
                    int t = itr->first->val;
                    itr->first->val = it->first->val;
                    it->first->val = t;
                    ++it;
                    ++itr;
                }
            }
            
            swap(dq,dq_new);
        }
                
        return root;
    }
};
