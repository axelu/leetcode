
// 87. Scramble String
// https://leetcode.com/problems/scramble-string/




class Solution {
private:
    int mem[30][30][31];

    bool scramble(string& s, string& t, int sl, int tl, int l) {
        // cout << "sl " << sl << " tl " << tl << " l " << l << endl;
        if( l == 1 )
            return s[sl] == t[tl];

        if( mem[sl][tl][l] != -1 )
            return mem[sl][tl][l];

        int f = 0;
        for(int i = 1; i < l; ++i) {
            // xs = s[sl,...,sl+i]
            // ys = s[sl+i+1,...,sl+l-1]

            // xt = t[tl,...,tl+i]
            // yt = t[tl+i+1,...,tl+l-1];

            // don't swap
            // cout << "don't swap" << endl;
            bool a = scramble(s,t,sl,tl,i);
            bool b = scramble(s,t,sl+i,tl+i,l-i);
            if( a && b ) {
                f = 1;
                break;
            }

            // swap
            // cout << "swap" << endl;
            bool c = scramble(s,t,sl,tl+l-i,i);
            bool d = scramble(s,t,sl+i,tl,l-i);
            if( c && d ) {
                f = 1;
                break;
            }

        }
        return mem[sl][tl][l] = f;
    }

public:
    bool isScramble(string s, string t) {
        if( s == t )
            return true;

        int n = s.size(); // s.length == t.length

        // quick check
        int cntS[26];memset(cntS,0,sizeof cntS);
        int cntT[26];memset(cntT,0,sizeof cntT);
        for(int i = 0; i < n; ++i) {
            ++cntS[s[i]-'a'];
            ++cntT[t[i]-'a'];
        }
        for(int i = 0; i < 26; ++i)
            if( cntS[i] != cntT[i] )
                return false;

        memset(mem,-1,sizeof mem);
        return scramble(s,t,0,0,n);
    }
};
