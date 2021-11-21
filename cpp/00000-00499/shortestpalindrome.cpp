

// 214. Shortest Palindrome
// https://leetcode.com/problems/shortest-palindrome/



class Solution {
private:
    /*
    bool validPalindrome(string& s, int l, int r) {
        while(l<r) {
            if( s[l] != s[r] ) return false;
            ++l;
            --r;
        }
        return true;
    }
    */

    void kmp_table(string& W, int T[]) {
        // https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm

        // input:  an array of characters, W (the word to be analyzed)
        // output: an array of integers, T (the table to be filled)

        int pos = 1; // current position we are computing in t
        int cnd = 0; // zero-based index in w of the next character of the current candidate substring

        T[0] = -1;

        while(pos < W.size()) {
            if( W[pos] == W[cnd] ) {
                T[pos] = T[cnd];
            } else {
                T[pos] = cnd;
                while(cnd >= 0 && W[pos] != W[cnd]) {
                    cnd = T[cnd];
                }
            }
            ++pos;
            ++cnd;
        }

        T[pos] = cnd; // only needed when all word occurrences are searched
    }

public:
    string shortestPalindrome(string& s) {
        int n = s.size();
        if( n < 2 ) return s;

        /*
        // brute force -> TLE
        int i;
        string f = "";
        for(i = n-1; i >= 0; --i) {
            if( s[0] == s[i] && validPalindrome(s,0,i) )
                break;
            f += s[i];
        }

        return f+s;
        */

        // idea remains the same as in brute force approach:
        // find the longest palindrome starting at index 0.
        // so our string s is basically s = palindrome + rest or short s = p + r.
        // reversing the rest and adding to the begin of s is the answer:
        // ans = reverse(r) + p + r.
        // enter the Partial Match Table in Knuth Morris Pratt (KMP) algorithm
        // http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/
        // definition of the Partion Match Table quote:
        // "The length of the longest proper prefix in the (sub)pattern that matches
        //  a proper suffix in the same (sub)pattern."
        // practical application to this problem:
        // W = s + seperator + reverse(s)   Note: seperator arbitrirally choosen
        // now we can find the longest prefix that matches a suffix, then if we remove that suffix
        // from the reversed s and add it to the front, we have our answer
        // Example 1:
        // s = aacecaaa -> W = aacecaaa*aaacecaa
        //                     -------   -------
        // the longest matching prefix that matches a suffix is aacecaa, remove that from the
        // reversed string and add the remainder a to the front of s for the ans = aaacecaaa
        // Example 2:
        // s = abcd -> W = abcd*dcba
        //                 -       -
        // the longest matching prefix that matches a suffix is a, remove that from the
        // reversed string and add the remainder dcb to the front of s for the ans = dcbabcd

        string sreversed = s; reverse(sreversed.begin(),sreversed.end());
        string W = s + "*" + sreversed;

        int T[W.size()+1]; // Partial Match Table
        kmp_table(W,T);

        /*
        // debug print the Partial Match Table
        for(int i = 0; i < W.size()+1; ++i)
            cout << T[i] << " ";
        cout << endl;
        */

        return sreversed.substr(0,n-T[2*n+1])+s;
    }
};
