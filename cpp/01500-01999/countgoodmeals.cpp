
// 1711. Count Good Meals
// https://leetcode.com/problems/count-good-meals/submissions/




// see 923. 3Sum With Multiplicity
// https://leetcode.com/problems/3sum-with-multiplicity/
// resources:
//   calculate number of combinations MOD 10^9+7
//   https://barkingbogart.wordpress.com/2013/02/21/cnk-mod-1000000007/


class Solution {
private:
    int MOD = 1000000007;

    long long modPow(long long a, long long x) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % MOD;
            a = (a*a) % MOD;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,MOD-2);
    }

    long long modCombinations(long long n, long long k) {
        // regular combinations formula C(n,k) = n!/(k!(n-k)!)
        // return C(n,k) mod MOD
        long long numerator = 1; // n*(n-1)* ... * (n-k+1)
        int i;
        for(i=0;i<k;i++) numerator = (numerator*(n-i))%MOD;

        long long denominator = 1; // k!
        for(i=1;i<=k;i++) denominator = (denominator*i) %MOD;

        long long res = modInverse(denominator);
        res = (res*numerator)%MOD;
        return res;
    }

public:
    int countPairs(vector<int>& deliciousness) {
        if( deliciousness.size() == 1 )
            return 0;
        
        // 0 <= deliciousness[i] <= 2^20
        // 2^20 = 1048576, worst case 2* 1048576 = 2097152 = 2^21
        // 2^0 = 1, 2^1 = 2, ... 2^21

        // if delicionsness is a power of 2 by itself, then
        // we can make 𝑛!/(𝑟!*(𝑛−𝑟)!) combinations
        // n being the number of times we have it, and r = 2
        // +
        // special attention must be paid to 0s
        // number of zeros * number of delicionsness that is a power of 2 by itself
        
        // if we find another deliciousness[j] such as
        // e = deliciousness[i] + deliciousness[j], with e being a power of 2
        // then we can make x * y pairs, where x is the count of deliciousness[i]
        // and y is the count of deliciousness[j]
        
        unordered_map<int,long> um;
        for(int i : deliciousness )
            ++um[i];
    
        long ans = 0;
        
        set<int> p2;
        int x = 1;
        while( x < 2097153 ) {
            p2.insert(x);
            x *= 2;
        }
        
        auto t = um.find(0);
        long zeros = t != um.end() ? t->second : 0;
        long cnt;
        int d;
        unordered_set<long> seen;
        for(auto it = um.begin(); it != um.end(); ++it) {
            x   = it->first;
            cnt = it->second;
            
            if( x == 0 )
                continue;
            
            // is x a power of 2?
            if( p2.find(x) != p2.end() ) {
                // calculate number of combinations
                ans = (ans + modCombinations(cnt,2)) % MOD;
                // do we have zeros that x can be combined with?
                ans = (ans + ((zeros * cnt) % MOD)) % MOD;
            }
            
            auto f = p2.upper_bound(x);
            for(; f != p2.end(); ++f) {
                if( *f == 2*x )
                    continue;
                
                d = *f - x;
                
                // skip if we have seen this pair before
                long al = (unsigned long) x << 32;
                al += d;
                if( seen.find(al) != seen.end() )
                    continue;
                
                al = (unsigned long) d << 32;
                al += x;
                seen.insert(al);
                
                auto d_it = um.find(d);
                if( d_it != um.end() )
                    ans = (ans + ((d_it->second * cnt) % MOD)) % MOD;
            }
        }
        
        return ans;
    }
};



