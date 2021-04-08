
// Maximum Width of Binary Tree
// https://leetcode.com/problems/maximum-width-of-binary-tree/



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
    int widthOfBinaryTree(TreeNode* root) {
        if( root == nullptr ) return 0;


        _walk(root, 0, 0);

        cout << "xmin" << endl;
        for(auto yx : xmin) cout << yx.first << " " << yx.second << endl;;
        cout << "xmax" << endl;
        for(auto yx : xmax) cout << yx.first << " " << yx.second << endl;


        return width;
    }

private:
    long long int width = 1;
    bool track = false;
    unordered_map<int,long long int> xmin; // keyed by row
    unordered_map<int,long long int> xmax; // keyed by row

    void _walk(TreeNode* root, long long int x, int y) {
        if( root == nullptr ) return;

        // only start tracking when root->left != nullptr && root->right != nullptr
        if( root->left != nullptr && root->right != nullptr ) track = true;

        // cout << "val " << root->val << " x " << x << " y " << y << endl;

        if( track ) {

        if( xmin.find(y) != xmin.end() ) {
            // cout << "updating" << endl;
            if( x < xmin[y] ) xmin[y] = x;
            if( x > xmax[y] ) xmax[y] = x;
            // offset when not crossing 0
            long long int offset = ( (xmin[y] < 0 && xmax[y] < 0) || (xmin[y] > 0 && xmax[y] > 0) ) ? 1 : 0;
            // cout << "xmax[y] - xmin[y] " << xmax[y] << " - " << xmin[y] << " = " << xmax[y] - xmin[y] << endl;
            width = max(width, xmax[y] - xmin[y] + offset);
        } else {
            // cout << "inserting" << endl;
            xmin.insert({y,x});
            xmax.insert({y,x});
        }

        long long int xl;
        long long int xr;

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

        _walk(root->left, xl, y - 1);
        _walk(root->right, xr, y - 1);

        } else {

        _walk(root->left, 0, 0);
        _walk(root->right, 0, 0);
        }
    }
};



int main() {
    Solution s;

    TreeNode* t11 = new TreeNode(5);
    TreeNode* t12 = new TreeNode(3);
    TreeNode* t13 = new TreeNode(3);
    t13->left = t11;
    t13->right = t12;
    TreeNode* t14 = new TreeNode(9);
    TreeNode* t15 = new TreeNode(2);
    t15->right = t14;
    TreeNode* t16 = new TreeNode(1);
    t16->left = t13;
    t16->right = t15;

    int r = s.widthOfBinaryTree(t16);

    cout << r << endl;



    return 0;
}
