
// 1176. Diet Plan Performance
// https://leetcode.com/problems/diet-plan-performance/



class Solution {
public:
    int dietPlanPerformance(vector<int>& calories, int k, int lower, int upper) {
        int n = calories.size();

        // sum for the initial seqence
        int T = 0;
        for(int i = 0; i < k; ++i)
            T += calories[i];

        int ans = 0;
        for(int i = 0; i <= n-k; ++i) {
            if( T < lower ) --ans;
            if( T > upper ) ++ans;
            if( i == n-k ) break;
            T -= calories[i];
            T += calories[i+k];
        }
        return ans;
    }
};
