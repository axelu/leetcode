
// 2554. Maximum Number of Integers to Choose From a Range I
// https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/


class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
        sort(banned.begin(),banned.end());

        // greedily pick every none banned number from smallest to largest

        int ans = 0;
        int sum = 0;

        for(int i = 0; i < banned.size() && sum < maxSum; ++i) {

            int t = i == 0 ? 1 : banned[i-1]+1;

            while( t < banned[i] && t <= n ) {
                sum += t;
                if( sum <= maxSum ) {
                    ++ans;
                    ++t;
                } else {
                    break;
                }
            }
            if( t > n )
                break;
        }
        for(int t = banned.back()+1; t <= n && sum < maxSum; ++t) {
            sum += t;
            if( sum <= maxSum)
                ++ans;
        }

        return ans;
    }
};
