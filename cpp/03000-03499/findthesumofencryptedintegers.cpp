
// 3079. Find the Sum of Encrypted Integers
// https://leetcode.com/problems/find-the-sum-of-encrypted-integers/




class Solution {
private:
    int encrypt(int x) {
        if( x < 10 )
            return x;

        int mx = 0;
        int cnt = 0;
        while( x ) {
            mx = max(mx, x % 10);
            ++cnt;
            x /= 10;
        }

        int ret = 0;
        while( cnt ) {
            ret = 10 * ret + mx;
            --cnt;
        }

        return ret;
    }

public:
    int sumOfEncryptedInt(vector<int>& nums) {
        int sum = 0;
        for(int x: nums)
            sum += encrypt(x);

        return sum;
    }
};
