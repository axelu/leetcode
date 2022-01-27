
// 709. To Lower Case
// https://leetcode.com/problems/to-lower-case/


class Solution {
public:
    string toLowerCase(string& str) {
        int n = str.size();

        int ci;
        for(int i = 0; i < n; ++i) {
            ci = (int)str[i];
            if( 65 <= ci && ci <= 90 )
                str[i] = (char)(ci+32);
        }
        return str;
    }
};
