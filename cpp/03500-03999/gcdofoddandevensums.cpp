
// 3658. GCD of Odd and Even Sums
// https://leetcode.com/problems/gcd-of-odd-and-even-sums/






class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        long long sumOdd = 0LL;
        long long addend = 1LL;
        for(int i = 0; i < n; ++i) {
            sumOdd += addend;
            addend += 2LL;
        }

        long long sumEven = 0LL;
        addend = 2LL;
        for(int i = 0; i < n; ++i) {
            sumEven += addend;
            addend += 2LL;
        }

        return gcd(sumOdd, sumEven);
    }
};
