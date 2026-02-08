
// 3734. Lexicographically Smallest Palindromic Permutation Greater Than Target
// https://leetcode.com/problems/lexicographically-smallest-palindromic-permutation-greater-than-target/



class Solution {
private:
    bool construct_best(int i, int n, int freq[], string& target, string& out) {
        // if we are arriving at the half point
        // distinguish between odd and even
        // check if we are beating in the second half
        // if so, return true, else return false
        if( i == n/2 ) {
            for(int j = i; j < n; ++j) {
                if( out[j] > target[j] )
                    return true;
                else if( out[j] < target[j] )
                    return false;
            }
            return false;
        }

        // we have to match or beat target
        // if we cannot match, we have to beat
        //    if at that point we cannot beat, we need to backtrack
        char target_char = target[i];
        if( freq[target_char-'a'] > 0 ) {
            freq[target_char-'a'] -= 2;
            out[i] = target_char;
            out[n-1-i] = target_char;
            bool f = construct_best(i+1, n, freq, target, out);
            if( f ) {
                return true;
            } else {
                // backtrack
                freq[target_char-'a'] += 2;
            }
        }
        // if we are here we must beat
        for(int k = (target_char-'a')+1; k < 26; ++k) {
            if( freq[k] > 0 ) {
                freq[k] -= 2;
                out[i] = k+'a';
                out[n-1-i] = k+'a';
                // fill in the rest
                int pos = i+1; // index in out
                for(int c = 0; c < 26; ++c) {
                    for(int j = 0; j < freq[c]; j += 2) {
                        out[pos] = out[n-1-pos] = c+'a';
                        ++pos;
                    }
                }
                return true;
            }
        }

        return false;
    }

public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size(); // 1 <= s.size() = target.size() << 300
        if( n == 1 )
            return s[0] > target[0] ? s : "";

        int freq[26]; memset(freq, 0, sizeof freq);
        int odds = 0;
        char largest_chr = 'a';
        for(char c: s) {
            ++freq[c-'a'];
            odds += freq[c-'a'] % 2 ? 1 : -1;
            largest_chr = max(largest_chr, c);
        }

        // quick check
        // can we make a palindromic string s at all?
        // if n is even, then we need even numbers of all chars
        // if n is odd, we need even numbers of all chars and 1 odd
        if( (n % 2 == 0 && odds != 0) || (n % 2 == 1 && odds != 1) )
            return "";

        // at this point we know s can be made into a palindrome

        // can only have a chance to make it if s has a char
        // greater than smallest char in target
        char smallest_chr_target = 'z';
        for(char c: target)
            smallest_chr_target = min(smallest_chr_target, c);
        if( largest_chr <= smallest_chr_target )
            return "";

        string out(n,'#');
        if( n % 2 ) {
            // we must put the odd numbered char at n / 2
            char odd_char; // guaranteed we have will have it
            for(int i = 0; i < 26; ++i)
                if( freq[i] % 2 ) {
                    odd_char = i+'a';
                    break;
                }
            --freq[odd_char-'a'];
            out[n/2] = odd_char;
        }

        bool f = construct_best(0, n, freq, target, out);
        return f ? out : "";
    }
};
