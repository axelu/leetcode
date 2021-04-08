
// day 3 September 2020 challenge
// Repeated Substring Pattern
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/554/week-1-september-1st-september-7th/3447/
// https://leetcode.com/problems/repeated-substring-pattern/

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        if( s.empty() || s.size() == 1 ) return false;
/*
        string s2 = s + s;
        auto p = s2.find(s,1);

        cout << "p " << p << endl;
        cout << "l " << s.size() << endl;

        return p < s.size();
*/
        return (s+s).find(s,1) < s.size();


    }
};
