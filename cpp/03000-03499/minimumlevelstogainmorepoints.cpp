
// 3096. Minimum Levels to Gain More Points
// https://leetcode.com/problems/minimum-levels-to-gain-more-points/




class Solution {
public:
    int minimumLevels(vector<int>& possible) {
        int n = possible.size();

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i) {
            int d = possible[i-1] == 1 ? 1 : -1;
            prefixSum[i] = prefixSum[i-1] + d;
        }

        for(int i = 1; i < n; ++i) {
            if( prefixSum[i] > prefixSum[n] - prefixSum[i] )
                return i;
        }

        return -1;
    }
};
