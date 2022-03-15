
// 1259. Handshakes That Don't Cross
// https://leetcode.com/problems/handshakes-that-dont-cross/


class Solution {
private:
    long mod = 1000000007;

    long rec(int numPeople, long mem[]) {
        if( mem[numPeople] != -1 )
            return mem[numPeople];

        long ret = 0L;

        // we have a choice of which two people we have shaking hands
        // we split the people into two sides
        // amongst the two people shaking hands
        // multiplying the number of times each side
        // can shake hands gives us all possibilities
        // example 6 people
        // first two people shaking hands,  leaves us 0 people to the left and 4 to the right
        // second two people shaking hands, leaves us 2 people to the left and 2 to the right
        // last two people shaking hands,   leaves us 4 people to the left and 0 to the right

        for(int k = 2; k <= numPeople; k += 2) {
            long t1 = rec(k - 2, mem);
            long t2 = rec(numPeople - k, mem);
            long t = (t1 * t2) % mod;
            ret = (ret + t) % mod;
        }

        return mem[numPeople] = ret;
    }

public:
    int numberOfWays(int numPeople) {

        long mem[numPeople+1];memset(mem,-1,sizeof mem);
        mem[0] = 1;

        return rec(numPeople,mem);
    }
};
