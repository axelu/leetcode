
// 1130. Minimum Cost Tree From Leaf Values
// https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/





class Solution {
private:
    // range maximum query using sparce table
    // K ≥ base 2 log MAXN
    // base 2 logarithm of 40 is 5.3219280949
    int K = 6;
    int * log;
    int (*st)[26]; // int st[50000][K + 1];

    int getMax(int L, int R) {
        int j = log[R - L + 1];
        return max(st[L][j], st[R - (1 << j) + 1][j]);
    }

    int mem[41][41];

    // dynamic programming top down
    int dp(int i, int j, vector<int>& arr) {
        // from the question:
        // for each possible way to partition the subarray i <= k < j,
        // the answer is max(arr[i]..arr[k]) * max(arr[k+1]..arr[j]) + dp(i, k) + dp(k+1, j).
        if( i == j ) return 0; // current node is a leave
        if( j - i == 1 ) return arr[i] * arr[j];
        if( mem[i][j] != -1 ) return mem[i][j];

        int mn = INT_MAX;
        for(int k = i; k < j; ++k) {
            // basically the value of the current node is the product of the max leaf in its left subtree getMax(i,k)
            // and the max leaf in its right subtree getMax(k+1,j)
            // and as we are looking for the min sum of each leaf node, we will need to add the minimum sum
            // of its left subtree dp(i,k,arr) and its right subtree dp(k+1,j,arr) non-leave nodes
            mn = min(mn,(getMax(i,k) * getMax(k+1,j)) + dp(i,k,arr) + dp(k+1,j,arr));
        }
        return mem[i][j] = mn;
    }


public:
    int mctFromLeafValues(vector<int>& arr) {
        // 2 <= arr.length <= 40
        // 1 <= arr[i] <= 15
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
                st[i][j] = max(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);


        memset(mem,-1,sizeof mem);
        return dp(0,N-1,arr);
    }
};
