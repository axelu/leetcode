
// 3798. Largest Even Number
// https://leetcode.com/problems/largest-even-number/


class Solution {
public:
    string largestEven(string s) {
        // rephrasing the problem:
        // delete trailing 1's
        while( !s.empty() && s.back() == '1' )
            s.pop_back();
        return s;
    }
};
