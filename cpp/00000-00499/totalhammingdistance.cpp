
// 477. Total Hamming Distance
// https://leetcode.com/problems/total-hamming-distance/





class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

public:
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 10^4
        if( n == 1 )
            return 0;

        int ans = 0;

        /*
        // brute force
        for(int i = 0; i < n-1; ++i) {
            for(int j = i+1; j < n; ++j) {
                int t = nums[i] ^ nums[j];
                ans += countSetBits(t);
            }
        }
        */

        // idea
        //   count how many times a given bit is set
        //   with that we can calculate the number of pairs where that bit is different

        int t[31];memset(t,0,sizeof t);
        for(int i = 0; i < n; ++i)
            for(int k = 0; k < 31; ++k)
                if( (nums[i] >> k) & 1 )
                    ++t[k];

         for(int i = 0; i < 31; ++i) {
             int bits_1 = t[i];         // number elements where the ith bit is set
             int bits_0 = n - bits_1;   // number elements where the ith bit is unset
             ans += bits_0 * bits_1;
         }

        return ans;
    }
};
