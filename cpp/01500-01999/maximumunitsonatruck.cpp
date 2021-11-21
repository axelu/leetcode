
// 1710. Maximum Units on a Truck
// https://leetcode.com/problems/maximum-units-on-a-truck/


class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        sort(begin(boxTypes),end(boxTypes),[](vector<int>& a, vector<int>& b) {
            return a[1] > b[1];
        });

        int ans = 0;
        for(int i = 0; i < boxTypes.size(); ++i) {
            if( boxTypes[i][0] <= truckSize ) {
                // take all those boxes
                ans += boxTypes[i][0]*boxTypes[i][1];
                truckSize -= boxTypes[i][0];
            } else {
                // boxTypes[i][0] > truckSize
                // take only as many boxes as we can [still] fit
                ans += truckSize * boxTypes[i][1];
                truckSize = 0;
            }
            if( 0 == truckSize ) break;
        }

        return ans;
    }
};
