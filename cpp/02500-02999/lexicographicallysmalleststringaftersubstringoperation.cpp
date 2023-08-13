
// 2734. Lexicographically Smallest String After Substring Operation
// https://leetcode.com/problems/lexicographically-smallest-string-after-substring-operation/




class Solution {
public:
    string smallestString(string& s) {
        int n = s.size();

        // find the 1st occurence of a char different than 'a'
        int b = -1;
        int i = 0;
        for(; i < n; ++i)
            if( s[i] != 'a' ) {
                b = i;
                break;
            }

        // we have to apply the operation once!
        if( b == -1 ) {
            s[n-1] = 'z';
            return s;
        }

        // find the 1st occurence of char 'a'
        int e = b;
        ++i;
        for(; i < n; ++i) {
            if( s[i] == 'a' )
                break;
            ++e;
        }

        for(i = b; i <= e; ++i)
            if( s[i] == 'a' )
                s[i] = 'z';
            else
                s[i] = s[i] - 1;

        return s;
    }
};
