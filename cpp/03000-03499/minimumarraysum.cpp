
// 3366. Minimum Array Sum
// https://leetcode.com/problems/minimum-array-sum/





class Solution {
private:
    int mem[100][101][101];

    int rec(vector<int>& nums, int n, int k, int pos, int op1, int op2) {
        if( pos == n )
            return 0;

        if( op1 == 0 && op2 == 0 ) {
            int sum = 0;
            for(int i = pos; i < n; ++i)
                sum += nums[i];
            return sum;
        }

        if( mem[pos][op1][op2] != -1 )
            return mem[pos][op1][op2];

        // we have choices
        //     don't apply op1 or op2 to nums[pos] OR
        //     apply op1 to nums[pos] (if we can) OR
        //     apply op2 to nums[pos] (if we can) OR
        //     apply op1 and op2 to nums[pos] (if we can)

        int a = nums[pos] + rec(nums, n, k, pos+1, op1, op2);

        int b = INT_MAX;
        if( op1 > 0 ) {
            int numspos_new = ceil(nums[pos] / 2.0);
            b = numspos_new + rec(nums, n, k, pos+1, op1-1, op2);
        }

        int c = INT_MAX;
        if( op2 > 0 && nums[pos] >= k ) {
            int numspos_new = nums[pos] - k;
            c = numspos_new + rec(nums, n, k, pos+1, op1, op2-1);

        }

        int d = INT_MAX;
        if( op1 > 0 && op2 > 0 ) {
            // if we apply both 1 and 2, we may as well do it in the order of biggest gain

            // op1, then op2
            int t = ceil(nums[pos] / 2.0);
            if( t >= k ) {
                int numspos_new = t - k;
                d = numspos_new + rec(nums, n, k, pos+1, op1-1, op2-1);
            }

            // op2, then op1
            if( nums[pos] >= k ) {
                int numspos_new = nums[pos] - k;
                numspos_new = ceil(numspos_new / 2.0);
                d = min(d, numspos_new + rec(nums, n, k, pos+1, op1-1, op2-1));
            }
        }

        return mem[pos][op1][op2] = min({a,b,c,d});
    }




public:
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        int n = nums.size(); // 1 <= n <= 100

        memset(mem,-1,sizeof mem);
        return rec(nums, n, k, 0, op1, op2);
    }
};
