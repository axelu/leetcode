
// 2904. Shortest and Lexicographically Smallest Beautiful String
// https://leetcode.com/problems/shortest-and-lexicographically-smallest-beautiful-string/







class Solution {
private:
    bool cmp(string& a, string& b) {
        // returns true if string a is lexicographically less than string b
        // it is guaranteed that a and b are same length and non empty

        int a_sz = a.size();
        for(int i = 0; i < a_sz; ++i)
            if( a[i] != b[i] )
                return a[i] < b[i];

        return false; // strings are equal, satisfy compiler
    }

public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        if( k == 1 ) {
            for(char c :s)
                if( c == '1' )
                    return "1";
            return "";
        }

        // find the 1st one if any, count total ones
        int i = -1;
        int ones = 0;
        for(int o = 0; o < n; ++o)
            if( s[o] == '1' ) {
                ++ones;
                if( i == -1 )
                    i = o;
            }
        if( ones < k )
            return "";

        string ans = "";

        // sliding window
        int mn_len = n+1;
        ones = 0;
        for(int j = i; j < n; ++j) {    // i left index, j right index
            // we will discover substring starting and ending with '1'
            if( s[j] == '1' )
                ++ones;

            if( ones == k ) {
                int len = j - i + 1;
                if( len < mn_len ) {
                    ans = s.substr(i,len);
                    mn_len = len;
                } else if( len == mn_len ) {
                    string candidate = s.substr(i,len);
                    if( cmp(candidate,ans) )
                        ans = candidate;
                }

                ++i;
                while( i < j && s[i] != '1' )
                    ++i;
                --ones;
            }
        }

        return ans;
    }
};
