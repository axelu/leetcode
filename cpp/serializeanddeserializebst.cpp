
// Serialize and Deserialize BST
// day 9 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/560/week-2-october-8th-october-14th/3489/
// https://leetcode.com/problems/serialize-and-deserialize-bst/



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
#include <climits>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
private:
    string _itob36(int i) {
        string s;
        int tmp;
        do {
            tmp = i;
			i /= 36;
			s += "ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[35 + (tmp - i * 36)];
        } while( i );
        reverse(begin(s),end(s));
        return s;
    }

    void _flatten(vector<TreeNode*> v, string& r) {
        vector<TreeNode*> z;
        for (TreeNode* t : v) {
            if ( t == nullptr ) {
                r += ",";
            } else {
                r += "," + _itob36(t->val);
                z.push_back(t->left);
                z.push_back(t->right);
            }
        }
        if ( !z.empty() ) _flatten(z, r);
    }

    pair<TreeNode*,int> _getNext(const string & data, const int & n, int pos) {
        TreeNode* t = nullptr;
        if( pos < n ) {
            auto next = data.find(",",pos);
            if( next == string::npos ) {
                t = new TreeNode(stoi(data.substr(pos),nullptr,36));
                pos = n;
            } else {
                if( next != pos )
                    t = new TreeNode(stoi(data.substr(pos, next - pos),nullptr,36));
                pos = next + 1;
            }
        }
        return make_pair(t,pos);
    }

    void _buildTree(vector<TreeNode*> vt, const string & data, const int & n, int pos) {
        if( pos == n ) return;
        vector<TreeNode*> z;
        for (auto t : vt) {
            // left
            auto p = _getNext(data,n,pos);
            if( p.first != nullptr ) {
                t->left = p.first;
                z.push_back(p.first);
            }
            pos = p.second;
            // right
            p = _getNext(data,n,pos);
            if( p.first != nullptr ) {
                t->right = p.first;
                z.push_back(p.first);
            }
            pos = p.second;
        }
        if( !z.empty() ) _buildTree(z, data, n, pos);
    }

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if( root == nullptr ) return "";

        string r = _itob36(root->val);

        vector<TreeNode*> vt;
        vt.push_back(root->left);
        vt.push_back(root->right);

        _flatten(vt, r);

        // strip trailing null's
        auto const pos = r.find_last_of("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        if( pos != string::npos ) r.erase(pos+1);

        return r;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if( data == "" ) return nullptr;

        auto n = data.size();
        auto [t,pos] = _getNext(data,n,0);
        if( pos != n ) {
            vector<TreeNode*> vt{t};
            _buildTree(vt, data, n, pos);
        }

        return t;
    }
};


int main() {

    // Your Codec object will be instantiated and called as such:
    // Codec* ser = new Codec();
    // Codec* deser = new Codec();
    // string tree = ser->serialize(root);
    // TreeNode* ans = deser->deserialize(tree);
    // return ans;

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
    TreeNode* subtree1 = new TreeNode(2);
    TreeNode* subtree2 = new TreeNode(4);
    TreeNode* subtree3 = new TreeNode(3);
    subtree3->left = subtree1;
    subtree3->right = subtree2;
    TreeNode* subtree4 = new TreeNode(7);
    TreeNode* subtree5 = new TreeNode(19);
    subtree5->right = subtree4;
    TreeNode* root = new TreeNode(2147483647);
    root->left = subtree3;
    root->right = subtree5;

    Codec* ser = new Codec();
    string tree = ser->serialize(root);
    cout << "result " << tree << endl;

    Codec* deser = new Codec();
    TreeNode* ans = deser->deserialize(tree);

    tree = ser->serialize(ans);
    cout << "result " << tree << endl;

    // case 10 initially runtime error
    // [5,3,6,2,4,null,null,1]
    subtree1 = new TreeNode(1);
    subtree2 = new TreeNode(2);
    subtree2->left = subtree1;
    subtree3 = new TreeNode(4);
    subtree4 = new TreeNode(3);
    subtree4->left = subtree2;
    subtree4->right = subtree3;
    subtree5 = new TreeNode(6);
    TreeNode* subtree6 = new TreeNode(5);
    subtree6->left = subtree4;
    subtree6->right = subtree5;

    tree = ser->serialize(subtree6);
    cout << "result " << tree << endl;

    ans = deser->deserialize(tree);

    tree = ser->serialize(ans);
    cout << "result " << tree << endl;

    // case 12 initially wrong answer
    // in  [41,37,44,24,39,42,48,1,35,38,40,null,43,46,49,0,2,30,36,null,null,null,null,null,null,45,47,null,null,null,null,null,4,29,32,null,null,null,null,null,null,3,9,26,null,31,34,null,null,7,11,25,27,null,null,33,null,6,8,10,16,null,null,null,28,null,null,5,null,null,null,null,null,15,19,null,null,null,null,12,null,18,20,null,13,17,null,null,22,null,14,null,null,21,23]
    // out [41,37,44,24,39,42,48,1,35,38,40,null,43,46,49,0,2,30,36,null,null,null,null,null,null,45,47,null,null,null,null,null,4,29,32,null,null,null,null,null,null,3,9,26,null,31,34,null,null,7,11,25,27,null,null,33,null,6,8,10,16,null,null,null,28,null,null,5,null,null,null,null,null,15,16,null,null,null,null,12,null,18,20,null,13,17,null,null,22,null,14,null,null,21,23]

/*
    root = new TreeNode(9999);
    TreeNode* parent = root;
    for(int i = 9998; i >= 0; --i) {
        TreeNode* child = new TreeNode(i);
        parent->left = child;
        parent = child;
    }

    tree = ser->serialize(root);
    cout << "result " << tree << endl;

    ans = deser->deserialize(tree);

    tree = ser->serialize(ans);
    cout << "result " << tree << endl;
*/
    return 0;
}
