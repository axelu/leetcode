
// 3506. Find Time Required to Eliminate Bacterial Strains
// https://leetcode.com/problems/find-time-required-to-eliminate-bacterial-strains/





// see 1199. Minimum Time to Build Blocks https://leetcode.com/problems/minimum-time-to-build-blocks/
// it is the same question, but the problem space is much greater, as we can have
// up to 100000 bacteria and with that could need 100000 white blood cells
// so for a DP solution, we would be looking at mem[100000][100000], which is not feasable
// see editorial of problem 1199, even in the bottom-up DP space optimized,
// we would only need a 1D mem, worst case mem[100001], but still runtime would be 100000*100000,
// which will be TLE, so really only approach left is Optimal Merge Pattern as detailed in the editorial of problem 1199
// hence solution here based on editorial of problem 1199 Optimal Merge Pattern

class Solution {
public:
    long long minEliminationTime(vector<int>& timeReq, int splitTime) {
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        for (long long t : timeReq)
            pq.push(t);

        // Make sibling white blood cells until we are left with only one root node
        while (pq.size() > 1) {
            // Pop two minimum. The time of the abstracted sub-root will be
            // split + max(x, y) which is split + y
            // long long x = pq.top();
            pq.pop();

            long long y = pq.top();
            pq.pop();

            pq.push((long long)splitTime + y);
        }

        // Time of final root node
        return pq.top();
    }
};
