
// 1717. Maximum Score From Removing Substrings
// https://leetcode.com/problems/maximum-score-from-removing-substrings/



class Solution {
private:

    int processStack(stack<char>& lstck, int x, int y) {
        int ret = 0;

        if( lstck.size() == 1 ) {
            lstck.pop();
        } else if( lstck.size() == 2 ) {
            char c2 = lstck.top();lstck.pop();
            char c1 = lstck.top();lstck.pop();
            if( c1 == c2 ) {
                // do nothing
            } else if( c1 == 'a' ) {
                ret += x;
            } else {
                ret += y;
            }
        } else {
            // empty left stack
            stack<char> rstck;
            while( !lstck.empty() ) {
                if( rstck.empty() || lstck.top() == rstck.top() ) {
                    rstck.push(lstck.top());
                    lstck.pop();
                } else {
                    // lstck.top() != rstck.top()
                    if( lstck.top() == 'a' )
                        ret += x;
                    else
                        ret += y;
                    lstck.pop();
                    rstck.pop();
                }
            }
        }

        return ret;
    }


public:
    int maximumGain(string s, int x, int y) {
        int n = s.size();

        // x points for ab
        // y points for ba

        int ans = 0;

        stack<char> stck;
        char c;
        for(int i = 0; i < n; ++i) {
            c = s[i];

            if( c != 'a' && c != 'b' ) {
                ans += processStack(stck,x,y);
            } else {
                // c is either 'a' or 'b'
                // on the way in the stack, we check and don't put
                // the more valuable order in to begin with (greedy)
                if( stck.empty() || stck.top() == c ) {
                    stck.push(c);
                } else {
                    // stck.top() and c are different
                    if( x > y ) {
                        if( stck.top() == 'a' ) {
                            ans += x;
                            stck.pop();
                        } else {
                            stck.push(c);
                        }
                    } else {
                        if( stck.top() == 'b' ) {
                            ans += y;
                            stck.pop();
                        } else {
                            stck.push(c);
                        }
                    }
                }
            }
        }
        ans += processStack(stck,x,y);

        return ans;
    }
};
