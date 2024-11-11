
// 3344. Maximum Sized Array
// https://leetcode.com/problems/maximum-sized-array/





class Solution {
private:
    // brute force
    long long solve(int n) {
        long long sum_int = (n-1) * (n)/2;

        long long res = 0;

        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < n; ++k) {
                long long jork = j | k;
                // cout << "j " << j << " k " << k << " j or k " << jork << endl;

                res = res + (sum_int * jork);
            }
        }

        return res;
    }

    // binary search
    int search(int s, int e, long long target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        long long res = solve(mid);
        if( res <= target ) {
            // can we do better?
            int t = search(mid+1, e, target);
            return t != -1 ? t : mid;
        }

        return search(s, mid-1, target);
    }

public:
    int maxSizedArray(long long s) {
        if( s == 0 )
            return 1;

        // A[i][j][k] = i * (j OR k), where 0 <= i, j, k < n
        // we are asked to get n where the sum of all elements in A does not exceed s
        //     so i would go from 0..n-1
        //     let (j OR k) be b
        //     0 * b + 1 * b + 2 * b ... => (0+1+2+...) * b, so sum of integers up to (n-1) * b
        //     formula sum of integers up to and including n: n * (n+1)/2

        // max n 1196 found by trial

        return search(1,1196,s);
    }
};
