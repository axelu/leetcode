
// 1458. Max Dot Product of Two Subsequences
// https://leetcode.com/problems/max-dot-product-of-two-subsequences/




class Solution {
private:
    int n1,n2;
    int * _nums1;
    int * _nums2;

    // int mem[500][500];
    int ** mem;

    int rec(int i, int j) {

        if( mem[i][j] != -1 )
            return mem[i][j];

        // we have choices

        int a = _nums1[i] * _nums2[j];
        int b = -1000000000;
        if( i < n1-1 && j < n2-1 )
            b = rec(i+1,j+1);
        int c = max({a,b,a+b});

        //for(int k = j+1; k < n2; ++k)
        //    c = max(c,rec(i,k));
        if( j+1 < n2 )
            c = max(c,rec(i,j+1));
        //for(int k = i+1; k < n1; ++k)
        //    c = max(c,rec(k,j));
        if( i+1 < n1 )
            c = max(c,rec(i+1,j));

        return mem[i][j] = c;
    }



public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        n1 = nums1.size();
        _nums1 = nums1.data();
        n2 = nums2.size();
        _nums2 = nums2.data();

        // memset(mem,-1,sizeof mem);
        mem = new int *[n1];
        for(int i = 0; i < n1; ++i) {
            mem[i] = new int[n2];
            for(int j = 0; j < n2; ++j)
                mem[i][j] = -1;
        }
        return rec(0,0);
    }
};
