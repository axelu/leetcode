
// 1170. Compare Strings by Frequency of the Smallest Character
// https://leetcode.com/problems/compare-strings-by-frequency-of-the-smallest-character/



class Solution {
private:
    int c[26];

    int f(string& s) {
        // calculates the frequency of the smallest character in s
        for(int i = 0; i < 26; ++i) c[i] = 0; // init,reset
        for(auto it = begin(s); it != end(s); ++it)
            ++c[*it-'a'];
        for(int i = 0; i < 26; ++i)
            if( c[i] != 0 ) return c[i];
        return -1;
    }

public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        size_t n = words.size();
        vector<int> v(n);
        for(int i = 0; i < n; ++i)
            v[i] = f(words[i]);
        sort(begin(v),end(v));

        size_t m = queries.size();
        vector<int> r(m);
        auto itvb = begin(v);
        auto itve = end(v);
        vector<int>::iterator it;
        for(int i = 0; i < m; ++i) {
            it = upper_bound(itvb,itve,f(queries[i]));
            r[i] = it == itve ? 0 : n - distance(itvb,it);
        }
        return r;
    }
};
