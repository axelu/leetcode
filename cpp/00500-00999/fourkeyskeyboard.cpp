
// 651. 4 Keys Keyboard
// https://leetcode.com/problems/4-keys-keyboard/



class Solution {
private:
    unordered_map<long,int> mem;

    int rec(long s, long b, long k) {
        // s number chars on screen
        // b number of chars in buffer
        // k number of keystrokes remaining

        if( k == 0 )
            return 0;
        if( k < 3 )
            return b > 0 ? b*k : k;

        long key = s + (b << 21) + (k << 42);
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        // we have a choice
        //  press A and move on:    cost 1 keystroke
        //  copy/paste and move on: cost 3 keystrokes
        //  ctrl+v and move on:     cost 1 keystroke

        int o1 = b == 0 ? 1 + rec(s+1,b,k-1) : 0;
        int o2 = s > 0 ? s + rec(s*2,s,k-3) : 0;
        int o3 = b > 0 ? b + rec(s+b,b,k-1) : 0;

        int t = max({o1,o2,o3});
        mem.insert({key,t});
        return t;
    }

public:
    int maxA(int n) {
        if( n <= 6 )
            return n;

        return 3 + rec(3,0,n-3);
    }
};
