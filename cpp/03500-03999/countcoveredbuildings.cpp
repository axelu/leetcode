
// 3531. Count Covered Buildings
// https://leetcode.com/problems/count-covered-buildings/




class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        pair<int,int> horizontal[100001]; // y -> min x, max x
        bool yseen[100001];memset(yseen,false,sizeof yseen);
        pair<int,int> vertical[100001];   // x -> min y, max y
        bool xseen[100001];memset(xseen,false,sizeof xseen);

        // pass 1
        for(auto& bldg: buildings) {
            int x = bldg[0];
            int y = bldg[1];

            if( !xseen[x] ) {
                vertical[x] = {y,y};
                xseen[x] = true;
            } else {
                vertical[x].first = min(vertical[x].first,y);
                vertical[x].second = max(vertical[x].second,y);
            }

            if( !yseen[y] ) {
                horizontal[y] = {x,x};
                yseen[y] = true;
            } else {
                horizontal[y].first = min(horizontal[y].first,x);
                horizontal[y].second = max(horizontal[y].second,x);
            }
        }

        int ans = 0;

        // pass 2
        for(auto& bldg: buildings) {
            int x = bldg[0];
            int y = bldg[1];

            bool is_covered = true;

            if( vertical[x].first == y || vertical[x].second == y )
                is_covered = false;

            if( is_covered ) {
                if( horizontal[y].first == x || horizontal[y].second == x )
                    is_covered = false;
            }

            if( is_covered )
                ++ans;

        }

        return ans;
    }
};
