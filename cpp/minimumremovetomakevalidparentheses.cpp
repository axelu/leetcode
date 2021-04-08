
// 1249. Minimum Remove to Make Valid Parentheses
// https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
// day 19 February 2021 challenge
// https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/586/week-3-february-15th-february-21st/3645/



class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int n = s.size();

        // base cases
        if( n == 0 ) return "";
        if( n == 1 ) return s[0] == '(' || s[0] == ')' ? "" : s;

        deque<int> dq;

        // pass 1
        // left to right
        for(int i = 0; i < n; ++i) {
            if( s[i] == '(' ) {
                dq.push_back(i);
            }
            if( s[i] == ')' ) {
                if( !dq.empty() )
                    dq.pop_back();
            }
        }
        // deleting umatched open parentheses
        while( !dq.empty() ) {
            s.erase(dq.back(),1);
            dq.pop_back();
        }

        // pass 2
        // right to left
        n = s.size(); // n may have changed
        for(int i = n-1; i >= 0; --i) {
            if( s[i] == ')' ) {
                dq.push_back(i);
            }
            if( s[i] == '(' ) {
                if( !dq.empty() )
                    dq.pop_back();
            }
        }
        // deleting umatched close parentheses
        while( !dq.empty() ) {
            s.erase(dq.front(),1);
            dq.pop_front();
        }

        return s;
    }
};
