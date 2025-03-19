
// 3474. Lexicographically Smallest Generated String
// https://leetcode.com/problems/lexicographically-smallest-generated-string/
// Rabin-Karp rolling hash no modulus






// initialize once
unsigned long long p_pow[10501];
bool initialized = false;

class Solution {
private:
    const int p = 31;

    unsigned long long h[10501];
    unsigned long long hstr2[500];
    unsigned long long finalh[10501];

    // generates best lexicographically smallest possible string
    // that is not equal str2
    string get_str(string s) {
        bool changed = false;
        for(int i = 0; i < s.size(); ++i) {
            if( s[i] == 'a' )
                continue;
            changed = true;
            s[i] = 'a';
        }
        if( !changed )
            s[s.size()-1] = 'b';
        return s;
    }

    // TODO if we had a prefix hash of s and str2, we could do this in O(1)
    bool overlay_match(string& str, string& str2, int s, int e) {
        int i = 0;
        for(; s <= e; ++s)
            if( str[s] != str2[i] )
                return false;
        return true;
    }

public:
    string generateString(string str1, string str2) {
        if( !initialized ) {
            initialized = true;
            p_pow[0] = 1ULL;
            for(int i = 1; i < 10501; ++i)
                p_pow[i] = p_pow[i-1] * p;
        }

        int n = str1.size();
        int m = str2.size();

        // edge case str1.size() == 1
        if( n == 1 )
            return str1 == "T" ? str2 : get_str(str2);

        // edge case str2.size() == 1
        if( m == 1 ) {
            char c = str2 == "a" ? 'b' : 'a';
            for(int i = 0; i < n; ++i)
                str1[i] = str1[i] == 'T' ? str2[0] : c;
            return str1;
        }

        vector<int> ts; // indicies of 'T' in str1
        for(int i = 0; i < n; ++i)
            if( str1[i] == 'T' )
                ts.push_back(i);

        string ans(m+n-1,'{');

        // edge case if str1 only Fs, then n + m - 1 a's is the answer
        if( ts.empty() ) {
            string s = get_str(str2);
            int s_idx = 0;
            int i = 0;
            for(; i < n; ++i) {
                ans[i] = s[s_idx];
                ++s_idx;
                if( s_idx == m )
                    s_idx = 0;
            }
            for(; s_idx < m; ++s_idx) {
                ans[i] = s[s_idx];
                ++i;
            }
            for(; i < m+n-1; ++i)
                ans[i] = 'a';
            return ans;
        }

        /*
        int i = 0;
        for(int t: ts) {
            if( i < t ) {
                // gap i ... t - 1
                // TODO
                i = t;
            }
            if( i == t ) {
                // no overlap and no gap
                for(int j = 0; j < m; ++j, ++i)
                    ans[i] = str2[j];
                continue;
            }

            // i is our next index in ans
            // we have written ans up to i-1
            // 01234567890123456789
            //         i
            //      t
            // we need to check if t..i-1 matches str2[0]...str2[i-1-t]
            // if it does, we write str2[i-t] into ans starting at i
            if( !overlay_match(ans, str2, t, i-1) )
                return "";
            for(int j = i-t; j < m; ++j, ++i)
                ans[i] = str2[j];
        }
        */

        // going 0, 1, 2, ... in ans
        // build a rolling hash as we go along
        // build a rolling hash of str2 (one time)
        // then we can use that for fast checks
        // for both, where str1[j] == 'T' and str1[j] == 'F'

        hstr2[0] = str2[0]-'a'+1;
        for(int k = 1; k < m; ++k)
            hstr2[k] = (hstr2[k-1] * p) + (str2[k]-'a'+1);
        // cout << "hstr2 " << hstr2[m-1] << endl;

        int i = 0;                      // we have written ans up to i-1
        for(int j = 0; j < n; ++j) {    // index in str1 and ans
            if( str1[j] == 'F' ) {
                if( j == i ) {
                    if( i == 0 ) {
                        h[0] = ans[0]-'a'+1;
                    } else {
                        h[i] = (h[i-1] * p) + (ans[i]-'a'+1);
                    }
                    ++i;
                }
                continue;
            }
            // we are at 'T'
            // we need to start str2 at j
            // i < j will never happen
            if( i == j ) {
                // no gap no overlap
                int k = 0; // index in str2
                if( i == 0 ) {
                    ans[0] = str2[0];
                    h[0] = ans[0]-'a'+1;
                    ++i;
                    ++k;
                }
                for(; k < m; ++k, ++i) {
                    ans[i] = str2[k];
                    h[i] = (h[i-1] * p) + (ans[i]-'a'+1);
                }

            } else { // i > j
                // we have written ans up to i-1
                // 01234567890123456789
                //         i
                //      j
                //      ---
                // we need to check if j..i-1 matches str2[0]...str2[i-1-j]
                // if it does, we write str2[i-j] into ans starting at i
                unsigned long long h_s = h[i-1] - (h[j-1] * p_pow[(i-1)-(j-1)]);
                if( h_s != hstr2[i-1-j] )
                    return "";
                for(int k = i-j; k < m; ++k, ++i) {
                    ans[i] = str2[k];
                    h[i] = (h[i-1] * p) + (ans[i]-'a'+1);
                }
            }
        }
        // gap at end i...n+m-2
        for(; i < n+m-1; ++i)
            h[i] = (h[i-1] * p) + (ans[i]-'a'+1);

        // check if Fs are satisfied, ignoring if an F at 0
        for(int j = 1; j < n; ++j) {    // index in str1 and ans
            if( str1[j] == 'F' ) {
                i = j + m;
                unsigned long long h_s = h[i-1] - (h[j-1] * p_pow[(i-1)-(j-1)]);
                if( h_s == hstr2[m-1] )
                    return "";
            }
        }

        // fill in the gaps as best as possible
        // gaps can mess up 'F's

        string finalans(m+n-1,'#');
        // it is always best to change the last possible position
        i = 0;
        int last = -1; // last position we can change
        for(; i < n+m-1; ++i) {
            if( ans[i] == '{' ) {
                finalans[i] = 'a';
                last = i;
            } else {
                finalans[i] = ans[i];
            }
            if( i == 0 ) {
                finalh[0] = finalans[0]-'a'+1;
            } else {
                finalh[i] = (finalh[i-1] * p) + (finalans[i]-'a'+1);
            }
            // we have to check if we violate an 'F'
            if( i-m+1 >= 0 && str1[i-m+1] == 'F' ) {
                unsigned long long h_s;
                if( i-m+1 == 0 )
                    h_s = finalh[i];
                else
                    h_s = finalh[i] - (finalh[i-m] * p_pow[m]);
                if( h_s == hstr2[m-1] ) {
                    // we need to backtrack and change last possible position
                    // we started with 'a' on it, so we will try b, c, ... z
                    // if still no good we will give up
                    if( last == -1 || finalans[last] == 'z' )
                        return "";
                    while( h_s == hstr2[m-1] && finalans[last] != 'z' ) {
                        ++finalans[last];
                        // rebuild finalhash starting at last
                        for(int j = last; j <= i; ++j) {
                            if( j== 0 ) {
                                finalh[0] = finalans[0]-'a'+1;
                            } else {
                                finalh[j] = (finalh[j-1] * p) + (finalans[j]-'a'+1);
                            }
                        }
                        // recalculate h_s
                        if( i-m+1 == 0 )
                            h_s = finalh[i];
                        else
                            h_s = finalh[i] - (finalh[i-m] * p_pow[m]);
                    }
                    if( finalans[last] == 'z' )
                        return "";
                }
            }
        }

        // cout << ans << endl;
        // cout << finalans << endl;

        return finalans;
    }
};
