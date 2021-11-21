
// 363. Max Sum of Rectangle No Larger Than K
// https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/
// day 3 July 2021 challenge
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/608/week-1-july-1st-july-7th/3801/





class Solution {
private:

    // maximum subarray no larger than k
    int maxSumSubarrayNoLargerThanK(vector<int>& v, int k) {
        int n = v.size();

        // prefix sum's sorted
        set<int> prefixSums;
        prefixSums.insert(0);

        int ret = INT_MIN;

        int runningSum = 0;
        set<int>::iterator f;
        for(int i = 0; i < n; ++i) {
            runningSum += v[i];

            int x = runningSum - k;

            f = prefixSums.lower_bound(x);
            if( f != prefixSums.end() )
                ret = max(ret,runningSum-*f);

            prefixSums.insert(runningSum);
        }

        return ret;
    }


public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();      // rows
        int n = matrix[0].size();   // cols

        // Note: it is garuanteed that there is an answer
        int ans = INT_MIN;


        // idea: reduce the problem to a 1D array
        //       maximum subarray no larger than k


        vector<int> v(n);
        for(int i = 0; i < m; ++i) {        // start row
            // reset
            fill(v.begin(),v.end(),0);

            for(int j = i; j < m; ++j) {    // end row

                for(int c = 0; c < n; ++c)  // col
                    v[c] += matrix[j][c];

                int t = maxSumSubarrayNoLargerThanK(v,k);

                ans = max(ans,t);

                // the possible max ans is k
                if( ans == k )
                    return k;
            }
        }

        return ans;
    }
};
