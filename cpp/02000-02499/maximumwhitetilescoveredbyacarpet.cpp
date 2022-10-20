
// 2271. Maximum White Tiles Covered by a Carpet
// https://leetcode.com/problems/maximum-white-tiles-covered-by-a-carpet/




class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        int n = tiles.size();

        // tiles are non-overlapping
        sort(tiles.begin(),tiles.end());

        multimap<int,pair<char,int>> mp;

        int prefixSum[n+1];memset(prefixSum,0,sizeof prefixSum);
        prefixSum[0] = 0;
        int max_consecutive_tiles = 0;
        for(int i = 0; i < n; ++i) {
            prefixSum[i+1] = prefixSum[i] + (tiles[i][1]-tiles[i][0]+1);
            max_consecutive_tiles = max(max_consecutive_tiles,tiles[i][1]-tiles[i][0]+1);
            mp.insert({tiles[i][0],{'s',i}});
            mp.insert({tiles[i][1],{'e',i}});
        }

        // edge cases
        if( carpetLen >= tiles.back()[1] - tiles[0][0] + 1 )
            return prefixSum[n];
        if( carpetLen <= max_consecutive_tiles )
            return carpetLen;

        // optimal position is to place carpet at the beginning
        // of a white tile segment

        int ans = 0;
        for(int i = 0; i < n; ++i) {
            // the carpet will start at tiles[i][0]
            int carpetEnd = tiles[i][0] + carpetLen - 1;

            // find which while tile segments our carpet covers
            auto lb = mp.lower_bound(carpetEnd);

            if( lb == mp.end() )
                return max(ans,prefixSum[n]-prefixSum[i]);

            if( lb->second.first == 's' ) {
                if( lb->first == carpetEnd )
                    ans = max(ans,prefixSum[lb->second.second] - prefixSum[i] + 1);
                else
                    ans = max(ans,prefixSum[lb->second.second] - prefixSum[i]);
            } else {
                if( lb->first == carpetEnd )
                    ans = max(ans,prefixSum[lb->second.second + 1] - prefixSum[i]);
                else
                    ans = max(ans,prefixSum[lb->second.second] - prefixSum[i] +
                                  (carpetEnd - prev(lb)->first + 1));
            }
        }

        return ans;
    }
};
