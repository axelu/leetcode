
// 961. N-Repeated Element in Size 2N Array
// https://leetcode.com/problems/n-repeated-element-in-size-2n-array/



class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        int n = A.size();
        int t = n/2; // A.length is even
        int cnt[10000]; memset(cnt,0,sizeof cnt); // 0 <= A[i] < 10000
        for(int i = 0; i < n; ++i) {
            ++cnt[A[i]];
            if( cnt[A[i]] == t ) return A[i];
        }
        return -1;
    }
};
