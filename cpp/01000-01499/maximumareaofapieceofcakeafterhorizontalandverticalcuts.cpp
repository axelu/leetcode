
// 1465. Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts
// https://leetcode.com/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/
// day 3 June 2021 challenge
// https://leetcode.com/explore/challenge/card/june-leetcoding-challenge-2021/603/week-1-june-1st-june-7th/3766/





class Solution {
private:
    long getMaxDistance(vector<int>& v, int e) {
        sort(begin(v),end(v));
        v.push_back(e);
        int ret = 0;
        int pre = 0;
        for(int i = 0; i < v.size(); ++i) {
            ret = max(ret,v[i]-pre);
            pre = v[i];
        }
        return ret;
    }


public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        // find the pair of distances with the maximum product
        long mxHDist = getMaxDistance(horizontalCuts,h);
        long mxVDist = getMaxDistance(verticalCuts,w);

        // cout << "mxHDist " << mxHDist << endl;
        // cout << "mxVDist " << mxVDist << endl;

        long MOD = 1000000007;
        return ( ( mxHDist % MOD ) * ( mxVDist % MOD ) ) % MOD;
    }
};
