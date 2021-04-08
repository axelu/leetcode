#include <iostream>
#include <cassert>

#include <vector>
#include <map>
#include <tuple>
#include <set>

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

// Vertical Order Traversal of a Binary Tree
// day 7 problem of the August 2020 challenge
// https://leetcode.com/explore/featured/card/august-leetcoding-challenge/549/week-1-august-1st-august-7th/3415/

class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {

        vector<vector<int>> r;
        
        if ( root == nullptr ) return r;

        map<int, map<int, multiset<int>>*> m;
        walk(root, 0, 0, &m);

        // debug
        // cout << endl;
        for (auto itx = m.begin(); itx != m.end(); ++itx) {
            vector<int> vinner;
            for (auto ity = itx->second->rbegin(); ity != itx->second->rend(); ++ity) {
                // debug
                // cout << "x=" << itx->first;
                // cout << " y=" << ity->first << " values=";
                for (auto itv = ity->second.begin(); itv != ity->second.end(); itv++) {
                    // debug
                    // cout << *itv;
                    vinner.push_back(*itv);
                }
                // cout << endl;
            }
            r.push_back(vinner);
        }
        // debug
        // cout << endl;

        return r;

    }

    void walk(TreeNode* tn, int x, int y, map<int, map<int, multiset<int>>*>* m) {

        if ( tn != nullptr ) {
            // debug
            // cout << "x=" << x << " y=" << y << " t=" << tn->val << endl;

            auto xit = m->find(x);
            if ( xit == m->end() ) {
                // x not found
                // cout << "x not found" << endl;
                multiset<int> v = {tn->val};
                map<int, multiset<int>>* yv = new map<int, multiset<int>>;
                yv->insert({y,v});
                m->insert({x,yv}); 
            } else {
                // x found
                // cout << "x found" << endl;
                map<int, multiset<int>>* yv = xit->second;

                // debug
                // cout << "y map before" << endl;
                // for (auto it = yv->begin(); it != yv->end(); ++it) {
                //     cout << "y=" << it->first << " values=";
                //     for (auto itv = it->second.begin(); itv != it->second.end(); ++itv) {
                //         cout << *itv;
                //     }
                //     cout << endl;
                // }

                auto yit = yv->find(y);
                if ( yit == yv->end() ) {
                    // y not found
                    // cout << "y not found" << endl;
                    multiset<int> v = {tn->val};
                    yv->insert({y,v});
                } else {
                    // y found
                    // cout << "y found" << endl;
                    multiset<int>* v = &yit->second;
                    v->insert(tn->val);
                }
                
                // debug
                // cout << "y map after" << endl;
                // for (auto it = yv->begin(); it != yv->end(); ++it) {
                //     cout << "y=" << it->first << " values=";
                //     for (auto itv = it->second.begin(); itv != it->second.end(); ++itv) {
                //         cout << *itv;
                //     }
                //     cout << endl;
                // }

            }

            // left
            walk(tn->left, x-1, y-1, m);
            // right
            walk(tn->right, x+1, y-1, m);
        }

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
    
    // map<tuple<int, int>, multiset<int>> m;

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

    // vector<string> r; // sample tree flattened expected: 5 3 6 2 4 null 7
    // s.flatten(&root, &r);

    /*
    if (!r.empty()) {                                                     
        for (auto i : r) {                                                
            cout << i << " ";                                             
        }
        cout << endl;
    } 
    */

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

    string ft;
    TreeNode* tn;

    // ft = "[5,3,6,2,4,null,7]";
    // tn = s.buildTree(ft);

    vector<string> ftn;
    // s.flatten(tn, &ftn);

    /*
    if (!ftn.empty()) {                                                     
        for (auto i : ftn) {                                                
            cout << i << " ";                                             
        }
        cout << endl;
    } 
    */


    vector<vector<int>> r;

    ft = "[3,9,20,null,null,15,7]";
    cout << ft << endl;
    tn = s.buildTree(ft);
    r = s.verticalTraversal(tn);

    vector<vector<int>> correct1;
    vector<int> v11 = {9};
    correct1.push_back(v11);
    vector<int> v12 = {3,15};
    correct1.push_back(v12);
    vector<int> v13 = {20};
    correct1.push_back(v13);
    vector<int> v14 = {7};
    correct1.push_back(v14);
    
    assert(r == correct1);



    ft = "[1,2,3,4,5,6,7]";
    cout << ft << endl;
    tn = s.buildTree(ft);
    r = s.verticalTraversal(tn);

    vector<vector<int>> correct2;
    vector<int> v21 = {4};
    correct2.push_back(v21);
    vector<int> v22 = {2};
    correct2.push_back(v22);
    vector<int> v23 = {1,5,6};
    correct2.push_back(v23);
    vector<int> v24 = {3};
    correct2.push_back(v24);
    vector<int> v25 = {7};
    correct2.push_back(v25);
    
    assert(r == correct2);




    return 0;
}
