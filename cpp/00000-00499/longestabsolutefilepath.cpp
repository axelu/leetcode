
// 388. Longest Absolute File Path
// https://leetcode.com/problems/longest-absolute-file-path/


class Solution {
private:
    struct Node {
        char type; // d directory, f file
        string name;
        vector<Node*> children;
        Node(char t, string name) : type(t), name(name), children({}) {}
    };

    Node * dfs(string& input, int n, int& i, int lvl) {
        // cout << "dfs i " << i << " lvl " << lvl << endl;

        // get name and type of node
        char type = 'd';
        string name = "";
        for(; i < n; ++i) {
            if( input[i] == 10 )
               break;
            if( input[i] == '.' )
                type = 'f';
            name += input[i];
        }

        // create node
        Node * node = new Node(type,name);

        while( i < n ) {
            // peek: is the next node a child of mine?
            // meaning is it a level below me
            int t = i;
            ++t; // advance new line
            int tab_cnt = 0;
            while( input[t] == 9 ) {
                ++tab_cnt;
                ++t;
            }
            if( tab_cnt == lvl + 1 ) {
                i = t;
                node->children.push_back(dfs(input,n,i,lvl+1));
            } else {
                break;
            }
        }

        return node;
    }

    int dfs2(Node * node) {

        // file nodes are leaf nodes
        if( node->type == 'f' )
            return node->name.size();

        int t = 0;
        for(auto child : node->children)
            t = max(t,dfs2(child));

        if( node->type == 'r' )
            return t == 0 ? 0 : t;
        else
            return t == 0 ? 0 : node->name.size() + 1 + t;
    }

public:
    int lengthLongestPath(string& input) {
        int n = input.size();

        // char 10 new line
        // char  9 tab

        Node * root = new Node('r',"");
        int i = 0;
        while( i < n ) {
            root->children.push_back(dfs(input,n,i,0));
            ++i; // advance new line
        }

        return dfs2(root);
    }
};
