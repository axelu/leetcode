
// 1442. Count Triplets That Can Form Two Arrays of Equal XOR
// https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/





class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int n = arr.size();
        if( n == 1 ) return 0;

        int i,j;


        // prefix xor
        int pxor[n+1];
        pxor[0] = 0;
        for(i = 0; i < n; ++i)
            pxor[i+1] = arr[i] ^ pxor[i];


        int ans = 0;
        for(i = 0; i < n-1; ++i) {
            for(j = i+1; j < n; ++j) {
                if( pxor[j+1] - pxor[i] == 0 )
                    ans += j-i;
            }
        }

        return ans;
    }
};
