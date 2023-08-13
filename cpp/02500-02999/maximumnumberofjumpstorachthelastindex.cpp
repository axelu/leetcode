
// 2770. Maximum Number of Jumps to Reach the Last Index
// https://leetcode.com/problems/maximum-number-of-jumps-to-reach-the-last-index/





class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();

        // idea
        // traverse nums from right to left
        // after we process an index and determine that it can reach the end,
        // we put that index in a priority queue sorted by number of steps (max heap)
        // when we get to the next index, we go into our priority queue
        // ( indexes are greater as we are going from right to left, so it meets i < j criteria)
        // and the 1st index in queue that we can get to gives us the greatest result

        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
            return a[0] < b[0];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);
        pq.push({0,nums[n-1]});

        for(int i = n-2; i >= 0; --i) {
            int numsi = nums[i];
            int t = -1; // init to cannot reach nums[n-1]
            stack<array<int,2>> park;
            while( !pq.empty() ) {
                // can we reach what is top of pq?
                int numsj = pq.top()[1];
                int diff = numsj - numsi;
                if( -target <= diff && diff <= target ) {
                    t = 1 + pq.top()[0];
                    break;
                } else {
                    park.push(pq.top());
                    pq.pop();
                }
            }

            if( i == 0 )
                return t;

            while( !park.empty() ) {
                pq.push(park.top());
                park.pop();
            }


            if( t != -1 ) {
                pq.push({t,numsi});
            }
        }

        return 99; // satisfy compiler
    }
};
