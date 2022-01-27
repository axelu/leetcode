
// 889. Construct Binary Tree from Preorder and Postorder Traversal
// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/




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
    int N;
    unordered_map<int,int> postOrderMap;
    TreeNode* constructFromPrePost(vector<int>& pre, int preFirst, int preLast, vector<int>& post, int postFirst, int postLast) {
        // root is 1st node in pre and last node in post
        TreeNode* root = new TreeNode(pre[preFirst]);

        int lftPreFirst,lftPreLast,lftPostLast,rgtPreFirst,rgtPostFirst,rgtPostLast;
        if( preFirst < preLast ) {
            // left subtree
            // the element immediate to root's right in preorder is root's left child
            // we need to locate said element in the post order, it will be the last element in post order
            //    for constructing the left subtree
            lftPreFirst = preFirst+1;
            lftPostLast = postOrderMap.find(pre[lftPreFirst])->second;
            lftPreLast = lftPreFirst + (lftPostLast-postFirst); // take as many elements as we are taking from postorder
            root->left = constructFromPrePost(pre,lftPreFirst,lftPreLast,post,postFirst,lftPostLast);

            // right subtree
            // preorder whatever is left after removing root and preorder substring from previous step
            // postorder whatever is left after removing root and postorder substring from previous step
            if( lftPreLast < preLast ) {
                rgtPreFirst = lftPreLast+1;
                rgtPostLast = postLast-1;
                rgtPostFirst = lftPostLast+1;
                root->right = constructFromPrePost(pre,rgtPreFirst,preLast,post,rgtPostFirst,rgtPostLast);
            }
        }

        return root;
    }
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        int N = pre.size(); // 1 <= pre.length == post.length <= 30
        if( N == 1 ) return new TreeNode(1);

        for(int i = 0; i < N; ++i) {
            postOrderMap.insert({post[i],i});
        }

        return constructFromPrePost(pre,0,N-1,post,0,N-1);
    }
};
