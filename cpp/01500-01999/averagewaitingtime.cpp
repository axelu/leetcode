
// 1701. Average Waiting Time
// https://leetcode.com/problems/average-waiting-time/



class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {

        long idle_time = 1;
        long wait_time = 0;
        for(auto& v: customers) {
            int arrival_time = v[0];
            int prep_time    = v[1];

            // our chef can work on the order starting at idle_time
            if( arrival_time >= idle_time ) {
                idle_time = arrival_time + prep_time;
                wait_time = wait_time + prep_time;
            } else {
                idle_time = idle_time + prep_time;
                wait_time = wait_time + (idle_time - arrival_time);
            }
        }

        double ans = (double)wait_time / customers.size();

        return ans;
    }
};
