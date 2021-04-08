
// 314. Binary Tree Vertical Order Traversal
// https://leetcode.com/problems/binary-tree-vertical-order-traversal/




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
    struct T {
        TreeNode* tn;
        int col;
        int row;
        int cnt;
        T(TreeNode* tn, int col, int row, int cnt) : tn(tn), col(col), row(row), cnt(cnt) {};
    };
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if( root == nullptr ) return ans;

        // BFS
        queue<T*> q;
        T* qe;
        q.push(new T(root,0,0,0));
        vector<T*> v;
        int cnt = 0;
        while(!q.empty()) {
            qe = q.front();
            q.pop();
            v.push_back(qe);
            if( qe->tn->left != nullptr ) {
                ++cnt;
                q.push(new T(qe->tn->left,qe->col-1,qe->row+1,cnt));
            }
            if( qe->tn->right != nullptr ) {
                ++cnt;
                q.push(new T(qe->tn->right,qe->col+1,qe->row+1,cnt));
            }
        }
        sort(v.begin(),v.end(),[](T* a, T* b){
            if( a->col < b->col ) return true;
            if( a->col == b->col ) {
                if( a->row < b->row ) return true;
                if( a->row == b->row ) {
                    if( a->cnt < b->cnt ) return true;
                }
            }
            return false;
        });

        int currCol = v[0]->col;
        vector<int> colValues;
        for(int i = 0; i < v.size(); ++i) {
            if( v[i]->col != currCol ) {
                ans.push_back(colValues);
                colValues.clear();
                currCol = v[i]->col;
            }
            colValues.push_back(v[i]->tn->val);
        }
        if( !colValues.empty() ) ans.push_back(colValues);
        return ans;
    }
};
