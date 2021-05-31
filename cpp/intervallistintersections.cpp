
// 986. Interval List Intersections
// https://leetcode.com/problems/interval-list-intersections/



class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& fL, vector<vector<int>>& sL) {
        vector<vector<int>> ans;
        int n1 = fL.size();
        int n2 = sL.size();
        if( n1 == 0 || n2 == 0 ) return ans;

        int i1 = 0, i2 = 0;
        while( i1 < n1 && i2 < n2 ) {

            // no touch
            if( fL[i1][1] < sL[i2][0] ) {
                ++i1;
                continue;
            }
            if( sL[i2][1] < fL[i1][0] ) {
                ++i2;
                continue;
            }

            // touch
            if( fL[i1][1] == sL[i2][0] ) {
                ans.push_back({fL[i1][1],sL[i2][0]});
                ++i1;
                continue;
            }
            if( sL[i2][1] == fL[i1][0] ) {
                ans.push_back({sL[i2][1],fL[i1][0]});
                ++i2;
                continue;
            }

            // overlap on end
            if( fL[i1][1] > sL[i2][0] && fL[i1][1] <= sL[i2][1] ) {
                ans.push_back({max(fL[i1][0],sL[i2][0]),min(fL[i1][1],sL[i2][1])});
                ++i1;
                continue;
            }
            if( sL[i2][1] > fL[i1][0] && sL[i2][1] <= fL[i1][1] ) {
                ans.push_back({max(fL[i1][0],sL[i2][0]),min(fL[i1][1],sL[i2][1])});
                ++i2;
                continue;
            }

            // overlap on start
            // equal
            // eclipse


        }
        return ans;
    }
};
