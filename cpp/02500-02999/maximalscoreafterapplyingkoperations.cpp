
// 2530. Maximal Score After Applying K Operations
// https://leetcode.com/problems/maximal-score-after-applying-k-operations/




class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {

        priority_queue<int> pq;
        for(int x: nums)
            pq.push(x);

        long long sum = 0LL;

        while( k > 0 ) {
            long long t = pq.top();
            pq.pop();
            sum += t;
            pq.push(ceil(t/3.0));
            --k;
        }

        return sum;
    }
};
