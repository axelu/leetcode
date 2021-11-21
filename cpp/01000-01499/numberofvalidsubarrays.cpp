
// 1063. Number of Valid Subarrays
// https://leetcode.com/problems/number-of-valid-subarrays/




// range minimum query (RMQ) sparse table
// https://www.geeksforgeeks.org/range-minimum-query-for-static-array/
// https://cp-algorithms.com/data_structures/sparse-table.html

class Solution {
private:
    // K ≥ base 2 log MAXN
    // base 2 logarithm of 50000 is 15.609640474
    int K = 25;
    int * log;
    int (*st)[26]; // int st[50000][K + 1];

    int getMin(int L, int R) {
        int j = log[R - L + 1];
        return min(st[L][j], st[R - (1 << j) + 1][j]);
    }

    // binary search
    int search(int s, int e, int start, int target) {
        // returns the right most index i
        // with s <= i <= e in which target is the minimum

        if( s > e ) return -1;

        int mid = s + ((e-s)/2);
        if( getMin(start,mid) == target ) {
            // can we do better?
            int t = search(mid+1,e,start,target);
            return t != -1 ? t : mid;
        } else {
            return search(s,mid-1,start,target);
        }
    }

public:
    int validSubarrays(vector<int>& arr) {
        int N = arr.size();
        int i,j;

        // precomputing all logarithms
        int Log[N+1];
        log = Log;
        log[1] = 0;
        for(i = 2; i <= N; ++i)
            log[i] = log[i/2] + 1;

        // precompute the Sparse Table structure
        int St[N][26];
        st = St;
        for(i = 0; i < N; i++)
            st[i][0] = arr[i];
        for(j = 1; j <= K; ++j)
            for(i = 0; i + (1 << j) <= N; ++i)
                st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);


        int ans = 0,t;
        for(i = 0; i < N; ++i) {
            t = search(i,N-1,i,arr[i]);
            ans += t-i+1;
        }

        return ans;
    }
};
