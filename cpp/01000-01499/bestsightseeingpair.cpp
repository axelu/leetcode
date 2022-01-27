
// 1014. Best Sightseeing Pair
// https://leetcode.com/problems/best-sightseeing-pair/



class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {

        int local_max = values[0];
        int global_max = INT_MIN;
        for(int i = 1; i < values.size(); ++i) {
            global_max = max(global_max, local_max + values[i] - i);

            local_max = max(local_max, values[i]+i);
        }

        return global_max;
    }
};
