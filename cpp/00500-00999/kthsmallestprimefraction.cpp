
// 786. K-th Smallest Prime Fraction
// https://leetcode.com/problems/k-th-smallest-prime-fraction/


// based on approach #1

class Solution {
private:
    vector<int> solve(vector<int>& arr, int n, double x) {
        // returns {count,numerator,denominator}
        int cnt = 0;
        int numer = 0, denom = 1;

        int i = -1;
        for(int j = 1; j < arr.size(); ++j) {
            // for each j, find the largest i so that arr[i]/arr[j] < x
            // it has to be at least as big as the previous i, so reuse it ("two pointer")
            while(arr[i+1] < arr[j] * x)
                ++i;

            // there are i+1 fractions: (arr[0],arr[j]),(arr[1],arr[j]), ..., (arr[i],arr[j])
            cnt += i+1;
            if( i >= 0 && numer * arr[j] < denom * arr[i] ) {
                numer = arr[i];
                denom = arr[j];
            }
        }
        return {cnt,numer,denom};
    }

public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        // numbers of arr are unique and sorted in strictly increasing order
        int n = arr.size();
        if( k == 1 )
            return {arr[0],arr[n-1]};

        vector<int> ans(2);

        double s = 0;
        double e = 1;
        while(e - s > 1e-9) {
            double mid = s + ((e-s)/2.0);
            vector<int> t = solve(arr,n,mid);
            if( t[0] < k ) {
                s = mid;
            } else {
                ans[0] = t[1];
                ans[1] = t[2];
                e = mid;
            }
        }

        return ans;
    }
};
