
// 2168. Unique Substrings With Equal Digit Frequency
// https://leetcode.com/problems/unique-substrings-with-equal-digit-frequency/




class Solution {
public:
    int equalDigitFrequency(string s) {
        int n = s.size(); // 1 <= s.length <= 1000
        int ans = 0;

        int p = 11;                         // base

        unordered_set<unsigned long long> seen;
        for(int i = 0; i < n; ++i) {
            vector<int> cnt(10,0);
            unsigned long long cur_h = 0;

            for(int j = i; j < n; ++j) {

                ++cnt[s[j]-'0'];

                // rolling hash
                cur_h = (cur_h * p) + (s[j]-'0'+1);
                if( !seen.insert(cur_h).second )
                    continue;


                bool f = true;
                int t = -1;
                for(int k = 0; k < 10; ++k) {
                    if( cnt[k] > 0 ) {
                        if( t == -1 ) {
                            t = cnt[k];
                        } else if( cnt[k] != t) {
                            f = false;
                            break;
                        }
                    }
                }
                if( f )
                    ++ans;
            }
        }

        return ans;
    }
};
