
// 1483. Kth Ancestor of a Tree Node
// https://leetcode.com/problems/kth-ancestor-of-a-tree-node/





class TreeAncestor {
private:
    int nbr_nodes;
    vector<vector<int>> ancestor_map;
    // ancestor_map[0] ancestor map 1 up (2^0)
    // ancestor_map[1] ancestor map 2 up (2^1)
    // ancestor_map[2] ancestor map 4 up (2^2)
    // ancestor_map[3] ancestor map 8 up (2^3)
    // ans so on

    // vector<int> * ptr_parent;

    void print_ancestor_map() {
        cout << "\t";
        for(int i = 0; i < nbr_nodes; ++i)
            cout << i << "\t";
        cout << endl;

        for(int i = 0; i < ancestor_map.size(); ++i) {
            int up = pow(2,i);
            cout << i << " up " << up << "\t";
            for(int j = 0; j < nbr_nodes; ++j)
                cout << ancestor_map[i][j] << "\t";
            cout << endl;
        }
    }

public:
    TreeAncestor(int n, vector<int>& parent) {
        nbr_nodes = n;
        // ptr_parent = &parent;

        // what is given to us is basically the 1st ancestor of each node
        // basically: ancestor_map[0] = parent;
        ancestor_map.push_back(parent);

        bool has_ancestors = true;
        while(has_ancestors) {
            has_ancestors = false;
            vector<int> ancestors(n,-1);
            for(int i = 0; i < n; ++i) {
                if( ancestor_map.back()[i] != -1 ) {
                    ancestors[i] = ancestor_map.back()[ancestor_map.back()[i]];
                    if( ancestors[i] != -1 )
                        has_ancestors = true;
                }
            }
            ancestor_map.push_back(ancestors);
        }
        // print_ancestor_map();
    }

    int getKthAncestor(int node, int k) {
        /*
        // brute force
        for(int i = 1; i <= k; ++i) {
            node = ptr_parent->at(node);
            if( node == -1 )
                break;
        }
        return node;
        */

        // the key idea here is, that any non-negative number can be
        // uniquely represented as a sum of decreasing powers of two.
        // example 7 binary 111 -> 7 = 4 + 2 + 1
        // so if we have the following tree of 10 nodes:
        // [-1,0,1,2,3,4,5,6,7,8], which is row 0 in our ancestor_map
        // we get the following ancestor map
        //  	     0	 1	 2	 3	 4	 5	 6	 7	 8	 9
        // 0 up 1	-1	 0	 1	 2	 3	 4	 5	 6	 7	 8
        // 1 up 2	-1	-1	 0	 1	 2	 3	 4	 5	 6	 7
        // 2 up 4	-1	-1	-1	-1	 0	 1	 2	 3	 4	 5
        // 3 up 8	-1	-1	-1	-1	-1	-1	-1	-1	 0	 1
        // 4 up 16	-1	-1	-1	-1	-1	-1	-1	-1	-1	-1
        // lets assume we want to get the 7th ancestor of node 9:
        // k = 7, bit 0 is set, so we do the 1st lookup
        // lookup ancestor_map[0][9] -> node 8
        // right shift k by 1 bit -> k becomes 3
        // k = 3, bit 0 is set, so we do the next lookup
        // lookup ancestor_map[1][8] -> node 6
        // rigth shift k by 1 bit -> k becomes 1
        // lookup ancestor_map[2][6] -> node 2
        // rigth shift k by 1 bit -> k becomes 0 -> we are done
        // in other words
        // the 7th ancestor of node 9 is the same as
        // the 1st ancestor of node 9 -> that node's 2nd ancestor -> the node's 4th ancestor
        // 7 = 1                      +              2            +             4

        int i = 0; // index into our ancestor map = row in our map
        while(k > 0) {
            if( i >= ancestor_map.size())
                return -1;

            // cout << "k " << k << " i " << i << endl;
            if( k & 1 ) {
                // cout << "lookup ancestor_map[" << i << "][" << idx << "]" << endl;
                node = ancestor_map[i][node];
                if( node == -1 ) {
                    return -1;
                }
            }
            k >>= 1;
            ++i;
        }

        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */
