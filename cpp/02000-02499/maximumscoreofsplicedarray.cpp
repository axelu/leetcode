
// 2321. Maximum Score Of Spliced Array
// https://leetcode.com/problems/maximum-score-of-spliced-array/




class Solution {
private:
    int mem[100000][2];

    int rec(vector<int>& nums1, vector<int>& nums2, int n, int pos, int swap, int prefixSum[]) {

        // cout << "rec pos " << pos << " swap " << swap << endl;

        // swap 0 we have not swap'd, 1 we are in a swap

        if( pos == n )
            return 0;

        if( mem[pos][swap] != -1 )
            return mem[pos][swap];

        // at each pos we have a choice
        //     continue w/o a swap (same as ending an ongoing swap)
        //     start a swap if we didn't have one so far
        //     continue an ongoing swap
        //     end an ongoing swap

        if( swap == 0 ) {

            // don't swap the current element
            int a = nums1[pos] + rec(nums1,nums2,n,pos+1,0,prefixSum);

            // start a swap at the current element
            int b = nums2[pos] + rec(nums1,nums2,n,pos+1,1,prefixSum);

            /* cout << "    rec pos " << pos << " swap " << swap << endl;
            cout << "    don't swap " << a << endl;
            cout << "    start swap " << b << endl;*/
            return mem[pos][swap] = max(a,b);

        } else {

            // end the ongoing swap at the current element
            int c = prefixSum[n] - prefixSum[pos];

            // continue the onging swap at the current element
            auto d = nums2[pos] + rec(nums1,nums2,n,pos+1,1,prefixSum);

            /*cout << "    rec pos " << pos << " swap " << swap << endl;
            cout << "    end swap  " << c << endl;
            cout << "    cont swap " << d << endl;*/
            return mem[pos][swap] = max(c,d);
        }
    }

public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); // nums1.length == nums2.length

        int prefixSum1[n+1];prefixSum1[0] = 0;
        int prefixSum2[n+1];prefixSum2[0] = 0;
        for(int i = 1; i <= n; ++i) {
            prefixSum1[i] = prefixSum1[i-1] + nums1[i-1];
            prefixSum2[i] = prefixSum2[i-1] + nums2[i-1];
        }

        memset(mem,-1,sizeof mem);
        int a = rec(nums1,nums2,n,0,0,prefixSum1);
        memset(mem,-1,sizeof mem);
        int b = rec(nums2,nums1,n,0,0,prefixSum2);

        return max(a,b);
    }
};
