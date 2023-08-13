
// 2170. Minimum Operations to Make the Array Alternating
// https://leetcode.com/problems/minimum-operations-to-make-the-array-alternating/



/* 0 1 2 3 4 5 6 7 8 9 0
 * lets assume we make the even ones the equal
 * x   x   x   x   x   x
 * lets assume we make the odd ones the equel
 *   x   x   x   x   x
 */
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;
        if( n == 2 )
            return nums[0] == nums[1] ? 1 : 0;

        int nbr_odds = n/2;
        int nbr_evens = n/2;
        if( n % 2 )
            ++nbr_evens;

        int cnt_odds[100001];memset(cnt_odds,0,sizeof cnt_odds);
        int cnt_evens[1000001];memset(cnt_evens,0,sizeof cnt_evens);
        for(int i = 0; i < n; ++i)
            if( i % 2 )
                ++cnt_odds[nums[i]];
            else
                ++cnt_evens[nums[i]];

        // process the evens
        // we need to keep the top 2 by count
        int even_mx_cnt = 0, even_mx_val;
        int even_mx_cnt1 = 0, even_mx_val1;
        for(int k = 1; k <= 100000; ++k) {
            if( cnt_evens[k] > even_mx_cnt ) {
                // push current max into second position
                even_mx_cnt1 = even_mx_cnt;
                even_mx_val1 = even_mx_val;
                // set new max
                even_mx_cnt = cnt_evens[k];
                even_mx_val = k;
            } else if(cnt_evens[k] > even_mx_cnt1)
                even_mx_cnt1 = cnt_evens[k];
                even_mx_val1 = k;
        }

        // process the odds
        // we need to keep the top 2 by count
        int odd_mx_cnt = 0, odd_mx_val;
        int odd_mx_cnt1 = 0, odd_mx_val1;
        for(int k = 1; k <= 100000; ++k) {
            if( cnt_odds[k] > odd_mx_cnt ) {
                // push current max into second position
                odd_mx_cnt1 = odd_mx_cnt;
                odd_mx_val1 = odd_mx_val;
                // set new max
                odd_mx_cnt = cnt_odds[k];
                odd_mx_val = k;
            } else if(cnt_odds[k] > odd_mx_cnt1) {
                odd_mx_cnt1 = cnt_odds[k];
                odd_mx_val1 = k;
            }
        }

        // case 1
        int t1 = nbr_evens - even_mx_cnt;
        if( odd_mx_val != even_mx_val )
            t1 += nbr_odds - odd_mx_cnt;
        else
            t1 += nbr_odds - odd_mx_cnt1;

        // case2
        int t2 = nbr_odds - odd_mx_cnt;
        if( even_mx_val != odd_mx_val )
            t2 += nbr_evens - even_mx_cnt;
        else
            t2 += nbr_evens - even_mx_cnt1;

        return min(t1,t2);
    }
};
