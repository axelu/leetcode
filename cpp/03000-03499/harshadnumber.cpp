
// 3099. Harshad Number
// https://leetcode.com/problems/harshad-number/




class Solution {
public:
    int sumOfTheDigitsOfHarshadNumber(int x) {

        int i = x;
        int sum = 0;
        while( i ) {
            int rem = i % 10;
            sum += rem;
            i /= 10;
        }

        return x % sum == 0 ? sum : -1;
    }
};
