
// 3729. Count Distinct Subarrays Divisible by K in Sorted Array
// https://leetcode.com/problems/count-distinct-subarrays-divisible-by-k-in-sorted-array/




class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    // function to return Least Common Multiple (LCM) of two numbers
    // LCM definition:
    // LCM of two numbers is the smallest number which can be divided by both numbers
    long long lcm(long a, long b) {
        return (a / gcd(a,b)) * b;
    }

public:
    long long numGoodSubarrays(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= nums.length <= 1e5
        cout << "n " << n << endl;
        if( n == 1 )
            return nums[0] % k == 0;

        // candidate for dup: same length and same sum
        // idea
        // prefixSum and prefixSum % k
        // if we ae at index i, we can count how many
        // are prefixSum with the same remainder are to our rigth
        // we need to discount duplicates
        // if we are at nums[i] == val and we have been before
        // at the same nums[i] == val, then determine where
        // the last nums[i] val is to our right, let that be j
        // divide the sum nums[i,j] by the lcm(val,k) to determine discount

        long long prefixSum[100001];
        prefixSum[0] = 0LL;
        unordered_map<int,int> rem_freq; // key: rem; value: count
        rem_freq[0] = 1;
        unordered_map<int,int> val_freq; // key: val; value: count
        for(int i = 0; i < n; ++i) {
            prefixSum[i+1] = prefixSum[i] + nums[i];
            ++rem_freq[prefixSum[i+1]%k];
            ++val_freq[nums[i]];
        }

        long long ans = 0LL;

        for(int i = 0; i < n; ++i) {
            int rem = prefixSum[i] % k;
            // don't count the position we are at
            --rem_freq[rem];
            //subarrays starting at i that are divisible by k
            int t = rem_freq[rem];

            // don't double count
            bool seen = i > 0 && nums[i-1] == nums[i] ? true : false;
            if( t && seen ) {
                long long _lcm = lcm(nums[i], k);
                // nums[i] remaining including us
                long long cnt = val_freq[nums[i]];
                long long sum = cnt * nums[i];
                long long discount = sum / _lcm;
                t -= discount;
            }

            ans += (long long)t;

            --val_freq[nums[i]];
        }

        return ans;
    }
};
