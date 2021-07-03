
// 1361. Validate Binary Tree Nodes
// https://leetcode.com/problems/validate-binary-tree-nodes/




class Solution {
private:
    bool dfs(int tree[][2], int root, int seen[], int& cnt) {
        if( seen[root] ) return false; // same node seen more than once
        seen[root] = 1;
        ++cnt;

        if( tree[root][0] != -1 )
            if( !dfs(tree,tree[root][0],seen,cnt) )
                return false;
        if( tree[root][1] != -1 )
            return dfs(tree,tree[root][1],seen,cnt);
        return true;
    }

public:
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        int seen[n];memset(seen,0,sizeof seen);
        int tree[n][2];memset(tree,-1,sizeof tree);

        int i;

        int c = 0; // parent count
        for(i = 0; i < n; ++i) {
            if( leftChild[i] != -1 ) {
                if( seen[leftChild[i]] ) return false; // node w/ more than one parent
                seen[leftChild[i]] = 1;
                ++c;
                tree[i][0] = leftChild[i];
            }
            if( rightChild[i] != -1 ) {
                if( seen[rightChild[i]] ) return false; // node w/ more than one parent
                seen[rightChild[i]] = 1;
                ++c;
                tree[i][1] = rightChild[i];
            }
        }
        if( c != n-1 ) return false; // more than one node w/o a parent

        // get node w/o parent
        for(i = 0; i < n; ++i)
            if( !seen[i] ) break;

        memset(seen,0,sizeof seen);
        c = 0; // node count, if not equal n than we have more than one root
        bool t = dfs(tree,i,seen,c);
        return !t || c != n ? false : true;
    }
};
