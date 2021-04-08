
// Unique Binary Search Trees II
// https://leetcode.com/problems/unique-binary-search-trees-ii/




#include <iostream>
#include <cassert>

#include <vector>


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
public:
    vector<TreeNode*> generateTrees(int n) {
        if( n == 0 ) return {};
        if( n == 1 ) {
            TreeNode* t = new TreeNode(1);
            return {t};
        }

        // recursion
        return generateTrees(1,n);
    }
private:

    vector<TreeNode*> generateTrees(int b, int n) {
        // cout << "b " << b << " n " << n << endl;
        // when our begin and end indicies cross return nullptr list
        if( b > n ) return {nullptr};

        vector <TreeNode*> v;

        for(int i = b; i <= n; ++i) {
            vector <TreeNode*> l = generateTrees(b, i - 1);
            vector <TreeNode*> r = generateTrees(i + 1, n);

            // return all possible combinations
            for(int k = 0; k < l.size(); ++k)
                for(int m = 0; m < r.size(); ++m) {

                    TreeNode* root = new TreeNode(i);
                    root->left = l[k];
                    root->right = r[m];
                    v.push_back(root);
                }
        }

        return v;
    }
};

int main() {

    Solution s;

    // s.generateTrees(3); // 5
    assert(s.generateTrees(3).size() == 5);

    // s.generateTrees(4); // 14
    assert(s.generateTrees(4).size() == 14);

    // s.generateTrees(8); // 1430
    assert(s.generateTrees(8).size() == 1430);

    return 0;
}
