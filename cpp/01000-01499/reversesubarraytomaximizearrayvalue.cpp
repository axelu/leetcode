
// 1330. Reverse Subarray To Maximize Array Value
// https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/





/* reversing a subarray does not change its 'value'
 * but if we pick up a greater difference on its borders,
 * that will change the score of the entire array, which
 * we have to maximize
 *            0 1 2 3 4
 * example    2 3 1 5 4
 *            |/|/|/|/
 *   value    1 2 4 1   = 8
 *   lets take subarray [1,3] inclusive
 *            3 1 5
 *            |/|/
 *   value    2 4   = 6
 *   reversed 5 1 3
 *            |/|/
 *            4 2   = 6
 *   put the suabarray [1,3] inclusive reversed into our array
 *            2 5 1 3 4
 *            |/|/|/|/
 *   value    3 4 2 1   = 10
 *   by reversing it we picked up a higher diff between pos 0 and 1 and had same diff between pos 3 and 4
 * so the question becomes which two indicies to switch
 *
 * example    1  3 25  value 24   abc
 *            3  1 25  value 26   bac
 *            1 25  3  value 46   acb
 *
 */
class Solution {
private:
    int get_val(vector<int>& nums, int n, int s, int e) {
        // n = nums.size();
        // 0 <= s <= e-1 < n
        int val = 0;
        for(int i = s; i < e; ++i) {
            val += abs(nums[i] - nums[i+1]);
        }

        return val;
    }

    int vals[30000];

    int change(vector<int>& nums, int n, int l, int r) {
        // 0 <= l < r < n

        // if we swap, we change the vals at l-1 and r
        int diff = 0;
        if( l > 0 )
            diff += abs(nums[l-1] - nums[r]) - vals[l-1];
        if( r < n-1 )
            diff += abs(nums[l] - nums[r+1]) - vals[r];

        return diff;
    }

public:
    int maxValueAfterReverse(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;
        if( n == 2 )
            return abs(nums[0] - nums[1]);

        int val_org = 0;
        for(int i = 0; i < n-1; ++i) {
            int val = abs(nums[i] - nums[i+1]);
            vals[i] = val;
            val_org += val;
        }
        /*
        // debug
        for(int i = 0; i < n-1; ++i)
            cout << i << ":" << vals[i] << " ";
        cout << endl;
        */

        int mx_gain = 0;

        /*
        // brute force
        for(int i = 0; i < n-1; ++i) {
            for(int j = i+1; j < n; ++j) {
                mx_gain = max(mx_gain,change(nums,n,i,j));
            }
        }
        return val_org + mx_gain;
        */

        // lets fix the left side of the subarray we are reversing to 0
        for(int r = 1; r < n-1; ++r)
            mx_gain = max(mx_gain,change(nums,n,0,r));

        // lets fix the right side of the subarray we are reversion to n-1
        for(int l = 0; l < n-1; ++l)
            mx_gain = max(mx_gain,change(nums,n,l,n-1));

        // now we need to deal with a subarray somewhere in the middle
        // 0 < l < r < n-1
        // if reverse subarray[l,r], we change the vals at l-1 and r
        // we need to maximize the following:
        //     -abs(nums[l-1] - nums[l]) - abs(nums[r] - nums[r+1]) + abs(nums[l-1] - nums[r]) + abs(nums[l] - nums[r+1])
        //      ------------------------   ------------------------
        //     -      vals[l-1]          -         vals[r]          + abs(nums[l-1] - nums[r]) + abs(nums[l] - nums[r+1])
        //
        // how can we simplify?
        // remember: abs(x-y) = max(x-y,y-x)
        //
        // case A:  nums[l-1] > nums[r] and nums[l] > nums[r+1]
        //     -abs(nums[l-1] - nums[l]) - abs(nums[r] - nums[r+1]) + (nums[l-1] - nums[r]) + (nums[l] - nums[r+1])
        //  -> -abs(nums[l-1] - nums[l]) + nums[l-1] + nums[l] - abs(nums[r] - nums[r+1]) - nums[r] - nums[r+1]
        //     -----------------------------------------------   ----------------------------------------------
        //
        // case B:  nums[l-1] > nums[r] and nums[l] <= nums[r+1]
        //     -abs(nums[l-1] - nums[l]) - abs(nums[r] - nums[r+1]) + (nums[l-1] - nums[r]) + (nums[r+1] - nums[l])
        //  -> -abs(nums[l-1] - nums[l]) + nums[l-1] - nums[l] - abs(nums[r] - nums[r+1]) - nums[r] + nums[r+1]
        //     -----------------------------------------------   ----------------------------------------------
        //
        // case C:  nums[l-1] <= nums[r] and nums[l] > nums[r+1]
        //     -abs(nums[l-1] - nums[l]) - abs(nums[r] - nums[r+1]) + (nums[r] - nums[l-1]) + (nums[l] - nums[r+1])
        //  -> -abs(nums[l-1] - nums[l]) - nums[l-1] + nums[l] - abs(nums[r] - nums[r+1]) + nums[r] - nums[r+1]
        //     -----------------------------------------------   ----------------------------------------------
        //
        // case D:  nums[l-1] <= nums[r] and nums[l] <= nums[r+1]
        //     -abs(nums[l-1] - nums[l]) - abs(nums[r] - nums[r+1]) + (nums[r] - nums[l-1]) + (nums[r+1] - nums[l])
        //  -> -abs(nums[l-1] - nums[l]) - nums[l-1] - nums[l] - abs(nums[r] - nums[r+1]) + nums[r] + nums[r+1]
        //     -----------------------------------------------   ----------------------------------------------
        int Al = INT_MIN, Ar = INT_MIN;
        int Bl = INT_MIN, Br = INT_MIN;
        int Cl = INT_MIN, Cr = INT_MIN;
        int Dl = INT_MIN, Dr = INT_MIN;
        for(int i = 1; i < n-1; ++i) {

            Al = max(Al, -vals[i-1] + nums[i-1] + nums[i]);
            Ar = max(Ar, -vals[i]   - nums[i] - nums[i+1]);

            Bl = max(Bl, -vals[i-1] + nums[i-1] - nums[i]);
            Br = max(Br, -vals[i]   - nums[i] + nums[i+1]);

            Cl = max(Cl, -vals[i-1] - nums[i-1] + nums[i]);
            Cr = max(Cr, -vals[i]   + nums[i] - nums[i+1]);

            Dl = max(Dl, -vals[i-1] - nums[i-1] - nums[i]);
            Dr = max(Dr, -vals[i]   + nums[i] + nums[i+1]);
        }
        mx_gain = max({mx_gain, Al + Ar, Bl + Br, Cl + Cr, Dl + Dr});

        return val_org + mx_gain;
    }
};
