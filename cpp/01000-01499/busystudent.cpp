
// 1450. Number of Students Doing Homework at a Given Time
// https://leetcode.com/problems/number-of-students-doing-homework-at-a-given-time/

class Solution {
public:
    int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
        int r = 0;
        int n = startTime.size(); // constraint: startTime.length == endTime.length
        for(int i = 0; i < n; ++i)
            if( startTime[i] <= queryTime && endTime[i] >= queryTime) ++r;

        return r;
    }
};
