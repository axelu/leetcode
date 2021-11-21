
// 1736. Latest Time by Replacing Hidden Digits
// https://leetcode.com/problems/latest-time-by-replacing-hidden-digits/



class Solution {
public:
    string maximumTime(string time) {
        // time is in the format hh:mm
        string ans = "99:99";

        // hh
        if( time[0] == '?' && time[1] == '?' ) {
            ans[0] = '2';
            ans[1] = '3';
        } else if( time[0] == '?' ) {
            if( time[1] == '0' || time[1] == '1' || time[1] == '2' || time[1] == '3' ) {
                ans[0] = '2';
            } else {
                ans[0] = '1';
            }
            ans[1] = time[1];
        } else if( time[1] == '?' ) {
            ans[0] = time[0];
            if( time[0] == '2' ) {
                ans[1] = '3';
            } else {
                ans[1] = '9';
            }
        } else {
            ans[0] = time[0];
            ans[1] = time[1];
        }

        // mm
        if( time[3] == '?' && time[4] == '?' ) {
            ans[3] = '5';
            ans[4] = '9';
        } else if( time[3] == '?' ) {
            ans[3] = '5';
            ans[4] = time[4];
        } else if( time[4] == '?' ) {
            ans[3] = time[3];
            ans[4] = '9';
        } else {
            ans[3] = time[3];
            ans[4] = time[4];
        }

        return ans;
    }
};
