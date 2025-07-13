
// 3545. Minimum Deletions for At Most K Distinct Characters
// https://leetcode.com/problems/minimum-deletions-for-at-most-k-distinct-characters/


class Solution {
public:
    int minDeletion(string s, int k) {
        vector<int> cnt(26, 0);
        for(char chr: s)
            ++cnt[chr-'a'];

        for(auto it = cnt.begin(); it != cnt.end(); )
            if( *it == 0 )
                it = cnt.erase(it);
            else
                ++it;

        if( cnt.size() <= k )
            return 0;

        sort(cnt.begin(), cnt.end());
        int ans = 0;
        int cnt_sz = cnt.size();
        for(int i = 0; i < cnt_sz && cnt_sz - i > k; ++i)
            ans += cnt[i];

        return ans;
    }
};
