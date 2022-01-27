
// 978. Longest Turbulent Subarray
// https://leetcode.com/problems/longest-turbulent-subarray/
// day 15 September 2021 challenge
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge-2021/638/week-3-september-15th-september-21st/3976/






class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int n = arr.size();
        if( n == 1 )
            return n;

        // n >= 2
        int ans = arr[0] == arr[1] ? 1 : 2;

        // n > 2
        int t = ans;
        for(int i = 2; i < n; ++i) {

            if( (arr[i] > arr[i-1] && arr[i-2] > arr[i-1]) ||
                (arr[i] < arr[i-1] && arr[i-2] < arr[i-1]) ) {

                ++t;
                ans = max(ans,t);

            } else {
                t = arr[i] == arr[i-1] ? 1 : 2;
            }
        }

        return ans;
    }
};
