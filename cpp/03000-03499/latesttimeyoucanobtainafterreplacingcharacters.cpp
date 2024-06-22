
// 3114. Latest Time You Can Obtain After Replacing Characters
// https://leetcode.com/problems/latest-time-you-can-obtain-after-replacing-characters/




class Solution {
public:
    string findLatestTime(string s) {
        // earliest 12-hour time is 00:00,
        // and the latest is 11:59

        string str_hr = s.substr(0,2);

        if( str_hr[0] == '?' && str_hr[1] == '?' ) {
            str_hr = "11";

        } else if( str_hr[0] == '?' && str_hr[1] != '?' ) {
            if( str_hr[1] == '0' || str_hr[1] == '1' )
                str_hr[0] = '1';
            else
                str_hr[0] = '0';

        } else if( str_hr[0] != '?' && str_hr[1] == '?' ) {
            if( str_hr[0] == '1' )
                str_hr[1] = '1';
            else
                str_hr[1] = '9';
        }


        string str_min = s.substr(3,2);

        if( str_min[0] == '?' && str_min[1] == '?' ) {
            str_min = "59";

        } else if( str_min[0] == '?' && str_min[1] != '?' ) {
                str_min[0] = '5';

        } else if( str_min[0] != '?' && str_min[1] == '?' ) {
                str_min[1] = '9';
        }

        return str_hr + ":" + str_min;
    }
};
