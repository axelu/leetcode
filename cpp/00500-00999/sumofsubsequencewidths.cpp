
// 891. Sum of Subsequence Widths
// https://leetcode.com/problems/sum-of-subsequence-widths/



class Solution {
private:
    size_t N;
    int MOD = 1000000007;
    long ans;
    long twoe[20000];

    void sumSubseqWidths2(int arr[], int index) {
        if(index == N-1 ) return;

        sumSubseqWidths2(arr,index+1);

        long l = arr[index], w;
        int e = 0;
        for(int i = index+1; i < N; ++i) {
            w = arr[i]-l;
            ans = (ans + (w*twoe[e])) % MOD;
            ++e;
        }
    }

public:
    int sumSubseqWidths(vector<int>& A) {
        N = A.size();
        if( N == 1 ) return 0;

        twoe[0] = 1;
        for(int i = 1; i < N; ++i)
            twoe[i] = ( twoe[i-1] *2 ) % MOD;

        sort(begin(A),end(A));
        ans = 0;
        // sumSubseqWidths2(A.data(),0); // TLE case 58/64

        // from the solution
        for(int i = 0; i < N; ++i)
            ans = (ans + (twoe[i] - twoe[N-1-i]) * A[i]) % MOD;

        return ans;
    }
};
