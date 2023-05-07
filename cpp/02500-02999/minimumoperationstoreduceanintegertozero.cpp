
// 2571. Minimum Operations to Reduce an Integer to 0
// https://leetcode.com/problems/minimum-operations-to-reduce-an-integer-to-0/



class Solution {
public:
    int minOperations(int n) {
        // example
        // binary
        // 39            100111
        // +1  2^0 = 40  101000
        // -8  2^3 = 32  100000
        // -32 2^5 = 0   000000

        // add if it reduces the number of set bits
        // it reduces it, if there are two or more consecutive set bits

        int ans = 0;

        int cnt = 0;
        for(int i = 0; i < 19; ++i) {
            if( (n >> i) & 1 ) {
                ++cnt;
            } else {
                if( cnt == 1 ) {
                    // we would subtract 2^(i-1)
                    ++ans;
                    cnt = 0;
                } else if( cnt > 1 ) {
                    // we would add 2^(i-cnt)
                    ++ans;
                    // our current unset bit would become set
                    cnt = 1;
                }
            }
        }

        return ans;
    }
};
