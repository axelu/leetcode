
// 849. Maximize Distance to Closest Person
// day 29 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/563/week-5-october-29th-october-31st/3512/
// https://leetcode.com/problems/maximize-distance-to-closest-person/



class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        auto n = seats.size();
        if( n == 2 ) return 1;

        int mxdist = 1;
        int dist;
        auto itl = begin(seats);
        int mode = *itl == 0 ? 0 : 1;
        auto it = next(itl);
        for(; it != end(seats); ++it) {
            if( *it == 1 ) {
                if( mode == 1 ) continue;
                if( itl == begin(seats) ) {
                    mxdist = distance(itl,it);
                } else {
                    dist = distance(itl-1,it)/2;
                    mxdist = max(mxdist,dist);
                }
                mode = 1;
            } else {
                if( mode == 0 ) continue;
                itl = it;
                mode = 0;
            }
        }
        // finish up
        if( mode == 0 ) {
            dist = distance(itl-1,it-1);
            mxdist = max(mxdist,dist);
        }

        return mxdist;
    }
};
