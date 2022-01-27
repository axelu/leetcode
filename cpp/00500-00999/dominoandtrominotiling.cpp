
// 790. Domino and Tromino Tiling
// https://leetcode.com/problems/domino-and-tromino-tiling/




class Solution {
private:
    long mod = 1000000007;

    long rec(int n, int i0, int i1, long mem[]) {
        // 1 -> ans 1
        // 2 -> ans 2
        // 3 -> ans 5
        if( (i0 == n   && i1 == n-1) || (i0 == n-1 && i1 == n)  )
            return 0;
        if( i0 == n-1 && i1 == n-1 || i0 == n && i1 == n)
            return 1;
        if( i0 == n-2 && i1 == n-2 )
            return 2;

        int memIdx = i0*n+i1;
        if( mem[memIdx] != -1 )
            return mem[memIdx];


        long a = 0, b = 0, c = 0, d = 0;
        if( i0 == i1 ) {
            // place a domino tile standing up |
            a = rec(n,i0+1,i1+1,mem);
            // place two domino tiles horizontally ==
            b = rec(n,i0+2,i1+2,mem);
            // place a tromino tile |_
            c = rec(n,i0+1,i1+2,mem);
            // place a tromino tile |-
            d = rec(n,i0+2,i1+1,mem);

        } else if( i0 > i1 ) {
            // place a tromino tile _|
            a = rec(n,i0+1,i1+2,mem);
            // place a domino tile _
            b = rec(n,i0,i1+2,mem);
        } else {
            // i0 < i1
            // place a tromino tile -|
            a = rec(n,i0+2,i1+1,mem);
            // place a domino tile -
            b = rec(n,i0+2,i1,mem);
        }



        return mem[memIdx] = (a+b+c+d)%mod;
    }
public:
    int numTilings(int n) {
        long mem[n*n];memset(mem,-1,sizeof mem);
        return rec(n,0,0,mem);

    }
};
