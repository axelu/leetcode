
// 3717. Minimum Operations to Make the Array Beautiful
// https://leetcode.com/problems/minimum-operations-to-make-the-array-beautiful/


class Solution {
private:
    vector<int> suffixSum; // "0-indexed"

    const int INF = 100000;

    int mem[101][101];

    int rec(vector<int>& nums, int mx_pos, int pos, int pre, int mx) {
        int n = nums.size();
        // pre is a proper multiple of nums[0]

        if( pre >= mx ) {
            int l = n - pos;
            return (l * pre) - suffixSum[pos];
        }

        if( mem[pos][pre] != -1 )
            return mem[pos][pre];

        int ret = INF;

        for(int f = 1; ; ++f) {
            if( f * pre < nums[pos] )
                continue;

            if( pos == mx_pos ) {
                int l = n - pos;
                return mem[pos][pre] = (l * f * pre) - suffixSum[pos];
            }

            int incr = (f * pre) - nums[pos];
            ret = min(ret, incr + rec(nums, mx_pos, pos+1, f*pre, mx));
            if( f * pre >= mx )
                break;
        }

        return mem[pos][pre] = ret;
    }

public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;

        // each nums[i] needs to become a multiple of nums[0]
        // we can only increment by 1

        // find mx_val and mx_pos (left most pos)
        int mx_val = 0; // 1 <= nums[i] <= 50
        int mx_pos = -1;
        for(int i = 0; i < n; ++i) {
            if( nums[i] > mx_val ) {
                mx_val = nums[i];
                mx_pos = i;
            }
        }

        // edge case
        if( mx_pos == 0 ) {
            int ans = 0;
            for(int i = 1; i < n; ++i)
                ans += mx_val - nums[i];
            return ans;
        }

         // find the next greater multiple of nums[0] to mx_val
        int f = 2;
        while( f * nums[0] < mx_val )
            ++f;

        //cout << "mx_val " << mx_val << " mx_pos " << mx_pos;
        //cout << " nums[0] " << nums[0] << " f " << f << " f*nums[0] " << f*nums[0] << endl;

        suffixSum.resize(n);
        suffixSum[n-1] = nums[n-1];
        for(int i = n-2; i >= 0; --i)
            suffixSum[i] = suffixSum[i+1] + nums[i];

        memset(mem, -1, sizeof mem);
        return rec(nums, mx_pos, 1, nums[0], f * nums[0]);
    }
};
