
// 2912. Number of Ways to Reach Destination in the Grid
// https://leetcode.com/problems/number-of-ways-to-reach-destination-in-the-grid/







class Solution {
private:
    long mod = 1000000007;

    long rec(long m, long n, int k, int in_dest_row, int in_dest_col, long mem[][2][2]) {
        // k number of remaining moves
        if( k == 1 ) {
            // we have one more move left
            // as we can only move either horizontally or vertically,
            // we can reach the destination if we are either in the destination row or
            // if we are in the destination column, but not in both
            return (in_dest_row && !in_dest_col) || (!in_dest_row && in_dest_col) ? 1L : 0L;
        }

        if( mem[k][in_dest_row][in_dest_col] != -1 )
            return mem[k][in_dest_row][in_dest_col];

        long ret = 0L;

        // k > 1
        // we have a choice
        //    we move horizontally OR
        //    we move vertically

        // horizontal
        if( in_dest_col == 1 ) {
            // if we are in the destination column, we can pick from n-1 other columns
            ret = (ret + (n-1L) * rec(m,n,k-1,in_dest_row,0,mem)) % mod;
        } else {
            // if we are not in the destination column, we have two options:
            //     we move into the destination column -> 1 pick OR
            //     we move into another non-destination column
            //        (so we cannot pick the destination column nor the column we are in -> n-2 picks)
            ret = (ret + rec(m,n,k-1,in_dest_row,1,mem)) % mod;
            ret = (ret + (n-2L) * rec(m,n,k-1,in_dest_row,0,mem)) % mod;
        }

        // vertical
        if( in_dest_row == 1 ) {
            // same comment as for columns above
            ret = (ret + (m-1L) * rec(m,n,k-1,0,in_dest_col,mem)) % mod;
        } else {
            // same comment as for columns above
            ret = (ret + rec(m,n,k-1,1,in_dest_col,mem)) % mod;
            ret = (ret + (m-2L) * rec(m,n,k-1,0,in_dest_col,mem)) % mod;
        }

        return mem[k][in_dest_row][in_dest_col] = ret;
    }



public:
    int numberOfWays(int m, int n, int k, vector<int>& source, vector<int>& dest) {
        int in_dest_row = 0;
        if( source[0] == dest[0] )
            in_dest_row = 1;

        int in_dest_col = 0;
        if( source[1] == dest[1] )
            in_dest_col = 1;

        long mem[k+1][2][2];memset(mem,-1,sizeof mem);
        return rec(m,n,k,in_dest_row,in_dest_col,mem);
    }
};
