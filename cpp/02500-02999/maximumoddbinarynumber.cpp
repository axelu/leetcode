
// 2864. Maximum Odd Binary Number
// https://leetcode.com/problems/maximum-odd-binary-number/



class Solution {
public:
    string maximumOddBinaryNumber(string s) {
        int n = s.size();

        int ones = 0;
        for(char c: s)
            if( c == '1' )
                ++ones;

        int zeros = n - ones;

        string p1(ones-1,'1');
        string p2(zeros,'0');
        string p3(1,'1');

        string ans = p1 + p2 + p3;
        return ans;
    }
};
