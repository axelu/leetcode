
// 1745. Palindrome Partitioning IV
// https://leetcode.com/problems/palindrome-partitioning-iv/




class Solution {
private:
    bool isPalindrome(string& s, int b, int e) {
        while(b < e) {
            if (s[b] != s[e]) return false;
            ++b;
            --e;
        }
        return true;
    }

public:
    bool checkPartitioning(string& s) {
        int n = s.size();
        if( n == 3 )
            return true;

        // indicies where left palindromes end
        vector<int> l{0};
        for(int i = 1; i < n-2; ++i)
            if( isPalindrome(s,0,i) )
                l.push_back(i);

        // indicies where right palindromes start
        vector<int> r;
        for(int i = 2; i < n; ++i)
            if( isPalindrome(s,i,n-1) )
                r.push_back(i);

        for(int i: l)
            for(int j: r) {
                if( j < i+2 )
                    continue;
                if( isPalindrome(s,i+1,j-1) )
                    return true;
            }

        return false;
    }
};
