
// 2600. K Items With the Maximum Sum
// https://leetcode.com/problems/k-items-with-the-maximum-sum/





class Solution {
public:
    int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {
        int ans = 0;

        if( numOnes >= k ) {
            return k;
        } else {
            k -= numOnes;
            ans += numOnes;
        }

        if( numZeros >= k ) {
            return ans;
        } else {
            k -= numZeros;
        }

        ans -= k;;

        return ans;
    }
};
