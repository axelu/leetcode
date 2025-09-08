
// 3633. Earliest Finish Time for Land and Water Rides I
// https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-i/




class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size();  // landStartTime.length == landDuration.length == n
        int m = waterStartTime.size(); // waterStartTime.length == waterDuration.length == n

        int ans = INT_MAX;

        // we can either start with a land ride or a water ride

        // start with the land ride that finishes earliest, then
        // ride the next possible shortest water ride OR
        // start with the water ride that finishes earliest, then
        // ride the next possible shortest land ride


        int A = INT_MAX; // land, then water

        int minLandFinish = INT_MAX;
        for(int i = 0; i < n; ++i) {
            int finish = landStartTime[i] + landDuration[i];
            minLandFinish = min(minLandFinish, finish);
        }
        for(int i = 0; i < m; ++i) {
            A = min(A, max(minLandFinish, waterStartTime[i]) + waterDuration[i]);
        }

        int B = INT_MAX; // water, then land

        int minWaterFinish = INT_MAX;
        for(int i = 0; i < m; ++i) {
            int finish = waterStartTime[i] + waterDuration[i];
            minWaterFinish = min(minWaterFinish, finish);
        }
        for(int i = 0; i < n; ++i) {
            B = min(B, max(minWaterFinish, landStartTime[i]) + landDuration[i]);
        }

        return min(A,B);
    }
};
