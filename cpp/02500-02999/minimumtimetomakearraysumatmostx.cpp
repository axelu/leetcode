
// 2809. Minimum Time to Make Array Sum At Most x
// https://leetcode.com/problems/minimum-time-to-make-array-sum-at-most-x/




class Solution {
private:
    int mem[1001][1001];

    int rec(const vector<vector<int>>& nums1nums2, const int n, const int pos, const int remainingOperations) {
        // cout << "rec pos " << pos << " remainingOperations " << remainingOperations << endl;

        int remainingPositions  = n - pos;              // including the current position

        if( remainingOperations == 0 || remainingPositions < remainingOperations )
            return 0;

        if( mem[pos][remainingOperations] != -1 )
            return mem[pos][remainingOperations];

        // we have a choice
        //    apply the operation OR
        //    don't apply the operation

        // reduction if we apply the operation at this time
        int reduction = nums1nums2[pos][0];     // intial value nums1[pos]
        reduction += nums1nums2[pos][1] * (remainingOperations); // number of times nums2[pos] was added

        int ret = reduction + rec(nums1nums2,n,pos+1,remainingOperations-1);

        ret = max(ret, rec(nums1nums2,n,pos+1,remainingOperations));

        return mem[pos][remainingOperations] = ret;
    }

public:
    int minimumTime(vector<int>& nums1, vector<int>& nums2, int x) {
        int n = nums1.size(); // nums1.length == nums2.length

        int sumNums1 = accumulate(nums1.begin(),nums1.end(),0);
        if( sumNums1 <=  x )
            return 0;

        int sumNums2 = accumulate(nums2.begin(),nums2.end(),0);

        vector<vector<int>> nums1nums2(n,vector<int>(2));
        for(int i = 0; i < n; ++i)
            nums1nums2[i] = {nums1[i],nums2[i]};
        sort(nums1nums2.begin(),nums1nums2.end(),[](const vector<int>& a, const vector<int>& b){
            // return a[1] < b[1]; // for solution based on hints
            return a[1] > b[1];
        });

        // assumption: we have to set a given nums1[i] to 0 only once
        // as time goes by, we would want to nix larger increases later.
        // so we can sort by nums2 ascending
        // issue though is, that nums1 has initial values
        // so we need to figure out the largest reduction we can achieve
        // by applying the operation to nums1[i] elements after we sorted
        // them alongside nums2
        // it goes unspoken that we apply the operation every second,
        // the question is: to which elements we apply it

        memset(mem,-1,sizeof mem);
        for(int time = 1; time <= n; ++time) {
            int currentSum = sumNums1 + sumNums2 * time;
            int maxReduction = rec(nums1nums2,n,0,time);
            if( currentSum - maxReduction <= x )
                return time;
        }

        /*
        // based on hints in the problem description

        // let dp[i][j] represent the maximum total value that can be reduced if we do j operations on the first i elements.
        // dp[i][0] = 0 (for all i = 0, 1, ..., n)
        // dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + nums2[i - 1] * j + nums1[i - 1]) (for 1 <= i <= n and 1 <= j <= i).
        int dp[n+1][n+1];memset(dp,0,sizeof dp);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= i; ++j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + nums1nums2[i - 1][1] * j + nums1nums2[i - 1][0]);
            }
        }

        // we have an initial sum, which is sum of nums1
        // every second our sum increases by sum of nums2
        // were we able to achieve a reduction by a given second that gets our current sum - reduction <= x?

        for(int time = 1; time <= n; ++time) {
            int currentSum = sumNums1 + sumNums2 * time;
            int maxReduction = dp[n][time];
            if( currentSum - maxReduction <= x )
                return time;
        }
        */

        return -1;
    }
};
