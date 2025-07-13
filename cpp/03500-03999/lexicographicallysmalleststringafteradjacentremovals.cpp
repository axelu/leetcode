
// 3563. Lexicographically Smallest String After Adjacent Removals
// https://leetcode.com/problems/lexicographically-smallest-string-after-adjacent-removals/

// bottom up passes

class Solution {

private:
    bool cmp(string& a, string& b) {
        // returns true if string a is lexicographically less than string b
        // it is guaranteed that a and b are different

        // A string s is lexicographically greater than a string t,
        // if in the first position where s and t differ,
        // string s has a letter that appears later in the alphabet than
        // the corresponding letter in t.
        // If the first min(s.length, t.length) characters do not differ,
        // then the longer string is the lexicographically greater one.

        int a_sz = a.size();
        int b_sz = b.size();
        for(int i = 0; i < min(a_sz,b_sz); ++i)
            if( a[i] != b[i] )
                return a[i] < b[i];

        return a_sz < b_sz;
    }

    bool is_adj(char a, char b) {
        return a+1 == b || a-1 == b || (a == 'a' and b == 'z') || (a == 'z' and b == 'a');
    }
/*
    // vector<vector<string>> mem;
    string mem[250][250];
    string s;

    string rec(int i, int j) {
        // cout << "rec i " << i << " j " << j << endl;
        if( i > j ) {
            // cout << "rec i " << i << " j " << j << " res " << endl;
            return "";
        }

        // we are asked to deliver the lexicographically smallest string
        // that we can make between i and j inclusive

        if( mem[i][j] != "#" ) {
            // cout << "rec i " << i << " j " << j << " res " << mem[i][j] << endl;
            return mem[i][j];
        }

        // base answer, we keep the char at i
        string ret = s[i] + rec(i+1, j);

        // now we try and see if s[i] and s[k] with i < k <= j
        // can be collapsed aka removed aka make ""
        for(int k = i+1; k <= j; ++k) {
            if( is_adj(s[i], s[k]) && rec(i+1, k-1) == "" ) {
                //string t = rec(k+1, j);
                //if( cmp(t, ret) )
                //    ret = t;
                ret = min(ret, rec(k+1, j));
            }
        }

        // cout << "rec i " << i << " j " << j << " res " << ret << endl;
        return mem[i][j] = ret;
    }
*/
public:
    string lexicographicallySmallestString(string s) {
        int n = s.size();
        if( n == 1 )
            return s;
        if( n == 2 ) {
            return is_adj(s[0],s[1]) ? "" : s;
        }

        /*
        // top down dp (memoization)

        // mem.resize(n,vector<string>(n,"#"));

        // pre-calc ans for len 1 for each pos
        for(int i = 0; i < n; ++i)
            mem[i][i] = string(1,s[i]);
        // pre-calc ans for len 2 for each pos
        for(int i = 0; i < n-1; ++i) {
            if( is_adj(s[i], s[i+1]) )
                mem[i][i+1] = "";
            else
                mem[i][i+1] = mem[i][i] + s[i+1];
        }
        for(int i = 0; i < n-2; ++i)
            for(int j = i+2; j < n; ++j)
                mem[i][j] = "#";

        this->s = s;
        // return rec(0, n-1);
        */


        // bottom up dp

        vector<vector<string>> dp(n,vector<string>(n));
        //string dp[250][250];
        for(int i = n-1; i >= 0; --i) {
            for(int j = i; j < n; ++j) {
                if( j == i ) {
                    dp[i][j] = string(1,s[i]);
                    continue;
                }
                if( j == i+1 ) {
                    if( is_adj(s[i], s[j]) )
                        dp[i][j] = "";
                    else
                        dp[i][j] = s.substr(i,2);
                    continue;
                }

                // base answer, we keep the char at i
                dp[i][j] = s[i] + dp[i+1][j];

                for(int k = i+1; k < j; ++k) {
                    if( is_adj(s[i], s[k]) && dp[i+1][k-1] == "" )
                        dp[i][j] = min(dp[i][j], dp[k+1][j]);
                }
                if( is_adj(s[i], s[j]) && dp[i+1][j-1] == "" )
                    dp[i][j] = "";

            }
        }

        return dp[0][n-1];
    }
};





// passes 828/930 test cases, then TLE
// test case 829 runs in ~50ms, correct result, but obviously too slow
// this is top down dp (memoization)


class Solution {
private:
    bool cmp(string& a, string& b) {
        // returns true if string a is lexicographically less than string b
        // it is guaranteed that a and b are different

        // A string s is lexicographically greater than a string t,
        // if in the first position where s and t differ,
        // string s has a letter that appears later in the alphabet than
        // the corresponding letter in t.
        // If the first min(s.length, t.length) characters do not differ,
        // then the longer string is the lexicographically greater one.

        int a_sz = a.size();
        int b_sz = b.size();
        for(int i = 0; i < min(a_sz,b_sz); ++i)
            if( a[i] != b[i] )
                return a[i] < b[i];

        return a_sz < b_sz;
    }

    bool is_adj(char a, char b) {
        return a+1 == b || a-1 == b || (a == 'a' and b == 'z') || (a == 'z' and b == 'a');
    }

    // vector<vector<string>> mem;
    string mem[250][250];
    string s;

    string rec(int i, int j) {
        // cout << "rec i " << i << " j " << j << endl;
        if( i > j ) {
            // cout << "rec i " << i << " j " << j << " res " << endl;
            return "";
        }

        // we are asked to deliver the lexicographically smallest string
        // that we can make between i and j inclusive

        if( mem[i][j] != "#" ) {
            // cout << "rec i " << i << " j " << j << " res " << mem[i][j] << endl;
            return mem[i][j];
        }

        // base answer, we keep the char at i
        string ret = s[i] + rec(i+1, j);

        // now we try and see if s[i] and s[k] with i < k <= j
        // can be collapsed aka removed aka make ""
        for(int k = i+1; k <= j; ++k) {
            if( is_adj(s[i], s[k]) && rec(i+1, k-1) == "" ) {
                //string t = rec(k+1, j);
                //if( cmp(t, ret) )
                //    ret = t;
                ret = min(ret, rec(k+1, j));
            }
        }

        // cout << "rec i " << i << " j " << j << " res " << ret << endl;
        return mem[i][j] = ret;
    }

public:
    string lexicographicallySmallestString(string s) {
        int n = s.size();
        if( n == 1 )
            return s;
        if( n == 2 ) {
            return is_adj(s[0],s[1]) ? "" : s;
        }

        // mem.resize(n,vector<string>(n,"#"));

        // pre-calc ans for len 1 for each pos
        for(int i = 0; i < n; ++i)
            mem[i][i] = string(1,s[i]);
        // pre-calc ans for len 2 for each pos
        for(int i = 0; i < n-1; ++i) {
            if( is_adj(s[i], s[i+1]) )
                mem[i][i+1] = "";
            else
                mem[i][i+1] = mem[i][i] + s[i+1];
        }
        for(int i = 0; i < n-2; ++i)
            for(int j = i+2; j < n; ++j)
                mem[i][j] = "#";

        this->s = s;
        return rec(0, n-1);
    }
};
