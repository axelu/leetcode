
// 1551. Minimum Operations to Make Array Equal
// https://leetcode.com/problems/minimum-operations-to-make-array-equal/
// day 6 April 2021 challenge
// https://leetcode.com/explore/featured/card/april-leetcoding-challenge-2021/593/week-1-april-1st-april-7th/3698/




class Solution {
public:
    int minOperations(int n) {

        int arr[n];
        int sum = 0,i;
        for(i = 0; i < n; ++i) {
            arr[i] = (2*i)+1;
            sum += arr[i];
        }
        int target = sum/n;

        // debug
        /* for(i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << sum << endl;
        cout << target << endl; */

        int ans = 0;
        for(i = 0; i < n; ++i) {
            if( arr[i] < target ) ans += target - arr[i];
        }

        return ans;
    }
};
