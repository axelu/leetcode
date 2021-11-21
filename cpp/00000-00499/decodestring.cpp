
// 394. Decode String
// https://leetcode.com/problems/decode-string/
// day 19 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/566/week-3-november-15th-november-21st/3536/



class Solution {
public:
    string decodeString(string s) {

        // if [ put number on cnt stack and empty string on char stack
        // if ] multiply string by number, pop number, pop string,
        //   and add string to whatever is in top of string stack

        stack<int> cnt;
        stack<string> str;
        str.push("");

        string n = "", t1, t2;
        int i,k;
        for(char ch : s) {
            if( islower(ch) ) {
                str.top() += ch;
                n = "";
            } else if( ch == '[' ) {
                cnt.push(stoi(n));
                n = "";
                str.push("");
            } else if( ch == ']' ) {
                k = cnt.top();
                cnt.pop();
                t1 = str.top();
                str.pop();
                t2 = "";
                for(i = 1; i <= k; ++i)
                       t2 += t1;
                str.top() += t2;
            } else {
                // digit
                n += ch;
            }
        }

        // top of string stack contains our result
        return str.top();
    }
};
