
// 2663. Lexicographically Smallest Beautiful String
// https://leetcode.com/problems/lexicographically-smallest-beautiful-string/






class Solution {
public:
    string smallestBeautifulString(string s, int k) {
        int n = s.size();

        // it is guaranteed that s is 'beautiful' to begin with
        // from the problem description:
        // A string is beautiful if:
        //     It consists of the first k letters of the English lowercase alphabet.
        //     It does not contain any substring of length 2 or more which is a palindrome.

        // pass 1 from right to left
        // we need to find the right most position in s in which we can increase the char,
        // but not exceed k or create a palindrome to the left of it
        int pos = -1;
        for(int i = n-1; i >= 0; --i) {
            // cout << "pass 1 i " << i << endl;
            int c = s[i] - 96;
            bool palindrome_l2 = true;
            bool palindrome_l3 = true;
            for(int c_new = c+1; c_new <= k; ++c_new) {
                palindrome_l2 = false;
                palindrome_l3 = false;
                // we will check to our left by 1 to not create a palindrome of length 2 and
                // to our left by 2 to not create a palindrome of length 3
                if( i-1 >= 0 && s[i-1] - 96 == c_new )
                    palindrome_l2 = true;
                if( !palindrome_l2 && i-2 >= 0 && s[i-2] - 96 == c_new)
                    palindrome_l3 = true;
                if( !palindrome_l2 && !palindrome_l3 ) {
                    pos = i;
                    s[i] = c_new + 96;
                    break;
                }
            }
            if( !palindrome_l2 && !palindrome_l3 )
                break;
        }
        if( pos == -1 )
            return "";

        // cout << "pos " << pos << endl;
        // cout << s << endl; // we already changed the char at pos

        // pass 2 from left to right starting at pos + 1
        for(int i = pos+1; i < n; ++i) {
            // cout << "pass 2 i " << i << endl;
            // we will target to set char at i to the smallest possible value starting with a
            // we will check to our left by 1 to not create a palindrome of length 2 and
            // to our left by 2 to not create a palindrome of length 3
            for(int c = 0; c < k; ++c) {
                char chr_new = c + 'a';
                int f = true;
                if( (i-1 >= 0 && s[i-1] == chr_new) || (i-2 >= 0 && s[i-2] == chr_new) )
                    f = false;
                if( f ) {
                    s[i] = chr_new;
                    break;
                }
            }
        }

        return s;
    }
};
