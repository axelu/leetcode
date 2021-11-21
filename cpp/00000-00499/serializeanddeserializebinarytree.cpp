
// 297. Serialize and Deserialize Binary Tree
// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/





/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if( root == nullptr ) return "[]";

        stack<string> stck;

        // BFS
        queue<TreeNode*> q;
        TreeNode* qe;
        q.push(root);
        while( !q.empty() ) {
            qe = q.front();
            q.pop();
            if( qe == nullptr ) {
                stck.push("null");
            } else {
                stck.push(to_string(qe->val));
                q.push(qe->left);
                q.push(qe->right);
            }
        }

        string ans = "";
        string se;
        while( !stck.empty() ) {
            se = stck.top();
            stck.pop();
            if( ans.empty() && se == "null" ) continue;
            if( ans.empty() )
                ans = se;
            else
                ans = se + "," + ans;
        }
        ans = "[" + ans + "]";
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if( data == "[]" ) return nullptr;

        // remove leading '[' and trailing ']' and
        // split the input string by ','
        vector<string> v;
        stringstream ss(data.substr(1,data.size()-2));
        string s;
        while( getline(ss,s,',') )
            v.push_back(s);

        // the 1st element is our root
        TreeNode* root = new TreeNode(stoi(v[0]));

        // basically reverse the BFS we used when we serialized the tree
        // we maintain a counter of where we are in our serialized representation of the tree
        queue<TreeNode*> q;
        TreeNode* qe;
        q.push(root);
        int n = v.size();
        int i = 1; // we already processed the root at index 0
        while( !q.empty() ) {
            if( i == n ) break;
            qe = q.front();
            q.pop();
            if( v[i] != "null" ) {
                qe->left = new TreeNode(stoi(v[i]));
                q.push(qe->left);
            }
            ++i;
            if( i == n ) break;
            if( v[i] != "null" ) {
                qe->right = new TreeNode(stoi(v[i]));
                q.push(qe->right);
            }
            ++i;
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
