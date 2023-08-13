
// 2195. Append K Integers With Minimal Sum
// https://leetcode.com/problems/append-k-integers-with-minimal-sum/




class Solution {
private:
    long long sum(long long s, long long e) {
        // TODO this may be TLE

        // long long ret = 0;
        // for(long long i = s; i <= e; ++i)
        //    ret += i;
        // return ret;

        long long a = (s-1) * s/2;
        long long b = e * (e+1)/2;
        return b - a;
    }

public:
    long long minimalKSum(vector<int>& nums, int k) {
        int n = nums.size();

        long long ans = 0;

        // we greedily want to us the smallest numbers possible to append
        sort(nums.begin(),nums.end());

        // can we add numbers before nums[0]
        if( nums[0] > 1 ) {
            // we have a gap before nums[0]
            int gap = nums[0] - 1;
            ans += sum(1, min(k,nums[0]-1));
            k -= min(k, gap);
        }

        for(int i = 0; i < n && k > 0; ++i) {

            if( i < n-1 && nums[i+1] > nums[i] + 1 ) {
                // we have a gap between nums[i] and nums[i+1];
                int gap = nums[i+1] - nums[i] - 1;

                ans += sum(nums[i]+1, min(nums[i]+k,nums[i+1]-1));
                k -= min(k, gap);
            }
        }

        // finish up
        if( k > 0 ) {
            // we still have to add k numbers
            ans += sum(nums[n-1]+1, nums[n-1]+k);
        }

        return ans;
    }
};
