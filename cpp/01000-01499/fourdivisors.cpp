
// 1390. Four Divisors
// https://leetcode.com/problems/four-divisors/




/* 1 * i * j * x -> x is only divisible by 1, i, j and itself
 * then i must be a prime
 * and j must only be divisible by 1, i and itself
 *
 * j must be a prime or i*i
 */
class Solution {
private:
    // primes between 2 and 315 inclusive
    vector<int> iprimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
                           61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127,
                           131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
                           197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269,
                           271, 277, 281, 283, 293, 307, 311, 313};

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

    bool three_divisors(int j, int i) {
        // j can only be divisible by 1, i and itself
        // also good if 1 and itself, meaning its a prime.

        int divisors = 0;
        for(int k = 2; k <= j/2; ++k) {
            if( k == i )
                continue;
            if( j % k == 0 )
                return false;
        }

        return true;
    }

public:
    int sumFourDivisors(vector<int>& nums) {

        int mx = *max_element(nums.begin(),nums.end());

        unordered_map<int,int> um;

        for(int i: iprimes) {
            if( i * (i+1) > mx )
                break;

            for(int j = i+1; i * j <= mx; ++j) {
                //if( !three_divisors(j,i) )
                //    continue;
                if( j != i*i && !isPrime(j) )
                    continue;

                int x = i*j;
                int s = 1 + i + j + x;
                // cout << "i " << i << " j " << j << " x " << x << endl;
                um[x] = s;
            }
        }

        int ans = 0;
        for(int x: nums) {
            auto f = um.find(x);
            if( f != um.end() )
                ans += f->second;
        }



        return ans;
    }
};
