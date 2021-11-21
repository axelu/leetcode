
// 1228. Missing Number In Arithmetic Progression
// https://leetcode.com/problems/missing-number-in-arithmetic-progression/


class Solution {
public:
    int missingNumber(vector<int>& arr) {
        int n = arr.size();
        if( n == 3 ) {
            int d1 = arr[1]-arr[0];
            int d2 = arr[2]-arr[1];
            if( d1 == 2*d2 ) return arr[0]+d2;
            else return arr[1]+d1;
        }

        int d1 = arr[1]-arr[0];
        int d2 = arr[n-1]-arr[n-2];
        int d = d1 == 2*d2 ? d2 : d1;
        int t;
        for(int i = 1; i < n; ++i) {
            t = arr[i] - arr[i-1];
            if( t != d ) return arr[i-1]+d;
        }

        return 0;
    }
};
