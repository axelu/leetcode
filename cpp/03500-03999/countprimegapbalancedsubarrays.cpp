
// 3589. Count Prime-Gap Balanced Subarrays
// https://leetcode.com/problems/count-prime-gap-balanced-subarrays/






// initialize once
bool init = false;
bool is_prime[50001];

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
    int primeSubarray(vector<int>& nums, int k) {
        // 1 <= nums[i] <= 5 * 1e4
        // 5133 prime numbers from 1 to 50000
        if( !init ) {
            init = true;
            for(int i = 0; i <= 50000; ++i)
                is_prime[i] = isPrime(i);
        }

        int n = nums.size(); // 1 <= n <= 5 * 1e4
        if( n == 1 )
            return 0;

        // worst case n = 50000
        // formula of number of non-empty subarrays n * ((n+1)/2)
        // = 1250025000 subarrays
        // discount subarrays of length 1: 1250025000 - 50000 = 1,249,975,000
        // obviously brute force will not work

        int ans = 0;

        map<int,int> mp; // primes in window; val, count
        int cnt = 0;
        int i = 0;
        int lft;

        int lst_prime;
        int lst_prime_pos;

        for(int j = 0; j < n; ++j) {
            int x = nums[j];

            if( is_prime[x] ) {
                // is this the 1st prime we encounter?
                if( cnt == 0 ) {
                    ++cnt;
                    ++mp[x];
                    lft = j;
                    lst_prime = x;
                    lst_prime_pos = j;
                    continue;
                }

                // does the prime x violate our constraint k?
                int cur_min_prime = mp.begin()->first;
                int cur_max_prime = mp.rbegin()->first;
                if( x < cur_min_prime && cur_max_prime - x > k ) {
                    // we need to adjust lft and i

                    // lft
                    // if the last prime encountered before prime at j
                    // is NOT violating k, then lft becomes that position,
                    // otherwise lft will become j, and i will become j also
                    if( abs(lst_prime - x) <= k ) {
                        // lst_prime does NOT violate k with current prime
                        lft = lst_prime_pos;

                        // i will be 1 + the index of the rightmost prime
                        // the violates the constraint
                        while( cur_max_prime - x > k ) {
                            if( is_prime[nums[i]] ) {
                                --cnt;
                                --mp[nums[i]];
                                if( mp[nums[i]] == 0 )
                                    mp.erase(nums[i]);
                                cur_max_prime = mp.rbegin()->first;
                            }
                            ++i;
                        }

                    } else {
                        // lst_prime does violate k with current prime
                        lft = j;
                        i = 1 + lst_prime_pos;
                        cnt = 0;
                        mp.clear();
                    }

                } else if( x > cur_max_prime && x - cur_min_prime > k ) {
                    // we need to ajdust lft and i

                    // lft
                    // if the last prime encountered before prime at j
                    // is NOT violating k, then lft becomes that position,
                    // otherwise lft will become j, and i will become j also
                    if( abs(lst_prime - x) <= k ) {
                        // lst_prime does NOT violate k with current prime
                        lft = lst_prime_pos;

                        // i will be 1 + the index of the rightmost prime
                        // the violates the constraint
                        while(  x - cur_min_prime > k ) {
                            if( is_prime[nums[i]] ) {
                                --cnt;
                                --mp[nums[i]];
                                if( mp[nums[i]] == 0 )
                                    mp.erase(nums[i]);
                                cur_min_prime = mp.begin()->first;
                            }
                            ++i;
                        }

                    } else {
                        // lst_prime does violate k with current prime
                        lft = j;
                        i = 1 + lst_prime_pos;
                        cnt = 0;
                        mp.clear();
                    }

                } else {
                    // lft becomes the last prime position
                    lft = lst_prime_pos;
                }

                ++cnt;
                ++mp[x];
                lst_prime = x;
                lst_prime_pos = j;
            }

            if( cnt >= 2 )
                ans = ans + (lft - i + 1);
        }

        return ans;
    }
};
