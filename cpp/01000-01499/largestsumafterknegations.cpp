
// 1005. Maximize Sum Of Array After K Negations
// https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/


class Solution {
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        size_t n = A.size();
        if( 0 == K )
            return accumulate(begin(A),end(A),0);

        int odd = K % 2;
        if( 1 == n )
            return odd ? -A[0] : A[0];

        sort(begin(A),end(A));

        if( 0 == A[0] )
            return accumulate(begin(A),end(A),0);

        if( 0 < A[0] ) {
            // A does NOT contain any elements less than 0
            // if K is odd, we flip the smallest
            if( odd ) A[0] = -A[0];
            return accumulate(begin(A),end(A),0);
        }

        // if A[i] < 0, flip all those starting with the smallest one
        // if we don't have K left after that, then we are done
        // if we still have K left and we have an A[i] == 0, we are done
        // if we still have K left and we don't have an A[i] == 0:
        //     if K left is even, we are done
        //     if K left is odd, flip the absolut smaller one of A[i] > 0 or A[i] < 0

        int ans = 0;
        for(int i = 0; i < n; ++i) {

            if( 0 < K ) {
                if( 0 > A[i] ) {
                    ans += -A[i];
                    --K;
                } else if( 0 == A[i] ) {
                    K = 0;
                } else {
                    // 0 < A[i]
                    odd = K % 2;
                    if( odd ) {
                        // we already added the last value < 0
                        if( abs(A[i]) >= abs(A[i-1]) ) {
                            ans += 2 * A[i-1];
                            ans += A[i];
                        } else {
                            ans -= A[i];
                        }
                    } else {
                        ans += A[i];
                    }
                    K = 0;
                }
                continue;
            }
            ans += A[i];
        }

        if( 0 < K ) {
            // A only contains 0 > A[i] and K > n
            odd = K % 2;
            if( odd ) {
                ans += -2 * A.back();
            }
        }

        return ans;
    }
};
