
// 2405. Optimal Partition of String
// https://leetcode.com/problems/optimal-partition-of-string/



class Solution {
public:
    int partitionString(string& s) {

        int ans = 1;

        // go as long as we don't have a duplicate letter -> greedy
        int cnt[26];memset(cnt,0,sizeof cnt);
        for(char c: s)
            if( cnt[c-'a'] == 0 ) {
                ++cnt[c-'a'];
            } else {
                ++ans;
                memset(cnt,0,sizeof cnt);
                ++cnt[c-'a'];
            }

        return ans;
    }
};
