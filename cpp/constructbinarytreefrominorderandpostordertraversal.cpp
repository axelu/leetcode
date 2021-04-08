#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <chrono>

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
    TreeNode* buildTree(vector<int>& io, vector<int>& po, int io_f = 0, int io_l = 0) {

        // inorder:   left, root, right
        // postorder: left, right, root
        
        if ( po_idx == -999 ) {
            // first invocation
            // debug
            cout << "first invocation" << endl;
           
            po_sz = po.size();
            if ( po.empty() || io.empty() || po_sz != io.size() )
                return nullptr;
           
            //debug
            cout << "po size " << po.size() << endl;

            po_idx = po_sz - 1;

            io_l = io.size() - 1;
            for (int i = 0; i <= io_l; i++) io_map.insert({io[i],i});
        }

        // debug
        cout << "po_idx = " << po_idx << endl;
        cout << "io_f = " << io_f << endl;
        cout << "io_l = " << io_l << endl;
        
        if ( po_idx < 0 || io_f > io_l ) return nullptr;

        TreeNode* r = new TreeNode(po[po_idx]);
        po_idx--;
        
        if ( io_f == io_l ) return r;

        int io_idx = io_map.at(r->val);
        
        // debug
        cout << "io_idx = " << io_idx << endl;

        cout << "right" << endl;
        r->right = buildTree(io, po, io_idx + 1, io_l);

        cout << "left" << endl;
        r->left = buildTree(io, po, io_f, io_idx - 1);

        return r;
    }

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
    int po_sz;
    int po_idx = -999;
    unordered_map<int, int> io_map;

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

    Solution s;

    // leetcode example
    // https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
    // vector<int> inorder = {9,3,15,20,7};
    // vector<int> postorder = {9,15,7,20,3};
    // expect 3 9 20 null null 15 7

    // geeksforgeeks.org example
    // https://www.geeksforgeeks.org/construct-a-binary-tree-from-postorder-and-inorder/
    // https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
    // vector<int> inorder = {2,1,3};
    // vector<int> postorder = {2,3,1};
    // expect 1 2 3

    // geeksforgeeks.org example
    // https://www.geeksforgeeks.org/construct-a-binary-tree-from-postorder-and-inorder/
    // https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
    // vector<int> inorder = {4, 8, 2, 5, 1, 6, 3, 7};
    // vector<int> postorder = {8, 4, 5, 2, 6, 7, 3, 1};
    // expect 1 2 3 4 5 6 7 null 8
    
    // leetcode example
    vector<int> inorder = {1,2};
    vector<int> postorder = {2,1};
    // expect 1 null 2
    
    chrono::time_point<std::chrono::system_clock> start, end; 
  
    start = chrono::system_clock::now(); 

    TreeNode* tn = s.buildTree(inorder, postorder);

    end = std::chrono::system_clock::now(); 
    std::chrono::duration<double> elapsed_seconds = end - start; 
  
    cout << "elapsed time: " << elapsed_seconds.count() << endl; 
   
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
