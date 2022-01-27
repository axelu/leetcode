
// 650. 2 Keys Keyboard
// https://leetcode.com/problems/2-keys-keyboard/


class Solution {
private:
    int rec(int s, int b, int n) {
        // s number of chars on screen
        // b number of chars in buffer
        if( s == n )
            return 0;
        if( s + b == n )
            return 1;
        if( s + b > n )
            return 1001;

        // we have a choice
        // Paste only OR
        // Paste and Copy All

        int po = 1 + rec(s+b,b,n);
        int pc = 2 + rec(s+b,s+b,n);

        return min(po,pc);
    }

public:
    int minSteps(int n) {
        if( n == 1 )
            return 0;

        return 1 + rec(1,1,n);
    }
};
