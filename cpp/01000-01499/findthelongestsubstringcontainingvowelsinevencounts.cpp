
// 1371. Find the Longest Substring Containing Vowels in Even Counts
// https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/




class Solution {
private:
    // debug
    void printState(int x) {
        for(int i = 4; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }
    
    bool isvowel(char c) {
        if( c == 'a' ||
            c == 'e' ||
            c == 'i' ||
            c == 'o' ||
            c == 'u' )
            return true;
        return false;
    }
public:
    int findTheLongestSubstring(string s) {
        int i;
        
        // idea: represent the state of the string in a bitmask
        // bit value 0 is even, bit value 1 is odd; when we encounter a given vowel we will toggle the bit
        // vowels a,e,i,o and u; a is the rightmost bit, e the second to rightmost bit and so on
        unordered_map<char,int> shift{{'a',0},{'e',1},{'i',2},{'o',3},{'u',4}};
        // we will safe the index of when we saw a given state the 1st time
        // how many states are there?  there are 5 vowels -> 2^5 states = 32 states
        // we will use a value of -2 to indicate a state that we have never seen before
        int seen[32];
        for(i = 0; i < 32; ++i)
            seen[i] = -2;
        
        // the state 0 we will say we have seen at idx -1
        // why? e.g. if s[0] is not a vowel, we will check when we first saw this state 0
        // and caculate the length as follows: l = i - seen[0] -> 0 - (-1) = 1
        seen[0] = -1;

        int ans = 0;
        int state = 0;
        for(i = 0; i < s.size(); ++i) {
            if( isvowel(s[i]) )
                state ^= (1 << shift[s[i]]); // XOR toggles the bit
            // cout << i << " ";printState(state);
            if( seen[state] != -2 )
                ans = max(ans,i-seen[state]);
            else
                seen[state] = i; // 1st time we encounterd this state
                                 // save the index that we encountered this state at
        }
        
        // example "eleetminicoworoep" states
        // -1 00000
        //  0 00010 e
        //  1 00010 l
        //  2 00000 e
        //  3 00010 e
        //  4 00010 t
        //  5 00010 m
        //  6 00110 i
        //  7 00110 n
        //  8 00010 i
        //  9 00010 c
        // 10 01010 o
        // 11 01010 w
        // 12 00010 o
        // 13 00010 r
        // 14 01010 o
        // 15 01000 e
        // 16 01000 p

        
        
        return ans;
    }
};
