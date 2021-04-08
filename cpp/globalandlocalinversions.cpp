
// 775. Global and Local Inversions
// https://leetcode.com/problems/global-and-local-inversions/
// day 5 April 2021 challenge
// https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/593/week-1-april-1st-april-7th/3697/




class Solution {
public:
    bool isIdealPermutation(vector<int>& A) {
        int n = A.size(); // 0 <= A[i] <= n-1
        if( n == 1 ) return true;

        // local inversions is the number of i with 0 <= i < N and A[i] > A[i+1]
        // global inversions is the number of i < j with 0 <= i < j < N and A[i] > A[j]
        // example [3,2,1]
        // this would result in 2 local inversions (i = 0, i = 1) and
        // 3 global inversions:
        // i  j  A[i]  A[j]
        // 0  1  3     2     1
        // 0  2  3     1     1
        // 1  2  2     1     1
        // to get an ideal permutation, either the numbers are increasing, or only
        // two neighboring numbers are swaped compared to a strictly increasing sequence

        for(int i = 0; i < n; ++i) {
            if( A[i] == i ) continue;
            if( A[i] < i-1 || A[i] > i+1 ) return false;
        }
        return true;
    }
};
