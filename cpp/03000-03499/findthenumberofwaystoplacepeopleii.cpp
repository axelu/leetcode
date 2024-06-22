
// 3027. Find the Number of Ways to Place People II
// https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/




class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        // -1000000000 <= points[i][0], points[i][1] <= 1000000000
        map<int,set<int>> xy;
        map<int,set<int>> yx;

        for(vector<int>& point: points) {
            int x = point[0];
            int y = point[1];

            xy[x].insert(y);
            yx[y].insert(x);
        }

        // lets assume a given point is Takina: xt, yt
        // there are only 3 possibilities for a fence with a point Chisato where Chisato is not sad
        // let the point Chisato be xc, yc
        //    A a point with xt == xc, and yc next greater yt
        //    B a point with yt == yc, and xc next smaller xt
        //    C a point with yt < yc and xt > xc, but if A exists, yc smaller than A yc and if B exist, xc > B xc

        int ans = 0;

        for(vector<int>& point: points) {
            int xt = point[0];
            int yt = point[1];

            // A
            int ycA = 1000000001;
            auto fx = xy.find(xt); // guaranteed to find
            auto ycA_it = fx->second.upper_bound(yt);
            if( ycA_it != fx->second.end() ) {
                ycA = *ycA_it;
                ++ans;
            }
            // B
            int xcB = -1000000001;
            auto fy = yx.find(yt);  // guaranteed to find
            auto xcB_it = fy->second.lower_bound(xt); // we will find ourselfs
            if( xcB_it != fy->second.begin() ) {
                xcB = *(prev(xcB_it));
                ++ans;
            }
            // C
            while( fx != xy.begin() ) {
                fx = prev(fx);
                if( fx->first == xcB )
                    break;

                auto yc_it = fx->second.upper_bound(yt);
                if( yc_it != fx->second.end() && *(yc_it) < ycA ) {
                    ycA = *(yc_it);
                    ++ans;
                }
            }
        }

        return ans;
    }
};
