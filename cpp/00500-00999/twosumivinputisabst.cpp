#include <iostream>
#include <vector>
//#include <map>

// 653. Two Sum IV - Input is a BST
// https://leetcode.com/problems/two-sum-iv-input-is-a-bst

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> r;

        //TreeNode * t1 = root->left;
        //if (t1 == nullptr) cout << "nullptr";
        //TreeNode * t2 = root.right;

        flatten(root, &r);

//        if (!r.empty()) {
//            for (auto i : r) {
//                cout << i << " ";
//            }
//        }

        size_t s = r.size();                                                    
        for (int i = 0; i < s; i++) {                                              
            for (int j = i + 1; j < s; j++) {                                      
                cout << "i=" << i << " j=" << j << endl;                           
                                                                                   
                if ( r.at(i) + r.at(j) == k ) {                         
                    return true;                                        
                }                                                                  
                                                                                   
            }                                                                      
        }                                                                          

        return false;
    }
private:
    void flatten(TreeNode* t, vector<int>* r) {
        r->push_back(t->val);
        if ( t->left != nullptr ) flatten(t->left, r);
        if ( t->right != nullptr ) flatten(t->right, r);
    }
};


int main() {

    /* sample tree
     *      5
     *     / \
     *    3   6
     *   / \   \
     *  2   4   7
     *
     * [5,3,6,2,4,null,7]
     */

    // constructing sample tree
    TreeNode subtree1 = TreeNode(2);
    TreeNode subtree2 = TreeNode(4);
    TreeNode subtree3 = TreeNode(3, &subtree1, &subtree2);
    TreeNode subtree4 = TreeNode(7);
    TreeNode subtree5 = TreeNode(6, nullptr, &subtree4);
    TreeNode root = TreeNode(5, &subtree3, &subtree5);

    TreeNode * root_pt = &root;
    int target = 11;

    Solution s;
    cout << s.findTarget(root_pt, target) << endl;

    return 0;
}




