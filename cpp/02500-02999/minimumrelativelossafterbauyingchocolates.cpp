
// 2819. Minimum Relative Loss After Buying Chocolates
// https://leetcode.com/problems/minimum-relative-loss-after-buying-chocolates/




/* example
 * prices = [1,2,3,4,5,6,7,8,9,10] sorted ascending
 * query [5,5]
 * index 0  1  2  3  4  5  6  7  8  9
 * price 1  2  3  4  5  6  7  8  9 10
 * Bob   1  2  3  4  5  5  5  5  5  5
 * Alice 0  0  0  0  0  1  2  3  4  5
 * b - a 1  2  3  4  5  4  3  2  1  0
 * so Bob choses chocolates at index 0, 1, 7 ,8 and 9 => ans = 1 + 2 + 2 + 1 + 0 = 6
 */
class Solution {
public:
    vector<long long> minimumRelativeLosses(vector<int>& prices, vector<vector<int>>& queries) {
        int n = prices.size();

        sort(prices.begin(),prices.end());

        long long prefixSum[n+1];
        prefixSum[0] = 0LL;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + prices[i-1];

        int q_sz = queries.size();
        vector<long long> ans(q_sz);

        for(int q = 0; q < q_sz; ++q) {
            int k = queries[q][0]; // price up to which Bob pays
            int m = queries[q][1]; // number of chocolates we need to buy

            // the relative loss for Bob for each chocolate i is what bob pays minus what alice pays
            //     loss[i]  = bob[i] - alice[i]
            // if prices[i] <= k
            //     bob[i]   = prices[i]
            //     alice[i] = 0
            //     loss[i]  = prices[i] - 0 = prices[i]
            // if prices[i] > k
            //     bob[i]   = k
            //     alice[i] = prices[i] - k
            //     loss[i]  = k - (prices[i] - k) = 2*k - prices[i]

            // we need to pick chocolates from the left [0,1,...,left] and
            // chocolates from the right [n-(m-left), n-(m-left)+1, ...,n-1] optimally where right = m-left

            // let mx_left = largest index in prices where prices[i] <= k
            // left will be in range [0,min(mx_left,m)]  inclusive

            // the loss of the left chocolates is
            //     prices[0] + prices[1] + ... + prices[left], which increases with left increasing
            // the loss of the right chocolates is
            //     2*k*right - (prices[n-right] + prices[n-right+1] + ... + prices[n-1]), which is decreasing with right increasing
            // as long as loss[left] < loss[n-right] we increase left, otherwise we decrease left

            // from example 1, m = 4, k = 18
            //         0  1  2  3  4
            // prices  1  9 10 19 22
            // bob     1  9 10 18 18
            // alice   0  0  0  1  4
            // loss    1  9 10 17 14
            // if we pick left idx 0 and right idx 2 -> relative loss 42
            // if we pick left idx 1 and right idx 3 -> relative loss 41
            // if we pick left idx 2 and right idx 4 -> relative loss 34

            auto ub = upper_bound(prices.begin(), prices.end(), k);

            // binary search upper bound
            int s = 0;
            int e = min((int)distance(prices.begin(),ub), m); // normally n
            int mid;
            while(s < e) {
                mid = s + ((e - s)/2);
                int right = m - mid;
                if( prices[mid] < 2LL*k - prices[n-right] )
                    s = mid + 1;
                else
                    e = mid;
            }

            int left = e;
            int right = m - left;
             ans[q] = prefixSum[left] + (2LL*k*right - (prefixSum[n] - prefixSum[n-right]));
         }

        return ans;
    }
};
