
// 1332. Remove Palindromic Subsequences
// https://leetcode.com/problems/remove-palindromic-subsequences/


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
    int removePalindromeSub(string s) {
        if( s.empty() ) {
            // string already empty, hence 0 steps required to make it empty.
            return 0;
        } else if( isPalindrome(s) ) {
            // we can remove the entire string in one step as a whole as it is already a palindrome.
            return 1;
        } else {
            // in step 1 we could remove all a's and in step 2 remove all b's
            // or vice versa but regardless, it will take 2 steps, but not more than 2 steps,
            // as we are dealing with a's and b's only.
            return 2;
        }
    }
};
