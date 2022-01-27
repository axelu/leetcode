
// 701. Insert into a Binary Search Tree
// day 6 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/559/week-1-october-1st-october-7th/3485/
// https://leetcode.com/problems/insert-into-a-binary-search-tree/




#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <iterator>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <map>
#include <cmath>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

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
private:
    void _walk(TreeNode* root, int val) {
        int p = root->val;
        if( val < p ) {
            if( root->left == nullptr ) {
                root->left = new TreeNode(val);
                return;
            } else {
                _walk(root->left, val);
            }
        } else {
            // val > p
            if( root->right == nullptr ) {
                root->right = new TreeNode(val);
                return;
            } else {
                _walk(root->right, val);
            }
        }
    }
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if( root == nullptr ) return new TreeNode(val);

        _walk(root,val);
        return root;
    }
};

int main() {

    // chrono::time_point<chrono::system_clock> start;
    // chrono::time_point<chrono::system_clock> end;
    // chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;

    // Example 1
    TreeNode* t1 = new TreeNode(1);
    TreeNode* t2 = new TreeNode(3);
    TreeNode* t3 = new TreeNode(2);
    t3->left = t1;
    t3->right = t2;
    TreeNode* t4 = new TreeNode(7);
    TreeNode* t5 = new TreeNode(4);
    t5->left = t3;
    t5->right = t4;
    s.insertIntoBST(t5,5);;




    return 0;
}
