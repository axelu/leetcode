
// 844. Backspace String Compare
// https://leetcode.com/problems/backspace-string-compare/



class Solution {
public:
    bool backspaceCompare(string S, string T) {
        string s = "", t = "";
        int ns = S.size();
        int nt = T.size();

        int is = 0, it = 0;
        while(is < ns || it < nt) {
            if( is < ns ) {
                if( S[is] == '#' ) {
                    if( !s.empty() ) s.pop_back();
                } else {
                    s += S[is];
                }
                ++is;
            }
            if( it < nt ) {
                if( T[it] == '#' ) {
                    if( !t.empty() ) t.pop_back();
                } else {
                    t += T[it];
                }
                ++it;
            }
        }
        // cout << "s " << s << " t " << t << endl;
        return s == t;
    }
};
