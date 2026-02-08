
// 3806. Maximum Bitwise AND After Increment Operations
// https://leetcode.com/problems/maximum-bitwise-and-after-increment-operations/





class Solution {
public:
    int maximumAND(vector<int>& nums, int k, int m) {
        int n = nums.size(); // 1 <= n <= 5 * 1e4; 1 <= nums[i] <= 1e9
        // 1 <= k <= 1e9
        // 1 <= m <= n
        //                                   0987654321098765432109876543210
        // decimal 1e9 = 1000000000 => binary 111011100110101100101000000000 (30digits)
        //               1073741823           111111111111111111111111111111
        // extreme example nums = [1000000000], k = 1000000000, m = 1
        //     ans = 2000000000              1110111001101011001010000000000 (31digits)
        // we can only increment !!!
        // maximum bitwise AND means we need to see which right bit we can get m
        // elements to all have.

        if( m == 1 ) {
            int mx = *max_element(nums.begin(), nums.end());
            return mx + k;
        }

        int res = 0;
        // try bit 30..0
        vector<int> bitindices; // bit indices set in response
        for(int bit = 30; bit >= 0; --bit) {
            int cand = res | (1<<bit);

            priority_queue<int,vector<int>,greater<int>> pq;
            for(int i = 0; i < n; ++i) {
                int num = nums[i];

                // get cost to set bits that are set in cand and NOT set in num
                // find right most bit set in cand and not set in num
                int highest_unset_bitidx = -1;
                for(int setbit: bitindices) {
                    if( !(num & (1<<setbit)) ) {
                        highest_unset_bitidx = setbit;
                        break;
                    }
                }
                if( highest_unset_bitidx == -1 && !(num & (1<<bit)) )
                    highest_unset_bitidx = bit;

                int cost = 0;
                if( highest_unset_bitidx != -1 ) {
                    int mask;
                    if( highest_unset_bitidx == 30 )
                        mask = 2147483647;
                    else
                        mask = (1<<(highest_unset_bitidx+1)) - 1;

                    int _num  = num & mask;
                    int _cand = cand & mask;
                    cost = _cand - _num;
                }
                if( cost <= k ) // no need to add if cost > k
                    pq.push(cost);
            }
            // if we can make this bit, then set this bit in our response
            if( pq.size() >= m ) {
                long long total_cost = 0;
                for(int i = 0; i < m && total_cost <= k; ++i) {
                    total_cost += (long long)pq.top();
                    pq.pop();
                }
                if( total_cost <= k ) {
                    res = cand;
                    bitindices.push_back(bit);
                }
            }
        }

        return res;
    }
};
