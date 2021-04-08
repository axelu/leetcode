
// Print Binary Tree
// https://leetcode.com/problems/print-binary-tree/


#include <iostream>
#include <cassert>

#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>

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
    vector<vector<string>> printTree(TreeNode* root) {
        if( root->left == nullptr && root->right == nullptr ) return {{to_string(root->val)}};

        unordered_map<int,unordered_map<int,int>> t; // y x val
        _walk(root, 0, 0, t);

        // debug

        for(auto r : t) {
            cout << "row " << r.first << ":" << endl;
            for(auto c : r.second) {
                cout << "  x " << c.first << " val " << c.second << endl;
            }
        }


        // calculate number of cells based on number of rows
        int n = 0;
        for(int i = 0; i >= y_min; --i) {
            n += pow(2,abs(i));
        }
        cout << "number columns " << n << endl;

        // print the tree
        cout << "printing the tree" << endl;
        vector<vector<string>> r;
        int idx = n;
        for(int i = 0; i >= y_min; --i) {
            vector<string> z(n,"");
            cout << "z.size() " << z.size() << endl;
            for(string s : z ) cout << "|" << s << "| ";
            cout << endl;
            cout << "row " << i << endl;

            // calculate distance between nodes
            int dst = idx + 1;
            cout << "dst " << dst << endl;

            // calculate index of row ( row is zero indexed !!! )
            idx = idx / 2;
            cout << "idx " << idx << endl;

            // calculate x min and x max for row
            int x_min = 0;
            int x_max = 0;
            if( i < 0) {
                x_max = pow(2,abs(i) - 1);
                x_min = x_max * (-1);
            }
            cout << "x_min " << x_min << endl;
            cout << "x_max " << x_max << endl;

            // fill in the nodes
            unordered_map<int,int> c = t.find(i)->second;
            int zidx = idx;
            for(int k = x_min; k <= x_max; ++k) {
                if( i < 0 && k == 0 ) continue;
                auto p = c.find(k);
                if( p != c.end() ) {
                    cout << "writing on idx " << zidx << " val " << p->second << endl;
                    z[zidx] = to_string(p->second);
                    cout << "written" << endl;
                }
                zidx += dst;
            }

            r.push_back(z);
        }

        return r;
    }
private:
    int y_min = 0; // number rows

    void _walk(TreeNode* root, int x, int y, unordered_map<int,unordered_map<int,int>>& t) {
        if( root == nullptr ) return;

        // cout << "x " << x << " y " << y << " val " << root->val << endl;

        y_min = min(y_min, y);

        auto r = t.find(y);
        if( r != t.end() ) {
            r->second.insert({x,root->val});
        } else {
            unordered_map<int,int> c = {{x, root->val}};
            t.insert({y,c});
        }

        int xl;
        int xr;

        if( x < 0 ) {
            xl = 2 * x;
            xr = xl + 1;
        } else if ( x > 0 ) {
            xr = 2 * x;
            xl = xr - 1;
        } else {
            // x == 0
            xl = x - 1;
            xr = x + 1;
        }

        _walk(root->left, xl, y - 1, t);
        _walk(root->right, xr, y - 1, t);
    }
};



int main() {
    Solution s;

    TreeNode* t11 = new TreeNode(4);
    TreeNode* t12 = new TreeNode(3);
    t12->left = t11;
    TreeNode* t13 = new TreeNode(2);
    t13->left = t12;
    TreeNode* t14 = new TreeNode(5);
    TreeNode* t15 = new TreeNode(1,t13,t14);

    s.printTree(t15);

    cout << "final" << endl;



    return 0;
}
