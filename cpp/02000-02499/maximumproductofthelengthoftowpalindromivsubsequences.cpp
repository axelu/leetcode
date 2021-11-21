
// 2002. Maximum Product of the Length of Two Palindromic Subsequences
// https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-subsequences/





class Solution {
private:
    int n;
    int ans;

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


    void genSubsequences2(string& s, int i, string substring, int length) {
        if( i == s.size() ) {
            int l = substring.size();
            if( l != 0 && isPalindrome(substring) )
                ans = max(ans,l*length);
        } else {
            // we have a choice
            // don't include char at current index
            genSubsequences2(s,i+1,substring,length);

            // include char at current index
            substring.push_back(s[i]);
            genSubsequences2(s,i+1,substring,length);
        }
        return;
    }


    void genSubsequences(string& s, int i, string substring, string remstring) {
        if( i == s.size() ) {
            int l = substring.size();
            if( l != 0 && l != n && isPalindrome(substring) ) {
                string ss = "";
                genSubsequences2(remstring,0,ss,l);
            }
        } else {
            // we have a choice
            // don't include char at current index
            remstring.push_back(s[i]);
            genSubsequences(s,i+1,substring,remstring);

            // include char at current index
            remstring.pop_back();
            substring.push_back(s[i]);
            genSubsequences(s,i+1,substring,remstring);
        }
        return;
    }
public:
    int maxProduct(string s) {
        n = s.size();
        ans = 0;

        string substring = "", remstring = "";
        genSubsequences(s,0,substring,remstring);

        return ans;
    }
};
