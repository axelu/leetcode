
// 3513. Number of Unique XOR Triplets I
// https://leetcode.com/problems/number-of-unique-xor-triplets-i/



class Solution {
private:
    void printBinary(int x) {
        for(int i = 16; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

    int findRightMostSetBit(unsigned int x) {
        // it is guaranteed that x > 0
        int ret = 0;
        x = x >> 1;
        while( x ) {
            ++ret;
            x = x >> 1;
        }
        return ret;
    }

public:
    int uniqueXorTriplets(vector<int>& nums) {
        // nums is a permutation of integers from 1 to n.
        // XOR triplet is defined as the XOR of three elements
        //    nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.
        // properties of XOR https://accu.org/journals/overload/20/109/lewin_1915/

        int n = nums.size();
        if( n == 1 )
            return 1;
        if( n == 2 )
            return 2;

        // for(int i = 1; i <= n; ++i)
        //    printBinary(i);

        int right_most_set_bit = findRightMostSetBit(n);
        return pow(2, right_most_set_bit + 1);

    }
};
