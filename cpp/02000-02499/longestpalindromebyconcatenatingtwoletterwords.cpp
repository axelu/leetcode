
// 2131. Longest Palindrome by Concatenating Two Letter Words
// https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/



class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        // if we have a word like "ab", we greedily look for "ba"
        // if we have a work like "aa", we greedily look for "aa",
        // but if in the end we have at least on like "aa",
        // we can apply it in the very middle

        int ans = 0;

        unordered_map<string,int> ab;
        unordered_map<string,int> aa;

        for(auto& s: words) {
            string o = "";
            o += s[1];
            o += s[0];
            if( s != o ) {
                if( ab[o] > 0 ) {
                    ans += 4;
                    --ab[o];
                } else {
                    ++ab[s];
                }
            } else {
                if( aa[o] > 0 ) {
                    ans += 4;
                    --aa[o];
                } else {
                    ++aa[s];
                }
            }
        }

        for(auto& p: aa) {
            if( p.second > 0 ) {
                ans += 2;
                break;
            }
        }

        return ans;
    }
};
