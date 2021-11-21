
// 1229. Meeting Scheduler
// https://leetcode.com/problems/meeting-scheduler/
// day 29 April 2021 challenge bonus question
// https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/597/week-5-april-29th-april-30th/3724/



class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        int n1 = slots1.size();
        sort(slots1.begin(),slots1.end());
        int n2 = slots2.size();
        sort(slots2.begin(),slots2.end());

        int i,j;
        bool possible = false;

        // putting slots1 in the driver seat
        int ans = -1;
        i = 0;
        j = 0;
        for(; i < n1; ++i) {
            if( slots1[i][1] - slots1[i][0] < duration ) continue;
            possible = true;

            for(; j < n2; ++j) {
                if( slots2[j][0] >= slots1[i][1]           ) break;
                if( slots1[i][1] - slots2[j][0] < duration ) break;

                if( slots2[j][1] <= slots1[i][0] ) continue;
                if( slots2[j][1] - slots1[i][0] < duration ) continue;

                if( slots2[j][1] - slots2[j][0] < duration ) continue;

                ans = max(slots1[i][0],slots2[j][0]);
                break;
            }
            if( ans != -1 || j == n2 ) break;
        }
        if( !possible || ans == -1 ) return {};
        return {ans,ans+duration};
    }
};
