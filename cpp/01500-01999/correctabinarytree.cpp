
// 1660. Correct a Binary Tree
// https://leetcode.com/problems/correct-a-binary-tree/





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
    struct T {
        TreeNode* node;
        TreeNode* parent;
        int depth;
        T(TreeNode* node, TreeNode* parent, int x) : node(node), parent(parent), depth(x) {}
    };

public:
    TreeNode* correctBinaryTree(TreeNode* root) {

        // BFS
        queue<T*> q;
        unordered_set<TreeNode*> s;
        T* qe = new T(root,nullptr,0);
        q.push(qe);
        int currDepth = 0;
        while( ! q.empty() ) {
            qe = q.front();
            q.pop();
            // new depth?
            if( qe->depth != currDepth ) {
                s.clear();
                currDepth = qe->depth;
            } else {
                if( qe->node->right != nullptr && s.find(qe->node->right) != s.end() ) {
                    // found our invalid node
                    if( qe->parent->left != nullptr && qe->parent->left == qe->node )
                        qe->parent->left = nullptr;
                    else
                        qe->parent->right = nullptr;
                    break;
                }
            }
            s.insert(qe->node);
            if( qe->node->right != nullptr ) {
                T* t = new T(qe->node->right,qe->node,qe->depth+1);
                q.push(t);
            }
            if( qe->node->left != nullptr ) {
                T* t = new T(qe->node->left,qe->node,qe->depth+1);
                q.push(t);
            }
        }

        return root;
    }
};
