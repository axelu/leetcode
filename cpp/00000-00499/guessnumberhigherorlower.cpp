
// 375. Guess Number Higher or Lower II
// https://leetcode.com/problems/guess-number-higher-or-lower-ii/

class Solution {
private:
    int mem[201][201];

    int rec(int i, int j) {
        // i <= j
        if( i == j ) {
            // we pick k == i == j
            // we don't have to pay
            return 0;

        } else if( j - i == 1 ) {
            // we would pick k == i and if we are wrong
            // we would pay i
            return i;

        } else if( j - i == 2 ) {
            // we pick k to be the number between i and j
            // if we are wrong we have to pay k
            return i+1;

        } else {

            if( mem[i][j] != -1 )
                return mem[i][j];

            int ret = INT_MAX;

            // pick a number k between i and j inclusive
            int t;
            for(int k = i+1; k < j; ++k) {
                t = k + max(rec(i,k-1),rec(k+1,j));
                ret = min(ret,t);
            }
            return mem[i][j] = ret;
        }
    }

public:
    int getMoneyAmount(int n) {
        // any number between 1 and n can be picked as the number to guess
        // any number between 1 and n can be our guess

        memset(mem,-1,sizeof mem);
        return rec(1,n);
    }
};
