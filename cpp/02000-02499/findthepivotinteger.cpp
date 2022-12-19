
// 2485. Find the Pivot Integer
// https://leetcode.com/problems/find-the-pivot-integer/



class Solution {
public:
    int pivotInteger(int n) {
        int prefixSum[1002];memset(prefixSum,0,sizeof prefixSum);

        prefixSum[0] = 0;
        for(int i = 1; i <= n+1; ++i)
            prefixSum[i] = prefixSum[i-1] + (i-1);

        /*
        for(int i = 0; i <= n+1; ++i)
            cout << i << ":" << prefixSum[i] << " ";
        cout << endl;
        */

        for(int i = 1; i <= n+1; ++i)
            if( prefixSum[i] == prefixSum[n+1]-prefixSum[i-1] )
                return i-1;

        return -1;
    }
};
