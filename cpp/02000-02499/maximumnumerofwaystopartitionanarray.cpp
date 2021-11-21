
// 2025. Maximum Number of Ways to Partition an Array
// https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/





/*
 example # 3
	0	1	2	3	4	5	6	7	8	9  10  11  12  13	n = 13
   22	4 -25 -20 -15  15 -16	7  19 -10	0 -13 -14
	0  22  26	1 -19 -34 -19 -35 -28  -9 -19 -19 -32 -46	prefix[i]
  -46 -68 -72 -47 -27 -12 -27 -11 -18 -37 -27 -27 -14		suffix[i]*
  -46 -90 -98 -48  -8  22  -8  24  10 -28  -8  -8  18		diff[i] = suffix-prefix
  notice the occurences of diff = -8

  k = -33, if we change nums[i] to -33
	0	1	2	3	4	5	6	7	8	9  10  11  12	    n = 13
  -55 -37  -8 -13 -18 -48 -17 -40 -52 -23 -33 -20 -19	    k - nums[i]
  notice that if we change nums[2] from -25 to -33, the delta is -8
  that delta of -8 has 4 occurences to the right (see above)

  here with nums[2] changed to -33
	0	1	2	3	4	5	6	7	8	9  10  11  12  13	n = 13
   22	4 -33 -20 -15  15 -16	7  19 -10	0 -13 -14
	0  22  26  -7 -27 -42 -27 -43 -36 -17 -27 -27 -40 -54		prefix[i]
  -54 -76 -80 -47 -27 -12 -27 -11 -18 -37 -27 -27 -14			suffix[i]*
  -54 -98-106 -40	0  30	0  32  18 -20	0	0  26			diff[i] = suffix-prefix
  where the diff is 0 now are pivot points

  we also need to look to the left at the same time!
  k =	-6, if we change nums[i] to -6
	0	1	2	3	4	5	6	7	8	9  10  11  12	        n = 13
  -28 -10  19  14	9 -21  10 -13 -25	4  -6	7	8		    k - nums[i]
  see how the delta for nums[12] becomes 8, so we need to look at
  the left diffs, but for the opposite, meaning delta * -1

  here with nums[12] change to -6
	0	1	2	3	4	5	6	7	8	9  10  11  12  13	n = 13
   22	4 -25 -20 -15  15 -16	7  19 -10	0 -13  -6
	0  22  26	1 -19 -34 -19 -35 -28  -9 -19 -19 -32 -38		prefix[i]
  -38 -60 -64 -39 -19  -4 -19  -3 -10 -29 -19 -19  -6			suffix[i]*
  -38 -82 -90 -40	0  30	0  32  18 -20	0	0  26			diff[i] =  = suffix-prefix
  where the diff is 0 now are pivot points

*/
class Solution {
public:
    int waysToPartition(vector<int>& nums, int k) {
        int n = nums.size();

        // there are n-1 ways to partition the array

        long total = 0L;
        for(int i = 0; i < n; ++i)
            total += (long)nums[i];

        int ans = 0;

        unordered_map<long,int> diff_cnt_right; // diff,number of occurence
        long lft = 0L,rgt;
        long d; // left - right
        for(int i = 0; i < n-1; ++i) {
            lft += nums[i];
            rgt = total-lft;
            if( lft == rgt )
                ++ans;

            d = lft - rgt;
            ++diff_cnt_right[d]; // will insert if not present
        }

        if( ans == n-1 ) // unchanged array can be optimally partitioned
            return ans;


        unordered_map<long,int> diff_cnt_left;
        lft = 0;
        long t;
        for(int i = 0; i < n; ++i) {
            lft += nums[i];
            rgt = total-lft;

            d = lft - rgt;

            t = k - (long)nums[i];
            // if we change nums[i] to k, then diff[1] to diff[i] decrease by t,
            // and diff[i+1] to diff[N-1] increase by t
            ans = max(ans,diff_cnt_left[t] + diff_cnt_right[-t]);

            // as we are moving from left to right, we move one occurence
            // of the current diff from right to left
            --diff_cnt_right[d];
            ++diff_cnt_left[d];
        }

        return ans;
    }
};
