
// Sum of Root To Leaf Binary Numbers
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/555/week-2-september-8th-september-14th/3453/



#include <iostream>
#include <cassert>

#include <vector>
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
    int sumRootToLeaf(TreeNode* root) {
        if( root == nullptr ) return 0;

        _walk(root);

        return sum;
    }
private:
    vector<int> path;
    int sum = 0;

    void _walk(TreeNode* root) {
        if( root == nullptr ) return;

        // add myself to path
        path.push_back(root->val);

        if( root->left == nullptr && root->right == nullptr ) {
            // if I am a leaf node, add my current path to sum
            int s = 0;
            int e = 0;
            for(auto it = path.rbegin(); it != path.rend(); ++it) {
                s += *it * pow(2,e);
                ++e;
            }
            sum += s;
        } else {
            _walk(root->left);
            _walk(root->right);
        }

        // remove myself from path
        path.pop_back();
    }
};



int main() {
    Solution s;

    TreeNode* t11 = new TreeNode(0);
    TreeNode* t12 = new TreeNode(1);
    TreeNode* t13 = new TreeNode(0);
    t13->left = t11;
    t13->right = t12;
    TreeNode* t14 = new TreeNode(0);
    TreeNode* t15 = new TreeNode(1);
    TreeNode* t16 = new TreeNode(1);
    t16->left = t14;
    t16->right = t15;
    TreeNode* t17 = new TreeNode(1);
    t17->left = t13;
    t17->right = t16;

    int r = s.sumRootToLeaf(t17);

    cout << r << endl;



    return 0;
}
