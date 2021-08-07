
// 1316. Distinct Echo Substrings
// https://leetcode.com/problems/distinct-echo-substrings/




// inspired by Rabin-Karp Algorithm
// https://cp-algorithms.com/string/rabin-karp.html
// rolling hash
class Solution {
public:
    int distinctEchoSubstrings(string& text) {
        int n = text.size();
        if( n == 1 )
            return 0;


        // calculate hash values for all the prefixes of text
        const int p = 31;
        const int m = 1e9 + 9;


        vector<long long> p_pow(n);
        p_pow[0] = 1;
        for(int i = 1; i < n; ++i)
            p_pow[i] = (p_pow[i-1] * p) % m;


        vector<long long> h(n+1,0);
        for(int i = 0; i < n; ++i)
            h[i+1] = (h[i] + (text[i]-'a'+1) * p_pow[i]) % m;



        // length of our maximum substring
        int lmax = n/2;


        // we will test every substring of size l [1,lmax]
        // at every position [0,n-2*l] and check if it
        // is followed by the same substring

        int ans = 0;
        set<string> st;

        int s1;   // start of substring1
        int s2;   // start of substring2, same length as sstring1 immediately folling sstring1
        for(int l = 1; l <= lmax; ++l) {
            st.clear();
            for(s1 = 0; s1 <= n-2*l; ++s1) {
                s2 = s1+l;

                long long h1 = (h[s1+l] + m - h[s1]) % m;
                long long h2 = (h[s2+l] + m - h[s2]) % m;

                if( h2 == h1 * p_pow[l] % m )
                    st.insert(text.substr(s1,l));
            }
            ans += st.size();
        }

        return ans;
    }
};
