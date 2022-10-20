
// 2262. Total Appeal of A String
// https://leetcode.com/problems/total-appeal-of-a-string/



class Solution {
public:
    long long appealSum(string& s) {
        int n = s.size();

        int last_seen[26];memset(last_seen,-1,sizeof last_seen);

        long long ans = 0;

        for(int i = 0; i < n; ++i) {
            // substrings ending at i

            last_seen[s[i]-'a'] = i;

            for(int c = 0; c < 26; ++c) {
                // number of substrings ending at index i that contain char c
                long long t = 1 + last_seen[c];


                // appeal of all substrings ending at index i
                // is the sum of the number of substrings that contain each alphabetic character.
                ans += t;
            }
        }

        return ans;
    }
};
