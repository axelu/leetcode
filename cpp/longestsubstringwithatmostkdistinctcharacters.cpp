
// 340. Longest Substring with At Most K Distinct Characters
// https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/




class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int n = s.size();

        int ans = 0;

        int cnt[256];memset(cnt,0,sizeof cnt);
        int l = 0; // left index
        int d = 0; // number of different letters
        for(int i = 0; i < n; ++i) {
            // cout << "before i " << i << " l " << l << " d " << d << endl;
            ++cnt[s[i]];
            if( cnt[s[i]] == 1 )
                ++d;
            // min sliding window size k+1
            //if( i-l < k)
            //    continue;

            while( d > k ) {
                --cnt[s[l]];
                if( cnt[s[l]] == 0 )
                    --d;
                ++l;
            }

            ans = max(ans,i-l+1);
            // cout << "after  i " << i << " l " << l << " d " << d << " ans " << ans << endl;
        }

        return ans;

    }
};
