
// 2312. Selling Pieces of Wood
// https://leetcode.com/problems/selling-pieces-of-wood/





class Solution {
private:
    int _prices[201][201]; // height,width
    long long mem[201][201];

    long long rec(int m, int n) {
        // cout << "rec m " << m << " n " << n << endl;
        // m rows   = height       -> cut horizontally
        // n colums = width        -> cut vertically

        if( m == 1 && n == 1 )
            return _prices[m][n];

        if( mem[m][n] != -1 )
            return mem[m][n];

        // we have a choice
        //    sell the wood in its current size OR
        //    cut the wood horizontally OR
        //    cut the wood vertically

        // sell the wood in its current size
        long long a = _prices[m][n];

        // cut the wood horizontally
        long long b = 0;
        if( m > 1 ) {
            // we can make m-1 cuts
            for(int i = 1; i <= m-1; ++i) {
                // upper part height i
                // lower part height m-i
                b = max(b,rec(i,n)+rec(m-i,n));
            }
        }

        // cut the wood vertically
        long long c = 0;
        if( n > 1 ) {
            // we can make n-1 cuts
            for(int i = 1; i <= n-1; ++i) {
                // left part width i
                // right part width n-i
                c = max(c,rec(m,i)+rec(m,n-i));
            }
        }

        return mem[m][n] = max({a,b,c});
    }

public:
    long long sellingWood(int m, int n, vector<vector<int>>& prices) {
        // m rows = height
        // n cols = width

        // prices[i] = [hi, wi, pricei]

        memset(_prices,0,sizeof _prices);
        for(auto& v: prices)
            _prices[v[0]][v[1]] = v[2];

        memset(mem,-1,sizeof mem);
        return rec(m,n);
    }
};
