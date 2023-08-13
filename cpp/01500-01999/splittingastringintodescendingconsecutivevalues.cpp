
// 1849. Splitting a String Into Descending Consecutive Values
// https://leetcode.com/problems/splitting-a-string-into-descending-consecutive-values/




class Solution {
private:
    bool rec(string& s, int n, int b, int pos) {
        // b is where the prior number starts
        // pos-1 is where the prior number ends

        if( pos == n )
            return true;

        // leading 0s don't matter, they don't make a valid number
        // unless we are at the very end and the number before is 1

        if( pos == 0 ) {
            bool nonzero = false;
            for(int i = 0; i < n-1; ++i) {
                if( s[i] != '0' ) {
                    nonzero = true;
                    if( rec(s,n,0,i+1) )
                        return true;
                } else {
                    if( nonzero && rec(s,n,0,i+1) )
                        return true;
                }
            }

        } else {
            // prior number pre
            unsigned long long pre = stoull(s.substr(b,pos-b));
            // edge case
            if( pre == 1 ) {
                for(int i = pos; i < n; ++i)
                    if( s[i] != '0' )
                        return false;
                return true;
            } else {
                for(int i = pos; i < n; ++i) {
                    unsigned long long cur = stoull(s.substr(pos,i-pos+1));
                    if( cur >= pre ) {
                        return false;
                    } else if( cur == pre - 1 ) {
                        return rec(s,n,pos,i+1);
                    }
                }
            }
        }

        return false;
    }

public:
    bool splitString(string s) {
        int n = s.size();
        if( n == 1 )
            return false;

        return rec(s,n,-1,0);
    }
};
