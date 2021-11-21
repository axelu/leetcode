
// 428. Serialize and Deserialize N-ary Tree
// https://leetcode.com/problems/serialize-and-deserialize-n-ary-tree/




/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        if( root == nullptr ) return "[]";

        stack<string> stck;

        // BFS, level order traversal
        queue<Node*> q;
        Node* qe;
        q.push(root);
        q.push(nullptr);
        while( !q.empty() ) {
            qe = q.front();
            q.pop();
            if( qe == nullptr ) {
                stck.push("null");
            } else {
                stck.push(to_string(qe->val));
                for(int i = 0; i < qe->children.size(); ++i)
                    q.push(qe->children[i]);
                q.push(nullptr); // seperate each group of children
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
        cout << ans << endl;
        return ans;
    }

    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        if( data == "[]" ) return nullptr;

        // remove leading '[' and trailing ']' and
        // split the input string by ','
        vector<string> v;
        stringstream ss(data.substr(1,data.size()-2));
        string s;
        while( getline(ss,s,',') )
            v.push_back(s);

        // the 1st element is our root
        Node* root = new Node(stoi(v[0]));

        // basically reverse the BFS we used when we serialized the tree
        // we maintain a counter of where we are in our serialized representation of the tree
        queue<Node*> q;
        Node* qe;
        q.push(root);
        int n = v.size();
        int i = 2; // we already processed the root at index 0 and its children (if any) seperator
        while( !q.empty() ) {
            if( i >= n ) break;
            qe = q.front();
            q.pop();
            while( v[i] != "null" ) {
                qe->children.push_back(new Node(stoi(v[i])));
                q.push(qe->children.back());
                ++i;
                if( i == n ) break;
            }
            ++i;
        }
        return root;
     }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
