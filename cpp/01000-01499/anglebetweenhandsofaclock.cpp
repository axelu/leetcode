
// 1344. Angle Between Hands of a Clock
// https://leetcode.com/problems/angle-between-hands-of-a-clock/



class Solution {
public:
    double angleClock(int hour, int minutes) {
        // degrees clockwise
        // 12 => 0deg, 1 => 30deg, ..., 11 => 330deg, let those be our based degrees based on the hour

        double hour_base_deg = hour == 12 ? 0 : hour * 30;
        //cout << "hour_base_deg " << hour_base_deg << endl;
        // each hour is 30deg's
        // the minutes determine what we need to add to the hour hand:
        // minutes / 60min * 30deg
        double hour_offset_deg = minutes * 0.5;

        double hour_deg = hour_base_deg + hour_offset_deg;
        //cout << "hour_deg " << hour_deg << endl;

        // minutes / 60min * 360deg
        double hand_deg = minutes * 6.0;
        //cout << "hand_deg " << hand_deg << endl;

        double a = abs(hour_deg - hand_deg);
        return min( a, 360 - a);
    }
};
