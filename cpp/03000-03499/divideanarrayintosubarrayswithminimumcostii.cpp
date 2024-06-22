
// 3013. Divide an Array Into Subarrays With Minimum Cost II
// https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-ii/





class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();
        if( n == k ) // dist must be 1 in that case
            return accumulate(nums.begin(),nums.end(),0LL);

        // nums[0] will alwasy be part of the answer

        // k - 2 <= dist <= n - 2

        if( k - 2 == dist ) {
            // sliding window of length dist+1
            // from index i = n - (dist+1) to index i = 1 from right to lect
            long long ans = LLONG_MAX;
            long long sum = 0LL;
            int i = 1;                      // left index
            for(int j = 1; j < n; ++j) {    // right index
                sum += (long long)nums[j];
                if( j - i + 1 == dist + 1 ) {
                    ans = min(ans,sum);
                    sum -= nums[i];
                    ++i;
                }
            }
            return (long long)nums[0] + ans;
        }

        map<int,int> mp; // keep track of (k-1) smallest values in window
        long long ans;
        long long sum = 0LL;
        map<int,int>::iterator tail_val;
        int tail_cnt;
        int j = n-1;                        // right index
        for(int i = n-1; i >= 1; --i) {     // left index
            ++mp[nums[i]];

            if( i > n - (k-1) ) {
                sum += (long long)nums[i];
                continue;
            }

            if( i == n - (k-1) ) {
                sum += (long long)nums[i];
                // init the tail
                tail_val = prev(mp.end());
                tail_cnt = tail_val->second;

                ans = sum;

            } else {
                // is nums[i] better than what we have?
                if( nums[i] < tail_val->first ) {
                    // replace the tail val with nums[i]
                    sum -= (long long)tail_val->first;
                    sum += (long long)nums[i];
                    ans = min(ans,sum);
                    // adjust the tail
                    if( tail_cnt > 1 ) {
                        --tail_cnt;
                    } else {
                        --tail_val;
                        tail_cnt = tail_val->second;
                    }
                }
            }

            // shrink the window
            if( j - i == dist ) {
                if( nums[j] == tail_val->first ) {
                    if( mp[nums[j]] == tail_cnt ) { // can never be mp[nums[j]] < tail_cnt
                        sum -= (long long)tail_val->first;
                        // the tail needs to move to the next larger element
                        ++tail_val;
                        sum += (long long)tail_val->first;
                        tail_cnt = 1;
                    }

                } else if( nums[j] < tail_val->first) {
                    sum -= (long long)nums[j];
                    if( tail_cnt < tail_val->second ) {
                        ++tail_cnt;
                    } else {
                        ++tail_val;
                        tail_cnt = 1;
                    }
                    sum += (long long)tail_val->first;
                }

                --mp[nums[j]];
                if( mp[nums[j]] == 0 )
                    mp.erase(nums[j]);
                --j;
            }
        }

        // finish up
        // shrink the window
        // we don't need to

        return (long long)nums[0] + ans;
    }
};
