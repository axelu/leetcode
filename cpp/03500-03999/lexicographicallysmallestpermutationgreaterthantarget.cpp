
// 3720. Lexicographically Smallest Permutation Greater Than Target
// https://leetcode.com/problems/lexicographically-smallest-permutation-greater-than-target/



class Solution {
private:

    string ans;

    bool rec(string& s, int n, int pos, int freq[], string& target) {
        if( pos == n )
            return false;

        // we will try to match char in s to char in target
        // at each position, said differently, we will delay
        // using a char at s[pos] > target[pos] as long as possible

        int c_target = target[pos]-'a';
        if( freq[c_target] > 0 ) {
            // we have at least 1x c_target left for s
            --freq[c_target];
            ans.push_back(c_target+'a');
            bool f = rec(s, n, pos+1, freq, target);
            if( f )
                return true;
            // backtrack
            ans.pop_back();
            ++freq[c_target];
        }

        // we must use the next greater char than c_target at position pos
        // if we can
        for(int i = c_target+1; i < 26; ++i) {
            if( freq[i] > 0 ) {
                --freq[i];
                ans.push_back(i+'a');

                // add any remaining char to ans
                for(int j = 0; j < 26; ++j) {
                    while( freq[j] > 0 ) {
                        --freq[j];
                        ans.push_back(j+'a');
                    }
                }
                return true;
            }
        }

        return false;
    }

public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size(); // 1 <= s.length == target.length <= 300

        // if we don't have a char in s that is greater than any char in target
        // then we would know right away that we do not have a a solution

        int freq[26];
        for(int i = 0; i < n; ++i)
            ++freq[s[i]-'a'];

        ans = "";
        bool f = rec(s, n, 0, freq, target);
        return f ? ans : "";
    }
};
