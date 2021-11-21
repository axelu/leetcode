
// 331. Verify Preorder Serialization of a Binary Tree
// https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/




class Solution {
private:
    int N;
    bool isValid;

    vector<string> path2vector(string& path) {
        vector<string> v;
        stringstream ss(path);
        string s;
        while( getline(ss,s,',') )
            v.push_back(s);
        return v;
    }

    void dfs(int& i, vector<string>& preorder) {
        if( !isValid ) return;

        if( i >= N ) {
            isValid = false;
            return;
        }

        string s = preorder[i];
        ++i;                    // advance
        if( s == "#" ) return;  // leaf node
        dfs(i,preorder);        // left
        dfs(i,preorder);        // right
    }

public:
    bool isValidSerialization(string& preorder) {
        vector<string> vPreorder = path2vector(preorder);
        N = vPreorder.size();

        isValid = true;
        int i = 0;
        dfs(i,vPreorder);
        return isValid && i == N;
    }
};
