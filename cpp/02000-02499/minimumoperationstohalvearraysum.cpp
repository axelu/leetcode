
// 2208. Minimum Operations to Halve Array Sum
// https://leetcode.com/problems/minimum-operations-to-halve-array-sum/



class Solution {
public:
    int halveArray(vector<int>& nums) {

        priority_queue<double> pq;

        double sum = 0.0;
        for(int x: nums) {
            sum += x;
            pq.push(x);
        }

        double sum2 = sum/2;

        int ans = 0;

        double reduction = 0.0;
        while( reduction < sum2 ) {
            ++ans;

            double t = pq.top()/2;
            pq.pop();

            reduction += t;
            pq.push(t);
        }

        return ans;
    }
};
