
// 2471. Minimum Number of Operations to Sort a Binary Tree by Level
// https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/



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
    int min_swaps(vector<pair<int,int>>& val_pos) {

        sort(val_pos.begin(),val_pos.end());

        int n = val_pos.size();
        int swapped[n];memset(swapped,0,sizeof swapped);

        int ret = 0;

        for(int i = 0; i < n; ++i) {
            // value in the correct position or
            // position already swapped
            if( val_pos[i].second == i || swapped[i] )
                continue;

            // chase the current val respectively position
            int swaps = 0;
            int j = i;
            while( !swapped[j] ) {
                swapped[j] = 1; // mark as swapped
                j = val_pos[j].second;
                ++swaps;
            }

            if( swaps > 0 )
                ret += swaps - 1;
        }

        return ret;
    }

public:
    int minimumOperations(TreeNode* root) {
        int ans = 0;

        queue<TreeNode*> q;
        q.push(root);

        while( !q.empty() ) {

            queue<TreeNode*> q_new;
            int i = 0;
            vector<pair<int,int>> val_pos; // array of {val,pos} of all nodes on this level
            while( !q.empty() ) {
                TreeNode* tn = q.front();
                q.pop();

                val_pos.push_back({tn->val,i++});

                if( tn->left != nullptr )
                    q_new.push(tn->left);
                if( tn->right != nullptr )
                    q_new.push(tn->right);
            }
            swap(q,q_new);
            ans += min_swaps(val_pos);
        }

        return ans;
    }
};
