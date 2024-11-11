
// 3218. Minimum Cost for Cutting Cake I
// https://leetcode.com/problems/minimum-cost-for-cutting-cake-i/





class Solution {
private:
    int mem[20][20][20][20];

    int rec(int t, int b, int l, int r, vector<int>& horizontalCut, vector<int>& verticalCut) {
        if( b - t == 0 && r - l == 0 )
            return 0;

        if( mem[t][b][l][r] != -1 )
            return mem[t][b][l][r];

        int ret = INT_MAX;

        if( b - t != 0 ) {
            for(int i = t; i < b; ++i) {
                ret = min(ret, horizontalCut[i] + rec(t, i, l, r, horizontalCut, verticalCut) + rec(i+1, b, l, r, horizontalCut, verticalCut));
            }
        }

        if( r - l != 0 ) {
            for(int i = l; i < r; ++i) {
                ret = min(ret, verticalCut[i] + rec(t, b, l, i, horizontalCut, verticalCut) + rec(t, b, i+1, r, horizontalCut, verticalCut));
            }
        }

        return mem[t][b][l][r] = ret;
    }
public:
    int minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {

        memset(mem,-1,sizeof mem);
        return rec(0, m-1, 0, n-1, horizontalCut, verticalCut);
    }
};
