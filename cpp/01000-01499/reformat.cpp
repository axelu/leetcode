
// 1417. Reformat The String
// https://leetcode.com/problems/reformat-the-string/



class Solution {
public:
    string reformat(string& s) {
        auto n = s.size();
        if( n == 1 ) return s; // base case

        char alphas[500];
        char digits[500];

        int cc = 0;
        int cd = 0;
        int i = 0;
        for(; i < n; ++i) {
            char ch = s[i];
            if( isalpha(ch) ) {
                alphas[cc] = ch;
                ++cc;
            } else {
                digits[cd] = ch;
                ++cd;
            }
        }

        string r = "";
        int dist = cc - cd;
        if( dist < -1 || dist > 1 ) return r;
        char * a;
        char * b;
        if( dist == -1 ) {
            a = digits;
            b = alphas;
        } else {
            a = alphas;
            b = digits;
        }

        i = 0;
        for(; i < n/2; ++i) {
            r += a[i];
            r += b[i];
        }
        if(dist != 0) r += a[i];

        return r;
    }
};
