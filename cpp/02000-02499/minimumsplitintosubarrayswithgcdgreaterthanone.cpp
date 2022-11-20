
// 2436. Minimum Split Into Subarrays With GCD Greater Than One
// https://leetcode.com/problems/minimum-split-into-subarrays-with-gcd-greater-than-one/




class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long a, long long b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    unordered_map<long,int> mem;

    int rec(vector<int>& nums, int n, long i, int lst_gcd) {
        // cout << "rec i " << i << " lst_gcd " << lst_gcd << endl;
        if( i == n )
            return 1;

        long key = (i<<30) + lst_gcd;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        // we have a choice
        //     start a new subarray
        //     add the current element to the prior subarray if we can

        // start a new subarray
        int a = 1 + rec(nums,n,i+1,nums[i]);

        // add the current subarray to the prior subarray
        int b = INT_MAX;
        long long new_gcd = gcd(lst_gcd,nums[i]);
        if( new_gcd > 1 )
            b = rec(nums,n,i+1,new_gcd);

        return mem[key] = min(a,b);
    }

public:
    int minimumSplits(vector<int>& nums) {
        int n = nums.size();

        // return rec(nums,n,1,nums[0]);

        if( n == 1 )
            return 1;

        int ans = 1;

        int lst_gcd = nums[0];
        for(int i = 1; i < n; ++i) {
            int new_gcd = gcd(lst_gcd,nums[i]);
            if( new_gcd > 1 ) {
                lst_gcd = new_gcd;
            } else {
                // we need to start a new subarray
                ++ans;
                lst_gcd = nums[i];
            }
        }

        return ans;
    }
};
