
// 3163. String Compression III
// https://leetcode.com/problems/string-compression-iii/




class Solution {
public:
    string compressedString(string word) {
        int n = word.size();
        string comp = "";

        if( n == 0 )
            return comp;

        char c = word[0];
        int cnt = 1;
        for(int i = 1; i < n; ++i) {
            if( cnt == 9 || word[i] != c ) {
                comp.append(1, cnt + '0');
                comp.append(1, c);

                cnt = 1;
                c = word[i] ;

            } else {
                ++cnt;
            }
        }
        // finish up
        comp.append(1, cnt + '0');
        comp.append(1, c);

        return comp;
    }
};
