
// 2520. Count the Digits That Divide a Number
// https://leetcode.com/problems/count-the-digits-that-divide-a-number/



class Solution {
public:
    int countDigits(int num) {
        int ans = 0;

        int k = num;
        while( k > 0 ) {
            int rem = k % 10;
            if( num % rem == 0 )
                ++ans;
            k /= 10;
        }

        return ans;
    }
};
