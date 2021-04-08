
// 985. Sum of Even Numbers After Queries
// https://leetcode.com/problems/sum-of-even-numbers-after-queries/


class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries) {
        int evenSum = 0;
        for(int i = 0; i < A.size(); ++i)
            if( A[i] % 2 == 0 ) evenSum += A[i];

        size_t n = queries.size();
        vector<int> ans(n);
        bool evenBefore,evenAfter;
        int idx,old;
        for(int i = 0; i < n; ++i) {
            idx = queries[i][1];

            // before | after | action
            // -------+-------+----------------------------
            // even   | even  | add (new value - old value)
            // odd    | even  | add new value
            // odd    | odd   | no change
            // even   | odd   | subtract old value

            old = A[idx];
            evenBefore = A[idx] % 2 == 0 ? true : false;
            A[idx] += queries[i][0];
            evenAfter = A[idx] % 2 == 0 ? true : false;

            if(  evenBefore &&  evenAfter ) evenSum += A[idx]-old;
            if( !evenBefore &&  evenAfter ) evenSum += A[idx];
            if(  evenBefore && !evenAfter ) evenSum -= old;
            ans[i] = evenSum;
        }

        return ans;
    }
};
