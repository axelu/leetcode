
// 801. Minimum Swaps To Make Sequences Increasing
// https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/



class Solution {
private:
    int n;
    int * _nums1;
    int * _nums2;

    int mem[2][100000];

    int rec(bool swapped, int i) {
        if( i == n )
            return 0;

        if( mem[swapped][i] != -1 )
            return mem[swapped][i];

        int ret = 100001;

        if( i == 0 ) {
            // we can continue as is OR
            // we can continue swapping
            ret = min(rec(false,i+1), 1 + rec(true,i+1));

        } else {
            if( !swapped ) {
                // can we continue w/o swapping
                if( _nums1[i-1] < _nums1[i] && _nums2[i-1] < _nums2[i] )
                    ret = min(ret,rec(0,i+1));
                // can we continue w/ swapping
                if( _nums1[i-1] < _nums2[i] && _nums2[i-1] < _nums1[i] )
                    ret = min(ret, 1 + rec(1,i+1));
            } else {
                // can we continue w/o swapping
                if( _nums2[i-1] < _nums1[i] && _nums1[i-1] < _nums2[i] )
                    ret = min(ret,rec(0,i+1));
                // can we continue w/ swapping
                if( _nums2[i-1] < _nums2[i] && _nums1[i-1] < _nums1[i] )
                    ret = min(ret, 1 + rec(1,i+1));
            }
        }

        return mem[swapped][i] = ret;
    }


public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        n = nums1.size(); // nums1.size() == nums2.size()
        _nums1 = nums1.data();
        _nums2 = nums2.data();

        memset(mem,-1,sizeof mem);
        return rec(0,0); // same as rec(1,0)
    }
};
