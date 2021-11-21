
// 131. Palindrome Partitioning
// https://leetcode.com/problems/palindrome-partitioning/
// day 14 Decemeber 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/570/week-2-december-8th-december-14th/3565/

class Solution {
private:
    size_t N;
    vector<string> curr;
    vector<vector<string>> ans;

    bool isPalindrome(string& s, int b, int e) {
        while(b < e) {
            if (s[b] != s[e]) return false;
            ++b;
            --e;
        }
        return true;
    }

    void rec(int start, string& s) {
        if( start >= N ) {
            ans.push_back(curr);
            return;
        }

        // walk all possible end points for substrings
        for(int i=start; i < N; ++i) {
            if( isPalindrome(s, start, i) ) {
                // add the substring to current result
                curr.push_back(s.substr(start,i-start+1));

                // recurse for remaining string
                rec(i+1,s);

                // backtrack by removing s[start..i] from current result
                curr.pop_back();
            }
        }
    }

public:
    vector<vector<string>> partition(string& s) {
        N = s.size();
        if( N == 1 ) return {{s}};

        rec(0,s);
        return ans;
    }
};
