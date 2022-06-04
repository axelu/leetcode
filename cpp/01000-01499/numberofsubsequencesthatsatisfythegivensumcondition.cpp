
// 1498. Number of Subsequences That Satisfy the Given Sum Condition
// https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/



class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        // example 2 3 3 4 6 7 target 12
        //   index 0 1 2 3 4 5
        // if nums[i] + nums[i] <= target, we can add 1
        // after that we can add 2^x -1 where x is the distance between i and max k,
        // with nums[i] + nums[k] <= target
        // back to the example
        // i = 0 -> 1 + 2^5-1 = 32
        // i = 1 -> 1 + 2^4-1 = 15
        // i = 2 -> 1 + 2^3-1 =  8
        // i = 3 -> 1 + 2^2-1 =  4
        // i = 4 -> 1 -> the next element 6 + 7 doesn fit anymore 2^0-1
        // i = 5 -> 0 we can abort if we hit nums[i] + nums[i] > target

        int n = nums.size();
        long MOD = 1000000007;

        // https://en.wikipedia.org/wiki/Modular_exponentiation
        // precalculate modular exponentiation
        long me[n+1];
        me[0] = 1;
        unsigned long long c = 1;
        for(int i = 0; i < n; ++i)
            me[i+1] = c = (c * 2) % MOD;


        // we can sort the input
        sort(nums.begin(),nums.end());

        long ans = 0L;

        int s,e,mid,t;
        for(int i = 0; i < n; ++i) {
            t = target - nums[i];
            if( t < nums[i] )
                break;

            s = i+1;

            if( i < n-1 ) {
                // returns 'n' if nums[n-1] <= target
                // binary search upper bound while loop
                // upper bound -> greater than target
                e = n;
                while(s < e) {
                    mid = s + ((e-s)/2);
                    if( t >= nums[mid] )
                        s = mid + 1;
                    else
                        e = mid;
                }
                if( s < n && nums[s] <= t )
                    ++s;
            }

            ans = (ans + me[s - i - 1]) % MOD;
       }

        return ans;
    }
};
