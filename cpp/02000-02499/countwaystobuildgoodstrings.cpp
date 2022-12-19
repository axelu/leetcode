
// 2466. Count Ways To Build Good Strings
// https://leetcode.com/problems/count-ways-to-build-good-strings/



class Solution {
private:
    long mod = 1000000007;

    int _low, _high, _zero, _one;

    int * mem;

    long rec(int pos) {

        if( mem[pos] != -1 )
            return mem[pos];

        // at each position we have a choice
        //      append zero 0s OR
        //      append one 1s
        // if we are after doing so between [low,high]
        // then we can count the answer

        long ret = 0;

        int l_new; // length after adding zero 0s or one 1s

        l_new = pos + _zero;
        if( l_new >= _low && l_new <= _high )
            ret = ret + 1;
        if( l_new < _high )
            ret = (ret + rec(l_new)) % mod;

        l_new = pos + _one;
        if( l_new >= _low && l_new <= _high )
            ret = ret + 1;
        if( l_new < _high )
            ret = (ret + rec(l_new)) % mod;

        return mem[pos] = ret;
    }

public:
    int countGoodStrings(int low, int high, int zero, int one) {
        _low = low;
        _high = high;
        _zero = zero;
        _one = one;

        mem = new int[high+1];
        for(int i = 0; i <= high; ++i)
            mem[i] = -1;
        return rec(0);
    }
};
