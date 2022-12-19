
// 1537. Get the Maximum Score
// https://leetcode.com/problems/get-the-maximum-score/




class Solution {
private:
    int n1,n2;
    unordered_map<int,int> um1, um2;
    int * _nums1;
    int * _nums2;

    long mem[2][2][100000];

    long rec(int src, int k, int i) {
        // k = 0 => i is idx in nums1, k = 1 => is in idx in nums2
        if( k == 0 && i == n1 )
            return 0;
        if( k == 1 && i == n2 )
            return 0;

        if( mem[src][k][i] != -1 )
            return mem[src][k][i];

        // at each index we have a choice
        //    continue in the current array
        //    switch arrays if same value exists

        long ret = k == 0 ? _nums1[i] : _nums2[i];
        ret += rec(k,k,i+1);

        if( k == 0 && src == 0 ) {
            // try jumping to nums2
            auto f = um2.find(_nums1[i]);
            if( f != um2.end() )
                ret = max(ret, rec(0,1,f->second));
        }
        if( k == 1 && src == 1 ) {
            // try jumping to nums1
            auto f = um1.find(_nums2[i]);
            if( f != um1.end() )
                ret = max(ret, rec(1,0,f->second));
        }

        return mem[src][k][i] = ret;
    }

public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        n1 = nums1.size();
        n2 = nums2.size();

        for(int i = 0; i < n1; ++i)
            um1.insert({nums1[i],i});
        for(int i = 0; i < n2; ++i)
            um2.insert({nums2[i],i});

        _nums1 = nums1.data();
        _nums2 = nums2.data();

        memset(mem,-1,sizeof mem);
        return max(rec(0,0,0),rec(1,1,0)) % 1000000007;
    }
};
