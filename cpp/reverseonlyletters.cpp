
// 917. Reverse Only Letters
// https://leetcode.com/problems/reverse-only-letters/



class Solution {
public:
    string reverseOnlyLetters(string S) {
        int n = S.size();

        char t;
        int l = 0, r = n-1;
        while(l<r) {
            while(l<r && !isalpha(S[l]) ) {
                ++l;
            }
            while(r>l && !isalpha(S[r]) ) {
                --r;
            }
            if( l == r ) break;
            t = S[l];
            S[l] = S[r];
            S[r] = t;
            ++l;
            --r;
        }
        return S;
    }
};
