
// 1694. Reformat Phone Number
// https://leetcode.com/problems/reformat-phone-number/


class Solution {
public:
    string reformatNumber(string& number) {
        if( number.size() == 2 ) return number;

        string t = "";
        int cnt = 0;
        stack<string> stck;
        for(char c : number) {
            if( isdigit(c) ) {
                ++cnt;
                t += c;
                if( cnt == 3 ) {
                    stck.push(t);
                    cnt = 0;
                    t = "";
                }
            }
        }
        string ans = t;

        t = "";
        while( !stck.empty() ) {
            t = stck.top();
            stck.pop();
            if( ans.size() == 1 ) {
                ans = t.substr(2) + ans;
                t = t.substr(0,2);
            } else if( ans.size() == 0 ) {
                ans = t;
                continue;
            }
            ans = t + "-" + ans;
        }

        return ans;
    }
};
