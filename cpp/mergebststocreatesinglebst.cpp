
// 1932. Merge BSTs to Create Single BST
// https://leetcode.com/problems/merge-bsts-to-create-single-bst/
// https://leetcode.com/contest/weekly-contest-249/problems/merge-bsts-to-create-single-bst/



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
    TreeNode* ans;
    
    // binary search
    int search(vector<TreeNode*>& trees, int s, int e, int x) {
        if( s > e )
            return -1;
        
        int mid = s + ((e-s)/2);
        int val = trees[mid]->val;
        if( val == x ) {
            return mid;
        } else if( val < x) {
            return search(trees,mid+1,e,x);
        } else {
            return search(trees,s,mid-1,x);
        }
    }

    bool merge(TreeNode* root, vector<TreeNode*>& trees, int n, int mn, int mx, int& merges) {
        
        if( root->val <= mn || root->val >= mx )
            return false;
        
        if( root->left == nullptr && root->right == nullptr ) {
            // we are at a leave
            // find the root to be merged
            
            int f = search(trees,0,n-1,root->val);
            if( f != -1 ) {
                root->left = trees[f]->left;
                root->right = trees[f]->right;
                ++merges;
            }
        }
        
        bool ret = true;

        if( root->left != nullptr )
            ret = merge(root->left,trees,n,mn,root->val,merges);
        
        if( ret && root->right != nullptr )
            ret = merge(root->right,trees,n,root->val,mx,merges);
                 
        return ret;
    }
    
public:
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        int n = trees.size();
        if( n == 1 )
            return trees[0];
        
        // no two roots of trees have the same value
        // meaning root values are unique
        sort(trees.begin(),trees.end(),[](TreeNode* a, TreeNode* b){
            return a->val < b->val;
        });

        
        // a leave is the merging point for a root
        // there must be one and only one root
        
        int seen[n];memset(seen,0,sizeof seen);
        int f;     // index of found root
        int c = 0; // counting roots seen
        for(int i = 0; i < n; ++i) {
            // left leave
            if( trees[i]->left != nullptr ) {
                f = search(trees,0,n-1,trees[i]->left->val);
                if( f != -1 ) {
                    if( seen[f] )
                        return nullptr; // more than one leave with same value
                    seen[f] = 1;
                    ++c;
                }
            }
            // right leave
            if( trees[i]->right != nullptr ) {
                f = search(trees,0,n-1,trees[i]->right->val);
                if( f != -1 ) {
                    if( seen[f] )
                        return nullptr; // more than one leave with same value
                    seen[f] = 1;
                    ++c;
                }
            }
        }
        
        if( c != n-1 )                  // more than one tree
            return nullptr;
        
        // get root tree
        TreeNode* root;
        for(int i = 0; i < n; ++i)
            if( !seen[i] ) {
                root = trees[i];
                break;
            }

        c = 0;
        if( merge(root,trees,n,INT_MIN,INT_MAX,c) && c == n-1 )
            return root;
        
        return nullptr;
    }
};
