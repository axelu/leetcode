
// 3303. Find the Occurrence of First Almost Equal Substring
// https://leetcode.com/problems/find-the-occurrence-of-first-almost-equal-substring/





// initialize once
unsigned long long p_pow[300001];
bool initialized = false;

class Solution {
private:
    const int p = 31;
    const int m = 1e9 + 9;

    unsigned long long h_s[300001];
    unsigned long long h_p[300001];

    // binary search
    int search(int i, int s, int e) {
        // cout << "search i " << i << " s " << s << " e " << e << endl;
        // finds the lenght of the longest prefix starting at index i in s that matches pattern Prefix HashSet.

        // i is the fix starting point in s
        // s = 0 means we don't even have the 1st char match
        // example target_size = 14
        //         01234567890123
        //            i
        // s       xyzgabce
        // pattern    gabde
        // result 3

        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);

        unsigned long long h = (h_s[i+mid] + m - h_s[i]) % m;
        if( h == h_p[mid] * p_pow[i] % m ) {
            // can we do better?
            int t = search(i, mid+1, e);
            return t != -1 ? t : mid;
        }

        return search(i, s, mid-1);
    }

public:
    int minStartingIndex(string s, string pattern) {
        // 1 <= pattern.length < s.length

        // brute force
        // we align s and pattern (p[0] at s[0])
        //     find the first mismatch by going along both
        //     we skip the mismatch and see if the remaining chars match
        //     if so we have our answer
        //     if not
        // then we slide pattern by one so that p[0] at s[1] line up and we repeat
        // how can we make this fast: rabin-karp hash and binary search

        if( !initialized ) {
            initialized = true;
            p_pow[0] = 1ULL;
            for(int i = 1; i < 300001; ++i)
                p_pow[i] = (p_pow[i-1] * p) % m;
        }

        int s_sz = s.size();
        h_s[0] = 0LL;
        for(int i = 0; i < s_sz; ++i)
            h_s[i+1] = (h_s[i] + (s[i]-'a'+1) * p_pow[i]) % m;

        int p_sz = pattern.size();
        h_p[0] = 0LL;
        for(int i = 0; i < p_sz; ++i)
            h_p[i+1] = (h_p[i] + (pattern[i]-'a'+1) * p_pow[i]) % m;

        for(int i = 0; i <= s_sz - p_sz ; ++i) {    // index in s
            // find first mismatch
            int t = search(i, 0, p_sz);
            if( t >= p_sz-1 ) // either full match or last char doesn't match
                return i;

            // we need hash in s starting at       i+t+1 till i+(m-1)
            unsigned long long h1 = (h_s[i+(p_sz-1)+1] + m - h_s[i+t+1]) % m;
            // we need hash in pattern starting at t+1   till m-1
            unsigned long long h2 = (h_p[(p_sz-1)+1] + m - h_p[t+1]) % m;

            if( h1 == h2 * p_pow[i] % m )
                return i;
        }

        return -1;
    }
};
