
// 201. Bitwise AND of Numbers Range
// https://leetcode.com/problems/bitwise-and-of-numbers-range/





class Solution {
private:
    void printBinary(int x) {
        for(int i = 31; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

    int msbPos(int x) {
        // return position of most significant bit
        int msb = -1;
        while(x) {
            x = x >> 1;
            ++msb;
        }
        return msb;
    }

public:
    int rangeBitwiseAnd(int left, int right) {
        // 0 <= left <= right <= 2^31 - 1
        if( left == right )
            return left;

        int ans = 0;

        int msbLeft,msbRight,t;
        while(left && right) {
            // get positions of most significant bit
            msbLeft  = msbPos(left);
            msbRight = msbPos(right);

            if( msbLeft != msbRight )
                break;

            // msbLeft == msbRight
            t = (1 << msbLeft); // same as pow(2,msbLeft);

            // add 2^msb to result
            ans += t;

            // subtract 2^msb from left and right
            left  -= t;
            right -= t;
        }

        return ans;
    }
};
