
// 2379. Minimum Recolors to Get K Consecutive Black Blocks
// https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/


class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int n = blocks.size();

        // we are looking for the sliding window of size k with minumum number of white blocks

        int ans = k;
        int w = 0;
        for(int i = 0; i < n; ++i) {
            if( blocks[i] == 'W' )
                ++w;
            if( i >= k-1 ) {
                ans = min(ans,w);
                if( blocks[i-(k-1)] == 'W' )
                    --w;
            }
        }

        return ans;
    }
};
