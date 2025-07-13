
// 3551. Minimum Swaps to Sort by Digit Sum
// https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum/





class Solution {
private:
    int get_digit_sum(int i) {
        int ret = 0;
        while (i)
        {
            int rem = i % 10;
            ret += rem;
            i /= 10;
        }
        return ret;
    }

public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        // it is guaranteed that nums consists of distinct positive integers.

        // pair<int,int> first: digitsum, second: integer
        auto cmp = [](const pair<int,int>& a, const pair<int,int>& b){
            if( a.first > b.first ) {
                return true;
            } else if( a.first == b.first ) {
                if( a.second > b.second) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

        unordered_map<int,int> um;
        for(int i = 0; i < n; ++i) {
            um[nums[i]] = i;
            int digitsum = get_digit_sum(nums[i]);
            pq.push({digitsum, nums[i]});
        }

        int ans = 0; // swaps
        int i = 0;
        while( !pq.empty() ) {
            int x = pq.top().second;
            pq.pop();

            // cout << "i " << i << " curr nums[i] " << nums[i] << " should be " << x << endl;

            if( nums[i] == x ) {
                ++i;
                continue;
            }

            int pos_x_curr = um[x];
            // the value at i needs to be put where x currently is
            // aka swap

            nums[pos_x_curr] = nums[i];
            um[nums[i]] = pos_x_curr;
            // nums[i] = x;    // we don't need to keep track of this
            // um[x] = i;      // we don't need to keep track of this

            ++ans;
            ++i;
        }

        return ans;
    }
};
