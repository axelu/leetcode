
// 806. Number of Lines To Write String
// https://leetcode.com/problems/number-of-lines-to-write-string/



class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string s) {
        int lines = 1;
        int pixel = 0;
        int w; // width of current char
        for(int i = 0; i < s.size(); ++i) {
            w = widths[s[i]-'a'];
            if( pixel + w > 100 ) {
                // this char needs to go onto the next line
                ++lines;
                pixel = w;
            } else {
                pixel += w;
            }
        }
        return {lines,pixel};
    }
};
