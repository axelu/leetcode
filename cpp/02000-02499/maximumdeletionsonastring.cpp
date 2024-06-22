
// 2430. Maximum Deletions on a String
// https://leetcode.com/problems/maximum-deletions-on-a-string/



/* in essence when we start at a given position
 * we add 1 char to the left string and
 * we remove the 1st char and add 2 chars to the right string
 * we then compare those strings
 * rolling hash to speed this up
 * see also 1316. Distinct Echo Substrings at https://leetcode.com/problems/distinct-echo-substrings/
 * inspired by Rabin-Karp Algorithm
 * https://cp-algorithms.com/string/rabin-karp.html
 */
class Solution {
private:
    const int p = 31;
    const int m = 1e9 + 9;

    long long p_pow[4000];
    long long h[4001];


    bool is_equal(string& s, int i, int j) {
        int i_limit = j;
        while( i < i_limit ) {
            if( s[i] != s[j] )
                return false;
            ++i;
            ++j;
        }
        return true;
    }

    int mem[4000];

    int rec(string& s, int n, int pos) {
        if( pos == n )
            return 0;
        if( pos == n-1 )
            return 1;

        if( mem[pos] != -1 )
            return mem[pos];

        // we have a choice
        //     delete the entire remaining string starting at pos OR
        //     attempt to delete portions if the conditions are met

        int a = 1;

        int b = 0;

        // length of our maximum substring
        int lmax = (n - pos)/2;

        // we will test every substring of size l [1,lmax] at pos and
        // check if it is followed by the same substring
        int s1 = pos; // start of substring1
        int s2;       // start of substring2, same length as sstring1 immediately folling sstring1
        for(int l = 1; l <= lmax; ++l) {
            s2 = s1 + l;

            long long h1 = (h[s1+l] + m - h[s1]) % m;
            long long h2 = (h[s2+l] + m - h[s2]) % m;
            if( h2 == h1 * p_pow[l] % m ) {
                // we could delete in one operation
                // s[pos,pos+l-1] inclusive
                b = max(b, 1 + rec(s,n,pos+l));
            }
        }

        return mem[pos] = max(a,b);
    }

public:
    int deleteString(string& s) {
        int n = s.size();
        if( n == 1 )
            return 1;

        // calculate hash values for all the prefixes of s
        p_pow[0] = 1;
        for(int i = 1; i < n; ++i)
            p_pow[i] = (p_pow[i-1] * p) % m;

        h[0] = 0;
        for(int i = 0; i < n; ++i)
            h[i+1] = (h[i] + (s[i]-'a'+1) * p_pow[i]) % m;


        memset(mem,-1,sizeof mem);
        return rec(s,n,0);
    }
};



// passes 115/129 test cases, then TLE as of 11/24/2023

class Solution {
private:
    bool is_equal(string& s, int i, int j) {
        int i_limit = j;
        while( i < i_limit ) {
            if( s[i] != s[j] )
                return false;
            ++i;
            ++j;
        }
        return true;
    }

    int mem[4000];

    int rec(string& s, int n, int pos) {
        if( pos == n )
            return 0;
        if( pos == n-1 )
            return 1;

        if( mem[pos] != -1 )
            return mem[pos];

        // we have a choice
        //     delete the entire remaining string starting at pos OR
        //     attempt to delete portions if the conditions are met

        int a = 1;

        int b = 0;
        int l_remaining = n - pos;
        int i = pos;
        string s1(1,s[i]);
        int j = pos+1;
        string s2(1,s[pos+1]);
        for(int l = 1; l <= l_remaining/2; ++l) {
            if( s1 == s2 ) {
                // we could delete in one operation
                // s[pos,pos+l-1] inclusive
                b = max(b, 1 + rec(s,n,pos+l));
            }
            ++i;
            s1 += s[i];

            s2.erase(0,1);
            ++j;
            if( j < n )
                s2 += s[j];
            ++j;
            if( j < n )
                s2 += s[j];
        }

        return mem[pos] = max(a,b);
    }

public:
    int deleteString(string& s) {
        int n = s.size();
        if( n == 1 )
            return 1;

        memset(mem,-1,sizeof mem);
        return rec(s,n,0);
    }
};
