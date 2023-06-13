
// 2680. Maximum OR
// https://leetcode.com/problems/maximum-or/



/* x * 2 same as x << 1
 *
 * we want to apply the operation on x
 * that 'covers' the most leftmost unset bit
 * if there is a tie,
 * chose the one that covers the next leftmost unset bit
 *
 * example 12,9
 *      543210
 * 12     1100
 *  9     1001
 * both, 12*2 and 9*2 would cover bit 4
 * but applying the operation on 9, would additionally cover bit 1
 * hence we are choosing to apply the operation on 9
 *      543210
 * 12     1100
 * 18    10010
 * -----------
 * 30    11110
 *
 */
class Solution {
private:
    void setbits(long long x, vector<int>& cnt) {
        for(int i = 0; i < 45; ++i)
            if( (x >> i) & 1LL )
                ++cnt[i];
    }

    int leftmostbit(long long x) {
        // x > 0
        int ret;
        for(int i = 0; i < 45; ++i)
            if( (x >> i) & 1LL )
                ret = i;

        return ret;
    }

    long long reverseor(long long x, vector<int> cnt) {
        long long ret = 0;
        for(int i = 0; i < 45; ++i) {
            if( (x >> i) & 1LL )
                --cnt[i];
            if( cnt[i] > 0 )
                ret |= 1LL << i;
        }

        return ret;
    }

public:
    long long maximumOr(vector<int>& nums, int k) {
        // 1 <= k <= 15
        //                   432109876543210987654321098765432109876543210
        // 1e9 binary                       111011100110101100101000000000
        //                   432109876543210987654321098765432109876543210
        // 1e9 << 15 binary  111011100110101100101000000000000000000000000

        vector<int> cnt(45,0);

        int mx_lmb = -1;
        unordered_set<long long> us;

        for(int x: nums) {
            setbits(x,cnt);
            int lmb = leftmostbit(x);
            if( lmb > mx_lmb ) {
                us.clear();
                us.insert(x);
                mx_lmb = lmb;
            } else if( lmb == mx_lmb ) {
                us.insert(x);
            }
        }

        long long ans = 0;

        // us contains all unique nums[i] that have the highest lmb seen set
        // apply operation k times to each and record max ans
        for(long long x: us) {

            // reverse OR
            long long t = reverseor(x,cnt);

            x = x << k;

            // apply OR
            t |= x;
            ans = max(ans,t);
        }

        return ans;
    }
};
