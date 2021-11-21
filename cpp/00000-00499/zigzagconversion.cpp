
// 6. ZigZag Conversion
// https://leetcode.com/problems/zigzag-conversion/


class Solution {
public:
    string convert(string s, int numRows) {
        if( numRows == 1 )
            return s;

        string row[numRows];

        int r = 0;
        int m = 0; // mode 0 down, 1 up
        for(int i = 0; i < s.size(); ++i) {

            row[r].push_back(s[i]);
            if( m == 0 ) {
                ++r;
                if( r == numRows-1 )
                    m = 1;
            } else {
                --r;
                if( r == 0 )
                    m = 0;
            }
        }

        string ans = "";
        for(int i = 0; i < numRows; ++i)
            ans += row[i];
        return ans;
    }
};
