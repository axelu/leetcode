#include <iostream>
#include <vector>
//#include <map>
#include <string>

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
    TreeNode* buildTree(string ft) {

        vector<string> fv;
        _string2vector(ft, &fv);

        TreeNode* t = new TreeNode();

        if (!fv.empty()) {

            t->val = stoi(fv.at(0));

            if (fv.size() > 1) {

                vector<TreeNode*> v;
                v.push_back(t);
                _buildTree(v, &fv, 1);

            }
        }                                                                     

        return t;
    }
    
    void flatten(TreeNode* t, vector<string>* r) {                                 
        
        r->push_back(to_string(t->val)); 

        vector<TreeNode*> v;

        v.push_back(t->left);
        v.push_back(t->right);

        _flatten(v, r);

        // strip trailing null's
        while ( r->back() == "null" ) {
            r->pop_back();
        }
    }

private:
    void _buildTree(vector<TreeNode*> vt, vector<string>* v, int pos) {

        vector<TreeNode*> z;

        for (auto t : vt) {

            // left
            if ( v->size() <= pos ) {
                t->left = nullptr;
            } else {
                if ( v->at(pos) == "null" ) {
                    t->left = nullptr;
                } else {
                    TreeNode * subtree = new TreeNode(stoi(v->at(pos)));
                    t->left = subtree;
                    z.push_back(subtree);
                }
                pos++;
            }
            // right
            if ( v->size() <= pos ) {
                t->right = nullptr;
            } else {
                if ( v->at(pos) == "null" ) {
                    t->right = nullptr;
                } else {
                    TreeNode * subtree = new TreeNode(stoi(v->at(pos)));
                    t->right = subtree;
                    z.push_back(subtree);
                }
                pos++;
            }
        }

        if ( !z.empty() ) _buildTree(z, v, pos);

    }

    void _string2vector(string ft, vector<string>* fv) {
        
        // trim leading [ and trailing ], assumed string length is at least 3
        ft = ft.substr(1, ft.size()-2);

        if ( ft.find(",") == string::npos ) {
            fv->push_back(ft);
        } else {
            size_t last = 0; 
            size_t next = 0; 
            while ( (next = ft.find(",", last)) != string::npos ) {
                fv->push_back(ft.substr(last, next - last));   
                last = next + 1; 
            }
            fv->push_back(ft.substr(last));
        }

        // strip trailing null's
        while ( fv->back() == "null" ) {
            fv->pop_back();
        }
    }

    void _flatten(vector<TreeNode*> v, vector<string>* r) {

        vector<TreeNode*> z;

        for (TreeNode* t : v) {

            if ( t == nullptr ) {
                r->push_back("null");
            } else {
                r->push_back(to_string(t->val));
                z.push_back(t->left);
                z.push_back(t->right);
            }
        }

        if ( !z.empty() ) _flatten(z, r);
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

    Solution s;

    vector<string> r; // sample tree flattened expected: 5 3 6 2 4 null 7
    s.flatten(&root, &r);

    if (!r.empty()) {                                                     
        for (auto i : r) {                                                
            cout << i << " ";                                             
        }
        cout << endl;
    }                                                                     

    // for convinience in order to create BINARY int trees to merge
    // borrowed from the leetcode problems
    // Breadth First Traversal or Level Order Traversal
    // tree represented flat as string starting w/ [ and ending w/ ]
    // flat representation starts at root
    // children are specified left 1st and then right
    // if only left or right child, empty child specified as null
    // a null at the very last element is optional
    // see examples at https://leetcode.com/problems/merge-two-binary-trees/
    // use leetcode tree visualizer

    string ft = "[5,3,6,2,4,null,7]";
    TreeNode* tn = s.buildTree(ft);

    vector<string> ftn;
    s.flatten(tn, &ftn);

    if (!ftn.empty()) {                                                     
        for (auto i : ftn) {                                                
            cout << i << " ";                                             
        }
        cout << endl;
    }                                                                     

    return 0;
}
