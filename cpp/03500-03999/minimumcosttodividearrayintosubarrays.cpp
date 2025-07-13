
// 3500. Minimum Cost to Divide Array Into Subarrays
// https://leetcode.com/problems/minimum-cost-to-divide-array-into-subarrays/


/* initially implemented Top Down and then Bottom Up DP
   where state is index and subarray order (2D), but too slow as
   it is 2 nested loops, so O(n*n*logn)
   intuition is to get to 1D DP to speed it up, and additional
   intuition is while doing so that we need to get rid of
   the order of the subarray, but keep the starting point
   hence let us use an example
        0 1 2 3
   nums a b c d
   cost w x y z

   let us assume we split at each index 0 1 2 3
                                        - - - -
   total_cost = (a+1*k)*w + (a+b+2*k)*x + (a+b+c+3*k)*y + (a+b+c+d+4*k)*z
                ---------   -----------   -------------   ---------------
   total_cost = a*w + 1*k*w + a*x + b*x + 2*k*x + a*y + b*y + c*y + 3*k*y + a*z + b*z + c*z + d*z + 4*k*z
                -----------   -----------------   -----------------------   -----------------------------
   total_cost = a*w + a*x + b*x + a*y + b*y + c*y + a*z + b*z + c*z + d*z + 1*k*w + 2*k*x + 3*k*y + 4*k*z
   total_cost = a*w + (a+b)*x + (a+b+c)*y + (a+b+c+d)*z + (1*w + 2*x + 3 * y + 4*z)*k
                ---   -------   ---------   -----------   ===========================
                these -- underlined expressions are basically sum of nums till end of subarray * sum of cost in subarray
                lets focuse on the part underliend with ==
                (1*w + 2*x + 3 * y + 4*z)*k = (w + x + x + y + y + y + z + z + z + z) * k
                                            = (w + x + y + z + x + y + z + y + z + z) * k
                                               -------------   ---------   -----   -
                The key observation is, that each represents the sum of cost from start of subarray to end of cost multiplied by k
                                            = (w + x + y + z)*k + (x + y + z)*k + (y + z)*k + z*k
                                               ----------------   -------------   ---------   ---
                if at every split we add that, we have gotten rid of tracking the order of the subarray
                and we can use a 1D DP
    let us proof that by splitting the array differently
    let us assume we split 0 1 2 3, so basically [a],[b,c],[d]
                           - --- -
    our expectation is, that we find (w + x + y + z)*k + (x + y + z)*k + z*k
                                     =======================================

    total_cost = (a+1*k)*w + (a+b+c+2*k)*(x*y) + (a+b+c+d+3*k)*z
                 ---------   -----------------   ---------------
    total_cost = a*w + 1*k*w + a*(x+y) + b*(x+y) + c*(x+y) + 2*k*(x+y) + a*z + b * x + c*z + d*z + 3*k*z
                 -----------   ---------------------------------------   -------------------------------
    total_cost = a*w + a*(x+y) + b*(x+y) + c*(x+y) + a*z + b * x + c*z + d*z + 1*k*w + 2*k*(x+y) + 3*k*z
    total_cost = a*w + (a+b+c)*(x+y) + (a+b+c+d)*z + (1*w + 2*(x+y) + 3*z)*k
    total_cost = a*w + (a+b+c)*(x+y) + (a+b+c+d)*z + (w + x + x + y + y + z + z + z) * k
    total_cost = a*w + (a+b+c)*(x+y) + (a+b+c+d)*z + (w + x + y + z)*k + (x + y + z)*k + z*k
                                                     =======================================

 */
class Solution {

private:
    vector<long long> prefixSum_nums;
    vector<long long> prefixSum_cost;
    int n;
    long long k;

