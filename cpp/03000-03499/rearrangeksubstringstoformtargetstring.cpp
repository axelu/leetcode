
// 3365. Rearrange K Substrings to Form Target String
// https://leetcode.com/problems/rearrange-k-substrings-to-form-target-string/

// Rabin-Karp rolling hash with modulus





// initialize once
long p_pow[200001];
bool init = false;

class Solution {
private:
    const int p = 31;
    const int m = 1e9 + 9;

public:
    bool isPossibleToRearrange(string s, string t, int k) {
        if( !init ) {
            init = true;
            p_pow[0] = 1L;
            for(int i = 1; i <= 200000; ++i)
                p_pow[i] = (p_pow[i-1] * p) % m;
        }

        int n = s.size(); // s.size() == t.size()

        // edge cases
        if( k == n )
            return true; // s and t are anagrams of each other
        if( k == 1 )
            return s == t;

        // we will split the strings into k equal sized substrings
        // it is guaranteed that n is divisible by k
        int length = n / k;

        // idea
        // create hashes of length of s and store in a map, key: hash, value: count
        // create hashes of length of t, try to find hash in map,
        // if not found the answer is false
        // if found decrement the count, if found and count is 0, the answer is false

        // calculate hash values [0, length - 1], [length, 2*length - 1], ... of s
        unordered_map<long, int> hashes; // hash, count
        long h = 0L;
        // cout << "hashes s" << endl;
        for(int i = 1; i <= n; ++i) {
            h = (h + (s[i-1]-'a'+1) * p_pow[(i-1)%length]) % m;
            if( (i % length) == 0 ) {
                // cout << "i " << i << " h " << h << endl;
                ++hashes[h];
                h = 0L;
            }
        }

        // calculate hash values [0, length - 1], [length, 2*length - 1], ... of t
        h = 0L;
        for(int i = 1; i <= n; ++i) {
            h = (h + (t[i-1]-'a'+1) * p_pow[(i-1)%length]) % m;
            if( (i % length) == 0 ) {
                auto f = hashes.find(h);
                if( f == hashes.end() || f->second == 0 )
                    return false;
                --f->second;
                h = 0L;
            }
        }

        return true;
    }
};
