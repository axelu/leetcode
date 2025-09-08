
// 3618. Split Array by Prime Indices
// https://leetcode.com/problems/split-array-by-prime-indices/




// initialize once
bool init = false;
bool is_prime[100001];

class Solution {
private:
   bool isPrime(int n) {
        if( n == 2 || n == 3 )
            return true;

        if( n <= 1 || n % 2 == 0 || n % 3 == 0  )
            return false;

        for(int i = 5; i * i <= n; i += 6 ) {
            if( n % i == 0 || n % (i + 2) == 0 )
                return false;
        }

        return true;
    }

public:
    long long splitArray(vector<int>& nums) {
        if( !init ) {
            init = true;
            for(int i = 0; i <= 100000; ++i)
                is_prime[i] = isPrime(i);
        }

        int n = nums.size();

        long long A = 0LL;
        long long B = 0LL;

        for(int i = 0; i < n; ++i) {
            if( is_prime[i] )
                A += (long long)nums[i];
            else
                B += (long long)nums[i];
        }

        return abs(A-B);
    }
};
