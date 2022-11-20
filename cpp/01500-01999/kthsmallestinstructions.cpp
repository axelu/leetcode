
// 1643. Kth Smallest Instructions
// https://leetcode.com/problems/kth-smallest-instructions/




class Solution {
private:
    int m,n;
    int mem[16][16];

    int dfs(int i, int j) {
        // cout << "dfs i " << i << " j " << j << endl;
        if( i == m && j == n )
            return 1;

        if( mem[i][j] != -1 )
            return mem[i][j];

        int ret = 0;

        // go right => Horizontal
        if( j+1 <= n ) {
            ret += dfs(i,j+1);
        }

        // go down => Vertical
        if( i+1 <= m )
            ret += dfs(i+1,j);

        return mem[i][j] = ret;
    }

public:
    string kthSmallestPath(vector<int>& destination, int k) {
        // example let destiniation be {2,3}
        // which is basically a matrix with 3 rows and 4 columns
        // the lexicographically best path would be:
        // HHHVV, basically H*columns and V*rows
        // all path have the same number of Hs and Vs
        // "HHHVV",
        // "HHVHV",
        // "HHVVH",
        // "HVHHV",
        // "HVHVH",
        // "HVVHH",
        // "VHHHV",
        // "VHHVH",
        // "VHVHH",
        // "VVHHH"
        // worst case destination {15,15}, k = 155117520 = nCr(row + column, row)

        m = destination[0]; // rows-1
        n = destination[1]; // cols-1

        memset(mem,-1,sizeof mem);
        dfs(0,0);

        /*
        // debug
        for(int i = 0; i <= m; ++i) {
            for(int j = 0; j <= n; ++j)
                cout << mem[i][j] << " ";
            cout << endl;
        }
        */

        string s = "";
        int i = 0, j = 0;
        while( true) {
            // cout << "i " << i << " j " << j << " k " << k << endl;

            if( i == m && j+1 == n ) {
                s += 'H';
                break;
            } else if( i+1 == m && j == n ) {
                s += 'V';
                break;
            }

            if( j+1 <= n ) {
                if( mem[i][j+1] >= k ) {
                    s += 'H';
                    j = j + 1;
                } else {
                    s += 'V';
                    k = k - mem[i][j+1];
                    i = i + 1;
                }
            } else {
                s += 'V';
                i = i + 1;
            }
        }

        return s;
    }
};
