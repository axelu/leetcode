

// 3574. Maximize Subarray GCD Score
// https://leetcode.com/problems/maximize-subarray-gcd-score/


map<int,map<int,int>> ums;

class Solution {
private:
    // prime factorization
    map<int,int> primeFactors(long long n) {
        // returns map of prime factors
        // key: prime, value: count
        map<int,int> um;
        // the number of 2s that divide n
        while(n % 2LL == 0LL) {
            // cout << 2 << " ";
            ++um[2];
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(long long i = 3; i <= sqrt(n); i = i + 2LL) {
            while(n % i == 0LL) {
                // cout << i << " ";
                ++um[i];
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2LL ) {
            // cout << n << " ";
            ++um[n];
        }

        return um;
    }

public:
    long long maxGCDScore(vector<int>& nums, int k) {
        int n = nums.size();

        // there are three possible answers right off the bet
        // A largest element in nums * 2
        // B 2 * k (as we could multiply each k elements by 2, so 2 would be a common divisor for those)
        // C n (GCD 1 * n)
        // we select the larger one, which becomes the number to beat

        // what we are really doing by multiplying by 2 is adding 2 as a prime factor
        // let us say we have 20 50 and k = 1
        // primefactors  20  50
        //        5       -   x
        //        5       x   x
        //        2       x   -
        //        2       x   x
        // our GCD would be 10 = 2 * 5, basically the product of all prime factors
        // that are in both numbers (watch out for them being there multiple times,
        // it means each occurence has to be there), but because we can multiply
        // by 2, we can stick another 2 in the missing 2 spot, we get GCD 20 for range [0,1]
        // 20 * 2 = 40, but 100 * 1 = 100, 100 is our best answer

        long long ans = max(n, 2 * k);


        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if( ums.find(x) == ums.end() ) {
                ums[x] = primeFactors(x);

                if( ums[x].find(2) == ums[x].end() )
                    ums[x].insert({2,0});

            }
            ans = max(ans, 2LL * x);
        }

        // cout << " initial best ans " << ans << endl;

        // we don't need to explore every possible subarray
        // adding an element to the subarray will either make the
        // gcd smaller or at best keep it the same, so we could track
        // based on remaining length if we can beat the best answer
        // and if not, we can exit early

        for(int i = 0; i < n-1; ++i) {
            map<int,int> base = ums[nums[i]];
            int low2 = 0;
            if( base.find(2) != base.end() )
                low2 = base[2];            
            int low2cnt = 1;

            // potential
            long long mn = nums[i];
            if( mn * 2LL * (long long)(n-i) <= ans )
                continue;

            for(int j = i+1; j < n; ++j) {
                // potential
                mn = min(mn, (long long)nums[j]);
                if( mn * 2LL * (long long)(n-i) <= ans )
                    continue;
                
                long long l = j-i+1;
                long long _gcd = 1LL;

                set<int> pfseen;

                // we need to create the intersection between base and ums[nums[j]]
                // and track lower numbers
                // special consideration to prime factor 2
                for(auto it = ums[nums[j]].begin(); it != ums[nums[j]].end(); ++it) {
                    int p = it->first;      // prime factor
                    int cnt = it->second;   // count

                    if( p == 2 ) {
                        if( cnt < low2 ) {
                            low2 = cnt;
                            low2cnt = 1;
                        } else if( cnt == low2 ) {
                            ++low2cnt;
                        }
                    }

                    pfseen.insert(p);
                    auto f = base.find(p);
                    if( f != base.end() ) {
                        f->second = min(f->second, cnt);

                        if( p != 2 || f->second > 0 ) {
                            _gcd = _gcd * (long long)pow(p, f->second);
                        }
                    }
                }

                // what we have not seen, we need to eliminate from base
                for(auto it = base.begin(); it != base.end(); ) {
                    if( pfseen.find(it->first) == pfseen.end() )
                        it = base.erase(it);
                    else
                        ++it;
                }

                if( k >= low2cnt )
                    _gcd *= 2LL;

                ans = max(ans, l * _gcd);

                // _gcd cannot become larger
                // could we still beat?
                if( _gcd * (long long)(n-i) <= ans )
                    break;
            }
        }

        return ans;
    }
};



