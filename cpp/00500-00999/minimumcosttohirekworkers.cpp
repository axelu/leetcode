
// 857. Minimum Cost to Hire K Workers
// https://leetcode.com/problems/minimum-cost-to-hire-k-workers/





// based on soltion approach 2

class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size(); // n == quality.length == wage.length

        // key insight: at least one worker will be paid their minimum wage expectation

        vector<array<double,2>> qw(n); // vector of {quality,wage}
        for(int i = 0; i < n; ++i)
            qw[i] = {(double)quality[i],(double)wage[i]};

        sort(qw.begin(),qw.end(),[](const array<double,2>& a, const array<double,2>& b){
            // ratio of wage / quality
            // this is the wage the worker demands to deliver that quality
            double ratio_a = a[1] / a[0]; // wage to quality
            double ratio_b = b[1] / b[0]; // wage to quality

            return ratio_a < ratio_b;
        });

        double ans = DBL_MAX;
        double sum_quality = 0;

        priority_queue<int> pq;;
        for(auto& worker: qw) {
            // cout << (worker[1]/worker[0]) << endl;

            // iterate over the ratio of wage/quality in ascending order
            // we know that all the workers considered thus far have a lower wage/quality ratio
            // let the current worker be the worker that is paid their minimum wage expectation
            // we can then calculate the candidate answer as the ratio of the current worker
            // times the sum of the quality of the smallest k workers

            pq.push(worker[0]);
            sum_quality += worker[0];
            if( pq.size() > k) {
                sum_quality -= pq.top();
                pq.pop();
            }
            if( pq.size() == k )
                ans = min(ans, sum_quality * (worker[1]/worker[0]));
        }

        return ans;
    }
};
