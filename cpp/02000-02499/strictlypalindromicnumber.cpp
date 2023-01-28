
// 2396. Strictly Palindromic Number
// https://leetcode.com/problems/strictly-palindromic-number/



class Solution {
private:
    bool isPalindrome(string& s) {
        if( s.size() == 1 ) return true;

        bool p = true;

        auto fi = s.begin();
        auto ri = s.rbegin();
        while( fi <= ri.base() ) {
            if( *fi == *ri ) {
                ++fi;
                ++ri;
            } else {
                p = false;
                break;
            }
        }

        return p;
    }

public:
    bool isStrictlyPalindromic(int n) {
        // 4 <= n <= 100000

        for(int b = 2; b <= n-2; ++b) {
            int x = n;
            string s = "";
            while( x > 0 ) {
                s = to_string(x % b) + s;
                x /= b;
            }
            if( !isPalindrome(s) )
                return false;
        }

        return true;
    }
};
