
// 3064. Guess the Number Using Bitwise Questions I
// https://leetcode.com/problems/guess-the-number-using-bitwise-questions-i/




/**
 * Definition of commonSetBits API.
 * int commonSetBits(int num);
 */

class Solution {
private:
    int rec(int s, int e) {

        int num = 0;
        for(int i = s; i <= e; ++i)
            num |= 1<<i;
        if( commonSetBits(num) == 0 )
            return 0;
        if( commonSetBits(num) == e - s + 1 )
            return num;

        int mid = s + ((e-s)/2);
        int r = rec(s, mid);
        int l = rec(mid+1, e);

        return r + l;
    }

public:
    int findNumber() {
        return rec(0,29);
    }
};
