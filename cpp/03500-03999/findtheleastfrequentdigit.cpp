
// 3663. Find The Least Frequent Digit
// https://leetcode.com/problems/find-the-least-frequent-digit/



class Solution {
public:
    int getLeastFrequentDigit(int n) {
        int cnt[10]; memset(cnt, 0, sizeof cnt);

        // 1 <= n <= 2^31- 1

        while( n ) {
            int rem = n % 10;
            ++cnt[rem];
            n /= 10;
        }

        int ans;
        int mn_cnt = INT_MAX;
        for(int i = 0; i < 10; ++i) {
            if( cnt[i] > 0 && cnt[i] < mn_cnt ) {
                ans = i;
                mn_cnt = cnt[i];
            }
        }

        return ans;
    }
};