    /*
    long long mem[1000][1001];

    long long rec(int pos, int i) {
        if( pos == n )
            return 0LL;

        int rem = n - pos;

        if( mem[pos][i] != -1LL )
            return mem[pos][i];

        long long ret = LLONG_MAX;

        // we have a choice
        //    use a subarray starting at pos of length 1..rem

        for(int len = 1; len <= rem; ++len) {
            long long nms = (prefixSum_nums[pos+len] + (k * (long long)i));
            long long cst = prefixSum_cost[pos+len] - prefixSum_cost[pos];
            long long t = nms * cst;

            ret = min(ret, t + rec(pos+len, i+1));
        }

        return mem[pos][i] = ret;
    }
    */

    long long mem[1000];

    long long rec(int pos) {
        if( pos == n )
            return 0LL;

        if( mem[pos] != -1LL )
            return mem[pos];

        int rem = n - pos;
        long long ret = LLONG_MAX;

        // pos is the start of our subarray

        for(int len = 1; len <= rem; ++len) {
            // subarray [pos, pos+len-1]
            long long t =  prefixSum_nums[pos+len] * (prefixSum_cost[pos+len]-prefixSum_cost[pos]);
            t += (prefixSum_cost[n] - prefixSum_cost[pos]) * (long long)k;

            ret = min(ret, t + rec(pos+len));
        }

        return mem[pos] = ret;
    }

public:
    long long minimumCost(vector<int>& nums, vector<int>& cost, int k) {
        n = nums.size(); // cost.length == nums.length
        this->k = (long long)k;

        if( n == 1 )
            return (long long)((nums[0]+k) * cost[0]);

        prefixSum_nums.resize(n+1);
        // long long prefixSum_nums[1001];
        prefixSum_nums[0] = 0LL;
        prefixSum_cost.resize(n+1);
        // long long prefixSum_cost[1001];
        prefixSum_cost[0] = 0LL;
        for(int i = 1; i <= n; ++i) {
            prefixSum_nums[i] = prefixSum_nums[i-1] + (long long)nums[i-1];
            prefixSum_cost[i] = prefixSum_cost[i-1] + (long long)cost[i-1];
        }

        // memset(mem,-1,sizeof mem);
        // return rec(0, 1LL);

        /*
        long long dp[1001][1001];memset(dp,0,sizeof dp);
        // fill in last column
        for(int i = 2; i <= n; ++i) {
            long long nms = prefixSum_nums[n] + ((long long)k * (long long)i);
            long long cst = (long long)cost[n-1];
            long long t = nms * cst;
            dp[i][n-1] = t;
        }

        for(int j = n-2; j >= 0; --j) {
            long long i_min = j != 0 ? 2 : 1;
            for(long long i = j+1; i >= i_min; --i) {

                long long res = LLONG_MAX;
                long long f = (long long)k * (long long)i;

                int rem = n - j; // length
                for(int len = 1; len <= rem; ++len) {
                    long long nms = prefixSum_nums[j+len] + f;
                    long long cst = prefixSum_cost[j+len] - prefixSum_cost[j];
                    long long t = nms * cst;

                    res = min(res, t + dp[i+1][j+len]);
                }
                dp[i][j] = res;
            }
        }

        return dp[1][0];
        */

        memset(mem,-1,sizeof mem);
        return rec(0);
    }
};





// BOTTOM UP DP
// passes 740/759 test cases, then TLE
// test case 741 runs in about ~600ms correct result, which is obviously too slow
// see below TOP DOWN DP, that test case runs in about ~600ms with this also returning correct result,
// so BOTTOM UP to TOP DOWN is a great improvement, but not enough

