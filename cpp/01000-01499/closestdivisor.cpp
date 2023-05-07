
// 1362. Closest Divisors
// https://leetcode.com/problems/closest-divisors/



class Solution {
public:
    vector<int> closestDivisors(int num) {
        vector<int> ans(2);

        int mn = INT_MAX;
        for(int k = 1; k <= 2; ++k) {
            int a = num + k;
            for(int i = 1; i * i <= a; ++i) {

                if( a % i == 0 ) {
                    // we have a candidate pair
                    int k = a / i;
                    int d = abs(i-k);
                    if( d < mn ) {
                        ans[0] = i;
                        ans[1] = k;
                        mn = d;
                    }
                }
            }
        }

        return ans;
    }
};
