

// 2059. Minimum Operations to Convert Number
// https://leetcode.com/problems/minimum-operations-to-convert-number/



// resources
// https://www.loginradius.com/blog/engineering/how-does-bitwise-xor-work/
// https://medium.com/@1206_90373/twos-complement-and-negative-numbers-for-integers-cf20a45bf098
// https://en.wikipedia.org/wiki/Two%27s_complement
// a ^ b works here if one or both are negative, because they are stored as two's compliment

class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {

        // BFS
        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            return a[1] > b[1];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);
        pq.push({start,0});

        int seen[1001];memset(seen,0,sizeof seen);
        seen[start] = 1;

        while( !pq.empty() ) {
            auto[x,steps] = pq.top();
            pq.pop();

            int x_new;
            for(int o : nums) {
                // x + nums[i]
                x_new = x + o;
                if( x_new == goal )
                    return steps+1;
                if( x_new >= 0 && x_new <= 1000 && !seen[x_new] ) {
                    seen[x_new] = 1;
                    pq.push({x_new,steps+1});
                }

                // x - nums[i]
                x_new = x - o;
                if( x_new == goal )
                    return steps+1;
                if( x_new >= 0 && x_new <= 1000 && !seen[x_new] ) {
                    seen[x_new] = 1;
                    pq.push({x_new,steps+1});
                }

                // x ^ nums[i]
                x_new = x ^ o;
                if( x_new == goal )
                    return steps+1;
                if( x_new >= 0 && x_new <= 1000 && !seen[x_new] ) {
                    seen[x_new] = 1;
                    pq.push({x_new,steps+1});
                }
            }
        }

        return -1;
    }
};
