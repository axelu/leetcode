
// 541. Reverse String II
// https://leetcode.com/problems/reverse-string-ii/


class Solution {
private:
    void reverseString(string& s, int i, int j) {
        char t;
        while( i < j ) {
            if( s[i] != s[j] ) {
                t = s[i];
                s[i] = s[j];
                s[j] = t;
            }
            ++i;
            --j;
        }
    }

public:
    string reverseStr(string& s, int k) {
        // base cases
        if( k == 1 ) return s;
        size_t n = s.size();
        if( n < 2 ) return s;
        if( k >= n ) {
            reverseString(s,0,n-1);
            return s;
        }

        int lft = 0;
        int cnt = 1;
        for(int i = 0; i < n; ++i) {
            if( cnt == k ) {
                reverseString(s,lft,i);
            } else if( cnt == 2*k ) {
                cnt = 0;
                lft = i+1;
            }
            ++cnt;
        }
        if( cnt > 0 && cnt <=k ) // we ran out of chars
            reverseString(s,lft,n-1);

        return s;
    }
};
