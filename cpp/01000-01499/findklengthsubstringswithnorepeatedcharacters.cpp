
// 1100. Find K-Length Substrings With No Repeated Characters
// https://leetcode.com/problems/find-k-length-substrings-with-no-repeated-characters/





class Solution {
public:
    int numKLenSubstrNoRepeats(string S, int K) {
        int n = S.size();
        if( K > n ) return 0;

        int cnt[26];memset(cnt,0,sizeof cnt);
        unordered_set<char> us;

        int ans = 0;

        for(int i = 0; i < n; ++i) {
            if( i < K-1 ) {
                ++cnt[S[i]-'a'];
                if( cnt[S[i]-'a'] > 1 ) us.insert(S[i]);
                continue;
            }
            ++cnt[S[i]-'a'];
            if( cnt[S[i]-'a'] > 1 ) us.insert(S[i]);
            if( us.size() == 0 ) ++ans;

            --cnt[S[i-K+1]-'a'];
            if( cnt[S[i-K+1]-'a'] == 1 ) us.erase(S[i-K+1]);
        }

        return ans;
    }
};
