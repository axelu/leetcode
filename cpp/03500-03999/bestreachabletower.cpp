
// 3809. Best Reachable Tower
// https://leetcode.com/problems/best-reachable-tower/



class Solution {
public:
    vector<int> bestTower(vector<vector<int>>& towers, vector<int>& center, int radius) {
        int xc = center[0];
        int yc = center[1];

        vector<int> best_tower{-1,-1};
        int best_quality = -1;

        for(auto& tower: towers) {
            int xt = tower[0];
            int yt = tower[1];
            int manhattan = abs(xc-xt) + abs(yc-yt);
            if( manhattan <= radius ) {
                int quality = tower[2];
                if( quality > best_quality ) {
                    best_quality = quality;
                    best_tower = {xt,yt};
                } else if( quality == best_quality ) {
                    if( xt < best_tower[0] ) {
                        best_tower = {xt,yt};
                    } else if( xt == best_tower[0] ) {
                        if( yt < best_tower[1] )
                            best_tower[1] = yt;
                    }
                }
            }
        }

        return best_tower;
    }
};
