
// 338. Counting Bits
// https://leetcode.com/problems/counting-bits/


// https://www.geeksforgeeks.org/count-set-bits-in-an-integer/
class Solution {
private:
    int num_to_bits[16] = { 0, 1, 1, 2, 1, 2, 2, 3,
                            1, 2, 2, 3, 2, 3, 3, 4 };
    int * R;

    int countSetBitsRec(unsigned int num) {
        if( 0 == num ) return 0;
        if( R[num] ) return R[num];

        // Find last nibble
        int nibble = 0;
        nibble = num & 0xf;

        // Use pre-stored values to find count
        // in last nibble plus recursively add
        // remaining nibbles.
        return num_to_bits[nibble] + countSetBitsRec(num >> 4);
    }
public:
    vector<int> countBits(int num) {
        if( num == 0 ) return {0};
        vector<int> r(num+1,0);
        R = r.data();

        for(int i = 1; i <= num; ++i)
            r[i] = countSetBitsRec(i);

        return r;
    }
};


