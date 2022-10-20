
// 2106. Maximum Fruits Harvested After at Most K Steps
// https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/



class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();

        int prefixSum[200002];memset(prefixSum,0,sizeof prefixSum);
        prefixSum[0] = 0;

        int f = 0; // fruit index
        for(int i = 1; i <= 200001; ++i) {
            int t = 0;
            if( f < n && fruits[f][0] == i-1 )
                t = fruits[f++][1];
            prefixSum[i] = prefixSum[i-1] + t;
        }

        // we always harvest the fruit at the starting position if any
        // edgecases
        // k == 0
        // startPos = 0      -> go right k
        // startPos = 200000 -> go left k
        // k == 1, k == 2
        // k so large that we cover the entire array fruits
        // startPos - k = -1, startPos + k  = 200001
        // other considerations
        // startPos <= min position
        // startPos >= max position

        if( k == 0 )
            return prefixSum[startPos+1] - prefixSum[startPos];

        if( startPos == 0 )
            return prefixSum[k+1];

        if( startPos == 200000 )
            return prefixSum[200001] - prefixSum[200000-k];

        if( k == 1 ) {
            int l = prefixSum[startPos+1] - prefixSum[startPos-1];
            int r = prefixSum[startPos+2] - prefixSum[startPos];
            return max(l,r);
        }

        if( k == 2 ) {
            int l = prefixSum[startPos+1] - prefixSum[max(0,startPos-2)];
            int r = prefixSum[min(startPos+3,200001)] - prefixSum[startPos];
            return max(l,r);
        }

        // we will extend max to the left to get started
        // we always want to go the shorter distance twice

        int ans = 0;

        for(int j = startPos; j <= min(startPos+k,200000); ++j) { // right index
            // calculate the left index i
            int rd = j - startPos;          // right distance
            int ld = max(k-(rd*2),(k-rd)/2);// left distance
            int i = max(0,startPos - ld);

            ans = max(ans,prefixSum[j+1]-prefixSum[i]);
        }

        return ans;
    }
};