class Solution {
/*
private:
    vector<long long> prefixSum_nums;
    vector<long long> prefixSum_cost;
    int n;
    long long k;

    long long mem[1000][1001];

    long long rec(int pos, int i) {
        if( pos == n )
            return 0LL;

        int rem = n - pos;

        if( mem[pos][i] != -1LL )
            return mem[pos][i];

        long long ret = LLONG_MAX;

        // we have a choice
        //    use a subarray starting at pos of length 1..rem

        for(int len = 1; len <= rem; ++len) {
            long long nms = (prefixSum_nums[pos+len] + (k * (long long)i));
            long long cst = prefixSum_cost[pos+len] - prefixSum_cost[pos];
            long long t = nms * cst;

            ret = min(ret, t + rec(pos+len, i+1));
        }

        return mem[pos][i] = ret;
    }
*/

public:
    long long minimumCost(vector<int>& nums, vector<int>& cost, int k) {
        int n = nums.size(); // cost.length == nums.length
        // this->k = (long long)k;

        if( n == 1 )
            return (long long)((nums[0]+k) * cost[0]);

        // prefixSum_nums.resize(n+1);
        long long prefixSum_nums[1001];
        prefixSum_nums[0] = 0LL;
        // prefixSum_cost.resize(n+1);
        long long prefixSum_cost[1001];
        prefixSum_cost[0] = 0LL;
        for(int i = 1; i <= n; ++i) {
            prefixSum_nums[i] = prefixSum_nums[i-1] + (long long)nums[i-1];
            prefixSum_cost[i] = prefixSum_cost[i-1] + (long long)cost[i-1];
        }

        // memset(mem,-1,sizeof mem);
        // return rec(0, 1LL);

        long long dp[1001][1001];memset(dp,0,sizeof dp);
        // fill in last column
        for(int i = 2; i <= n; ++i) {
            long long nms = prefixSum_nums[n] + ((long long)k * (long long)i);
            long long cst = (long long)cost[n-1];
            long long t = nms * cst;
            dp[i][n-1] = t;
        }

        for(int j = n-2; j >= 0; --j) {
            long long i_min = j != 0 ? 2 : 1;
            for(long long i = j+1; i >= i_min; --i) {

                long long res = LLONG_MAX;

                int rem = n - j; // length
                for(int len = 1; len <= rem; ++len) {
                    long long nms = prefixSum_nums[j+len] + ((long long)k * (long long)i);
                    long long cst = prefixSum_cost[j+len] - prefixSum_cost[j];
                    long long t = nms * cst;

                    res = min(res, t + dp[i+1][j+len]);
                }
                dp[i][j] = res;
            }
        }

        return dp[1][0];
    }
};




// TOP DOWN DP
// passes 736/759 test cases as of 4/9/2025, then TLE
// case 737 runs in about ~1500ms with correct result, but obviously to slow

class Solution {
private:
    vector<long long> prefixSum_nums;
    vector<long long> prefixSum_cost;
    int n;
    long long k;

    long long mem[1000][1001];

    long long rec(int pos, int i) {
        if( pos == n )
            return 0LL;

        int rem = n - pos;

        if( mem[pos][i] != -1LL )
            return mem[pos][i];

        long long ret = LLONG_MAX;

        // we have a choice
        //    use a subarray starting at pos of length 1..rem

        for(int len = 1; len <= rem; ++len) {
            long long nms = (prefixSum_nums[pos+len] + (k * (long long)i));
            long long cst = prefixSum_cost[pos+len] - prefixSum_cost[pos];
            long long t = nms * cst;

            ret = min(ret, t + rec(pos+len, i+1));
        }

        return mem[pos][i] = ret;
    }


public:
    long long minimumCost(vector<int>& nums, vector<int>& cost, int k) {
        n = nums.size(); // cost.length == nums.length
        this->k = (long long)k;

        prefixSum_nums.resize(n+1);
        prefixSum_nums[0] = 0LL;
        prefixSum_cost.resize(n+1);
        prefixSum_cost[0] = 0LL;
        for(int i = 1; i <= n; ++i) {
            prefixSum_nums[i] = prefixSum_nums[i-1] + (long long)nums[i-1];
            prefixSum_cost[i] = prefixSum_cost[i-1] + (long long)cost[i-1];
        }

        memset(mem,-1,sizeof mem);
        return rec(0, 1LL);
    }
};
