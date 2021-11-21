
// 2042. Check if Numbers Are Ascending in a Sentence
// https://leetcode.com/problems/check-if-numbers-are-ascending-in-a-sentence/


class Solution {
public:
    bool areNumbersAscending(string s) {
        stringstream ss(s);
        string t;
        int prev = 0, i;
        while( getline(ss,t,' ') )
            if( isdigit(t[0]) ) {
                i = stoi(t);
                if( i <= prev )
                    return false;
                prev = i;
            }

        return true;
    }
};
