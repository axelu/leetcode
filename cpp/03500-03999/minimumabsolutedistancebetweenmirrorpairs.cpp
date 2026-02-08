
// 3761. Minimum Absolute Distance Between Mirror Pairs
// https://leetcode.com/problems/minimum-absolute-distance-between-mirror-pairs/


class Solution {
private:
    long long reversex(int x) {
        string x_string = to_string(x);
        reverse(begin(x_string), end(x_string));
        long long ret = stoll(x_string);
        return ret;
    }

public:
    int minMirrorPairDistance(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 1e5; 1 <= nums[i] <= 1e9
        // formula number of pairs n * (n-1)/2
        // worst case number of pairs 4999950000
        // int max                    2147483647

        // reverse(nums[i]) == nums[j]
        // idea
        // go through nums right to left 0 <= i < n-1
        // keep track of leftmost pos j of a given value seen
        // reverse nums i, check when last seen and note
        // the smallest distance

        int ans = INT_MAX;
        unordered_map<long long, int> seen;
        seen.insert({nums[n-1], n-1});
        for(int i = n-2; i >= 0; --i) {
            int x = nums[i];
            int x_rev = reversex(x);
            // cout << i << " nums[i] " << x << " reverse(nums[i]) " << x_rev << endl;
            auto f = seen.find(x_rev);
            if( f != seen.end() ) {
                int j = f->second;
                ans = min(ans, abs(i-j));
                if( ans == 1 )
                    break;
            }
            seen[x] = i;
        }

        return ans != INT_MAX ? ans : -1;
    }
};
