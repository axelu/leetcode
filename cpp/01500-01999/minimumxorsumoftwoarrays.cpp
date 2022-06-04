
// 1879. Minimum XOR Sum of Two Arrays
// https://leetcode.com/problems/minimum-xor-sum-of-two-arrays/



class Solution {
private:
    int mem[14][16383]; // position in nums1, mask of used positions in nums2

    int rec(vector<int>& nums1, vector<int>& nums2, int n, int pos1, int mask) {
        if( pos1 == n )
            return 0;

        if( mem[pos1][mask] != -1 )
            return mem[pos1][mask];

        // we can combine nums1[pos1] with any unused i from nums2
        int ret = INT_MAX;
        for(int i = 0; i < n; ++i) {
            if( !((mask >> i) & 1) ) {
                mask |= 1 << i;     // set ith bit
                int t = (nums1[pos1] ^ nums2[i]) + rec(nums1,nums2,n,pos1+1,mask);
                ret = min(ret,t);
                // backtrack
                mask &= ~(1 << i);  // clear ith bit
            }
        }

        return mem[pos1][mask] = ret;
    }

public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); // n == nums1.length == nums2.length

        memset(mem,-1,sizeof mem);
        return rec(nums1,nums2,n,0,0);
    }
};
