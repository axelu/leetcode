
// 471. Encode String with Shortest Length
// https://leetcode.com/problems/encode-string-with-shortest-length/



class Solution {
private:
    unordered_map<string,string> mem;

    string _encode(string s) {
        int n = s.size();
        if( n <= 4 )
            return s;

        auto f = mem.find(s);
        if( f != mem.end() )
            return f->second;

        vector<string> v[n];

        int n2 = n/2;

        for(int l = 1; l <= n2; ++l) {
            for(int i = n-l; i >= 0; --i) {
                v[i].push_back(s.substr(i,l));
            }
        }

        string dp[n+1]; // shortest encoded string starting at index i
        dp[n]   = "";
        dp[n-1] = s.substr(n-1,1);
        dp[n-2] = s.substr(n-2,2);
        dp[n-3] = s.substr(n-3,3);
        dp[n-4] = s.substr(n-4,4);

        for(int i = n-5; i >= 0; --i) {

            int l_mx = n-i;
            string t = s.substr(i); // initially our best answer
            string b;

            for(int l = 1; l <= l_mx; ++l) {

                // get number of repetitions for s.substr(i,l)
                // starting at i+l
                string a = s.substr(i,l);
                int r = 1; // 1st repetition starting at i
                int e = i+l;
                for(int j = i + l; j <= n-l; j += l)
                    if( v[j][l-1] != a ) {
                        break;
                    } else {
                        ++r;
                        e = j+l;
                    }

                int r_needed = 2;   // we need at least 2 repetitions
                if( l == 1 )
                    r_needed = 5;   // we need at least 5 repetitions
                else if( l <= 3 )
                    r_needed = 3;   // we need at least 3 repetitions

                if( r >= r_needed ) {
                    for(; r >= r_needed; --r, e -= l) {
                        b = to_string(r) + "[" + _encode(a) + "]" + dp[e];
                        if( b.size() < t.size() )
                            t = b;
                    }
                } else {
                    b = "";
                    for(int k = 0; k < r; ++k)
                        b += a;
                    b += dp[e];
                    if( b.size() < t.size() )
                        t = b;
                }

            }

            dp[i] = b.size() < t.size() ? b : t;
        }

        return mem[s] = dp[0];
    }

public:
    string encode(string s) {
        int n = s.size();
        if( n <= 4 )
            return s;

        return _encode(s);
    }
};
