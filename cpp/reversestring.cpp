
// 344. Reverse String
// https://leetcode.com/problems/reverse-string/



class Solution {
public:
    void reverseString(vector<char>& s) {
        size_t n = s.size();
        int i = 0;
        int j = n-1;
        char t;
        while( i < j ) {
            if( s[i] != s[j] ) {
                t = s[i];
                s[i] = s[j];
                s[j] = t;
            }
            ++i;
            --j;
        }
    }
};
