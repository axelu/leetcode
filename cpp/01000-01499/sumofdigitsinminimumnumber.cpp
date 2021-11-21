
// 1085. Sum of Digits in the Minimum Number
// https://leetcode.com/problems/sum-of-digits-in-the-minimum-number/


class Solution {
public:
    int sumOfDigits(vector<int>& A) {
        // 1 <= A.length <= 100
        // 1 <= A[i] <= 100
        sort(A.begin(),A.end());
        int min = A[0];
        int t = 0;
        while( min > 0 ) {
            t += min % 10;
            min /= 10;
        }
        return t % 2 == 0;
    }
};
