
// 3681. Maximum XOR of Subsequences
// https://leetcode.com/problems/maximum-xor-of-subsequences/



// based on hint:
//     linear XOR basis
// resources
// https://www.geeksforgeeks.org/dsa/xor-basis-algorithm/
// https://www.programmersought.com/article/36824220613/
//
//     KEY INSIGHT::
//     Each number in the linear basis is the result of the XOR of some numbers in the original set.
//
// https://usaco.guide/adv/xor-basis?lang=cpp
//     follow also link in this article to https://codeforces.com/blog/entry/68953 and
//         Problem 3 in that link is our problem !!!

class Solution {
private:
    // debug
    void printBinary(long x, int c) {
        for(int i = c; i >= 0; --i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    // linear XOR basis
    // get the basis vectors
    // NOTE: this implementation is for the 1st msb that is set !!!
    //       because we are after the max XOR out of a subsequence of elements of nums
    vector<int> get_basis_vectors(vector<int>& nums) {
        // dimension of vector, must be at least the
        // largest number of bits of any element in input vector nums
        // we could dynamically get that by going through nums
        // and get the largest index of the most significant set bit
        // of any element in nums and add 1 to that index
        // for our problem constraint we know max nums[i] is 1e9 which has 30 digits binary
        int d = 30;

        vector<int> basis(d, 0);

        int n = nums.size();
        for(int i = 0; i < n; ++i) {
            int x = nums[i];

            for(int j = d-1; j >= 0; --j) { // msb aka most significant set bit
            // for (int j = 0; j < d; ++j) {
                if( x & (1 << j) ) {
                    // if the current value of x
                    // has first set bit at i
                    if( basis[j] == 0 ) {
                        // if no basis vector exists
                        // with first set bit at j
                        basis[j] = x;
                        break;
                    }
                    // subtracting basis[j] from x
                    x ^= basis[j];
                }
            }
        }

        return basis;
    }


public:
    int maxXorSubsequences(vector<int>& nums) {
        // 2 <= nums.length <= 1e5
        // 0 <= nums[i] <= 1e9

        // worst case nums[i]
        // decimal 1e9 = 1000000000 -> binary 111011100110101100101000000000 (30 digits)

        // create linear xor basis from nums
        vector<int> basis = get_basis_vectors(nums);
        // debug
        /*
        for(int i = 0; i < basis.size(); ++i)
            cout << basis[i] << " ";
        cout << endl;
        */


        int ans = 0;

        /*
        // works also
        for(int i = basis.size()-1; i >= 0; --i)
            if( (ans ^ basis[i]) > ans )
                ans ^= basis[i];
        */

        for(int i = basis.size() - 1; i >= 0; --i) {
            if( !basis[i] )
                continue;

            if( ans & 1 << i )
                continue;

            ans ^= basis[i];
        }

        return ans;
    }
};
