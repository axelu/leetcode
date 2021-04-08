
// 264. Ugly NUmber II
// https://leetcode.com/problems/ugly-number-ii/



// solution approach #1
class Solution {
public:
    int nthUglyNumber(int n) {
        int nums[1690];
        set<long> seen;
        priority_queue<long,vector<long>,greater<long>> pq; // min heap

        seen.insert(1L);
        pq.push(1L);

        long currUgly, newUgly;
        int primes[3] = {2,3,5};
        for(int i = 0; i < 1690; ++i) {
            currUgly = pq.top();
            pq.pop();
            nums[i] = (int)currUgly;
            for(int j = 0; j < 3; ++j) {
                newUgly = currUgly * primes[j];
                if( seen.find(newUgly) == end(seen) ) {
                    seen.insert(newUgly);
                    pq.push(newUgly);
                }
            }
        }

        return nums[n-1];
    }
};
