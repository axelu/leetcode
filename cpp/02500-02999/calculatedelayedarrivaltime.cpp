
// 2651. Calculate Delayed Arrival Time
// https://leetcode.com/problems/calculate-delayed-arrival-time/




class Solution {
public:
    int findDelayedArrivalTime(int arrivalTime, int delayedTime) {
        return (arrivalTime + delayedTime) % 24;
    }
};
